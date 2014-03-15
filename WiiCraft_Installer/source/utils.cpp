/*
utils.cpp - Various functions that don't fit anywhere else
*/
#include "utils.h"
#include "debug.h"

void *xfb[2] = {NULL, NULL};
GXRModeObj *rmode;
f32 yscale;
u32 xfbHeight;
u32	fb = 0;
GXColor background = {0, 0, 0, 0xff};
void *gp_fifo = NULL;

Mtx44 projection;
Mtx view, model, modelview;

float fps = 0.0f;
u32 pressed; // GC, Wii Remote, Nuchuck, or Classic Controller input
u32 expansion_type;
struct joystick_t *js;
WPADData *wmote_data;


void InitPad()
{
	WPAD_Init();
	PAD_Init();
	WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
	WPAD_SetVRes(WPAD_CHAN_ALL, rmode->fbWidth, rmode->xfbHeight);
	WPAD_Probe(0, &expansion_type);	
}

void UpdatePad()
{
	WPAD_ScanPads();
	WPAD_Probe(0, &expansion_type);	
	wmote_data = WPAD_Data(0);
	js = &wmote_data->exp.nunchuk.js;
	pressed = WPAD_ButtonsHeld(0);
}

u32 DetectInput(u8 DownOrHeld) 
{
	u32 pressed = 0;
	// Wii Remote (and Classic Controller) take precedence over GC to save time
	if (WPAD_ScanPads() > WPAD_ERR_NONE) // Scan the Wii remotes.  If there any problems, skip checking buttons
	{
		if (DownOrHeld == DI_BUTTONS_DOWN) {
			pressed = WPAD_ButtonsDown(0); //Store buttons down
		} else {
			pressed = WPAD_ButtonsHeld(0); //Store buttons held
		}
		
		// Convert to wiimote values
		if (pressed & WPAD_CLASSIC_BUTTON_ZR) pressed |= WPAD_BUTTON_PLUS;
		if (pressed & WPAD_CLASSIC_BUTTON_ZL) pressed |= WPAD_BUTTON_MINUS;

		if (pressed & WPAD_CLASSIC_BUTTON_PLUS) pressed |= WPAD_BUTTON_PLUS;
		if (pressed & WPAD_CLASSIC_BUTTON_MINUS) pressed |= WPAD_BUTTON_MINUS;

		if (pressed & WPAD_CLASSIC_BUTTON_A) pressed |= WPAD_BUTTON_A;
		if (pressed & WPAD_CLASSIC_BUTTON_B) pressed |= WPAD_BUTTON_B;
		if (pressed & WPAD_CLASSIC_BUTTON_X) pressed |= WPAD_BUTTON_2;
		if (pressed & WPAD_CLASSIC_BUTTON_Y) pressed |= WPAD_BUTTON_1;
		if (pressed & WPAD_CLASSIC_BUTTON_HOME) pressed |= WPAD_BUTTON_HOME;
		
		if (pressed & WPAD_CLASSIC_BUTTON_UP) pressed |= WPAD_BUTTON_UP;
		if (pressed & WPAD_CLASSIC_BUTTON_DOWN) pressed |= WPAD_BUTTON_DOWN;
		if (pressed & WPAD_CLASSIC_BUTTON_LEFT) pressed |= WPAD_BUTTON_LEFT;
		if (pressed & WPAD_CLASSIC_BUTTON_RIGHT) pressed |= WPAD_BUTTON_RIGHT;

	}

	// Return Classic Controller and Wii Remote values
	if (pressed) {
		VIDEO_WaitVSync();
		return pressed;
	}
	// No buttons on the Wii remote or Classic Controller were pressed
	if (PAD_ScanPads() > PAD_ERR_NONE)
	{
		if (DownOrHeld == DI_BUTTONS_HELD) {
			pressed = PAD_ButtonsDown(0); //Store buttons down
		} else {
			pressed = PAD_ButtonsHeld(0); //Store buttons held
		}
		
		if (pressed) {
			// Button on GC controller was pressed
			if (pressed & PAD_TRIGGER_R) pressed |= WPAD_BUTTON_PLUS;
			if (pressed & PAD_TRIGGER_L) pressed |= WPAD_BUTTON_MINUS;
			if (pressed & PAD_BUTTON_A) pressed |= WPAD_BUTTON_A;
			if (pressed & PAD_BUTTON_B) pressed |= WPAD_BUTTON_B;
			if (pressed & PAD_BUTTON_X) pressed |= WPAD_BUTTON_1;
			if (pressed & PAD_BUTTON_Y) pressed |= WPAD_BUTTON_2;
			if (pressed & PAD_BUTTON_MENU) pressed |= WPAD_BUTTON_HOME;
			if (pressed & PAD_BUTTON_UP) pressed |= WPAD_BUTTON_UP;
			if (pressed & PAD_BUTTON_LEFT) pressed |= WPAD_BUTTON_LEFT;
			if (pressed & PAD_BUTTON_DOWN) pressed |= WPAD_BUTTON_DOWN;
			if (pressed & PAD_BUTTON_RIGHT) pressed |= WPAD_BUTTON_RIGHT;
		}
	}
	VIDEO_WaitVSync();
	return pressed;
}

void EndVideo()
{
	free(MEM_K1_TO_K0(xfb[0])); xfb[0] = NULL;
	#ifdef USBGECKO
	Debug("Video:		xfb[0] Removed From Memory");
	#endif
	free(MEM_K1_TO_K0(xfb[1])); xfb[1] = NULL;
	#ifdef USBGECKO
	Debug("Video:		xfb[1] Removed From Memory");
	#endif
	free(gp_fifo); gp_fifo = NULL;
	#ifdef USBGECKO
	Debug("Video:		gp_fifo Removed From Memory");
	#endif
}

void InitVideo()
{
	VIDEO_Init();

	rmode = VIDEO_GetPreferredMode(NULL);
	Debug("Video:		rmode Loaded into memory");
	
	xfb[0] = (u32 *)MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
	Debug("Video:		xfb[0] Loaded into memory");
	xfb[1] = (u32 *)MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
	Debug("Video:		xfb[1] Loaded into memory");
	
	VIDEO_Configure (rmode);
	Debug("Video:		Configured rmode\n");
	VIDEO_SetNextFramebuffer(xfb[fb]);
	Debug("Video:		Changed Framebuffer to xfb[fb]");
	VIDEO_SetBlack(FALSE);
	Debug("Video:		Set video BlackMode to false");
	VIDEO_Flush();
	Debug("Video:		Flushed Video");
	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();
	fb ^= 1;

	gp_fifo = (u8 *) memalign(32, DEFAULT_FIFO_SIZE);
	memset(gp_fifo, 0, DEFAULT_FIFO_SIZE);
	GX_Init (gp_fifo, DEFAULT_FIFO_SIZE);
	GX_SetCopyClear(background, 0x00ffffff);

	// other gx setup
	GX_SetViewport(0,0,rmode->fbWidth,rmode->efbHeight,0,1);
	yscale = GX_GetYScaleFactor(rmode->efbHeight,rmode->xfbHeight);
	xfbHeight = GX_SetDispCopyYScale(yscale);
	GX_SetScissor(0,0,rmode->fbWidth,rmode->efbHeight);
	GX_SetDispCopySrc(0,0,rmode->fbWidth,rmode->efbHeight);
	GX_SetDispCopyDst(rmode->fbWidth,xfbHeight);
	GX_SetCopyFilter(rmode->aa,rmode->sample_pattern,GX_TRUE,rmode->vfilter);
	GX_SetFieldMode(rmode->field_rendering,((rmode->viHeight==2*rmode->xfbHeight)?GX_ENABLE:GX_DISABLE));

	if (rmode->aa)
		GX_SetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
	else
		GX_SetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);

	GX_SetDispCopyGamma(GX_GM_1_0);


	// setup the vertex descriptor
	// tells the flipper to expect direct data
	GX_InvVtxCache();
	GX_ClearVtxDesc();
	GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_CLR0, GX_NONE);
	GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	//GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	
	GX_SetNumChans(1);
	GX_SetNumTexGens(1); //Only GX_TEXMAP0
	
	GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
	GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
	GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_TEX0, GX_IDENTITY);
	
	
	GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
	GX_SetAlphaUpdate(GX_TRUE);	
	GX_SetCullMode(GX_CULL_NONE);	
	

	guPerspective(projection, 45, rmode->viWidth / rmode->viHeight, 0.1F, 300.0F);
	GX_LoadProjectionMtx(projection, GX_PERSPECTIVE);
	
	
	GX_SetLineWidth(25, GX_TO_ZERO);
	
	guMtxIdentity(model);
	
	GX_InvalidateTexAll();
	
	//console
	console_init(xfb[0],20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);

}


void SwapBuffer()
{
	GX_DrawDone();
	
	GX_SetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
	GX_SetColorUpdate(GX_TRUE);
	GX_CopyDisp(xfb[fb],GX_TRUE);

	VIDEO_SetNextFramebuffer(xfb[fb]);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	
	fb ^= 1;		// flip framebuffer
}

void DrawCubeTex(float x, float y, float z)  //THIS IS A PROVISIONAL SHITTY FUNCTION, JUST TESTING
{
	#define BLOCK_SIZE 1
	GX_Begin(GX_QUADS, GX_VTXFMT0, 24);
		GX_Position3f32(x, y + BLOCK_SIZE, z);
			GX_TexCoord2f32(0.0f, 0.0f);
		GX_Position3f32(x + BLOCK_SIZE, y + BLOCK_SIZE, z);
			GX_TexCoord2f32(0.0f, 1.0f);
		GX_Position3f32(x + BLOCK_SIZE, y + BLOCK_SIZE, z + BLOCK_SIZE);
			GX_TexCoord2f32(1.0f, 1.0f);
		GX_Position3f32(x, y + BLOCK_SIZE, z + BLOCK_SIZE);
			GX_TexCoord2f32(1.0f, 0.0f);

		GX_Position3f32(x, y, z);
			GX_TexCoord2f32(0.0f, 0.0f);
		GX_Position3f32(x + BLOCK_SIZE, y, z);
			GX_TexCoord2f32(0.0f, 1.0f);
		GX_Position3f32(x + BLOCK_SIZE, y, z + BLOCK_SIZE);
			GX_TexCoord2f32(1.0f, 1.0f);
		GX_Position3f32(x, y, z + BLOCK_SIZE);		
			GX_TexCoord2f32(1.0f, 0.0f);
	//Right
		GX_Position3f32(x + BLOCK_SIZE, y, z);
			GX_TexCoord2f32(1.0f, 1.0f);
		GX_Position3f32(x + BLOCK_SIZE, y, z + BLOCK_SIZE);
			GX_TexCoord2f32(0.0f, 1.0f);
		GX_Position3f32(x + BLOCK_SIZE, y + BLOCK_SIZE, z + BLOCK_SIZE);		
			GX_TexCoord2f32(0.0f, 0.0f);		
		GX_Position3f32(x + BLOCK_SIZE, y + BLOCK_SIZE, z);	
			GX_TexCoord2f32(1.0f, 0.0f);
	//Left
		GX_Position3f32(x, y, z);
			GX_TexCoord2f32(1.0f, 1.0f);
		GX_Position3f32(x, y, z + BLOCK_SIZE);
			GX_TexCoord2f32(0.0f, 1.0f);
		GX_Position3f32(x, y + BLOCK_SIZE, z + BLOCK_SIZE);		
			GX_TexCoord2f32(0.0f, 0.0f);	
		GX_Position3f32(x, y + BLOCK_SIZE, z);
			GX_TexCoord2f32(1.0f, 0.0f);			
	//Front
		GX_Position3f32(x, y, z + BLOCK_SIZE);
			GX_TexCoord2f32(0.0f, 1.0f);
		GX_Position3f32(x + BLOCK_SIZE, y, z + BLOCK_SIZE);
			GX_TexCoord2f32(1.0f, 1.0f);
		GX_Position3f32(x + BLOCK_SIZE, y + BLOCK_SIZE, z + BLOCK_SIZE);
			GX_TexCoord2f32(1.0f, 0.0f);
		GX_Position3f32(x, y + BLOCK_SIZE, z + BLOCK_SIZE);
			GX_TexCoord2f32(0.0f, 0.0f);
	//Back
		GX_Position3f32(x, y, z);
			GX_TexCoord2f32(0.0f, 1.0f);
		GX_Position3f32(x + BLOCK_SIZE, y, z);
			GX_TexCoord2f32(1.0f, 1.0f);
		GX_Position3f32(x + BLOCK_SIZE, y + BLOCK_SIZE, z);
			GX_TexCoord2f32(1.0f, 0.0f);
		GX_Position3f32(x, y + BLOCK_SIZE, z);
			GX_TexCoord2f32(0.0f, 0.0f);
	GX_End();
}


void DrawCube(float x, float y, float z)  //THIS IS A PROVISIONAL SHITTY FUNCTION, JUST TESTING
{	
	
	GX_Begin(GX_QUADS, GX_VTXFMT0, 24);			// Draw a Cube

	GX_Position3f32( x + 1.0f, y+1.0f,-1.0f + z);	// Top Left of the quad (top)
		GX_Color4u8(0, 255, 0, 255);			// Set The Color To Green
	GX_Position3f32(x + -1.0f, y+1.0f,-1.0f + z);	// Top Right of the quad (top)
		GX_Color4u8(0, 255, 0, 255);			// Set The Color To Green
	GX_Position3f32(x + -1.0f, y+1.0f, 1.0f + z);	// Bottom Right of the quad (top)
		GX_Color4u8(0, 255, 0, 255);			// Set The Color To Green
	GX_Position3f32(x +  1.0f, y+1.0f, 1.0f + z);		// Bottom Left of the quad (top)
		GX_Color4u8(0, 255, 0, 255);			// Set The Color To Green
		

	GX_Position3f32(x +  1.0f,y+-1.0f, 1.0f + z);	// Top Left of the quad (bottom)
		GX_Color4u8(255, 128, 0, 255);			// Set The Color To Orange
	GX_Position3f32(x + -1.0f,y+-1.0f, 1.0f + z);	// Top Right of the quad (bottom)
		GX_Color4u8(255, 128, 0, 255);			// Set The Color To Orange
	GX_Position3f32(x + -1.0f,y+-1.0f,-1.0f + z);	// Bottom Right of the quad (bottom)
		GX_Color4u8(255, 128, 0, 255);			// Set The Color To Orange
	GX_Position3f32(x +  1.0f,y+-1.0f,-1.0f + z);	// Bottom Left of the quad (bottom)
		GX_Color4u8(255, 128, 0, 255);			// Set The Color To Orange

	GX_Position3f32( x + 1.0f, y+1.0f, 1.0f + z);		// Top Right Of The Quad (Front)
		GX_Color4u8(255, 0, 0, 255);			// Set The Color To Red
	GX_Position3f32(x + -1.0f, y+1.0f, 1.0f + z);	// Top Left Of The Quad (Front)
		GX_Color4u8(255, 0, 0, 255);			// Set The Color To Red
	GX_Position3f32(x + -1.0f,y+-1.0f, 1.0f + z);	// Bottom Left Of The Quad (Front)
		GX_Color4u8(255, 0, 0, 255);			// Set The Color To Red
	GX_Position3f32(x +  1.0f,y+-1.0f, 1.0f + z);	// Bottom Right Of The Quad (Front)
		GX_Color4u8(255, 0, 0, 255);			// Set The Color To Red

	GX_Position3f32(x + 1.0f,y+-1.0f,-1.0 + z);	// Bottom Left Of The Quad (Back)
		GX_Color4u8(255, 255, 0, 255);			// Set The Color To Yellow
	GX_Position3f32(x +-1.0f,y+-1.0f,-1.0f + z);	// Bottom Right Of The Quad (Back)
		GX_Color4u8(255, 255, 0, 255);			// Set The Color To Yellow
	GX_Position3f32(x +-1.0f, y+1.0f,-1.0f + z);	// Top Right Of The Quad (Back)
		GX_Color4u8(255, 255, 0, 255);			// Set The Color To Yellow
	GX_Position3f32(x + 1.0f,y+ 1.0f,-1.0f + z);	// Top Left Of The Quad (Back)
		GX_Color4u8(255, 255, 0, 255);			// Set The Color To Yellow

	GX_Position3f32(x + -1.0f, y+1.0f, 1.0f + z);	// Top Right Of The Quad (Left)
		GX_Color4u8(0, 0, 255, 255);			// Set The Color To Blue
	GX_Position3f32(x + -1.0f,y+ 1.0f,-1.0f + z);	// Top Left Of The Quad (Left)
		GX_Color4u8(0, 0, 255, 255);			// Set The Color To Blue
	GX_Position3f32(x + -1.0f,y+-1.0f,-1.0f + z);	// Bottom Left Of The Quad (Left)
		GX_Color4u8(0, 0, 255, 255);			// Set The Color To Blue
	GX_Position3f32(x + -1.0f,y+-1.0f, 1.0f + z);	// Bottom Right Of The Quad (Left)
		GX_Color4u8(0, 0, 255, 255);			// Set The Color To Blue

	GX_Position3f32(x +  1.0f, y+1.0f,-1.0f + z);	// Top Right Of The Quad (Right)
		GX_Color4u8(255, 0, 255, 255);			// Set The Color To Violet
	GX_Position3f32(x +  1.0f,y+ 1.0f, 1.0f + z);		// Top Left Of The Quad (Right)
		GX_Color4u8(255, 0, 255, 255);			// Set The Color To Violet
	GX_Position3f32(x +  1.0f,y+-1.0f, 1.0f + z);	// Bottom Left Of The Quad (Right)
		GX_Color4u8(255, 0, 255, 255);			// Set The Color To Violet
	GX_Position3f32(x +  1.0f,y+-1.0f,-1.0f + z);	// Bottom Right Of The Quad (Right)		
		GX_Color4u8(255, 0, 255, 255);			// Set The Color To Violet

	GX_End();									// Done Drawing The Quad
}



//FPS
	unsigned long lastTime, currentTime, diffTime;
	unsigned int frame_count;

	void initFPS()
	{
		currentTime = getTime();
		lastTime = currentTime;
		frame_count = 0;
	}

	void FPS(float *fps_var)
	{
		frame_count++;
		currentTime = getTime();
		diffTime = currentTime - lastTime;
		if(diffTime >= 1000)
		{
			*fps_var = (float)frame_count/(diffTime/1000.0f);
			frame_count = 0;
			lastTime = getTime();
		}
}
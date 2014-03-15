 #include <gccore.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ogc/machine/processor.h>
#include <wiiuse/wpad.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "video.h"
#include "background_image.h"
#include "filelist.h"
#include "devicemounter.h"

#define EXECUTE_ADDR	((u8 *) 0x92000000)
#define BOOTER_ADDR		((u8 *) 0x93000000)
#define ARGS_ADDR		((u8 *) 0x93200000)

typedef void (*entrypoint) (void);
extern void __exception_setreload(int t);
extern void __exception_closeall();
extern const u8 app_booter_bin[];
extern const u32 app_booter_bin_size;

static FILE *open_file(const char *dev, char *filepath)
{
	sprintf(filepath, "%s:/apps/WiiCraft/wiicraft.dol", dev);
	FILE *exeFile = fopen(filepath ,"rb");
	if (exeFile == NULL)
	{
		sprintf(filepath, "%s:/wiicraft/wiicraft.dol", dev);
		exeFile = fopen(filepath ,"rb");
	}
	if (exeFile == NULL)
	{
		sprintf(filepath, "%s:/apps/wiicraft/wiicraft.elf", dev);
		exeFile = fopen(filepath ,"rb");
	}
	if (exeFile == NULL)
	{
		sprintf(filepath, "%s:/wiicraft/wiicraft.elf", dev);
		exeFile = fopen(filepath ,"rb");
	}

	return exeFile;
}

void SystemMenu()
{
	*(vu32*)0x8132FFFB = 0x50756e65;
	DCFlushRange((void *)(0x8132FFFB), 4);
	ICInvalidateRange((void *)(0x8132FFFB), 4);
	SYS_ResetSystem(SYS_RETURNTOMENU, 0, 0);
}

    //--------------------------------------------------
	//Wiilight
	//--------------------------------------------------
	lwp_t light_thread = 0;
	void *light_loop (void *arg);
	//vu32 *light_reg = (u32*) HW_GPIO;
	bool light_on = false;
	u8 light_level = 0;
	struct timespec light_timeon = { 0 };
	struct timespec light_timeoff = { 0 };
	void WIILIGHT_TurnOn(){
		*(u32*)0xCD0000C0 |= 0x20;
	}

	void WIILIGHT_TurnOff(){
		*(u32*)0xCD0000C0 &= ~0x20;
	}

	void WIILIGHT_SetLevel(int level){
		light_level = MIN(MAX(level, 0), 100);
		// Calculate the new on/off times for this light intensity
		u32 level_on;
		u32 level_off;
		level_on = (light_level * 2.55) * 40000;
		level_off = 10200000 - level_on;
		light_timeon.tv_nsec = level_on;
		light_timeoff.tv_nsec = level_off;
	}
	//--------------------------------------------------
	//Wiilight
	//--------------------------------------------------
	
	
int main(int argc, char *argv[]){
	WIILIGHT_SetLevel(255);
	WIILIGHT_TurnOn();
	
	u32 cookie;
	FILE *exeFile = NULL;
	void *exeBuffer = (void *)EXECUTE_ADDR;
	u32 exeSize = 0;
	entrypoint exeEntryPoint;
	__exception_setreload(0);

	/* int videomod */
	InitVideo();
	/* get imagedata */
	u8 *imgdata = GetImageData();
	fadein(imgdata); //Fade in Image, All Menus NEED to be before this!!!

	char filepath[200];

	//init wiimote
	WPAD_Init();

	// try SD Card First
	SDCard_Init();
	exeFile = open_file(DeviceName[SD], filepath);
	// if app not found on SD Card try USB
	if (exeFile == NULL)
	{
		USBDevice_Init();
		int dev;
		for(dev = USB1; dev < MAXDEVICES; ++dev)
		{
			if(!exeFile)
				exeFile = open_file(DeviceName[dev], filepath);
		}
	}

	// if nothing found exiting
	if (exeFile == NULL)
	{
		fadeout(imgdata);
		fclose(exeFile);
		SDCard_deInit();
		USBDevice_deInit();
		StopGX();
		free(imgdata);
		SystemMenu();
	}

	fseek(exeFile, 0, SEEK_END);
	exeSize = ftell(exeFile);
	rewind(exeFile);

	if(fread(exeBuffer, 1, exeSize, exeFile) != exeSize)
	{
		fadeout(imgdata);
		fclose(exeFile);
		SDCard_deInit();
		USBDevice_deInit();
		StopGX();
		free(imgdata);
		SystemMenu();
	}
	fclose(exeFile);

	memcpy(BOOTER_ADDR, app_booter_bin, app_booter_bin_size);
	DCFlushRange(BOOTER_ADDR, app_booter_bin_size);

	fadeout(imgdata);
	SDCard_deInit();
	USBDevice_deInit();
	StopGX();
	free(imgdata);

	exeEntryPoint = (entrypoint)BOOTER_ADDR;
	
	WIILIGHT_TurnOff();
	
	//bool menuBool = true;
	
	/*printf("\x1b[2;0H");
	
	printf("Welcome To WiiCraft Launcher!\n");
	printf("Controlls:\n");
	printf(" [*] A: 		Check for Uppdate And Launch WiiCraft\n");
	printf(" [*] Minus: 	Launch WiiCraft Without Checking For Uppdate\n");
	printf(" [*] Home:		Exit\n");
	printf("\n");
	
	while(menuBool){
	
		WPAD_ScanPads();
		
		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_A){
			//wc_updating = true;
			//menuBool = false;
			SYS_ResetSystem(SYS_SHUTDOWN, 0, 0);
			_CPU_ISR_Disable(cookie);
			__exception_closeall();
			exeEntryPoint();
			_CPU_ISR_Restore(cookie);
		}
		else if (WPAD_ButtonsDown(0) & WPAD_BUTTON_MINUS){
			//wc_updating = false;
			//menuBool = false;
			SYS_ResetSystem(SYS_SHUTDOWN, 0, 0);
			_CPU_ISR_Disable(cookie);
			__exception_closeall();
			exeEntryPoint();
			_CPU_ISR_Restore(cookie);
		}
		else if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME){
			printf("Exiting...\n");
			
			fadeout(imgdata);
			fclose(exeFile);
			SDCard_deInit();
			USBDevice_deInit();
			StopGX();
			free(imgdata);
			SystemMenu();
		}
		VIDEO_WaitVSync();
	}*/
	
	/* cleaning up and load dol */
	WPAD_Shutdown();
	
	SYS_ResetSystem(SYS_SHUTDOWN, 0, 0);
	_CPU_ISR_Disable(cookie);
	__exception_closeall();
	exeEntryPoint();
	_CPU_ISR_Restore(cookie);
	return 0;
}

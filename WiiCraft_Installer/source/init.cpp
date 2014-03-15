#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fat.h>
#include <asndlib.h>
#include <mp3player.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include "utils.h"
#include "debug.h"

void Initialize(void){
	fatInitDefault();	
	DebugStart(true, "sd://WiiCraft.log");
	Debug("\n");
	Debug("\n");
	Debug("\n");
	Debug("-------------------[WiiCraft Debug Log]----------------------");
	InitVideo();
	Debug("InitVideo() Done");
	InitPad();
	Debug("InitPad() Done");
	initFPS();
	Debug("InitFPS() Done");
//	ASND_Init();
//	Debug("ASND_Init() Done");
//	MP3Player_Init();
//	Debug("MP3Player_Init Done");

}

void Deinitialize(void){
	WPAD_Shutdown();
	Debug("WPAD_Shutdown Passed");
	
	EndVideo();
	Debug("EndVideo Passed");
	
//	ASND_End();
//	Debug("ASND_End Passed");

//	MP3Player_Stop();
//	Debug("MP3Player_Stop Passed");

	DebugStop();
	gprintf("DebugStop passed\n");
	}
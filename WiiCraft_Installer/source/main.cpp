// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013      filfat, xerpi, JoostinOnline

#include <iostream>
#include <gccore.h>
#include <grrlib.h>
#include <wiiuse/wpad.h>
#include <wiikeyboard/keyboard.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fat.h>
#include <sdcard/wiisd_io.h>
#include <png.h>
#include <pngu.h>
//#include <GEMS_WifiWii.h>
#include <network.h>

//Classes:
#include "debug.h"
#include "init.h"
#include "main.h"
#include "utils.h"
#include "common.h"
#include "update.h"

#include "FreeTypeGX.h"
#include "Metaphrasis.h"

//Font:
#include <ft2build.h>
#include FT_FREETYPE_H
//Color:
extern "C" {
                extern void __exception_setreload(int t);
}

int fatDevice = FAT_DEVICE_NONE;

s32 ret;

        char localip[16] = {0};
        char gateway[16] = {0};
        char netmask[16] = {0};
        int clientForServer = 0;

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

                //----------------------------------------------------------
                //Function's:
                //----------------------------------------------------------

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

inline void clear(){
        printf("\x1b[2J");   // Clear
        printf("\x1b[2;0H"); // Reset cursor position
}

int main(int argc, char **argv)
{       
                // In the event of a code dump, the app will exit after 10 seconds (unless you press POWER)
                __exception_setreload(10);
                initialise_reset_button();
                Initialize();
                fatMountSimple("sd", &__io_wiisd);
                Debug("fatMountSimple() Done");
                
                //Disk light turn on and init
                //WIILIGHT_Init();
                WIILIGHT_SetLevel(255);
                WIILIGHT_TurnOn();
				   
                //char test;
                //sscanf(argv[0], "%c", &test); //read first character from argv[0] into test
                /*if(test == 115){*/ fatDevice = FAT_DEVICE_SD; //} //first character = s (SD)
                //else if(test == 117){ fatDevice = FAT_DEVICE_USB; } //first character = u (USB)
                
                //Debug("The User Has a %s", fatDevice); for some reason it does not work.
               
                Debug("Image() Done");
                
                //ADD OTHER INIT'S HERE
                
                Debug("All Inits is Done");
				
                //Menu
                s8 selected = 1; // Make sure that "selected" is defined as 1-6
                WIILIGHT_TurnOff();
				
                goto mainMenu;
        mainMenu:selected = 1;
        while(true) {
                //VIDEO_ClearFrameBuffer(rmode,xfb[fb],COLOR_BLACK);
                printf("\x1b[2;0H"); // This resets the position of the console
                CHANGE_COLOR(GREEN);
                printf("WiiCraft Installer\n");
                CHANGE_COLOR(WHITE);
                MENU("Install                 ", 1); // MENU(description, option number)
                MENU("Exit                    ", 2);
                do {pressed = DetectInput(DI_BUTTONS_DOWN);} while(!pressed);
                if (pressed & WPAD_BUTTON_DOWN) {
                        selected++;
                        if (selected>2) selected = 1;
                        continue;
                }
                if (pressed & WPAD_BUTTON_UP) {
                        selected--;
                        if (selected<1) selected = 2;
                        continue;
                }
                if (pressed & WPAD_BUTTON_A) {
                        if(selected == 1){
                                Update();
								goto EXIT;
                        }
                        if(selected == 2){
								selected = 2;
                                goto EXIT;
                        }
                }
                if(pressed & WPAD_BUTTON_B){
                        //DO NOTHING
                }
        }
                
                EXIT:printf("\x1b[2;0H");
                VIDEO_ClearFrameBuffer(rmode,xfb[fb],COLOR_BLACK);
                SwapBuffer();
                Deinitialize();
                exit(0);
                
                Debug("ERROR: PASSED LAST LINE OF CODE!");
                exit(-1);
}
#ifndef _WIN32_H_
#define _WIN32_H_

#ifdef __cplusplus
extern "C" {
#endif

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <commdlg.h>
#include <stdlib.h>
#include <stdio.h>
#include <strstrea.h>
#include <fstream.h>
#include <time.h>
#include <assert.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <win32/glext.h>

#ifndef __cplusplus
#include "math.h"
#define cosf (float)cos
#define sinf (float)sin
#define tanf (float)tan
#define sqrtf (float)sqrt
#define fabsf (float)fabs
#define acosf (float)acos
#define inline __inline
#endif

#pragma warning (disable:4244) // (type conversion) Possible loss of data
#pragma warning (disable:4761) // 
#pragma warning (disable:4018) // sign mismatch
#pragma warning (disable:4068) // unknown pragma

void WinInit();
void WinSwapBuffers();
void WinDestroy();

//PPC opcode that needs to be a function on win32
unsigned __int32 __cntlzw(unsigned __int32 d); //u32 NumLeadingZeros(u32 d) from DOLPHIN\build\libraries\gx\src\GXTexture.c(257)


typedef struct WinKey_Str {
	int button; 
	int stickX; // -127 <= stickX    <= 127
	int stickY; // -127 <= stickY    <= 127
	int substickX; // -127 <= stickX    <= 127
	int substickY; // -127 <= stickY    <= 127
	int triggerLeft; // 0 - 255
	int triggerRight; // 0 - 255
	unsigned int down[64];
	int downCnt;
	unsigned int up[64];
	int upCnt;
} WinKey;
extern WinKey winKey;

// change the byte order
void EndianSwap32(void* buffer);
void EndianSwap16(void* buffer);
unsigned __int32 EndianSwapReturn32(void* buffer);
unsigned __int16 EndianSwapReturn16(void* buffer);

#ifndef NO_MULTI_TEX
	// OpenGL Extension Function Prototypes
	extern PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
	extern PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
	extern PFNGLMULTITEXCOORD4FARBPROC glMultiTexCoord4fARB;
#endif
extern int multiTexOn;

// Output Window Handle
extern HANDLE outputWinHandle;
extern HANDLE inputWinHandle;
extern FILE * outfile;

// Paths
extern char initialPath[];
extern char installPath[];

extern unsigned int retraceCount;

#define APP_STRING "PC Dolphin Emulator 2.8"
#define KEY_STRING "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\pcemu.Exe"

#define WINKEY_PAD_BUTTON_LEFT			PAD_BUTTON_LEFT
#define WINKEY_PAD_BUTTON_RIGHT			PAD_BUTTON_RIGHT
#define WINKEY_PAD_BUTTON_DOWN			PAD_BUTTON_DOWN
#define WINKEY_PAD_BUTTON_UP			PAD_BUTTON_UP
#define WINKEY_PAD_TRIGGER_Z			PAD_TRIGGER_Z
#define WINKEY_PAD_TRIGGER_R			PAD_TRIGGER_R
#define WINKEY_PAD_TRIGGER_L			PAD_TRIGGER_L
#define WINKEY_PAD_BUTTON_A				PAD_BUTTON_A
#define WINKEY_PAD_BUTTON_B				PAD_BUTTON_B
#define WINKEY_PAD_BUTTON_X				PAD_BUTTON_X
#define WINKEY_PAD_BUTTON_Y				PAD_BUTTON_Y
#define WINKEY_PAD_BUTTON_MENU			PAD_BUTTON_MENU
#define WINKEY_PAD_ORIGIN				PAD_ORIGIN


/* Types of Pads */
#define PCPAD_TYPE_UNKNOWN		0
#define PCPAD_TYPE_GAMEPAD		1
#define PCPAD_TYPE_GAMEPADPRO	2
#define PCPAD_TYPE_FREESTYLEPRO	3
#define PCPAD_TYPE_3DPRO		4
#define PCPAD_TYPE_ISHOCK		5
#define PCPAD_TYPE_GRAVISPADPRO 6

/* Joystate fields for each Gamepad button */
#define	PCPAD_GAMEPAD_BUTTON_A			0
#define PCPAD_GAMEPAD_BUTTON_B			1
#define PCPAD_GAMEPAD_BUTTON_C			2
#define PCPAD_GAMEPAD_BUTTON_X			3
#define PCPAD_GAMEPAD_BUTTON_Y			4
#define PCPAD_GAMEPAD_BUTTON_Z			5
#define PCPAD_GAMEPAD_BUTTON_L			6
#define PCPAD_GAMEPAD_BUTTON_R			7
#define PCPAD_GAMEPAD_BUTTON_START		8
#define PCPAD_GAMEPAD_BUTTON_SELECT		9

/* Joystate fields for each Gamepadpro button */
#define PCPAD_GAMEPADPRO_BUTTON_A			0
#define PCPAD_GAMEPADPRO_BUTTON_B			1
#define PCPAD_GAMEPADPRO_BUTTON_C			2
#define PCPAD_GAMEPADPRO_BUTTON_X			3
#define PCPAD_GAMEPADPRO_BUTTON_Y			4
#define PCPAD_GAMEPADPRO_BUTTON_Z			5
#define PCPAD_GAMEPADPRO_BUTTON_L			6
#define PCPAD_GAMEPADPRO_BUTTON_R			7
#define PCPAD_GAMEPADPRO_BUTTON_START		8

/* Joystate fields for each FreestylePro button */
#define	PCPAD_FREESTYLEPRO_BUTTON_A			0
#define PCPAD_FREESTYLEPRO_BUTTON_B			1
#define PCPAD_FREESTYLEPRO_BUTTON_C			2
#define PCPAD_FREESTYLEPRO_BUTTON_X			3
#define PCPAD_FREESTYLEPRO_BUTTON_Y			4
#define PCPAD_FREESTYLEPRO_BUTTON_Z			5
#define PCPAD_FREESTYLEPRO_BUTTON_L			6
#define PCPAD_FREESTYLEPRO_BUTTON_R			7
#define PCPAD_FREESTYLEPRO_BUTTON_START		8
#define PCPAD_FREESTYLEPRO_BUTTON_SELECT	9

#define PCPAD_FREESTYLEPRO_UP			0
#define PCPAD_FREESTYLEPRO_UPRIGHT		4500
#define PCPAD_FREESTYLEPRO_RIGHT		9000
#define PCPAD_FREESTYLEPRO_DOWNRIGHT	13500
#define PCPAD_FREESTYLEPRO_DOWN			18000
#define PCPAD_FREESTYLEPRO_DOWNLEFT		22500
#define PCPAD_FREESTYLEPRO_LEFT			27000
#define PCPAD_FREESTYLEPRO_UPLEFT		31500

/* Joystate fields for each 3DPro button */
#define	PCPAD_3DPRO_TRIGGER				0
#define PCPAD_3DPRO_BUTTON_THUMB		1
#define PCPAD_3DPRO_BUTTON_STICKTOP		2
#define PCPAD_3DPRO_BUTTON_STICKBOTTOM	3
#define PCPAD_3DPRO_BUTTON_BASEUL		4
#define PCPAD_3DPRO_BUTTON_BASEUR		5
#define PCPAD_3DPRO_BUTTON_BASELR		6
#define PCPAD_3DPRO_BUTTON_BASELL		7
#define PCPAD_3DPRO_UP			0
#define PCPAD_3DPRO_UPRIGHT		4500
#define PCPAD_3DPRO_RIGHT		9000
#define PCPAD_3DPRO_DOWNRIGHT	13500
#define PCPAD_3DPRO_DOWN		18000
#define PCPAD_3DPRO_DOWNLEFT	22500
#define PCPAD_3DPRO_LEFT		27000
#define PCPAD_3DPRO_UPLEFT		31500

/* Joystate fields for each iShock button */
#define PCPAD_ISHOCK_BUTTON_DPAD_UP			0
#define PCPAD_ISHOCK_BUTTON_DPAD_DOWN		1
#define PCPAD_ISHOCK_BUTTON_DPAD_LEFT		2
#define PCPAD_ISHOCK_BUTTON_DPAD_RIGHT		3
#define PCPAD_ISHOCK_BUTTON_TRIANGLE		4
#define PCPAD_ISHOCK_BUTTON_CIRCLE			5
#define PCPAD_ISHOCK_BUTTON_X				6
#define PCPAD_ISHOCK_BUTTON_SQUARE			7
#define PCPAD_ISHOCK_BUTTON_C				8
#define PCPAD_ISHOCK_BUTTON_B				9
#define PCPAD_ISHOCK_BUTTON_A				10
#define PCPAD_ISHOCK_BUTTON_F				11
#define PCPAD_ISHOCK_BUTTON_R1				12
#define PCPAD_ISHOCK_BUTTON_R2				13
#define PCPAD_ISHOCK_BUTTON_L1				14
#define PCPAD_ISHOCK_BUTTON_L2				15
#define PCPAD_ISHOCK_BUTTON_JOY_L			16
#define PCPAD_ISHOCK_BUTTON_JOY_R			17
#define PCPAD_ISHOCK_BUTTON_D				18
#define PCPAD_ISHOCK_BUTTON_E				19
#define PCPAD_ISHOCK_BUTTON_SELECT			9
#define PCPAD_ISHOCK_BUTTON_START			10

/* Joystate fields for each Gravis GamePad Pro button */
#define	PCPAD_GRAVISPADPRO_BUTTON_RED		0
#define PCPAD_GRAVISPADPRO_BUTTON_YELLOW	1
#define PCPAD_GRAVISPADPRO_BUTTON_GREEN		2
#define PCPAD_GRAVISPADPRO_BUTTON_BLUE		3
#define PCPAD_GRAVISPADPRO_BUTTON_L1		4
#define PCPAD_GRAVISPADPRO_BUTTON_R1		5
#define PCPAD_GRAVISPADPRO_BUTTON_L2		6
#define PCPAD_GRAVISPADPRO_BUTTON_R2		7
#define PCPAD_GRAVISPADPRO_BUTTON_SELECT	8
#define PCPAD_GRAVISPADPRO_BUTTON_START		9

#ifdef __cplusplus
}
#endif

#endif

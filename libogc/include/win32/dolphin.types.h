/*---------------------------------------------------------------------*

Project:  Dolphin to WIN32 for MCC 
File:     dolphin.types.h

(C) 2000 Nintendo

-----------------------------------------------------------------------*/

#ifndef __DOLPHIN_TO_WIN32_H__
#define __DOLPHIN_TO_WIN32_H__

// HEADER INCLUDE
// ================
#include <stdio.h>
#include "../dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

	// DEFINES
	// ================
	#define OSContext	void
	#define OSReport	printf
	#define OSTick		s32
	//#define DCInvalidateRange(p,i) {}
	//#define DCFlushRange(p,i) {}
	#define OSGetTick	GetTickCount
	#define OSTicksToSeconds(t) ((t)/1000)
	#define OSSecondsToTicks(t) ((t)*1000)

	#ifndef ASSERT
	#define ASSERT(a) (((a)!=0)?(puts("ASSERT")):0)
	#endif

#ifdef __cplusplus
}
#endif

#endif//

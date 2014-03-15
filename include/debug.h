// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	stfour, JoostinOnline

#ifndef _STFDEBUG_
#define _STFDEBUG_

#if defined(HW_RVL)

//Comment next two lines to speed up the code:
#define USBGECKO

#ifdef __cplusplus
extern "C" {
#endif
/* __cplusplus */

s32 DebugStart (bool gecko, const char *fn);
#ifdef USBGECKO
void DebugStop (void);
void Debug(const char *text, ...);
void Debug_hexdump(void *d, int len);
void Debug_hexdumplog (void *d, int len);
void gprintf(const char *format, ...);

#else
 
#define DebugStop()
#define Debug(...)
#define Debug_hexdump(...)
#define Debug_hexdumplog(...)
#define gprintf(...)
 
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* defined(HW_RVL) */

#endif
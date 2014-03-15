// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	stfour, JoostinOnline

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <ogc/usbgecko.h>
#include <ogc/exi.h>

#include "debug.h"

#define ascii(X) (((unsigned)((X)-0x20) < 0x5F) ? (X) : '.') // replace X<0x20 and X>0x7E with '.'

/*

Debug, will write debug information to sd and/or gecko.... as debug file is open/closed it will be VERY SLOW

*/

#ifdef USBGECKO
static int started = 0;
static int geckolog = 0;
static FILE * fdebug = NULL;
#endif

s32 DebugStart (bool gecko, const char *dbgfile) {
	#ifdef USBGECKO
	started = 0;

	geckolog = usb_isgeckoalive (EXI_CHANNEL_1);

	// Open or create dbgfile
	fdebug = fopen(dbgfile, "wb");  // File will be cleared if it already exists.
	if (fdebug || geckolog) started = 1;

	return started;
	#endif
	return 0;
}

#ifdef USBGECKO
void DebugStop (void) {
	if (fdebug) fclose (fdebug);
	fdebug = NULL;
	started = 0;
	return;
}

void Debug (const char *text, ...) {
	if (!started || text == NULL) return;

	char mex[2048] = {0};

	va_list argp;
	va_start(argp, text);
	if (geckolog) vsnprintf(mex, sizeof(mex)-1, text, argp);
	if (fdebug) {
		vfprintf(fdebug, text, argp);
		fprintf(fdebug, "\r\n");
		fflush(fdebug);
	}
	va_end(argp);

	if (geckolog) {
		strncat(mex, "\n", sizeof(mex)-1);
		usb_sendbuffer(EXI_CHANNEL_1, mex, strlen(mex));
		usb_flush(EXI_CHANNEL_1);
		usleep (500);
	}
}

void gprintf (const char *format, ...) {
	char * tmp = NULL;
	va_list va;
	va_start(va, format);

	if((vasprintf(&tmp, format, va) >= 0) && tmp)
	{
		usb_sendbuffer(EXI_CHANNEL_1, tmp, strlen(tmp));
	}
	va_end(va);

	if(tmp)
		free(tmp);
}

void Debug_hexdump (void *d, int len) {
	u8 *data;
	int i, off;
	data = (u8*) d;

	gprintf("\n       0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F  0123456789ABCDEF");
	gprintf("\n====  ===============================================  ================\n");

	for (off = 0; off < len; off += 16) {
		gprintf("%04x  ", off);
		for (i = 0; i < 16; i++)
			if ((i + off) >= len)
				gprintf("   ");
			else gprintf("%02x ", data[off + i]);

		gprintf(" ");
		for (i = 0; i < 16; i++)
			if ((i + off) >= len)
				gprintf(" ");
			else gprintf("%c", ascii(data[off + i]));
		gprintf("\n");
	}
}
#endif
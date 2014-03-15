// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	filfat, xerpi, JoostinOnline

#ifndef __MAIN_H__
#define __MAIN_H__

#define FAT_DEVICE_NONE		0
#define FAT_DEVICE_SD		1
#define FAT_DEVICE_USB		2
#define WIICRAFT_VERSION	"070INDEV"

#define	BLACK	"\x1b[30;1m"
#define	RED	"\x1b[31;1m"
#define	GREEN	"\x1b[32;1m"
#define	YELLOW	"\x1b[33;1m"
#define BLUE    "\x1b[34;1m"
#define MAGENTA "\x1b[35;1m"
#define CYAN    "\x1b[36;1m"
#define	WHITE	"\x1b[37;1m"
#define CHANGE_COLOR(X)	(printf((X)))

extern int fatDevice;

#endif
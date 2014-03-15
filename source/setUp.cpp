// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 3.0 for more details.

// Copyright (C) 2012-2013	filfat, xerpi, JoostinOnline

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <stdio.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <fat.h>
#include <zlib.h>
#include <sstream>
#include <sys/stat.h>
#include "setUp.h"
#include "utils.h"
#include "main.h"

using namespace std;

int initFolders(int SD){

	if(SD == FAT_DEVICE_SD)
		return mkdir("sd:/WiiCraft", S_IRWXU|S_IRGRP|S_IXGRP);
	else if(SD == FAT_DEVICE_USB)
		return mkdir("usb:/WiiCraft", S_IRWXU|S_IRGRP|S_IXGRP);
	else
		return FAT_DEVICE_NONE;
}

/*---------------------------------------------------------------------------*
  Project:  Revolution THP Core/Utilities Libraries
  File:     thpcommon.h

  Copyright (C)2003-2006 Nintendo  All Rights Reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: thpcommon.h,v $
  Revision 1.1  02/08/2006 02:52:42  aka
  Imported from Dolphin Tree.

    
    3     03/09/15 5:51p Akagi
    Added THP_ERROR_THPFILE, THP_ERROR_JPEGFILE and THP_ERROR_DATA.
    Removed THP_ERROR_FILEFORMAT.
    
    2     03/09/15 1:29p Akagi
    Changed THP_ERROR_XXX from define to enum.
    
    1     03/07/01 3:10p Akagi
    Initial check-in. Modified to divide old THPConv.exe into 2 LIBs and 1
    EXE by Ohki-san@NTSC.
    
  $NoKeywords: $
  
 *---------------------------------------------------------------------------*/

#ifndef __THPCOMMON_H__
#define __THPCOMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

// error
enum
{
    THP_ERROR_NOERROR =  0,
    THP_ERROR_FILEIO,
    THP_ERROR_THPFILE,
    THP_ERROR_JPEGFILE,
    THP_ERROR_DATA,
    THP_ERROR_FATAL,

    NUM_THP_ERRORS
};

#ifdef __cplusplus
}
#endif

#endif // __THPCOMMON_H__

/*---------------------------------------------------------------------------*
  Project:  Revolution THP Core Library
  File:     thpcore.h

  Copyright (C)2003-2006 Nintendo  All Rights Reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: thpcore.h,v $
  Revision 1.1  02/08/2006 02:52:42  aka
  Imported from Dolphin Tree.

    
    3     03/09/15 1:19p Akagi
    Modified misspelling and renamed a function.
    
    2     03/07/03 10:56a Akagi
    Renamed some functions.
    
    1     03/07/01 3:10p Akagi
    Initial check-in. Modified to divide old THPConv.exe into 2 LIBs and 1
    EXE by Ohki-san@NTSC.
    
  $NoKeywords: $
  
 *---------------------------------------------------------------------------*/

#ifndef __THPCORE_H__
#define __THPCORE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <revolution/types.h>

// Structure
    
//--------------------------------------
// THPImageStatus
//--------------------------------------
typedef struct
{
    u32     xSize;
    u32     ySize;
    u32     h[3];
    u32     v[3];
    u32     imageSize;
    
} THPImageStatus;

// Global Value
    
//--------------------------------------
// VerboseFlag(default: 0)
//--------------------------------------
extern u32 THPVerboseFlag;

//--------------------------------------
// Output message callback
//--------------------------------------
extern void (*THPPrintFunc)( const char* format, va_list argptr );
    
//--------------------------------------
// Output Error message callback
//--------------------------------------
extern void (*THPPrintErrorFunc)( const char* format, va_list argptr );

//--------------------------------------
// Output Log message callback(If VerboseFlag =1)
//--------------------------------------
extern void (*THPPrintLogFunc)( const char* format, va_list argptr );

//--------------------------------------
// Memory fllocation callback(default: malloc)
//--------------------------------------
extern void* (*THPMalloc)( size_t size );
    
//--------------------------------------
// Memory free callback (default: free)
//--------------------------------------
extern void (*THPFree)( void* memblock );

// Function

//--------------------------------------
// Output message
//--------------------------------------
void THPPrint( const char* format, ... );

//--------------------------------------
// Output Error message
//--------------------------------------
void THPPrintError( const char* format, ... );

//--------------------------------------
// Output Log message
//--------------------------------------
void THPPrintLog( const char* format, ... );
    
//--------------------------------------
// Convert jpeg to thp
//--------------------------------------
s32  THPConvertJPEG2THP( void *jpeg_ptr, void* thp_ptr, s32 jpeg_length, THPImageStatus* status );

#ifdef __cplusplus
}
#endif

#endif // __THPCORE_H__

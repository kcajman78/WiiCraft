/*---------------------------------------------------------------------------*
  Project:  Revolution THP Utilities Library
  File:     thputilities.h

  Copyright (C)2002-2006 Nintendo  All Rights Reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: thputilities.h,v $
  Revision 1.1  02/08/2006 02:52:42  aka
  Imported from Dolphin Tree.

    
    11    03/12/24 1:48p Akagi
    Added THPUtyCopyTHPFile().
    
    10    03/09/15 5:50p Akagi
    Renamed all functions from THPCONVXXXX to THPUtyXXXX.
    
    9     03/07/03 10:57a Akagi
    Renamed some functions.
    
    8     03/07/01 3:09p Akagi
    Modified to divide old THPConv.exe into 2 LIBs and 1 EXE by
    Ohki-san@NTSC.
    
    7     03/07/01 2:59p Akagi
    Moved from build/tools/THPConv/include.
    
    6     03/07/01 9:19a Akagi
    Moved from securebuild/tools.
    
    5     02/05/08 2:30p Akagi
    modified [-trk] option By Tsuji (IRD)
    
    1     02/01/16 4:56p Akagi
    Initial revision made by Tsuji-san (IRD).
    
  $NoKeywords: $
  
 *---------------------------------------------------------------------------*/

#ifndef __THPUTILITIES_H__
#define __THPUTILITIES_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <revolution/types.h>
#include <revolution/thpfile.h>
#include <win32/thpaudio.h>

//--------------------------------------
// flags for THPUtyCreateTHP
//--------------------------------------
#define THP_CREATETHP_FILEFLAG_JPEGS  0
#define THP_CREATETHP_FILEFLAG_THP    1

//--------------------------------------
// THPFileName
//--------------------------------------
typedef struct
{
    char           name[_MAX_PATH];
    unsigned long  fileSize;
    
} THPFileName;

//--------------------------------------
// Utility Functions
//--------------------------------------

void THPUtyConvertToUnixFmt( char* fmt );
    
u16  THPUtyReverseEndianU16( u16   data );
u32  THPUtyReverseEndianU32( u32   data );
f32  THPUtyReverseEndianF32( f32   data );
    
s32  THPUtyWritePad32      ( FILE* op, u32 bytes );
s32  THPUtyPutU32          ( FILE* op, u32 data );
s32  THPUtyPutF32          ( FILE* op, f32 data );

//--------------------------------------
// THP File Write Functions
//--------------------------------------

void THPUtyHeaderInit( THPHeader* header );
    
s32  THPUtyWriteTHPHeader        ( FILE* op, THPHeader*        header );
s32  THPUtyWriteTHPFrameCompInfo ( FILE* op, THPFrameCompInfo* compinfo );
s32  THPUtyWriteTHPVideoInfo     ( FILE* op, THPVideoInfo*     videoinfo );
s32  THPUtyWriteTHPAudioInfo     ( FILE* op, THPAudioInfo*     audioinfo );
s32  THPUtyWriteTHPFrameHeader   ( FILE* op, THPFrameCompInfo* frameCompInfo,
                                             THPFrameHeader*   frameHeader );
s32  THPUtyWriteTHPComponentsInfo( FILE* op, THPFrameCompInfo* compinfo,
                                             THPVideoInfo*     videoinfo,
                                             THPAudioInfo*     audioinfo,
                                             s32*              compinfosize );
s32  THPUtyWriteTHPFileHeader    ( FILE* op, THPFileHeader*    fileHeader,
                                             s32*              compInfoSize );

//--------------------------------------
// THP File Read Functions
//--------------------------------------

s32  THPUtyReadTHPHeader       ( FILE* ip, THPHeader*        header );
s32  THPUtyReadTHPFrameCompInfo( FILE* ip, THPFrameCompInfo* compinfo );
s32  THPUtyReadTHPVideoInfo    ( FILE* ip, THPVideoInfo*     videoinfo );
s32  THPUtyReadTHPVideoInfoOld ( FILE* ip, THPVideoInfo*     videoinfo );
s32  THPUtyReadTHPAudioInfo    ( FILE* ip, THPAudioInfo*     audioinfo );
s32  THPUtyReadTHPAudioInfoOld ( FILE* ip, THPAudioInfo*     audioinfo );
s32  THPUtyReadTHPFrameHeader  ( FILE* ip, THPFrameHeader*   frameHeader,
                                           s32               componentNum );
s32  THPUtyReadTHPFileHeader   ( FILE* ip, THPFileHeader*    fileHeader );

//--------------------------------------
// THP File Manipulating Functions
//--------------------------------------

s32  THPUtyCopyTHPFile     ( FILE* ip,  THPFileHeader*   fileHeader,
                                        FILE*            op );
s32  THPUtyCreateTHP       ( FILE* op,  s32              fileFlag,
                                        void*            filePtr,
                                        THPFileHeader*   fileHeader,
                                        THPAudioHandle** audioHandleList );
s32  THPUtyChangeAudioTrack( FILE* iop, THPFileHeader*   fileHeader,
                                        THPAudioHandle** audioHandleList );

#ifdef __cplusplus
}
#endif

#endif // __THPUTILITIES_H__

/*---------------------------------------------------------------------------*
  Project:  Revolution THP Audio Library
  File:     thpaudio.h

  Copyright (C)2002-2006 Nintendo  All Rights Reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: thpaudio.h,v $
  Revision 1.2  03/20/2006 11:22:56  hiratsu
  Fixed unsafe macro.

  Revision 1.1  02/08/2006 02:52:42  aka
  Imported from Dolphin Tree.

    
    10    03/09/15 9:33a Akagi
    
    9     03/07/03 10:56a Akagi
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

#ifndef __THPAUDIO_H__
#define __THPAUDIO_H__

#include <revolution/types.h>
#include <revolution/thpfile.h>
#include <win32/dsptool.h>

#ifdef __cplusplus
extern "C" {
#endif
        
#define THP_TAP_SIZE 16
        
//#define THP_NTSC_RATE         (59.94)
#define THP_GC_OUTPUT_RATE      (1125.0 / 1124.0)
#define THP_OVERLAP_FRAME       (50)
#define THP_OVERLAP_SAMPLE      (14 * THP_OVERLAP_FRAME)
#define THP_ENCODE_SAMPLE       (3600 * 14)
#define THP_SAMPLE_BUFFER_SIZE  (THP_ENCODE_SAMPLE + THP_OVERLAP_SAMPLE)
#define THP_ADPCM_BUFFER_SIZE   ((THP_SAMPLE_BUFFER_SIZE / 14) * 8)
        
#define THPADPCMSampleToByte(x) (u32)(((x) / 14) * 8)
#define THPGetEncDataPtr(x, y)  (u8 *)((u32)(x) + THPADPCMSampleToByte(y))
#define THPGetDecDataPtr(x, y)  (s16 *)((u32)(x) + (y) * 2)

typedef struct
{
    char  fileName[_MAX_PATH];
    FILE* fileHandle;
    u32   frequency;
    u32   channel;
    u32   bitPerSample;
    u32   totalSampleSize;
    u32   dataBlockOffset;
    u32   curFileOffset;
    s32   formatType;
    s32   type;
    
} THPAudioFileInfo;
        
typedef struct
{
    u32  offsetNextChannel;
    u32  sampleSize;
    u16  lCoef[16];
    u16  rCoef[16];
    u16  lYn1;
    u16  lYn2;
    u16  rYn1;
    u16  rYn2;
    
} THPAudioRecordHeader;

typedef struct
{
    u32  init;
    u32  cpos;
    u32  set;
    u32  readSample;
    u32  processSample;
    s16  leftHistory [THP_TAP_SIZE];
    s16  rightHistory[THP_TAP_SIZE];
    
} THPAudioResampleParameter;

typedef struct
{
    THPAudioFileInfo           audioInfo;
    u32                        restEncodedSample;
    u32                        currentFrameNumber;
    f64                        frameRate;
    s16*                       leftDecodedPtr;
    s16*                       rightDecodedPtr;
    u8*                        leftADPCMPtr;
    u8*                        rightADPCMPtr;
    ADPCMINFO                  leftADPCMInfo;
    ADPCMINFO                  rightADPCMInfo;
    THPAudioRecordHeader       recordHeader;
    s16                        leftSampleBuffer  [THP_SAMPLE_BUFFER_SIZE];
    s16                        rightSampleBuffer [THP_SAMPLE_BUFFER_SIZE];
    s16                        leftDecodedBuffer [THP_SAMPLE_BUFFER_SIZE];
    s16                        rightDecodedBuffer[THP_SAMPLE_BUFFER_SIZE];
    u8                         leftADPCMBuffer   [THP_ADPCM_BUFFER_SIZE];
    u8                         rightADPCMBuffer  [THP_ADPCM_BUFFER_SIZE];
    THPAudioResampleParameter  resampleParameter;
    BOOL                       resampleFlag;
    
} THPAudioHandle;

extern s32  THPAudioInit( void );
extern s32  THPAudioQuit( void );

extern THPAudioHandle* THPAudioCreateHandle( char* fileName, f32 framerate );
extern void            THPAudioFreeHandle  ( THPAudioHandle* handle );

extern s32  THPAudioGetInfo           ( THPAudioHandle* handle, THPAudioInfo* audioInfo );
extern u32  THPAudioGetTotalSamples   ( THPAudioHandle* handle, s32 frame );
extern u32  THPAudioGetFrameSize      ( THPAudioHandle* handle, u32 frame );
extern u32  THPAudioGetMaxFrameSize   ( THPAudioHandle* handle, s32 frame );
extern u32  THPAudioGetMaxFrameSamples( THPAudioHandle* handle, s32 frame );

extern s32  THPAudioWriteFrame( THPAudioHandle* handle, FILE* output, s32 flag );

#ifdef __cplusplus
}
#endif

#endif //__THPAUDIO_H__

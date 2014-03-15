/*---------------------------------------------------------------------------*
  Project:  Revolution DSP ADPCM win32 DLL
  File:     dsptool.h

  Copyright (C)2002-2006 Nintendo  All Rights Reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: dsptool.h,v $
  Revision 1.1  02/08/2006 02:52:42  aka
  Imported from Dolphin Tree.

    
    8     03/07/01 3:05p Akagi
    Copied build/libraries/dsptool/src/dspadpcm.h.
    
    7     03/07/01 2:59p Akagi
    Moved from build/tools/THPConv/include.
    
    6     03/07/01 9:19a Akagi
    Moved from securebuild/tools.
    
    5     02/05/08 2:30p Akagi
    modified [-trk] option By Tsuji (IRD)
    
    1     02/01/16 4:55p Akagi
    Initial revision made by Tsuji-san (IRD).
    
  $NoKeywords: $
  
 *---------------------------------------------------------------------------*/

#ifndef __DSPTOOL_H__
#define __DSPTOOL_H__


#ifdef MAKE_A_DLL
#define LINKDLL __declspec(dllexport)
#else
#define LINKDLL __declspec(dllimport)
#endif


/*---------------------------------------------------------------------------*
    ADPCM info passed to the caller
 *---------------------------------------------------------------------------*/
typedef struct
{
    // start context
    s16 coef[16];
    u16 gain;
    u16 pred_scale;
    s16 yn1;
    s16 yn2;

    // loop context
    u16 loop_pred_scale;
    s16 loop_yn1;
    s16 loop_yn2;

} ADPCMINFO;


/*---------------------------------------------------------------------------*
    exported functions
 *---------------------------------------------------------------------------*/
LINKDLL u32 getBytesForAdpcmBuffer      (u32 samples);
LINKDLL u32 getBytesForAdpcmSamples     (u32 samples);
LINKDLL u32 getBytesForPcmBuffer        (u32 samples);
LINKDLL u32 getBytesForPcmSamples       (u32 samples);
LINKDLL u32 getNibbleAddress            (u32 samples);
LINKDLL u32 getNibblesForNSamples       (u32 samples);
LINKDLL u32 getSampleForAdpcmNibble     (u32 nibble);
LINKDLL u32 getBytesForAdpcmInfo        (void);

LINKDLL void encode
(
    s16         *src,   // location of source samples (16bit PCM signed little endian)
    u8          *dst,   // location of destination buffer
    ADPCMINFO   *cxt,   // location of adpcm info
    u32         samples // number of samples to encode         
);

LINKDLL void decode
(
    u8          *src,   // location of encoded source samples
    s16         *dst,   // location of destination buffer (16 bits / sample)
    ADPCMINFO   *cxt,   // location of adpcm info
    u32         samples // number of samples to decode         
);

LINKDLL void getLoopContext
(
    u8          *src,      // location of ADPCM buffer in RAM
    ADPCMINFO   *cxt,      // location of adpcminfo
    u32         samples    // samples to desired context
);


#endif // __DSPTOOL_H__

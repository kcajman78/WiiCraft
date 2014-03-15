/*---------------------------------------------------------------------------*
  Project:  Miscellaneous audio visualization tools
  File:     DEMOAVX.h

  Copyright 2002 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: DEMOAVX.h,v $
  Revision 1.1.1.1  2005/05/12 02:41:06  yasuh-to
  transitioned from the Dolphin source tree

    
    1     1/11/02 4:56p Eugene
    For new AVX functions.
    
    
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
 * Includes
 *---------------------------------------------------------------------------*/

#define AVX_FRAME_SIZE_SAMPLES   160        // 160 stereo samples @ 32KHz
#define AVX_FRAME_SIZE_WORDS     (160*2)    // 2 words per stereo sample
#define AVX_FRAME_SIZE_BYTES     (160*2*2)  // 2 bytes per sample, 2 channels


void    DEMOAVXInit             (s16 *left, s16 *right, u32 size);
u32     DEMOAVXRefreshBuffer    (u32 *start_index, u32 *end_index);

void    DEMOAVXAttach           (void *buffer, u32 num_frames);
u32     DEMOAVXGetFrameCounter  (void);
u32     DEMOAVXGetNumFilled     (void);

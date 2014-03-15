/*---------------------------------------------------------------------------*
  Project:  Dolphin DEMO library
  File:     DEMOPuts.h

  Copyright 1998-2001 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: DEMOPuts.h,v $
  Revision 1.1.1.1  2005/05/12 02:41:06  yasuh-to
  transitioned from the Dolphin source tree

    
    2     7/12/01 17:59 Shiki
    Added DEMOGetROMFontSize() and DEMOGetRFTextHeight().

    1     5/09/01 9:37p Hirose
    separated from demo.h

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __DEMOPUTS_H__
#define __DEMOPUTS_H__


#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*
    DEMOPuts.c
 *---------------------------------------------------------------------------*/
// filtering type for DEMOLoadFont texture
typedef enum
{
    DMTF_POINTSAMPLE,   // Point sampling
    DMTF_BILERP         // Bilerp filtering
} DMTexFlt;

// caption font type
#define DM_FT_OPQ   0
#define DM_FT_RVS   1
#define DM_FT_XLU   2

// DEMOFont functions
extern  void            DEMOSetFontType ( s32 );
extern  void            DEMOSetupScrnSpc( s32, s32, f32 );
extern  void            DEMOInitCaption ( s32, s32, s32 );
extern  void            DEMOLoadFont    ( GXTexMapID, GXTexMtx, DMTexFlt );

extern  void            DEMOPuts        ( s16, s16, s16, char* );
extern  void            DEMOPrintf      ( s16, s16, s16, char*, ... );

// ROM font functions
extern  OSFontHeader*   DEMOInitROMFont     ( void );
extern  void            DEMOSetROMFontSize  ( s16 size, s16 space );
extern  void            DEMOGetROMFontSize  ( s16* size, s16* space );
extern  int             DEMOGetRFTextWidth  ( char* string );
extern  int             DEMOGetRFTextHeight ( char* string );

extern  int             DEMORFPuts          ( s16 x, s16 y, s16 z, char* string );
extern  int             DEMORFPutsEx        ( s16 x, s16 y, s16 z, char* string, s16 maxWidth, int length);
extern  int             DEMORFPrintf        ( s16 x, s16 y, s16 z, char* fmt, ... );

extern  char*           DEMODumpROMFont     ( char* string );

/*---------------------------------------------------------------------------*
    DEMOFont.c
 *---------------------------------------------------------------------------*/
extern  u32 DEMOFontBitmap[];


/*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif // __DEMOPUTS_H__

/*===========================================================================*/

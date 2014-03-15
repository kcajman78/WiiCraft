/*---------------------------------------------------------------------------*
  Project:  Dolphin DEMO library
  File:     demo.h

  Copyright 1998-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: demo.h,v $
  Revision 1.7  2006/08/11 09:28:45  yasumoto_yoshitaka
  suppress unused warning

  Revision 1.6  03/11/2006 06:55:23  hirose
  Integrated MEMAllocator, added switch to use heap defined in MEM library.
  Moved easy-packed tpl functions from <revolution/tpl.h>

  Revision 1.5  2006/02/04 13:05:44  hashida
  (none)

  Revision 1.4  01/07/2006 06:47:13  hirose
  Reconstruction from simpler form.

  Revision 1.3  12/20/2005 05:26:36  hirose
  (none)

  Revision 1.2  08/03/2005 02:52:20  hirose
  Substitution of obsolete charPipeline libs by new tpl library.

  Revision 1.1.1.1  2005/05/12 02:41:06  yasuh-to

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __DEMO_H__
#define __DEMO_H__

/*---------------------------------------------------------------------------*/
#include <revolution.h>
#include <stdio.h>

#include <revolution/mem.h>
#include <revolution/tpl.h>

#include <demo/DEMOPad.h>
#include <demo/DEMOPuts.h>
/*---------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*
    DEMOInit.c
 *---------------------------------------------------------------------------*/
// Global variables
extern MEMAllocator		DemoAllocator1;		// For MEM1
extern MEMAllocator		DemoAllocator2;		// For MEM2

// Function prototypes
extern void             DEMOInit_Real       ( GXRenderModeObj* mode );
extern void             DEMOBeforeRender    ( void );
extern void             DEMODoneRender      ( void );
extern void             DEMOSwapBuffers     ( void );
extern GXRenderModeObj* DEMOGetRenderModeObj( void );
extern void*            DEMOGetCurrentBuffer( void );
extern void             DEMOReInit          ( GXRenderModeObj *mode );

// Definition of DEMOInit()
//
// If compiler switch 'DEMO_USE_MEMLIB' is defined, set DemoUseMEMHeap
// flag inside the library before DEMOInit_Real() is called.
extern u32 DemoUseMEMHeap;

#ifdef DEMO_USE_MEMLIB
#define DEMOInit(mode)   \
{                        \
	DemoUseMEMHeap = 1;  \
	DEMOInit_Real(mode); \
}
#else
#define DEMOInit(mode)   \
{                        \
	DemoUseMEMHeap = 0;  \
	DEMOInit_Real(mode); \
}
#endif


/*---------------------------------------------------------------------------*
    Extension of <revolution/tpl.h>
    Easy-packed TPL file access functions (inline)
 *---------------------------------------------------------------------------*/
inline void TPLGetPalette ( TPLPalettePtr *pal, char *name )
{
	DVDFileInfo dfi;

	(void)DVDOpen(name, &dfi);
	(*pal) = (TPLPalettePtr)MEMAllocFromAllocator(&DemoAllocator1, OSRoundUp32B(dfi.length));
	(void)DVDRead(&dfi, (*pal), (s32)OSRoundUp32B(dfi.length), 0);
	(void)DVDClose(&dfi);

	TPLBind(*pal);
}

/*---------------------------------------------------------------------------*/
inline void TPLReleasePalette ( TPLPalettePtr *pal )
{
    if ( pal )
	{
		MEMFreeToAllocator(&DemoAllocator1, *pal);
		*pal = 0;
	}		
}
/*---------------------------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif // __DEMO_H__

/*===========================================================================*/

/*---------------------------------------------------------------------*
Project:  tc library
File:     TCLayer.h

Copyright 1998-2001 Nintendo.  All rights reserved.

These coded instructions, statements and computer programs contain
proprietary information of Nintendo of America Inc. and/or Nintendo
Company Ltd., and are protected by Federal copyright law.  They may
not be disclosed to third parties or copied or duplicated in any form,
in whole or in part, without the prior written consent of Nintendo.

Change History:

   $Log: TCLayer.h,v $
   Revision 1.1  2006/02/17 09:04:06  mitu
   1st version

    
    2     4/11/01 3:30p John
    Updated header for copyright and pathname.
    
    1     12/03/99 4:15p Ryan
   
  $NoKeywords: $

-----------------------------------------------------------------------*/

#ifndef __TCLAYER_H__
#define __TCLAYER_H__

/********************************/
#include <dolphin/types.h>

/********************************/
#define LY_IMAGE_COLOR_RGB24	0x0001
#define LY_IMAGE_COLOR_CI16		0x0002
#define LY_IMAGE_ALPHA_A8		0x0004

/********************************/
typedef struct
{
    u32 type;                   
                                                   
    u32 width;                   
    u32 height;                               

    u8* data;           

}TCLayer, *TCLayerPtr;

/*>*******************************(*)*******************************<*/
TCLayer*	TCCreateLayer		( void );

void		TCSetLayerAttributes( TCLayer* ly, u32 type, u32 width, 
								  u32 height );

u8*			TCSetLayerBuffer	( TCLayer* ly );
void		TCSetLayerValue		( TCLayer* ly, u32 x, u32 y, u16  ria,    
								  u8  g, u8 b );

void		TCGetLayerValue		( TCLayer* ly, u32 x, u32 y, u16* riaPtr, 
								  u8* gPtr, u8* bPtr );

/*>*******************************(*)*******************************<*/

#endif  // __TCLAYER_H__

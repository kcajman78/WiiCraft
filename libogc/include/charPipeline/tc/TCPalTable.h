/*---------------------------------------------------------------------*
Project:  tc library
File:     TCPalTable.h

Copyright 1998-2001 Nintendo.  All rights reserved.

These coded instructions, statements and computer programs contain
proprietary information of Nintendo of America Inc. and/or Nintendo
Company Ltd., and are protected by Federal copyright law.  They may
not be disclosed to third parties or copied or duplicated in any form,
in whole or in part, without the prior written consent of Nintendo.

Change History:

   $Log: TCPalTable.h,v $
   Revision 1.1  2006/02/17 09:04:06  mitu
   1st version

    
    2     4/11/01 3:30p John
    Updated header for copyright and pathname.
    
    1     12/03/99 4:15p Ryan
   
  $NoKeywords: $

-----------------------------------------------------------------------*/

#ifndef __TCPALTABLE_H__
#define __TCPALTABLE_H__

/********************************/
#include <dolphin/types.h>

/********************************/
typedef struct 
{
	u32 numEntry;
	u8* rgba;

} TCPalTable, *TCPalTablePtr;

/*>*******************************(*)*******************************<*/
TCPalTable* TCCreatePalTable	( u32 numEntry );
void        TCSetPalTableValue	( TCPalTable* ptPtr, u32 index, u8  r,    
								  u8 g, u8 b, u8 a );

void		TCGetPalTableValue	( TCPalTable* ptPtr, u32 index, u8* rPtr, 
								  u8* gPtr, u8* bPtr, u8* aPtr );

/*>*******************************(*)*******************************<*/

#endif  // __TCPALTABLE_H__

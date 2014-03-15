/*---------------------------------------------------------------------*
Project:  tc library
File:     TCCommon.h

Copyright 1998-2001 Nintendo.  All rights reserved.

These coded instructions, statements and computer programs contain
proprietary information of Nintendo of America Inc. and/or Nintendo
Company Ltd., and are protected by Federal copyright law.  They may
not be disclosed to third parties or copied or duplicated in any form,
in whole or in part, without the prior written consent of Nintendo.

Change History:

   $Log: TCCommon.h,v $
   Revision 1.1  2006/02/17 09:04:06  mitu
   1st version

    
    3     4/11/01 3:30p John
    Updated header for copyright and pathname.
    
    2     3/17/00 1:12p Mikepc
    change tc to use indices numbered from 0:
    added #define TC_UNUSED 0xFFFFFFFF for unused .tcs file component.
    added TCAssertMsg prototype
    added TCStrToUpper prototype
    
    1     12/03/99 4:15p Ryan
   
  $NoKeywords: $

-----------------------------------------------------------------------*/

#ifndef __TCCOMMON_H__
#define __TCCOMMON_H__

/********************************/
#include <stdarg.h>

#include <dolphin/types.h>


// flag used by internal structures to indicate
// an unused TCLayer
#define TC_UNUSED 0xFFFFFFFF

/*>*******************************(*)*******************************<*/
void TCErrorMsg(   char* msg, ...            );
void TCAssertMsg(  int   exp, char* msg, ... );
void TCStrToUpper( char* str );
/*>*******************************(*)*******************************<*/


#endif  // __TCCOMMON_H__

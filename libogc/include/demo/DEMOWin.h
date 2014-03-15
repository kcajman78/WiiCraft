/*---------------------------------------------------------------------------*
 *       N I N T E N D O  C O N F I D E N T I A L  P R O P R I E T A R Y
 *---------------------------------------------------------------------------*
 *
 *  Project    : Dolphin OS - DEMOWin
 * File:    DEMOWin.h
 *
 * Copyright 2001 Nintendo.  All rights reserved.
 *
 * These coded instructions, statements, and computer programs contain
 * proprietary information of Nintendo of America Inc. and/or Nintendo
 * Company Ltd., and are protected by Federal copyright law.  They may
 * not be disclosed to third parties or copied or duplicated in any form,
 * in whole or in part, without the prior written consent of Nintendo.
 *
 * $Log: DEMOWin.h,v $
 * Revision 1.4  2006/05/21 15:02:25  ekwon
 * Revised to accomodate MEM library usage if DEMO_USE_MEMLIB is #define'd before DEMOWIN.h is included.
 *
 * Also supports using MEM2 via  #define of DEMOWIN_USE_MEM2. However, this has not been tested yet.
 *
 * Note that these changes are backwards compatible with older demos.
 *
 * Revision 1.3  2006/03/20 11:22:56  hiratsu
 * Fixed unsafe macro.
 *
 * Revision 1.2  2006/02/04 13:05:45  hashida
 * (none)
 *
 * Revision 1.1.1.1  2005/05/12 02:41:06  yasuh-to
 * dolphinシースツリーから移植
 *
    
    13    02/08/26 20:14 Hashida
    Suppressed a warning.
    
    12    2/05/02 4:01p Eugene
    Added pad data to window structure so that it may be exposed to calling
    application.
    
    11    5/08/01 10:49p Eugene
    
    10    5/08/01 2:18a Eugene
    
    9     5/08/01 2:06a Eugene
    
    8     5/07/01 11:54p Eugene
    
    7     5/07/01 11:14p Eugene
    
    6     5/07/01 11:13p Eugene
    
    5     5/07/01 10:01p Eugene
    
    4     5/07/01 1:28p Eugene
    
    3     5/06/01 11:28p Eugene
    
    2     5/06/01 11:07p Eugene
    
    1     5/06/01 8:30p Eugene
    For unsupported, undocumented windowing system. This file must be
    explicitly included before the DEMOWin library can be used.
    
    1     12/04/00 7:28p Eugene
 *   
 *
 * $NoKeywords: $
 *
 *---------------------------------------------------------------------------*
 *
 * Description
 * -----------
 * 
 * 
 * 
 *
 *---------------------------------------------------------------------------*/

  
#ifndef __DEMOWIN_H__
#define __DEMOWIN_H__

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*
 * Includes
 *---------------------------------------------------------------------------*/

#include <revolution/types.h>

/*---------------------------------------------------------------------------*
 * Definitions
 *---------------------------------------------------------------------------*/

// font-size calibrations
#define DEMOWIN_MAX_STRING_SIZE     128
#define FONT_CHAR_WIDTH               8
#define FONT_CHAR_HEIGHT              8
#define DEMOWIN_X_CHAR_PAD            7
#define DEMOWIN_Y_CHAR_PAD            2

// calculating minimum window dimensions
// takes number of characters as parameters; returns size in pixels
#define DEMOWIN_CALC_MENU_WIDTH_PIXELS(w)   ((((w)+DEMOWIN_X_CHAR_PAD)*FONT_CHAR_WIDTH)+4) 
#define DEMOWIN_CALC_MENU_HEIGHT_PIXELS(h)  (((DEMOWIN_Y_CHAR_PAD+(h))*FONT_CHAR_HEIGHT)+4)

// window flags
#define DEMOWIN_FLAG_ATTACHED   0x00000001
#define DEMOWIN_FLAG_VISIBLE    0x00000002

// window priority (Z value) - note that DEMO lib looks down the positive Z axis
#define DEMOWIN_PRIORITY_FORE   0x0000
#define DEMOWIN_PRIORITY_BACK   0x0001

// window color attributes
#define DEMOWIN_COLOR_CAPTION   0
#define DEMOWIN_COLOR_BKGND     1
#define DEMOWIN_COLOR_BORDER    2
#define DEMOWIN_COLOR_RESET     3

// for window scrolling function
#define DEMOWIN_SCROLL_HOME     0 // set curr_view_line to curr_output_line
#define DEMOWIN_SCROLL_UP       1 // text moves down
#define DEMOWIN_SCROLL_DOWN     2 // text moves up

#define DEMOWIN_LIST_HOME       0
#define DEMOWIN_LIST_UP         1
#define DEMOWIN_LIST_DOWN       2

// ******************************************
// DEMOWIN PAD structure
// ******************************************

typedef struct 
{
    PADStatus pads           [PAD_MAX_CONTROLLERS];
    u32       button         [PAD_MAX_CONTROLLERS];
    u32       old_button     [PAD_MAX_CONTROLLERS];
    u32       changed_button [PAD_MAX_CONTROLLERS];
    u32       repeat_button  [PAD_MAX_CONTROLLERS];
    u32       repeat_ctr     [PAD_MAX_CONTROLLERS];
} DEMOWinPadInfo;

#define PAD_THRESHOLD        64
#define TRIGGER_THRESHOLD   128

// *****************************************
// For PopUp menu system
// *****************************************

// item flags
#define DEMOWIN_ITM_NONE       0x00000000 //
#define DEMOWIN_ITM_DISABLED   0x00000001 //
#define DEMOWIN_ITM_CHECK      0x00000002 //
#define DEMOWIN_ITM_CHK_STATE  0x00000004 //
#define DEMOWIN_ITM_SEPARATOR  0x00000008 //
#define DEMOWIN_ITM_EOF        0x00000010 // menu should exit after invoking this function
#define DEMOWIN_ITM_TERMINATOR 0x80000000

// window flag
#define DEMOWIN_MNU_NONE       0x00000000 //
#define DEMOWIN_MNU_EOM        0x00000001 // parent should exit after invoking this menu


// menu navigation
#define DEMOWIN_MNU_UP         0x0001
#define DEMOWIN_MNU_DOWN       0x0002
#define DEMOWIN_MNU_LEFT       0x0003
#define DEMOWIN_MNU_RIGHT      0x0004
#define DEMOWIN_MNU_SELECT     0x0005 
#define DEMOWIN_MNU_CANCEL     0x0006

// *****************************************
// For PAD system
// *****************************************
#define DEMOWIN_PAD_REPEAT_THRESH_DEF  15   // in video frames
#define DEMOWIN_PAD_REPEAT_RATE_DEF     2   // in video frames


#define DEMOWIN_STICK_U           0x00010000      // analog value exceed specified threshold
#define DEMOWIN_STICK_D           0x00020000
#define DEMOWIN_STICK_R           0x00040000
#define DEMOWIN_STICK_L           0x00080000
#define DEMOWIN_SUBSTICK_U        0x00100000
#define DEMOWIN_SUBSTICK_D        0x00200000
#define DEMOWIN_SUBSTICK_R        0x00400000
#define DEMOWIN_SUBSTICK_L        0x00800000
#define DEMOWIN_TRIGGER_R         0x01000000
#define DEMOWIN_TRIGGER_L         0x02000000

/*---------------------------------------------------------------------------*
 * Types
 *---------------------------------------------------------------------------*/


typedef struct STRUCT_DEMOWIN
{
    // user defined window properties
    s32      x1;
    s32      y1; 
             
    s32      x2;
    s32      y2;
             
    u32      priority;
             
    u32      flags;                  
             
    u16      x_cal;             // corrective offset, for centering window contents horizontally
    u16      y_cal;             // corrective offset, for centering window contents vertically
             
    u16      pixel_width;       // width of window, in pixels
    u16      pixel_height;      // height of window, in pixels
             
    u16      char_width;        // width of window, in characters
    u16      char_height;       // height of window, in characters
             
    u16      num_scroll_lines;  // number of scrollback lines
    u16      total_lines;       // total number of buffer lines (including visible)
             
    u16      curr_output_line;  // current row in buffer at which "log printf" will output text
    u16      curr_output_col;   // current col in a line at which "log printf" will output text
    u16      curr_view_line;    // for scrolling through the buffer
    s16      cursor_line;       // if <0, no highlight; otherwise, draw highlight
                   
    char    *caption;
    u8      *buffer;            // private; dynamically allocated

    GXColor  bkgnd;
    GXColor  cap;
    GXColor  border;

    void     (*refresh)(struct STRUCT_DEMOWIN *handle);
    struct   STRUCT_DEMOWIN   *next;
    struct   STRUCT_DEMOWIN   *prev;
    void     *parent;           // pointer to a 'superstructure' which includes this window handle

    DEMOWinPadInfo  pad;        // pad data for given window


} DEMOWinInfo;



/*---------------------------------------------------------------------
 * "Modal" menu system
 *---------------------------------------------------------------------*/


// ******************************************
// Menu item
// ******************************************

struct STRUCT_MENU;
typedef struct STRUCT_MENU_ITEM
{
    char *name;                                     // NULL terminated string; name of menu item
    u32  flags;                                     // menu item attributes

    void (*function)(struct STRUCT_MENU *menu, u32 item, u32 *result);       
    struct STRUCT_MENU *link;                       // child menu, if any

} DEMOWinMenuItem;

// The "function" member is the callback to invoke if this item is selected. The
// function may return a value in "result". If this item has the "DEMOWIN_ITM_EOF"
// flag asserted, the menu will exit after calling this function and return the
// value of "result". Kludgy, yes, I know.


// ******************************************
// Menu information
// ******************************************
typedef struct STRUCT_MENU
{
    char            *title;                         // menu title
    DEMOWinInfo     *handle;                        // window associated with this menu
    DEMOWinMenuItem *items;                         // list of menu items
    s32              max_display_items;             // max number of items to display at once
    u32              flags;                         // menu attributes

    void (*cb_open)  (struct STRUCT_MENU *menu, u32 item);
    void (*cb_move)  (struct STRUCT_MENU *menu, u32 item);
    void (*cb_select)(struct STRUCT_MENU *menu, u32 item);
    void (*cb_cancel)(struct STRUCT_MENU *menu, u32 item);

    // private menu state information
    s32 num_display_items;      // actual number of items to display
    s32 num_items;              // actual number of items in list
    u32 max_str_len;            // max item/caption string length
    s32 curr_pos;               // curr position in list
    s32 display_pos;            // curr 'home' row displayed in list

} DEMOWinMenuInfo;


/*---------------------------------------------------------------------
 * List box stuff
 *---------------------------------------------------------------------*/

// ******************************************
// Listbox item
// ******************************************
typedef struct STRUCT_LISTBOX_ITEM
{

    char *name;     // name of item
    u32   flags;    // item attributes, if any

} DEMOWinListItem;


// ******************************************
// Listbox information
// ******************************************
typedef struct STRUCT_LISTBOX
{

    char            *title;      // listbox title/caption
    DEMOWinInfo     *handle;     // Window handle
    DEMOWinListItem *items;      // pointer to array of items

    s32  max_display_items;      // maximum number of items to display
    u32  flags;                  // listbox attributes, if any

    // private menu state information
    s32  num_display_items;      // actual number of items to display
    s32  num_items;              // actual number of items in list
    u32  max_str_len;            // max item/caption string length
    s32  curr_pos;               // curr position in list
    s32  display_pos;            // curr 'home' row displayed in list
    BOOL cursor_state;           // ON or OFF


} DEMOWinListInfo;


/*---------------------------------------------------------------------------*
 * Globals
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
 * Function Prototypes
 *---------------------------------------------------------------------------*/

// initialization
void             DEMOWinInit_Real        (BOOL mem_lib_flag, BOOL mem2_flag);


#ifdef DEMO_USE_MEMLIB

    #ifdef DEMOWIN_USE_MEM2

        #define DEMOWinInit() DEMOWinInit_Real(TRUE,TRUE)

    #else

        #define DEMOWinInit() DEMOWinInit_Real(TRUE,FALSE)

    #endif

#else

    #define DEMOWinInit() DEMOWinInit_Real(FALSE, FALSE)

#endif


// instantiation
DEMOWinInfo     *DEMOWinCreateWindow     (s32 x1, s32 y1, s32 x2, s32 y2, char *caption, u16 scroll, void *func);
void             DEMOWinOpenWindow       (DEMOWinInfo *handle);
void             DEMOWinCloseWindow      (DEMOWinInfo *handle);
void             DEMOWinDestroyWindow    (DEMOWinInfo *handle);

// attribute control
void             DEMOWinScrollWindow     (DEMOWinInfo *handle, u32 dir);
void             DEMOWinSetWindowColor   (DEMOWinInfo *handle, u32 item, u8 r, u8 g, u8 b, u8 a);
void             DEMOWinBringToFront     (DEMOWinInfo *handle);
void             DEMOWinSendToBack       (DEMOWinInfo *handle);

void             DEMOWinSetCursorLine    (DEMOWinInfo *handle, s16 n);
s32              DEMOWinGetCursorLine    (DEMOWinInfo *handle);

// I/O
void             DEMOWinLogPrintf        (DEMOWinInfo *handle, char *fmt, ...);
void             DEMOWinPrintfXY         (DEMOWinInfo *handle, u16 col, u16 row, char *fmt, ...);
void             DEMOWinClearRow         (DEMOWinInfo *handle, u16 row);
void             DEMOWinClearWindow      (DEMOWinInfo *handle);
void             DEMOWinClearBuffer      (DEMOWinInfo *handle);

void             DEMOWinPadInit          (DEMOWinPadInfo *p);
void             DEMOWinPadRead          (DEMOWinPadInfo *p);
void             DEMOWinResetRepeat      (void);
void             DEMOWinSetRepeat        (u32 threshold, u32 rate);

// infrastructure
void             DEMOWinRefresh          (void);

// menu system
DEMOWinMenuInfo *DEMOWinCreateMenuWindow (DEMOWinMenuInfo *menu, u16 x, u16 y);
u32              DEMOWinMenuChild        (DEMOWinMenuInfo *items, BOOL child_flag);
void             DEMOWinDestroyMenuWindow(DEMOWinMenuInfo *menu);

// List box
DEMOWinListInfo *DEMOWinCreateListWindow (DEMOWinListInfo *list, u16 x, u16 y);
void             DEMOWinDestroyListWindow(DEMOWinListInfo *list);
void             DEMOWinListSetCursor    (DEMOWinListInfo *list, BOOL x);
s32              DEMOWinListScrollList   (DEMOWinListInfo *list, u32 dir); 
s32              DEMOWinListMoveCursor   (DEMOWinListInfo *list, u32 dir);

// aliased functions
#define          DEMOWinGetNumRows(h) ((h)->char_width)
#define          DEMOWinGetNumCols(h) ((h)->char_height)
#define          DEMOWinMenu(ptr) DEMOWinMenuChild((ptr),FALSE)

#define          DEMOWinListGetCurPos(l) ((l)->curr_pos)
#define          DEMOWinListSetCurPos(l,x) ((l)->curr_pos = (s32)(x))


#ifdef __cplusplus
}
#endif

#endif // __DEMOWIN_H__

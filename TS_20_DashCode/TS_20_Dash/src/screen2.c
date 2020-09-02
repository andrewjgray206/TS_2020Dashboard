/**
 * @file screen2.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "screen1.h"
#include "screen2.h"
#include "screen3.h"
#include "menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t * header;
static lv_obj_t * bar_value;
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void screen2Init(lv_theme_t * th)
{

lv_obj_t * win = lv_win_create(lv_scr_act(), NULL);
lv_win_set_title(win, "Test"); 

/*Add control button to the header*/

lv_obj_t * close_btn = lv_win_add_btn(win, LV_SYMBOL_CLOSE);  /*Add close button and use built-in close action*/

lv_obj_set_event_cb(close_btn, lv_win_close_event_cb);
lv_win_add_btn(win, LV_SYMBOL_SETTINGS);        /*Add a setup button*/ 

/*Add some dummy content*/
lv_obj_t * txt = lv_label_create(win, NULL);
lv_label_set_text(txt, "This is the content of screen2.c\n\n"
                       "it is a test windowview.\n"
                       "the window header\n\n"
                       "The content area becomes automatically\n"
                       "scrollable is it's large enough.\n\n"
                       " You can scroll the content\n"
                       "See the scroll bar on the right!\n "
                       "dsfdfdff\n");
}

void lv_win_close_event_lol(lv_obj_t * btn, lv_event_t event)
    {
        if(event == LV_EVENT_RELEASED) {

        lv_obj_t * win = lv_win_get_from_btn(btn); 

        lv_obj_del(win);
    }
}

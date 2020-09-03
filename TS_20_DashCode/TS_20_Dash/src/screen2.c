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
static void header_create(void);
static void btn_event(lv_obj_t * obj, lv_event_t event); //btn1 event.
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

    lv_theme_set_current(th);
    th = lv_theme_get_current();    
    lv_obj_t * scr = lv_cont_create(NULL, NULL);
    lv_disp_load_scr(scr);

    lv_obj_t * win = lv_win_create(scr,NULL); 
    lv_win_set_title(win,"Hello ts_20");

    

    /*Add control button to the header*/

    lv_obj_t * close_btn = lv_win_add_btn(win, LV_SYMBOL_CLOSE);  /*Add close button and use built-in close action*/
    lv_obj_set_event_cb(close_btn, btn_event);
    lv_win_set_btn_size(win, 30);

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

    header_create();
}

static void header_create(void)
{
    header = lv_cont_create(lv_disp_get_scr_act(NULL), NULL);
    lv_obj_set_width(header, lv_disp_get_hor_res(NULL) - 30);
    lv_obj_set_height(header, 30);

    //lv_obj_t * con_btn = lv_btn_create(header, NULL);
    //lv_obj_align(con_btn, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);

    lv_obj_t * sym = lv_label_create(header, NULL);
    lv_label_set_text(sym, "TS 20");
    lv_obj_align(sym, NULL, LV_ALIGN_IN_RIGHT_MID, -LV_DPI/10, 0);

    lv_obj_t * ams_state = lv_label_create(header, NULL);
    lv_label_set_text(ams_state, "AMS STATE: Idle");
    lv_obj_align(ams_state, NULL, LV_ALIGN_CENTER, LV_DPI/10, 0);

    lv_obj_t * clock = lv_label_create(header, NULL);
    lv_label_set_text(clock, "RUN TIME: 0");
    lv_obj_align(clock, NULL, LV_ALIGN_IN_LEFT_MID, LV_DPI/10, 0);
        
    //lv_cont_set_fit2(header, LV_FIT_NONE, LV_FIT_TIGHT);   /*Let the height set automatically*/
    lv_obj_set_pos(header, 0, 0);

}

static void btn_event(lv_obj_t * obj, lv_event_t event)
/* This function contains the event handler for a button.
*  in this case it's button one, and all it's used to do
*  is close the screen and navigate to another one. */
{
    lv_obj_t * currentScreen = lv_scr_act(); //gets the screen.
    if ( event == LV_EVENT_RELEASED)
    {
        lv_obj_del(currentScreen);  //literally just deletes the screen.
        menuInit(lv_theme_night_init(63488, NULL)); //call to another file to run it's screen.
    }
}

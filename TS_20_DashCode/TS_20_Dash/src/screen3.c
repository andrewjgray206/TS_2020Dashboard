/**
 * @file screen3.c
 *
 */

/**
  ******************************************************************************
  * @file    screen1.c
  * @author  Andrew Gray, Christian Lazarovski, Tansel Kahrahman
  * @version V1.0
  * @date    02-09-2020
  * @brief   Main Screen #3.
  ******************************************************************************
*/

/*********************
 *      INCLUDES
 *********************/
#include "menu.h"
#include "screen3.h"
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
static void navButton1Handler(lv_obj_t * obj, lv_event_t event);


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

/**
 * Create a test screen with a lot objects and apply the given theme on them
 * @param th pointer to a theme
 */

void screen3Init(lv_theme_t * th)
{
    //BEGIN SCREEN SETUP.
    lv_theme_set_current(th);
    th = lv_theme_get_current();    
    lv_obj_t * scr = lv_cont_create(NULL, NULL); 
    lv_disp_load_scr(scr);

    /*lv_obj_t * win = lv_win_create(lv_scr_act(),NULL); //creates a new window
    lv_win_set_title(win,"Hello ts_20");
    lv_obj_set_size(win, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));*/

    //END SCREEN SETUP
    //START MENU BUTTONS
    //lv_obj_t * btn1 = lv_win_add_btn(win,LV_SYMBOL_WARNING);
    //lv_obj_t * btn2 = lv_win_add_btn(win,LV_SYMBOL_WIFI);

    lv_obj_t * widCon = lv_cont_create(scr, NULL);
    //lv_obj_set_pos(widCon, 100, 100);
    lv_obj_align(widCon, scr, LV_ALIGN_CENTER, 0,0);
    lv_obj_t * navButton1 = lv_btn_create(widCon,NULL);
    lv_obj_set_event_cb(navButton1, navButton1Handler);
    lv_obj_t * navButton1Label = lv_label_create(navButton1,NULL);
    lv_label_set_text(navButton1Label,"To Menu.c");

    header_create();
}

static void navButton1Handler(lv_obj_t * obj, lv_event_t event)
{
    lv_obj_t * currentScreen = lv_scr_act(); //gets the screen.
    if ( event == LV_EVENT_RELEASED)
    {
        lv_obj_del(currentScreen);  //literally just deletes the screen.
        //screen1Init(lv_theme_night_init(63488, NULL)); //call to another file to run it's screen.
        menuInit(lv_theme_night_init(63488, NULL));
    }
}

static void header_create(void)
{
    header = lv_cont_create(lv_disp_get_scr_act(NULL), NULL);
    lv_obj_set_width(header, lv_disp_get_hor_res(NULL));
    lv_obj_set_height(header, 30);

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
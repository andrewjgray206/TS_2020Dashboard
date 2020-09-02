/**
 * @file lv_test_window.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_test_window.h"
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
static void create_tab1(lv_obj_t * parent);
static void create_tab2(lv_obj_t * parent);
static void create_tab3(lv_obj_t * parent);
void exampleBarMovement(lv_obj_t * bar);
static void bar_set_value(lv_obj_t * bar, int16_t value);
static void header_create(void);
static void bar_event_cb(lv_obj_t * slider, lv_event_t event);

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


void lv_test_window(lv_theme_t * th)
{
    lv_theme_set_current(th);
    th = lv_theme_get_current();    
    lv_obj_t * scr = lv_cont_create(NULL, NULL); //creates the screen scr
    lv_disp_load_scr(scr);

    //lv_obj_t * win = lv_win_create(lv_scr_act(),NULL); //creates a new window
    //lv_win_set_title(win,"Hello ts_20");
    //lv_obj_set_size(win, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));

    //lv_obj_t * btn1 = lv_win_add_btn(win,LV_SYMBOL_WARNING); //first button
    //lv_obj_t * btn2 = lv_win_add_btn(win,LV_SYMBOL_WIFI); //second button.

    header_create();
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
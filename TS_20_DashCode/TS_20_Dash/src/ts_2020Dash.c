 /**
 * @file ts_2020Dash.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "ts_2020Dash.h"
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
//static void create_screen1(lv_obj_t * parent,lv_obj_t * header); //screen1
static void bar_event_cb(lv_obj_t * slider, lv_event_t event); //allows sliding between the screens.


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
 * Creates the first window
 * @param th pointer to a theme
 */
void dashInit(lv_theme_t * th) //sets the screen up.
{
    /* This integration of LVGL V6 uses a window view
    * with buttons to navigate between screens. (hopefully)
    * The window is the main object, becoming the parent for everything
    * else drawn on the screen. From here i currently don't know
    * how to align stuff on its own, so i'm doing it manually.
    * Have fun sussing!*/

    lv_obj_t * win = lv_win_create(lv_scr_act(),NULL); //creates a new window
    lv_win_set_title(win,"Hello ts_20");
    lv_obj_t * btn1 = lv_win_add_btn(win,LV_SYMBOL_WARNING); //first button
    lv_obj_t * btn2 = lv_win_add_btn(win,LV_SYMBOL_WIFI); //second button.


    lv_obj_t * bar1 = lv_bar_create(win, NULL);
    lv_bar_set_anim_time(bar1, 2000);
    lv_bar_set_value(bar1, 20, LV_ANIM_ON);

    lv_obj_t * label2 = lv_label_create(win,NULL);
    lv_label_set_text(label2,"Rineheart Temp");
    lv_obj_align(label2,bar1,LV_ALIGN_IN_RIGHT_MID,120,0);


    lv_obj_t * bar2 = lv_bar_create(win,NULL);
    lv_bar_set_value(bar2,90,LV_ANIM_ON);
    lv_obj_align(bar2,bar1,LV_ALIGN_IN_BOTTOM_MID,0,45);

    lv_obj_t * label3 = lv_label_create(win,NULL);
    lv_label_set_text(label3,"Acuumulator Temp");
    lv_obj_align(label3,bar2,LV_ALIGN_IN_RIGHT_MID,120,0);


}

/**********************
 *   STATIC FUNCTIONS
 **********************/
/*static void create_screen1(lv_obj_t * parent, lv_obj_t * header) //THIS FUNCTION IS DEFUNCT AT THE MOMENT,HANDY FOR REFERENCE THOUGH.
{
    //Sets the styling.
    //lv_page_set_scrl_layout(parent, LV_LAYOUT_CENTER);

    lv_theme_t * th = lv_theme_get_current();

    static lv_style_t h_style;
    lv_style_copy(&h_style, &lv_style_transp);
    h_style.body.padding.inner = LV_DPI / 10;
    h_style.body.padding.left = LV_DPI / 4; 
    h_style.body.padding.right = LV_DPI / 4;
    h_style.body.padding.top = LV_DPI / 10;
    h_style.body.padding.bottom = LV_DPI / 10;

    //creates a container "h". This becomes the parent object for all of our widgets.
    lv_obj_t * h = lv_cont_create(parent, NULL); 
    lv_obj_set_style(h, &h_style);
    lv_obj_set_click(h, false);
    lv_cont_set_fit(h, LV_FIT_TIGHT);
    lv_cont_set_layout(h, LV_LAYOUT_COL_M);
    lv_obj_set_pos(h,0,0);

    /********************************************************
     * The above h is out container for all our widgets.
     * When creating a new widget, if we use h as the parent
     * they will all align nicely, and then we can fine tune
     * using the align functionality of lvgl.
     *******************************************************

     Call the header create function, using h as its parent. 

    lv_obj_t * label1 = lv_label_create(h,NULL);
    lv_label_set_text(label1,"Battery        ");

    lv_obj_t * bar = lv_bar_create(h, NULL);
    lv_obj_set_event_cb(bar, bar_event_cb);
    lv_bar_set_anim_time(bar, 2000);
    lv_bar_set_value(bar, 100, LV_ANIM_ON);

    Create a label below the slider 
    bar_value = lv_label_create(label1,NULL);
    lv_label_set_text(bar_value, "100");
    lv_obj_align(bar_value,label1,LV_ALIGN_IN_RIGHT_MID,0,0);

    Rineheart temp Label
    lv_obj_t * label2 = lv_label_create(h,NULL);
    lv_label_set_text(label2,"Rineheart Temp        ");

    bar_value = lv_label_create(label2,NULL);
    lv_label_set_text(bar_value, "20");
    lv_obj_align(bar_value,label2,LV_ALIGN_IN_RIGHT_MID,0,0);

    lv_obj_t * bar2 = lv_bar_create(h, NULL);
    lv_bar_set_anim_time(bar2, 2000);
    lv_bar_set_value(bar2, 20, LV_ANIM_ON);

    //accumulator temp label
    lv_obj_t * label3 = lv_label_create(h,NULL);
    lv_label_set_text(label3,"Accumulator Temp        ");

    bar_value = lv_label_create(label3,NULL);
    lv_label_set_text(bar_value, "40");
    lv_obj_align(bar_value,label3,LV_ALIGN_IN_RIGHT_MID,0,0);

    lv_obj_t * bar3 = lv_bar_create(h,NULL);
    lv_bar_set_anim_time(bar3, 2000);
    lv_bar_set_value(bar3, 40, LV_ANIM_ON);

}*/

static void bar_event_cb(lv_obj_t * bar, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        static char buf[4]; /* max 3 bytes for number plus 1 null terminating byte */
        snprintf(buf, 4, "%u", lv_slider_get_value(bar));
        lv_label_set_text(bar_value, buf);
    }
}

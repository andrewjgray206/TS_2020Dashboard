 /**
 * @file menu.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "menu.h"
#include "screen1.h"
#include "screen2.h"
#include "screen3.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if LV_USE_TESTS
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
static void header_create(void);

void exampleBarMovement(lv_obj_t * bar);
static void bar_set_value(lv_obj_t * bar, int16_t value);
static void bar_event_cb(lv_obj_t * slider, lv_event_t event);

static void navButto1Handler(lv_obj_t * obj, lv_event_t event);
static void navButton2Handler(lv_obj_t * obj, lv_event_t event);

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
void menuInit(lv_theme_t * th)
{   
    //BEGIN SCREEN SETUP
    lv_theme_set_current(th);
    th = lv_theme_get_current();    
    lv_obj_t * scr = lv_cont_create(NULL, NULL); //creates the screen scr
    lv_disp_load_scr(scr);

    lv_obj_t * tv = lv_tabview_create(scr, NULL); //allows us to add tabs in more easily later.
    lv_obj_set_size(tv, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_t * tab1 = lv_tabview_add_tab(tv, "Home Screen"); //tab1.
    lv_obj_t * tab2 = lv_tabview_add_tab(tv, "Tab 2");
    lv_obj_t * tab3 = lv_tabview_add_tab(tv, "Tab 3");

    //END SCREEN SETUP

    lv_tabview_set_btns_hidden(tv, true); //tabs are hidden.

    //BEGIN SCREEN CONTENT.
    create_tab1(tab1);
    create_tab2(tab2);
    create_tab3(tab3);
    header_create();

    //END SCREEN CONTENT
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void navButton1Handler(lv_obj_t * obj, lv_event_t event)
{
    lv_obj_t * currentScreen = lv_scr_act(); //gets the screen.
    if ( event == LV_EVENT_PRESSED )
    {
        lv_obj_del(currentScreen);  //literally just deletes the screen.
        //screen1Init(lv_theme_night_init(63488, NULL)); //call to another file to run it's screen.
        screen3Init(lv_theme_night_init(63488, NULL));
    }
}

static void navButton2Handler(lv_obj_t * obj, lv_event_t event)
{
    lv_obj_t * currentScreen = lv_scr_act(); //gets the screen.
    if ( event == LV_EVENT_PRESSED )
    {
        lv_obj_del(currentScreen);  //literally just deletes the screen.
        screen1Init(lv_theme_night_init(63488, NULL));
    }
}


static void header_create(void)
{
    header = lv_cont_create(lv_disp_get_scr_act(NULL), NULL);
    lv_obj_set_width(header, lv_disp_get_hor_res(NULL));
    lv_obj_set_height(header, 10);

    lv_obj_t * sym = lv_label_create(header, NULL);
    lv_label_set_text(sym, LV_SYMBOL_GPS LV_SYMBOL_WIFI LV_SYMBOL_BLUETOOTH LV_SYMBOL_VOLUME_MAX);
    lv_obj_align(sym, NULL, LV_ALIGN_IN_RIGHT_MID, -LV_DPI/10, 0);

    lv_obj_t * clock = lv_label_create(header, NULL);
    lv_label_set_text(clock, "AMS: Idle");
    lv_obj_align(clock, NULL, LV_ALIGN_IN_LEFT_MID, LV_DPI/10, 0);

    //lv_cont_set_fit2(header, LV_FIT_NONE, LV_FIT_TIGHT);   /*Let the height set automatically*/
    lv_obj_set_pos(header, 0, 0);

}

static void create_tab1(lv_obj_t * parent)
{
    //Sets the styling.
    lv_page_set_scrl_layout(parent, LV_LAYOUT_PRETTY);
    
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

    lv_obj_t * label = lv_label_create(h,NULL);
    lv_label_set_text(label,"Motor Temp");

    lv_obj_t * bar = lv_bar_create(h, NULL);
    lv_obj_set_event_cb(bar, bar_event_cb);
    lv_bar_set_range(bar, 0, 300);
    lv_bar_set_anim_time(bar, 2000);
    lv_bar_set_value(bar, 100, LV_ANIM_ON);

    /* Create a label below the slider 
    //bar_value = lv_label_create(lv_scr_act(), NULL);
    //lv_label_set_text(bar_value, "6");
    lv_obj_set_auto_realign(bar_value, true);
    lv_obj_align(bar_value, bar, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);*/

    label = lv_label_create(h,NULL);
    lv_label_set_text(label,"Rineheart Temp");

    lv_obj_t * bar2 = lv_bar_create(h, NULL);
    lv_bar_set_range(bar2, 0, 300);
    lv_bar_set_anim_time(bar2, 2000);
    lv_bar_set_value(bar2, 40, LV_ANIM_ON);
    //lv_bar_set_value(bar2, 38, false);

    //animated bar
    label = lv_label_create(h,NULL);
    lv_label_set_text(label,"Accumulator Temp");

    lv_obj_t * bar3 = lv_bar_create(h,NULL);
    lv_bar_set_anim_time(bar3, 2000);
    lv_bar_set_value(bar3, 60, LV_ANIM_ON);

}

static void create_tab2(lv_obj_t * parent) //this is gonna have our nav buttons.
{
    //Sets the styling.
    lv_page_set_scrl_layout(parent, LV_LAYOUT_PRETTY);
    
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


    lv_obj_t * navButton1 = lv_btn_create(h,NULL);
    lv_obj_set_event_cb(navButton1, navButton1Handler);
    lv_obj_t * navButton1Label = lv_label_create(navButton1,NULL);
    lv_label_set_text(navButton1Label,"To Screen3.c");

    lv_obj_t * navButton2 = lv_btn_create(h,NULL);
    lv_obj_set_event_cb(navButton2, navButton2Handler);
    lv_obj_t * navButton2Label = lv_label_create(navButton2,NULL);
    lv_label_set_text(navButton2Label,"To Screen1.c");

}

static void create_tab3(lv_obj_t * parent)
{
    //Sets the styling.
    lv_page_set_scrl_layout(parent, LV_LAYOUT_PRETTY);
    
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

    lv_obj_t * label = lv_label_create(h,NULL);
    lv_label_set_text(label,"Motor Temp");

    lv_obj_t * bar = lv_bar_create(h, NULL);
    lv_obj_set_event_cb(bar, bar_event_cb);
    lv_bar_set_range(bar, 0, 300);
    lv_bar_set_anim_time(bar, 2000);
    lv_bar_set_value(bar, 100, LV_ANIM_ON);

}
#endif /*LV_USE_TESTS*/

static void bar_event_cb(lv_obj_t * bar, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        static char buf[4]; /* max 3 bytes for number plus 1 null terminating byte */
        snprintf(buf, 4, "%u", lv_slider_get_value(bar));
        lv_label_set_text(bar_value, buf);
    }
}

static void bar_set_value(lv_obj_t * bar, int16_t value)
{
    lv_bar_set_value(bar, value, LV_ANIM_OFF);
}

void lv_ex_bar_1(void)
{
    lv_obj_t * bar1 = lv_bar_create(lv_scr_act(), NULL);
    lv_obj_set_size(bar1, 200, 30);
    lv_obj_align(bar1, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_bar_set_anim_time(bar1, 1000);
    lv_bar_set_value(bar1, 100, LV_ANIM_ON);
}


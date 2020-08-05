 /**
 * @file lv_test_theme_1.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_test_theme_1.h"
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
static void create_tab1(lv_obj_t * parent,lv_obj_t * header);
static void create_tab2(lv_obj_t * parent, lv_obj_t * header);
static void bar_set_value(lv_obj_t * bar, int16_t value);
static void header_create(lv_obj_t * parent);
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
void lv_test_theme_1(lv_theme_t * th)
{
    lv_theme_set_current(th);
    th = lv_theme_get_current();    
    lv_obj_t * scr = lv_cont_create(NULL, NULL); //creates the screen scr
    lv_disp_load_scr(scr);

    lv_obj_t * tv = lv_tabview_create(scr, NULL); //allows us to add tabs in more easily later.
    //lv_obj_set_width(tv, 800);
    //lv_obj_set_height(tv, 480);
    lv_obj_set_size(tv, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_t * tab1 = lv_tabview_add_tab(tv, "Home Screen"); //tab1.
    
    lv_obj_t * tab2 = lv_tabview_add_tab(tv,"Tab2");

    lv_tabview_set_btns_hidden(tv, true); //hides the tab buttons, but allows us to implement them later on.

    create_tab1(tab1,header);
    create_tab2(tab2, header);
}

static void header_create(lv_obj_t * parent) //uses h as its parent.
{
    header = lv_cont_create(parent, NULL); //creates the header as a container.
    lv_obj_set_width(header, lv_disp_get_hor_res(NULL));
    lv_obj_align(header,parent,LV_ALIGN_CENTER,0,0);

    lv_obj_t * sym = lv_label_create(header, NULL);
    lv_label_set_text(sym, "TS 20");
    lv_obj_align(sym, NULL, LV_ALIGN_IN_RIGHT_MID, -LV_DPI/10, 0);

    lv_obj_t * ams_state = lv_label_create(header, NULL);
    lv_label_set_text(ams_state, "AMS STATE: Idle");
    lv_obj_align(ams_state, NULL, LV_ALIGN_CENTER, LV_DPI/10, 0);

    lv_obj_t * clock = lv_label_create(header, NULL);
    lv_label_set_text(clock, "RUN TIME: 0");
    lv_obj_align(clock, NULL, LV_ALIGN_IN_LEFT_MID, LV_DPI/10, 0);

    lv_cont_set_fit2(header, LV_FIT_NONE, LV_FIT_TIGHT);   /*Let the height set automatically*/
    lv_obj_set_pos(header,0,0);

}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void create_tab1(lv_obj_t * parent, lv_obj_t * header)
{
    //Sets the styling.
    lv_page_set_scrl_layout(parent, LV_LAYOUT_CENTER);

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
     *******************************************************/

    /* Call the header create function, using h as its parent. */
    header_create(h);
    //lv_obj_align(h, );

    lv_obj_t * label1 = lv_label_create(h,NULL);
    lv_label_set_text(label1,"Battery        ");

    lv_obj_t * bar = lv_bar_create(h, NULL);
    lv_obj_set_event_cb(bar, bar_event_cb);
    lv_bar_set_anim_time(bar, 2000);
    lv_bar_set_value(bar, 100, LV_ANIM_ON);

    /* Create a label below the slider */
    bar_value = lv_label_create(label1,NULL);
    lv_label_set_text(bar_value, "100");
    lv_obj_align(bar_value,label1,LV_ALIGN_IN_RIGHT_MID,0,0);

    //Rineheart temp Label
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

}

static void create_tab2(lv_obj_t * parent, lv_obj_t * header)
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

    /********************************************************
     * The above h is out container for all our widgets.
     * When creating a new widget, if we use h as the parent
     * they will all align nicely, and then we can fine tune
     * using the align functionality of lvgl.
     *******************************************************/

    /* Call the header create function, using h as its parent. */
    header_create(h);

    lv_coord_t w = lv_page_get_scrl_width(parent);

    lv_obj_t * chart = lv_chart_create(parent, NULL);
    lv_chart_set_type(chart, LV_CHART_TYPE_AREA);
    lv_obj_set_size(chart, w / 3, lv_disp_get_ver_res(NULL) / 3);
    lv_obj_set_pos(chart, LV_DPI / 10, LV_DPI / 10);
    lv_chart_series_t * s1 = lv_chart_add_series(chart, LV_COLOR_RED);
    lv_chart_set_next(chart, s1, 30);
    lv_chart_set_next(chart, s1, 20);
    lv_chart_set_next(chart, s1, 10);
    lv_chart_set_next(chart, s1, 12);
    lv_chart_set_next(chart, s1, 20);
    lv_chart_set_next(chart, s1, 27);
    lv_chart_set_next(chart, s1, 35);
    lv_chart_set_next(chart, s1, 55);
    lv_chart_set_next(chart, s1, 70);
    lv_chart_set_next(chart, s1, 75);

    lv_obj_t * ch_label = lv_label_create(chart ,NULL);
    lv_label_set_text(ch_label, "Battery Consumption ");
    lv_obj_align(ch_label,chart,LV_ALIGN_IN_TOP_MID,0,0);


    lv_obj_t * gauge = lv_gauge_create(parent, NULL);
    lv_gauge_set_value(gauge, 0, 40);
    lv_obj_set_size(gauge, w / 4, w / 4);
    lv_obj_align(gauge, chart, LV_ALIGN_OUT_BOTTOM_LEFT, 0, LV_DPI / 4);

    lv_obj_t * gauge_label = lv_label_create(gauge ,NULL);
    lv_label_set_text(gauge_label, "Motor Temps ");
    lv_obj_align(gauge_label,gauge,LV_ALIGN_IN_BOTTOM_MID,0,0);


    lv_obj_t * sw_h = lv_cont_create(h, NULL);
    lv_cont_set_style(sw_h, LV_CONT_STYLE_MAIN, &lv_style_transp);
    lv_cont_set_fit2(sw_h, LV_FIT_NONE, LV_FIT_TIGHT);
    lv_obj_set_width(sw_h, LV_HOR_RES / 4);
    lv_cont_set_layout(sw_h, LV_LAYOUT_PRETTY);

    lv_obj_t * sw = lv_sw_create(sw_h, NULL);
    lv_sw_set_anim_time(sw, 250);

    lv_obj_t * sw_label = lv_label_create(sw_h ,NULL);
    lv_label_set_text(sw_label, "Traction Control ");
    lv_obj_align(sw_label,sw_h,LV_ALIGN_IN_TOP_MID,0,0);

    //sw = lv_sw_create(sw_h, sw);
    //lv_sw_on(sw, LV_ANIM_OFF);

}

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


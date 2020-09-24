/**
  ******************************************************************************
  * @file    menu.c
  * @author  Andrew Gray, Christian Lazarovski, Tansel Kahrahman
  * @version V1.0
  * @date    02-09-2020
  * @brief   Menu screens, intitial screen on startup with important information
  * regarding hardware status.
  ******************************************************************************
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
#include <math.h>

/*********************
 *      DEFINES
 *********************/

/*********************
 *      EXTERN
 *      VARIABLES
 *********************/
extern float max_accum_temp;
extern uint16_t accum_lowest_voltage;
extern uint16_t motor_highest_temp;
extern uint16_t rineheart_highest_temp;
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

static void navButton1Handler(lv_obj_t * obj, lv_event_t event);
static void navButton2Handler(lv_obj_t * obj, lv_event_t event);
static void navButton3Handler(lv_obj_t * obj, lv_event_t event);

static void value_handler(lv_task_t * task);
static void test_iterator(lv_task_t * task);
/**********************
 *  STATIC VARIABLES
 **********************/
static lv_task_t * value_handle;
static lv_task_t * iterate;

static lv_obj_t * header;
static lv_obj_t * slider_label;

static lv_obj_t * motor_bar;
static lv_obj_t * motor_temp_value;

static lv_obj_t * rineheart_bar;
static lv_obj_t * rineheart_temp_label;

static lv_obj_t * accum_temp;
static lv_obj_t * accum_temp_label;

static lv_obj_t * accum_volt;
static lv_obj_t * accum_volt_label;

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
    lv_obj_set_pos(tv, 0,30);
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

static void create_tab1(lv_obj_t * parent)
{
    //Sets the styling.    
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
    lv_obj_align(h, parent, LV_ALIGN_IN_TOP_LEFT, 100, 20);

    lv_obj_t * motorTempLabel = lv_label_create(h,NULL);
    lv_label_set_text(motorTempLabel,"Motor Temp");

    motor_bar = lv_bar_create(h, NULL);
    lv_bar_set_range(motor_bar, 0, 300);
    lv_bar_set_anim_time(motor_bar, 2000);
    lv_bar_set_value(motor_bar, 0, LV_ANIM_ON);

    motor_temp_value = lv_label_create(parent, NULL);
    lv_label_set_text_fmt(motor_temp_value, "%u", lv_bar_get_value(motor_temp_value));
    lv_obj_set_pos(motor_temp_value, 20, 65);

    lv_obj_t * rineheart_label = lv_label_create(h,NULL);
    lv_label_set_text(rineheart_label,"Rineheart Temp");

    rineheart_bar = lv_bar_create(h, NULL);
    lv_bar_set_range(rineheart_bar, 0, 300);
    lv_bar_set_anim_time(rineheart_bar, 2000);
    lv_bar_set_value(rineheart_bar, 0, LV_ANIM_ON);

    rineheart_temp_label = lv_label_create(parent, NULL);
    lv_label_set_text(rineheart_temp_label, "0");
    lv_obj_set_pos(rineheart_temp_label, 20, 137);

    lv_obj_t * accum_label = lv_label_create(h,NULL);
    lv_label_set_text(accum_label,"Accumulator Temp");

    accum_temp = lv_bar_create(h,NULL);
    lv_bar_set_anim_time(accum_temp, 2000);
    lv_bar_set_value(accum_temp, 0, LV_ANIM_ON);

    accum_temp_label = lv_label_create(parent, NULL);
    lv_label_set_text(accum_temp_label, "0");
    lv_obj_set_pos(accum_temp_label, 20, 210);

    lv_obj_t * h2 = lv_cont_create(parent, NULL); 
    lv_obj_set_style(h2, &h_style);
    lv_obj_set_click(h2, false);
    lv_cont_set_fit(h2, LV_FIT_TIGHT);
    lv_cont_set_layout(h2, LV_LAYOUT_COL_M);
    lv_obj_align(h2, parent, LV_ALIGN_IN_TOP_LEFT, 320, 20);

    lv_obj_t * accum_vert_label = lv_label_create(h2,NULL);
    lv_label_set_text(accum_vert_label,"Accumulator Voltage");

    accum_volt = lv_bar_create(h2,NULL);
    lv_bar_set_anim_time(accum_volt, 2000);
    lv_bar_set_value(accum_volt, 0, LV_ANIM_ON);
    lv_obj_set_size(accum_volt, 35, 180);

    accum_volt_label = lv_label_create(h2,NULL);
    lv_label_set_text(accum_volt_label,"0");

    value_handle = lv_task_create(value_handler,1000,LV_TASK_PRIO_MID,NULL);

    iterate = lv_task_create(test_iterator,100,LV_TASK_PRIO_MID,NULL);

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
    lv_label_set_text(navButton1Label,"To Screen1.c");

    lv_obj_t * navButton2 = lv_btn_create(h,NULL);
    lv_obj_set_event_cb(navButton2, navButton2Handler);
    lv_obj_t * navButton2Label = lv_label_create(navButton2,NULL);
    lv_label_set_text(navButton2Label,"To Screen2.c");

    lv_obj_t * navButton3 = lv_btn_create(h,NULL);
    lv_obj_set_event_cb(navButton3, navButton3Handler);
    lv_obj_t * navButton3Label = lv_label_create(navButton3,NULL);
    lv_label_set_text(navButton3Label,"To Screen3.c");
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

    lv_obj_t * slider1 = lv_slider_create(h,NULL);
    lv_obj_t * slider2 = lv_slider_create(h,NULL);

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

static void test_iterator(lv_task_t * task)
{
    rineheart_highest_temp ++;
    accum_lowest_voltage ++;
    motor_highest_temp ++;
    max_accum_temp ++;
    
    if (motor_highest_temp == 200)
    {
        rineheart_highest_temp = 0;
        accum_lowest_voltage = 0;
        motor_highest_temp = 0;
        max_accum_temp = 0;
    }
}

static void value_handler(lv_task_t * task)
{
    if(lv_bar_get_value(motor_bar)!= motor_highest_temp)
    {
        char temp[10] = "";
        sprintf(temp,"%u",motor_highest_temp);
        lv_bar_set_value(motor_bar,motor_highest_temp,LV_ANIM_ON);
        lv_label_set_text(motor_temp_value,temp);
    }

    if (lv_bar_get_value(accum_temp) != max_accum_temp)
    {
        int temperature = max_accum_temp; //convert to an int for printing purposes.
        char temp[] = "";
        sprintf(temp,"%i",temperature);
        lv_bar_set_value(accum_temp,max_accum_temp,LV_ANIM_ON);
        lv_label_set_text(accum_temp_label,temp);
        printf(temp);
    }

    if(lv_bar_get_value(accum_volt)!= accum_lowest_voltage)
    {
        char temp[] = "";
        sprintf(temp,"%u",accum_lowest_voltage);
        lv_bar_set_value(accum_volt,accum_lowest_voltage,LV_ANIM_ON);
        lv_label_set_text(accum_volt_label,temp);
    }

    if (lv_bar_get_value(rineheart_bar) != rineheart_highest_temp)
    {
        char temp[] = "";
        sprintf(temp,"%u",motor_highest_temp);
        lv_bar_set_value(rineheart_bar,rineheart_highest_temp,LV_ANIM_ON);
        lv_label_set_text(rineheart_temp_label,temp);
    }
}

static void navButton1Handler(lv_obj_t * obj, lv_event_t event)
{
    lv_obj_t * currentScreen = lv_scr_act(); //gets the screen.
    if ( event == LV_EVENT_RELEASED)
    {
        lv_task_del(iterate);
        lv_task_del(value_handle);
        lv_obj_del(currentScreen);  //literally just deletes the screen.
        screen1Init(lv_theme_night_init(63488, NULL));
    }
}

static void navButton2Handler(lv_obj_t * obj, lv_event_t event)
{
    lv_obj_t * currentScreen = lv_scr_act(); //gets the screen.
    if ( event == LV_EVENT_RELEASED)
    {
        lv_task_del(iterate);
        lv_task_del(value_handle);
        lv_obj_del(currentScreen);  //literally just deletes the screen.
        screen2Init(lv_theme_night_init(63488, NULL));
    }
}

static void navButton3Handler(lv_obj_t * obj, lv_event_t event)
{
    lv_obj_t * currentScreen = lv_scr_act(); //gets the screen.
    if ( event == LV_EVENT_RELEASED)
    {
        lv_task_del(iterate);
        lv_task_del(value_handle);
        lv_obj_del(currentScreen);  //literally just deletes the screen.
        screen3Init(lv_theme_night_init(63488, NULL));
    }
}



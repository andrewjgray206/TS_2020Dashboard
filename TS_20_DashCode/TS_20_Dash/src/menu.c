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
#include "common.h"

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
extern int ams_state;
extern bool precharge_pressed;
extern bool drive_pressed;
extern float max_accum_temp;
extern uint16_t accum_lowest_voltage;
extern uint16_t motor_highest_temp;
extern uint16_t rineheart_highest_temp;

extern lv_obj_t * driveWarningLine;
extern lv_obj_t * prechargeWarningLine;
extern lv_style_t style_line;
extern lv_point_t line_points[];
extern lv_obj_t * header;
extern lv_obj_t * ams_label;
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void create_tab1(lv_obj_t * parent);
static void create_tab2(lv_obj_t * parent);
static void create_tab3(lv_obj_t * parent);


static void navButton1Handler(lv_obj_t * obj, lv_event_t event);
static void navButton2Handler(lv_obj_t * obj, lv_event_t event);
static void navButton3Handler(lv_obj_t * obj, lv_event_t event);

extern void ams_task_handler(lv_task_t * task);
extern void can_test_iterator(lv_task_t * task);
extern void draw_precharge_warning();
extern void draw_drive_warning();
extern void header_create();
/**********************
 *  STATIC VARIABLES
 **********************/
extern lv_task_t * task_handler;
extern lv_task_t * can_message_iterator;

extern lv_obj_t * header;
extern lv_obj_t * slider_label;

extern lv_obj_t * motor_bar;
extern lv_obj_t * motor_temp_value;

extern lv_obj_t * rineheart_bar;
extern lv_obj_t * rineheart_temp_label;

extern lv_obj_t * accum_temp;
extern lv_obj_t * accum_temp_label;

extern lv_obj_t * accum_volt;
extern lv_obj_t * accum_volt_label;

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
    lv_bar_set_range(motor_bar, 0, 80);
    lv_bar_set_anim_time(motor_bar, 500);
    lv_bar_set_value(motor_bar, 0, LV_ANIM_ON);

    motor_temp_value = lv_label_create(parent, NULL);
    lv_label_set_text_fmt(motor_temp_value, "%u", lv_bar_get_value(motor_temp_value));
    lv_obj_set_pos(motor_temp_value, 20, 65);

    lv_obj_t * rineheart_label = lv_label_create(h,NULL);
    lv_label_set_text(rineheart_label,"Rineheart Temp");

    rineheart_bar = lv_bar_create(h, NULL);
    lv_bar_set_range(rineheart_bar, 0, 80);
    lv_bar_set_anim_time(rineheart_bar, 500);
    lv_bar_set_value(rineheart_bar, 0, LV_ANIM_ON);

    rineheart_temp_label = lv_label_create(parent, NULL);
    lv_label_set_text(rineheart_temp_label, "0");
    lv_obj_set_pos(rineheart_temp_label, 20, 137);

    lv_obj_t * accum_label = lv_label_create(h,NULL);
    lv_label_set_text(accum_label,"Accumulator Temp");

    accum_temp = lv_bar_create(h,NULL);
    lv_bar_set_range(accum_temp, 0, 80);
    lv_bar_set_anim_time(accum_temp, 500);
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
    lv_bar_set_range(accum_volt, 0, 600);
    lv_bar_set_anim_time(accum_volt, 500);
    lv_bar_set_value(accum_volt, 0, LV_ANIM_ON);
    lv_obj_set_size(accum_volt, 35, 180);

    accum_volt_label = lv_label_create(h2,NULL);
    lv_label_set_text(accum_volt_label,"0");

    //ALARM BOX
    lv_style_copy(&style_line, &lv_style_plain);
    style_line.line.color = LV_COLOR_RED;
    style_line.line.width = 10;
    style_line.line.rounded = 1;

    warning_lines();

    task_handler = lv_task_create(ams_task_handler,1000,LV_TASK_PRIO_MID,NULL);
    can_message_iterator = lv_task_create(can_test_iterator,1000,LV_TASK_PRIO_MID,NULL);

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

static void can_test_iterator2(lv_task_t * task)
/* NOTE: When implementing with real CAN messages
* This function can be deleted or commented out.
* As all it does is simulate can messages
* for simulation testing. */
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

    ams_state = ams_state + 1; // for ams state
    if (ams_state == 8)
    {
        ams_state = 0;
    }
    switch (precharge_pressed)
    {
    case 0:
        precharge_pressed = 1;
        break;
    
    case 1:
        precharge_pressed = 0;
        break;
    }

    switch (drive_pressed)
    {
    case 0:
        drive_pressed = 1;
        break;
    
    case 1:
        drive_pressed = 0;
        break;
    }    
}


static void ams_task_handler2(lv_task_t * task)
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

    switch(ams_state){ //looks at the AMS_state can signal.
        case 0:
            lv_label_set_text(ams_label,"AMS STATE: 0 IDLE");
        break;
        case 1:
            lv_label_set_text(ams_label,"AMS STATE: 1 Precharge Waiting");
        break;
        case 2:
            lv_label_set_text(ams_label,"AMS STATE: 2 Precharging");
        break;
        case 3:
            lv_label_set_text(ams_label,"AMS STATE: 3 Waiting for Drive");
        break;
        case 4:
            lv_label_set_text(ams_label,"AMS STATE: 4 DRIVE");
        break;
        case 7:
            lv_label_set_text(ams_label,"AMS STATE: 7 Error");
    }

    //START PRECHARGE AND DRIVE PRESSED CHECKS.
    
    switch (precharge_pressed)
    {
        case 0:
            lv_obj_set_hidden(prechargeWarningLine,true);
        break;
        
        case 1:
            draw_precharge_warning();
        break;
    }
    
    switch (drive_pressed)
    {
        case 0:
            lv_obj_set_hidden(driveWarningLine,true);
        break;
        
        case 1:
            draw_drive_warning();
        break;

    }
}

static void navButton1Handler(lv_obj_t * obj, lv_event_t event)
{
    lv_obj_t * currentScreen = lv_scr_act(); //gets the screen.
    if ( event == LV_EVENT_RELEASED)
    {
        lv_task_del(can_message_iterator);
        lv_task_del(task_handler);
        lv_obj_del(currentScreen);  //literally just deletes the screen.
        screen1Init(lv_theme_night_init(63488, NULL));
    }
}

static void navButton2Handler(lv_obj_t * obj, lv_event_t event)
{
    lv_obj_t * currentScreen = lv_scr_act(); //gets the screen.
    if ( event == LV_EVENT_RELEASED)
    {
        lv_task_del(can_message_iterator);
        lv_task_del(task_handler);
        lv_obj_del(currentScreen);  //literally just deletes the screen.
        screen2Init(lv_theme_night_init(63488, NULL));
    }
}

static void navButton3Handler(lv_obj_t * obj, lv_event_t event)
{
    lv_obj_t * currentScreen = lv_scr_act(); //gets the screen.
    if ( event == LV_EVENT_RELEASED)
    {
        lv_task_del(can_message_iterator);
        lv_task_del(task_handler);
        lv_obj_del(currentScreen);  //literally just deletes the screen.
        screen3Init(lv_theme_night_init(63488, NULL));
    }
}

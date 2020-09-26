/**
 * @file screen3.c
 *
 */

/**
  ******************************************************************************
  * @file    screen1.c
  * @author  Andrew Gray, Christian Lazarovski, Tansel Kahrahman
  * @version V1.1
  * @date    02-09-2020
  * @brief   Main Screen #3.
  ******************************************************************************
*/

/*********************
 *      INCLUDES
 *********************/
#include "menu.h"
#include "screen3.h"
#include "common.h"
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
 * PROTOTYPES
 **********************/
static void btn_event(lv_obj_t * obj, lv_event_t event); //btn1 event.
extern void ams_task_handler(lv_task_t * task);
extern void can_test_iterator(lv_task_t * task);
extern void header_create();

/**********************
 *  STATIC VARIABLES
 * NOTE---- THOSE VALUES BEING CHANGED BY THE CAN SHOULD BE STATIC
 * AND GLOBAL FOR EASY ACCESS BETWEEN FUNCTIONS.
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

/***********************
 * EXTERNAL VARIABLES 
 **********************/
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
    lv_theme_set_current(th);
    th = lv_theme_get_current();    
    lv_obj_t * scr = lv_cont_create(NULL, NULL);
    lv_disp_load_scr(scr);

    lv_obj_t * win = lv_win_create(scr,NULL); 
    lv_win_set_title(win,"");
    header_create();
    
    static lv_style_t h_style;
    lv_style_copy(&h_style, &lv_style_transp);
    h_style.body.padding.inner = LV_DPI / 10;
    h_style.body.padding.left = LV_DPI / 4; 
    h_style.body.padding.right = LV_DPI / 4;
    h_style.body.padding.top = LV_DPI / 10;
    h_style.body.padding.bottom = LV_DPI / 10;
    //END SCREEN SETUP

    lv_obj_t * h = lv_cont_create(win, NULL); 
    lv_obj_set_style(h, &h_style);
    lv_obj_set_click(h, false);
    lv_cont_set_fit(h, LV_FIT_TIGHT);
    lv_cont_set_layout(h, LV_LAYOUT_COL_M);
    lv_obj_align(h, win, LV_ALIGN_IN_TOP_LEFT, 100, 20);
    
    //START MENU RIBBON BUTTONS
    lv_obj_t * close_btn = lv_win_add_btn(win, LV_SYMBOL_CLOSE);  /*Add close button and use built-in close action*/
    lv_obj_set_event_cb(close_btn, btn_event);
    lv_win_set_btn_size(win, 30);

    lv_obj_t * motorTempLabel = lv_label_create(h,NULL);
    lv_label_set_text(motorTempLabel,"Motor Temp");

    motor_bar = lv_bar_create(h, NULL);
    lv_bar_set_range(motor_bar, 0, 80);
    lv_bar_set_anim_time(motor_bar, 500);
    lv_bar_set_value(motor_bar, 0, LV_ANIM_ON);

    motor_temp_value = lv_label_create(h, NULL);
    lv_label_set_text_fmt(motor_temp_value, "%u", lv_bar_get_value(motor_temp_value));
    lv_obj_set_pos(motor_temp_value, 20, 65);

    lv_obj_t * rineheart_label = lv_label_create(h,NULL);
    lv_label_set_text(rineheart_label,"Rineheart Temp");

    rineheart_bar = lv_bar_create(h, NULL);
    lv_bar_set_range(rineheart_bar, 0, 80);
    lv_bar_set_anim_time(rineheart_bar, 500);
    lv_bar_set_value(rineheart_bar, 0, LV_ANIM_ON);

    rineheart_temp_label = lv_label_create(h, NULL);
    lv_label_set_text(rineheart_temp_label, "0");
    lv_obj_set_pos(rineheart_temp_label, 20, 137);

    lv_obj_t * accum_label = lv_label_create(h,NULL);
    lv_label_set_text(accum_label,"Accumulator Temp");

    accum_temp = lv_bar_create(h,NULL);
    lv_bar_set_range(accum_temp, 0, 80);
    lv_bar_set_anim_time(accum_temp, 500);
    lv_bar_set_value(accum_temp, 0, LV_ANIM_ON);

    accum_temp_label = lv_label_create(h, NULL);
    lv_label_set_text(accum_temp_label, "0");
    lv_obj_set_pos(accum_temp_label, 20, 210);

    lv_obj_t * h2 = lv_cont_create(win, NULL); 
    lv_obj_set_style(h2, &h_style);
    lv_obj_set_click(h2, false);
    lv_cont_set_fit(h2, LV_FIT_TIGHT);
    lv_cont_set_layout(h2, LV_LAYOUT_COL_M);
    lv_obj_align(h2, win, LV_ALIGN_IN_TOP_LEFT, 320, 20);

    lv_obj_t * accum_vert_label = lv_label_create(h2,NULL);
    lv_label_set_text(accum_vert_label,"Accumulator Voltage");

    accum_volt = lv_bar_create(h2,NULL);
    lv_bar_set_range(accum_volt, 0, 600);
    lv_bar_set_anim_time(accum_volt, 500);
    lv_bar_set_value(accum_volt, 0, LV_ANIM_ON);
    lv_obj_set_size(accum_volt, 35, 180);

    accum_volt_label = lv_label_create(h2,NULL);
    lv_label_set_text(accum_volt_label,"0");

    warning_lines();

    //START TASK CREATION.
    task_handler = lv_task_create(ams_task_handler,10,LV_TASK_PRIO_LOW,NULL);
    can_message_iterator = lv_task_create(can_test_iterator,1000,LV_TASK_PRIO_MID,NULL);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void btn_event(lv_obj_t * obj, lv_event_t event)
/* This function contains the event handler for a button.
*  in this case it's button one, and all it's used to do
*  is close the screen and navigate to another one. */
{
    lv_obj_t * currentScreen = lv_scr_act(); //gets the screen.
    if ( event == LV_EVENT_RELEASED)
    {
        lv_task_del(task_handler);
        lv_task_del(can_message_iterator);
        lv_obj_del(currentScreen);  //literally just deletes the screen.
        menuInit(lv_theme_night_init(63488, NULL)); //call to another file to run it's screen.
    }
}
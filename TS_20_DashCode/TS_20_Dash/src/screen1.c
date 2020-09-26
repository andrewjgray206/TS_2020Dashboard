/**
 * @file screen1.c
 *
 */

/**
  ******************************************************************************
  * @file    screen1.c
  * @author  Andrew Gray, Christian Lazarovski, Tansel Kahrahman
  * @version V1.0
  * @date    02-09-2020
  * @brief   Main Screen #1.
  ******************************************************************************
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
static void header_create();
static void btn_event(lv_obj_t * obj, lv_event_t event); //btn1 event.
static void ams_task_handler(lv_task_t * task);
static void can_test_iterator(lv_task_t * task);

/**********************
 *  STATIC VARIABLES
 * NOTE---- THOSE VALUES BEING CHANGED BY THE CAN SHOULD BE STATIC
 * AND GLOBAL FOR EASY ACCESS BETWEEN FUNCTIONS.
 **********************/
static lv_obj_t * header;
static lv_obj_t * ams_label;
static lv_task_t * task;
static lv_task_t * testIterator;
static lv_obj_t * driveWarningLine;
static lv_obj_t * prechargeWarningLine;

static lv_style_t style_line;
static lv_point_t line_points[] = {{0,0},{800,0},{800, 480},{0, 480},{0,0}};

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

/***********************
 * EXTERNAL VARIABLES 
 * (CAN SIGNALS)
 **********************/
extern int ams_state;
extern bool precharge_pressed;
extern bool drive_pressed;
extern int ams_state;
extern bool precharge_pressed;
extern bool drive_pressed;
extern float max_accum_temp;
extern uint16_t accum_lowest_voltage;
extern uint16_t motor_highest_temp;
extern uint16_t rineheart_highest_temp;

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
void screen1Init(lv_theme_t * th) //sets the screen up.
{
    /* This integration of LVGL V6 uses a window view
    * with buttons to navigate between screens. (hopefully)
    * The window is the main object, becoming the parent for everything
    * else drawn on the screen. From here i currently don't know
    * how to align stuff on its own, so i'm doing it manually.
    * Have fun sussing!
    * Note: This window view is what's going to be used for
    * each of the "event" screens, using top ribbon buttons
    * for navigation.*/

   /* When drawing a new screen, the screen object needs to be created
   * or else the Window view doensn't have a screen parent. This is important
   * to note for when we make more screens, these next lines of code
   * will make for creating a screen from scratch, successfully. */
  
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

    //ALARM BOX
    lv_style_copy(&style_line, &lv_style_plain);
    style_line.line.color = LV_COLOR_RED;
    style_line.line.width = 10;
    style_line.line.rounded = 1;

    driveWarningLine = lv_line_create(lv_scr_act(), NULL);
    lv_obj_set_hidden(driveWarningLine,true); //start as hidden.
    lv_line_set_points(driveWarningLine, line_points, 5);//Set the points

    prechargeWarningLine = lv_line_create(lv_scr_act(),NULL);
    lv_obj_set_hidden(prechargeWarningLine,true); //start as hidden.
    lv_line_set_points(prechargeWarningLine, line_points, 5);//Set the points

    //START TASK CREATION.
    task = lv_task_create(ams_task_handler,10,LV_TASK_PRIO_LOW,NULL);
    testIterator = lv_task_create(can_test_iterator,1000,LV_TASK_PRIO_MID,NULL);

}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void draw_precharge_warning()
//UNFINISHED IMPLMENETAION, ANDREW WILL GET BACK TO THIS.
{
    style_line.line.color = LV_COLOR_ORANGE;
    lv_line_set_style(prechargeWarningLine, LV_LINE_STYLE_MAIN, &style_line);
    lv_obj_set_hidden(prechargeWarningLine,false);
}

static void draw_drive_warning()
{
    style_line.line.color = LV_COLOR_GREEN;
    lv_line_set_style(driveWarningLine, LV_LINE_STYLE_MAIN, &style_line);
    lv_obj_set_hidden(driveWarningLine,false);
}


static void can_test_iterator(lv_task_t * task)
/* NOTE: When implementing with real CAN messages
* This function can be deleted or commented out.
* As all it does is simulate can messages
* for simulation testing. */
{
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

static void ams_task_handler(lv_task_t * task)
{

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

static void btn_event(lv_obj_t * obj, lv_event_t event)
/* This function contains the event handler for a button.
*  in this case it's button one, and all it's used to do
*  is close the screen and navigate to another one. */
{
    lv_obj_t * currentScreen = lv_scr_act(); //gets the screen.
    if ( event == LV_EVENT_RELEASED)
    {
        lv_task_del(task);
        lv_task_del(testIterator);
        lv_obj_del(currentScreen);  //literally just deletes the screen.
        menuInit(lv_theme_night_init(63488, NULL)); //call to another file to run it's screen.
    }
}

static void header_create()
{
    header = lv_cont_create(lv_disp_get_scr_act(NULL), NULL);
    lv_obj_set_width(header, lv_disp_get_hor_res(NULL) - 30);
    lv_obj_set_height(header, 30);

    ams_label = lv_label_create(header, NULL);
    lv_label_set_text(ams_label, "AMS STATE: 0 Idle");
    lv_obj_align(ams_label, NULL, LV_ALIGN_CENTER, LV_DPI/10, 0);


    lv_obj_t * sym = lv_label_create(header, NULL);
    lv_label_set_text(sym, "TS 20");
    lv_obj_align(sym, NULL, LV_ALIGN_IN_RIGHT_MID, -LV_DPI/10, 0);

    lv_obj_t * clock = lv_label_create(header, NULL);
    lv_label_set_text(clock, "RUN TIME: 0");
    lv_obj_align(clock, NULL, LV_ALIGN_IN_LEFT_MID, LV_DPI/10, 0);

    //lv_cont_set_fit2(header, LV_FIT_NONE, LV_FIT_TIGHT);   /*Let the height set automatically*/
    lv_obj_set_pos(header, 0, 0);
}
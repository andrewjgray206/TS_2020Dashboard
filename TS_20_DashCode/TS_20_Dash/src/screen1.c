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
static lv_obj_t * header_create();
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
static lv_obj_t * warningLine;

//UNFINISHED IMPLMENETAION, ANDREW WILL GET BACK TO THIS.
//static lv_style_t style_line;
//static lv_point_t line_points[] = {{0,0},{500,0},{500, 300},{0, 300},{0,0}};

/***********************
 * EXTERNAL VARIABLES 
 * (CAN SIGNALS)
 **********************/
extern int ams_state;
extern bool precharge_pressed;
extern bool drive_pressed;


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
  
  //START SCREEN SETUP
    lv_theme_set_current(th);
    th = lv_theme_get_current();    
    lv_obj_t * scr = lv_cont_create(NULL, NULL);
    lv_disp_load_scr(scr);

    lv_obj_t * win = lv_win_create(scr,NULL); 
    lv_win_set_title(win,"");
    lv_obj_t * amsLabel = header_create();

    //END SCREEN SETUP
    //START MENU RIBBON BUTTONS
    lv_obj_t * close_btn = lv_win_add_btn(win, LV_SYMBOL_CLOSE);  /*Add close button and use built-in close action*/
    lv_obj_set_event_cb(close_btn, btn_event);
    lv_win_set_btn_size(win, 30);

    //END MENU RIBBON BUTTONS
    //START SCREEN CONTENT.
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


    //START TASK CREATION.
    task = lv_task_create(ams_task_handler,5,LV_TASK_PRIO_LOW,NULL);
    testIterator = lv_task_create(can_test_iterator,1000,LV_TASK_PRIO_MID,NULL);

}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*static void draw_precharge_warning()
//UNFINISHED IMPLMENETAION, ANDREW WILL GET BACK TO THIS.
{
    lv_style_copy(&style_line, &lv_style_plain);
    style_line.line.width = 10;
    style_line.line.rounded = 1;

    warningLine = lv_line_create(lv_scr_act(), NULL);
    lv_line_set_points(warningLine, line_points, 5);     /*Set the points
    lv_line_set_style(warningLine, LV_LINE_STYLE_MAIN, &style_line);
}*/
/*
static void draw_drive_warning()
//UNFINISHED IMPLMENETAION, ANDREW WILL GET BACK TO THIS.

{
    style_line.line.color = LV_COLOR_GREEN;
}
*/
static void can_test_iterator(lv_task_t * task)
{
    ams_state = ams_state + 1; // for ams state
    if (ams_state == 8){
        ams_state = 0;
    }
    /*switch (precharge_pressed)
    //UNFINISHED IMPLMENETAION, ANDREW WILL GET BACK TO THIS.

    {
    case 0:
        precharge_pressed =1;
        break;
    
    case 1:
        precharge_pressed = 0;
        break;
    }*/
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
    //UNFINISHED IMPLMENETAION, ANDREW WILL GET BACK TO THIS.

    /*switch (precharge_pressed)
    {
    case 0:
        lv_obj_set_hidden(warningLine,true);
        break;
    
    case 1:
        lv_obj_set_hidden(warningLine,false);
        break;
    }*/
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

static lv_obj_t * header_create()
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

    return ams_label;
}
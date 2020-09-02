/**
 * @file screen1.c
 *
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
static void btn_event(lv_obj_t * obj, lv_event_t event); //btn1 event.

/**********************
 *  STATIC VARIABLES
 **********************/

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
    lv_win_set_title(win,"Hello ts_20");

    //END SCREEN SETUP
    //START MENU RIBBON BUTTONS
    lv_obj_t * btn1 = lv_win_add_btn(win,LV_SYMBOL_DIRECTORY); 
    //lv_obj_t * btn2 = lv_win_add_btn(win,LV_SYMBOL_WIFI); 

    lv_obj_set_event_cb(btn1,btn_event); //each button needs it's own event function.

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
    if ( event == LV_EVENT_PRESSED )
    {
        lv_obj_del(currentScreen);  //literally just deletes the screen.
        menuInit(lv_theme_night_init(63488, NULL)); //call to another file to run it's screen.
    }
}

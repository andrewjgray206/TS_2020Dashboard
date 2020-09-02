/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/



#include <stdlib.h>
#include <unistd.h>

#include "lvgl.h"
#include "driver.h"

#include "ts_2020Dash.h"
#include "lv_test_theme_1.h"
#include "lv_test_window.h"

//static void hal_init(void);
//static int tick_thread(void *data); //explicit declarations.
static void dashInit(lv_theme_t *data);
static void lv_test_window(lv_theme_t * data);
void win_test(void);

int main(void)
{
	lv_init();

	hw_init();

  //uncomment to test andys screen
  //dashInit(lv_theme_night_init(63488, NULL)); //run the dash code.

  //uncomment for main menu tabview screen
  //lv_test_theme_1(lv_theme_night_init(63488, NULL));

  //uncomment for christian's static dash under dev
  //lv_test_window(lv_theme_night_init(63488, NULL));

  //uncomment to test closing screens
  win_test();
 
	hw_loop();
}

/**
  ******************************************************************************
  * @file    main.c
  * @author  Andrew Gray, Christian Lazarovski, Tansel Kahrahman
  * @version V1.1
  * @date    02-09-2020
  * @brief   Default main function with splashscreen and menu call.
  ******************************************************************************
*/

//test

#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "lvgl.h"
#include "driver.h"

#include "menu.h"
#include "splash.h"

#include "screen1.h"
#include "screen2.h"
#include "screen3.h"

#include <unistd.h>


int main(void)
{
	lv_init();
	hw_init();
  
  load_splash();

  for (int i = 0; i < 2000; i++) {
    lv_task_handler();
    HAL_Delay(1);
  }
   

  
  

  //runs the main menu, the hub of our dashboard.
  menuInit(lv_theme_night_init(63488, NULL));
  //screen2Init(lv_theme_night_init(63488, NULL));
 
	hw_loop();

  menuInit(lv_theme_night_init(63488, NULL));   //runs the main menu, the hub of our dashboard.
	hw_loop();
  return 0;
}

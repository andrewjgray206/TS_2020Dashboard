/**
  ******************************************************************************
  * @file    main.c
  * @author  Andrew Gray, Christian Lazarovski, Tansel Kahrahman
  * @version V1.0
  * @date    02-09-2020
  * @brief   Default main function.
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


int main(void)
{
	lv_init();
	hw_init();
  
  load_splash();
  int i = 0;
  while(i < 350) //3.5 seconds total.
  {
      lv_task_handler();
      usleep(10000); // 1 second.
      i++;
  } 

  menuInit(lv_theme_night_init(63488, NULL));   //runs the main menu, the hub of our dashboard.
 
	hw_loop();
  return 0;
}

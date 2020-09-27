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

#include "lvgl.h"
#include "driver.h"

#include "menu.h"

#include "screen1.h"
#include "screen2.h"
#include "screen3.h"

int main(void)
{
	lv_init();
	hw_init();
  

  //I wanna make a splash screen, that function will go here.
  //splashScreen(blah blah);

  //runs the main menu, the hub of our dashboard.
  menuInit(lv_theme_night_init(63488, NULL));
  //screen2Init(lv_theme_night_init(63488, NULL));
 
	hw_loop();
}

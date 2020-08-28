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

static void hal_init(void);
static int tick_thread(void *data); //explicit declarations.
static void dashInit(lv_theme_t *data);

int main(void)
{
	lv_init();

	hw_init();

  dashInit(lv_theme_night_init(63488, NULL)); //run the dash code.
  
	hw_loop();
}

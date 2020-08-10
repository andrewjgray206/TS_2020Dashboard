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
static int tick_thread(void *data);

int main(void)
{
	lv_init();

	hw_init();

  lv_theme(lv_theme_night_init(63488, NULL));
  
	hw_loop();
}

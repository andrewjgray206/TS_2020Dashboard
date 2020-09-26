/**
 * @file screen3.h
 *
 */


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#include "lv_ex_conf.h"
#else
#include "../../../lvgl/lvgl.h"
#include "../../../lv_ex_conf.h"
#endif



/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void warning_lines();
void draw_precharge_warning();
void draw_drive_warning();
void can_test_iterator(lv_task_t * task);
void ams_task_handler(lv_task_t * task);

/**********************
 *      MACROS
 **********************/

#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


extern int ams_state;
extern bool precharge_pressed;
extern bool drive_pressed;
extern float max_accum_temp;
extern uint16_t accum_lowest_voltage;
extern uint16_t motor_highest_temp;
extern uint16_t rineheart_highest_temp;
extern int ams_state;
extern bool precharge_pressed;
extern bool drive_pressed;

lv_task_t * task_handler;
lv_task_t * can_message_iterator;

lv_obj_t * slider_label;

lv_obj_t * motor_bar;
lv_obj_t * motor_temp_value;

lv_obj_t * rineheart_bar;
lv_obj_t * rineheart_temp_label;

lv_obj_t * accum_temp;
lv_obj_t * accum_temp_label;

lv_obj_t * accum_volt;
lv_obj_t * accum_volt_label;


lv_obj_t * driveWarningLine;
lv_obj_t * prechargeWarningLine;

lv_obj_t * header;
lv_obj_t * ams_label;

lv_style_t style_line;
static lv_point_t line_points[] = {{0,0},{800,0},{800, 480},{0, 480},{0,0}};


void warning_lines()
{
    driveWarningLine = lv_line_create(lv_scr_act(), NULL);
    lv_obj_set_hidden(driveWarningLine,true); //start as hidden.
    lv_line_set_points(driveWarningLine, line_points, 5);//Set the points

    prechargeWarningLine = lv_line_create(lv_scr_act(),NULL);
    lv_obj_set_hidden(prechargeWarningLine,true); //start as hidden.
    lv_line_set_points(prechargeWarningLine, line_points, 5);//Set the points
}

void draw_precharge_warning()
//UNFINISHED IMPLMENETAION, ANDREW WILL GET BACK TO THIS.
{
    style_line.line.color = LV_COLOR_ORANGE;
    lv_line_set_style(prechargeWarningLine, LV_LINE_STYLE_MAIN, &style_line);
    lv_obj_set_hidden(prechargeWarningLine,false);
}

void draw_drive_warning()
{
    style_line.line.color = LV_COLOR_GREEN;
    lv_line_set_style(driveWarningLine, LV_LINE_STYLE_MAIN, &style_line);
    lv_obj_set_hidden(driveWarningLine,false);
}

void header_create()
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

void can_test_iterator(lv_task_t * task)
/* NOTE: When implementing with real CAN messages
* This function can be deleted or commented out.
* As all it does is simulate can messages
* for simulation testing. */
{
    rineheart_highest_temp ++;
    accum_lowest_voltage ++;
    motor_highest_temp ++;
    max_accum_temp ++;
    
    if (motor_highest_temp == 200)
    {
        rineheart_highest_temp = 0;
        accum_lowest_voltage = 0;
        motor_highest_temp = 0;
        max_accum_temp = 0;
    }
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

void ams_task_handler(lv_task_t * task)
{
    if(lv_bar_get_value(motor_bar)!= motor_highest_temp)
    {
        char temp[10] = "";
        sprintf(temp,"%u",motor_highest_temp);
        lv_bar_set_value(motor_bar,motor_highest_temp,LV_ANIM_ON);
        lv_label_set_text(motor_temp_value,temp);
    }

    if (lv_bar_get_value(accum_temp) != max_accum_temp)
    {
        int temperature = max_accum_temp; //convert to an int for printing purposes.
        char temp[] = "";
        sprintf(temp,"%i",temperature);
        lv_bar_set_value(accum_temp,max_accum_temp,LV_ANIM_ON);
        lv_label_set_text(accum_temp_label,temp);
        printf(temp);
    }

    if(lv_bar_get_value(accum_volt)!= accum_lowest_voltage)
    {
        char temp[] = "";
        sprintf(temp,"%u",accum_lowest_voltage);
        lv_bar_set_value(accum_volt,accum_lowest_voltage,LV_ANIM_ON);
        lv_label_set_text(accum_volt_label,temp);
    }

    if (lv_bar_get_value(rineheart_bar) != rineheart_highest_temp)
    {
        char temp[] = "";
        sprintf(temp,"%u",motor_highest_temp);
        lv_bar_set_value(rineheart_bar,rineheart_highest_temp,LV_ANIM_ON);
        lv_label_set_text(rineheart_temp_label,temp);
    }

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


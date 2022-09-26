/*
 * File:   main.c
 * Author: Descamps Francois
 *
 * Created on 23 septembre 2022, 23:26
 */

#include <p18f2520.h>
#include "pwm_helper.h"
#include "battery_supervision.h"

#pragma config OSC = INTIO67
#pragma config PBADEN = OFF, WDT = OFF, LVP = OFF, DEBUG = ON

int i;

void main(void)
{
    setup_battery_supervision();
    init_pwm();
    for (i = 0; i < 10000; i++)
    {
        /* NOP */
    }
    //update_rc1_pwm_duty_cycle(200);
    //update_rc2_pwm_duty_cycle(200);
    while(1)
    {
        /* NOP */
    }
}
/*
 * File:   main.c
 * Author: Descamps Francois et Gioda Alexis
 *
 * Created on 23 septembre 2022, 23:26
 */

#include <p18f2520.h>
#include "pwm_helper.h"
#include "battery_supervision.h"
#include "driving.h"

#pragma config OSC = INTIO67
#pragma config PBADEN = OFF, WDT = OFF, LVP = OFF, DEBUG = ON

// int i;

void main(void)
{
    setup_battery_supervision();
    init_pwm();
    init_timer1();
    enable_timer1_interrupt();
//    for (i = 0; i < 10000; i++)
//    {
//        /* NOP */
//    }
//    update_rc1_pwm_duty_cycle(100);
//    update_rc2_pwm_duty_cycle(100);
    while(1)
    {
        /* NOP */
    }
}

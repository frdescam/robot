/*
 * File:   main.c
 * Author: Descamps Francois
 *
 * Created on 23 septembre 2022, 23:26
 */

#include <p18f2520.h>
#include "pwm_helper.h"

#pragma config OSC = INTIO67
#pragma config PBADEN = OFF, WDT = OFF, LVP = OFF, DEBUG = ON

void main(void)
{
    init_pwm();
    
    while(1)
    {
        /* NOP */
    }
}
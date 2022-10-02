/*
 * File:   main.c
 * Author: Descamps Francois & Gioda Alexis
 *
 * Created on 23 septembre 2022, 23:26
 */

#include <p18f2520.h>
#include "battery_supervision.h"
#include "driving.h"

#pragma config OSC = INTIO67
#pragma config PBADEN = OFF, WDT = OFF, LVP = OFF, DEBUG = ON

void main(void)
{
    start_battery_supervision();
    start_driving_procedure();

    while(1)
    {
        /* NOP */
    }
}

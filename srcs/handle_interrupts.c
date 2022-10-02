/* 
 * File:   battery_supervision.c
 * Author: Descamps Francois et Alexis Gioda
 *
 * Created on September 25, 2022, 5:51 PM
 */

#include <p18f2520.h>
#include "driving.h"

int is_low_battery = 0;
int motor_mode_OFF2 = 0;
int counter_timer1 = 0;

#pragma code
#pragma interrupt handle_high_priority_interrupts
void handle_high_priority_interrupts(void)
{
    // Timer0
    if (INTCONbits.TMR0IF)
    {
        // Clear interrupt flag
        INTCONbits.TMR0IF = 0;
        // Start the ADC conversion
        ADCON0bits.GO = 1;
    }
    // ADC
    if (PIR1bits.ADIF)
    {
        // Clear interrupt flag
        PIR1bits.ADIF = 0;
        if (ADRESH < 140)
        {
            // turn on battery status LED
            PORTBbits.RB5 = 1;
        }
    }
    // Timer1
    if (PIR1bits.TMR1IF)
    {
        // Clear interrupt flag
        PIR1bits.TMR1IF = 0;

        if(!motor_mode_OFF2) 
        {
            counter_timer1 ++;
        
            if(counter_timer1 <= 62)
                acceleration_mode();
            if(counter_timer1 >= 162 && counter_timer1 <= 200)
                constant_speed_mode();
            if(counter_timer1 >= 200 && counter_timer1 <= 262 )
                decceleration_mode();
            if(counter_timer1 >= 262)
            {
                stop_motor();
                counter_timer1 = 0;
            }
        }
    }
}

#pragma code HighVector=0x08
void IntHighVector(void)
{
    _asm goto handle_high_priority_interrupts _endasm
}
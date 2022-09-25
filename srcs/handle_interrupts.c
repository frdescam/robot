/* 
 * File:   battery_supervision.c
 * Author: Descamps Francois
 *
 * Created on September 25, 2022, 5:51 PM
 */

#include <p18f2520.h>

int is_low_battery = 0;

#pragma code
#pragma interrupt handle_high_priority_interrupts
void handle_high_priority_interrupts(void)
{
    // Timer0
    if (INTCONbits.INT0IF)
    {
        INTCONbits.INT0IF = 0;
        // Start the ADC conversion
        ADCON0bits.GO = 1;
    }
    // ADC
    if (PIR1bits.ADIF)
    {
        PIR1bits.ADIF = 0;
        if (ADRESH < 30000)
        {
            is_low_battery = 1;
        }
    }
}

#pragma code HighVector=0x08
void IntHighVector(void)
{
    _asm goto handle_high_priority_interrupts _endasm
}
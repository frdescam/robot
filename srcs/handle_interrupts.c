/* 
 * File:   handle_interrupts.c
 * Author: Descamps Francois & Alexis Gioda
 *
 * Created on September 25, 2022, 5:51 PM
 */

#include <p18f2520.h>
#include "driving.h"

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
        /* 
         * Reload value is on 16 bits so it should be given to peripheral using
         * 2 register :
         *   - TMR0L for 8 MSB
         *   - TMR0H for 8 LSB
         * Using 229 to get a 15 s interruption period
         */
        TMR0H = 229 & 0b11111111;
        TMR0L = 229 >> 8;
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

        update_motor_speed();
    }
}

#pragma code HighVector=0x08
void IntHighVector(void)
{
    _asm goto handle_high_priority_interrupts _endasm
}

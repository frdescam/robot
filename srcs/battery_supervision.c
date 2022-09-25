/* 
 * File:   battery_supervision.c
 * Author: Descamps Francois
 *
 * Created on September 25, 2022, 12:35 PM
 */

#include <p18f2520.h>

#pragma code
#pragma interrupt handle_timer0_interrupt
void handle_timer0_interrupt(void)
{
    if (INTCONbits.INT0IF)
    {
        INTCONbits.INT0IF = 0;
    }
}

#pragma code HighVector=0x08
void IntHighVector(void)
{
    _asm goto handle_timer0_interrupt _endasm
}

void init_timer0(void)
{
    // Enable Timer 0
    T0CONbits.TMR0ON = 1;
    // Configure it to use 16 bits
    T0CONbits.T08BIT = 0;
    // Use internal clock (work as timer not counter)
    T0CONbits.T0CS = 0;
    // Increment timer on rising edge
    T0CONbits.T0SE = 0;
    // Use prescaler
    T0CONbits.PSA = 0;
    // Use /256 prescaler => interruption period = 16,777216 s
    T0CONbits.T0PS = 0b111;
}

void enable_timer0_interrupt(void)
{
    // Enable interruptions globally
    INTCONbits.GIE = 1;
    // Enable peripheral interruptions
    INTCONbits.PEIE = 1;
    // Enable timer0 interruptions
    INTCONbits.TMR0IE = 1;
    // Set timer0 interrupt as hight priority
    INTCON2bits.TMR0IP = 1;
}

void setup_battery_supervision(void)
{
    init_timer0();
    init_adc();
    enable_timer0_interrupt();
}
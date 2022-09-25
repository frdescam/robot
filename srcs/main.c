/*
 * File:   main.c
 * Author: Descamps Francois et Gioda Alexis
 *
 * Created on 23 septembre 2022, 23:26
 */

#include <p18f2520.h>
#include "pwm_helper.h"

#pragma config OSC = INTIO67
#pragma config PBADEN = OFF, WDT = OFF, LVP = OFF, DEBUG = ON

int i;

void init_timer1(void)
{
    // Enable Timer 1
    T1CONbits.TMR1ON = 1;
    // Use internal clock (work as timer not counter)
    T1CONbits.TMR1CS = 0;
    // Do not synchronize external clock input
    T1CONbits.TMR1CS = 0;
    //Timer1 Oscillator Enable
    T1CONbits.T1OSCEN = 1;
    // Use /8 prescaler => interruption period = 0,524288 s
    T1CONbits.T1CKPS0 = 1;
    T1CONbits.T1CKPS1 = 1;
    // Use internal clock (work as timer not counter)
    T1CONbits.T1RUN = 1;
    // Configure it to use 16 bits
    T1CONbits.RD16 = 1; 
}







void main(void)
{
    init_pwm();
    for (i = 0; i < 10000; i++)
    {
        /* NOP */
    }
    update_rc1_pwm_duty_cycle(200);
    update_rc2_pwm_duty_cycle(200);
    while(1)
    {
        /* NOP */
    }
}
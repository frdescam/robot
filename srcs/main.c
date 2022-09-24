/*
 * File:   main.c
 * Author: Descamps Francois
 *
 * Created on 23 septembre 2022, 23:26
 */

#include<p18f2520.h>
#pragma config OSC = INTIO67
#pragma config PBADEN = OFF, WDT = OFF, LVP = OFF, DEBUG = ON

void main(void) {
    // Pin RC2 as output
    TRISCbits.RC2 = 0;
    // Pin RC1 as ouput
    TRISCbits.RC1 = 0;
    // Activating Timer2
    T2CONbits.TMR2ON = 1;

    // Prescaler = /1
    T2CONbits.T2CKPS = 0;
    // PWM Period = 10 kHz => 4 000 000 / (4 * 10 000) - 1 = 99
    PR2 = 99;
    // Duty cycle = 50% => (50 * 4 000 000) / (100 * 10 000) = 200
    CCPR1L = 200 >> 2;
    CCP1CONbits.DC1B = 200 & 0b11;
    CCPR2L = 200 >> 2;
    CCP2CONbits.DC2B = 200 & 0b11;

    // CCP in pwm mode
    CCP1CONbits.CCP1M = 0b1100;
    CCP2CONbits.CCP2M = 0b1100;

    // Postscaler = /10
    T2CONbits.T2OUTPS = 0b1001; 

    while(1) {
        /* NOP */
    }
}
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
    // Pin RC2 en sortie
    TRISCbits.RC2 = 0;
    // Pin RC1 en sortie
    TRISCbits.RC1 = 0;
    //Timer2 activation
    T2CONbits.TMR2ON = 1;

    //prescaler = /1
    T2CONbits.T2CKPS0 = 0;
    T2CONbits.T2CKPS1 = 0;
    //PR2
    PR2 = 0x18;
    // Rapport cyclique = 50% = 500
    CCPR1L = 0b00110010;
    CCPR2L = 0b00110010;

    // Mode de PWM
    
    CCP1CONbits.DC1B = 0b00;
    CCP1CONbits.CCP1M = 0b1100;

    CCP2CONbits.DC2B = 0b00;
    CCP2CONbits.CCP2M = 0b1100;

    //postscaler = /10
    T2CONbits.T2OUTPS = 0b1001;
    while(1) {
        /* NOP */
    }
}
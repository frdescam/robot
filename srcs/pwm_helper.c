/* 
 * File:   pwm_helper.c
 * Author: Descamps Francois et Alexis Gioda
 *
 * Created on September 24, 2022, 5:50 PM
 */

#include <p18f2520.h>

void update_rc1_pwm_duty_cycle(unsigned short new_duty_cycle)
{
    /* 
     * Duty cycle is a 10 bits value that should be given to peripheral using
     * 2 register :
     *   - CCPR1L for 8 MSB
     *   - DC1B bits of CCP1CON for 2 LSB
     */
    CCPR1L = new_duty_cycle >> 2;
    CCP1CONbits.DC1B = new_duty_cycle & 0b11;
}

void update_rc2_pwm_duty_cycle(unsigned short new_duty_cycle)
{
    /* 
     * Duty cycle is a 10 bits value that should be given to peripheral using
     * 2 register :
     *   - CCPR2L for 8 MSB
     *   - DC2B bits of CCP2CON for 2 LSB
     */
    CCPR2L = new_duty_cycle >> 2;
    CCP2CONbits.DC2B = new_duty_cycle & 0b11;
}

void init_pwm(void)
{
    // Pin RC2 as output
    TRISCbits.RC2 = 0;
    // Pin RC1 as output
    TRISCbits.RC1 = 0;
    // Activating Timer2
    T2CONbits.TMR2ON = 1;

    // Prescaler = /1
    T2CONbits.T2CKPS = 0;
    
    /*
     * PWM Period (10 kHz) :
     * 
     * PR2 = fosc / (4 * fpwm * prescaler) - 1
     * => 4 000 000 / (4 * 10 000) - 1 = 99
     *                                   ^^
     */
    PR2 = 99;

    // CCP in pwm mode
    CCP1CONbits.CCP1M = 0b1100;
    CCP2CONbits.CCP2M = 0b1100;
    
    update_rc1_pwm_duty_cycle(0);
    update_rc2_pwm_duty_cycle(0);

    // Postscaler = /10
    T2CONbits.T2OUTPS = 0b1001; // Looks useless
}
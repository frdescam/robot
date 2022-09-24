#include<p18f2520.h>

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

    /*
     * Duty cycle (50%) :
     * 
     * (DC in % * fosc) / (100 * prescaler * fpwm)
     * => (50 * 4 000 000) / (100 * 10 000) = 200    // Why tf not 1MHz as fosc ???
     *                                        ^^^
     */
    CCPR1L = 200 >> 2;
    CCP1CONbits.DC1B = 200 & 0b11;
    CCPR2L = 200 >> 2;
    CCP2CONbits.DC2B = 200 & 0b11;

    // CCP in pwm mode
    CCP1CONbits.CCP1M = 0b1100;
    CCP2CONbits.CCP2M = 0b1100;

    // Postscaler = /10
    T2CONbits.T2OUTPS = 0b1001; // Looks useless
}
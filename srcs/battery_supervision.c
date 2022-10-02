/* 
 * File:   battery_supervision.c
 * Author: Descamps Francois & Alexis Gioda
 *
 * Created on September 25, 2022, 12:35 PM
 */

#include <p18f2520.h>

void init_timer0(void)
{
    // Enable Timer0
    T0CONbits.TMR0ON = 1;
    // Configure it to use 16 bits
    T0CONbits.T08BIT = 0;
    // Use internal clock (work as timer not counter)
    T0CONbits.T0CS = 0;
    // Increment counter on rising edge
    T0CONbits.T0SE = 0;
    // Use prescaler
    T0CONbits.PSA = 0;
    // Use /256 prescaler => interruption period = 15 s with reload = 6942
    T0CONbits.T0PS = 0b111;
    /*
     * Reload value is on 16 bits so it should be given to peripheral using
     * 2 register :
     *   - TMR0L for 8 MSB
     *   - TMR0H for 8 LSB
     * Using 6942 to get a 15 s interruption period
     */
    TMR0H = 6942 & 0b11111111;
    TMR0L = 6942 >> 8;
}

void init_adc(void)
{
    // Pin RA2 as input
    TRISAbits.RA2 = 1;
    // Select Channel 2 for ADC conversions
    ADCON0bits.CHS = 0b0010;
    // Configure AN0, AN1 and AN2 as analog, others as digital
    ADCON1bits.PCFG = 0b1100;
    // Activate ADC
    ADCON0bits.ADON = 1;
    // Use VDD and VSS as references
    ADCON1bits.VCFG = 0;
    // Left justify so we can read only left register and loose some precision
    ADCON2bits.ADFM = 0;

    // TODO : change that comment
    
    //temps de conversion TAD
    //Fosc/4 => TAD = 1 us > TADmin = 0,7 us => définie sur le temps d'horloge définie pour l'ADC de l'horloge
    //010 = 4*TAD = 4 us avec une plage de fonctionnement à 72°C pour un pire cas TACQ = 4.25 us
    
    // Acquisition time 
    ADCON2bits.ACQT = 0b010;
}

void init_battery_status_led(void)
{
    // Pin RB5 as output
    TRISBbits.RB5 = 0;
    // Turn off battery status LED
    PORTBbits.RB5 = 0;
}

void enable_timer0_interrupts(void)
{
    // Enable interruptions globally
    INTCONbits.GIE = 1;
    // Enable peripheral interruptions
    //INTCONbits.PEIE = 1;
    // Enable timer0 interruptions
    INTCONbits.TMR0IE = 1;
    // Enable interruptions priority
    RCONbits.IPEN = 1;
    // Set timer0 interrupt as hight priority
    INTCON2bits.TMR0IP = 1;
}

void enable_adc_interrupts(void)
{
    // Enable interruptions globally
    INTCONbits.GIE = 1;
    // Enable peripheral interruptions
    INTCONbits.PEIE = 1;
    // Enable adc interruptions
    PIE1bits.ADIE = 1;
    // Enable interruptions priority
    RCONbits.IPEN = 1;
    // Set ADC interrupt as hight priority
    IPR1bits.ADIP = 1;
}

void start_battery_supervision(void)
{
    init_timer0();
    init_adc();
    init_battery_status_led();
    enable_timer0_interrupts();
    enable_adc_interrupts();
    // Start first battery check
    ADCON0bits.GO = 1;
}
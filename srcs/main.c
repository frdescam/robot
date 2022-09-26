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
int duty_cycle_incr = 0;
int counter_timer1 = 0;


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
    // Use /1 prescaler => interruption period = 0,065535 s
    T1CONbits.T1CKPS = 0b00;
    // Use internal clock (work as timer not counter)
    T1CONbits.T1RUN = 1;
    // Configure it to use 16 bits
    T1CONbits.RD16 = 1; 
}

void enable_timer1_interrupt(void)
{
    // Enable interruptions globaly
    INTCONbits.GIE = 1;
    // Enable peripheral interruptions
    INTCONbits.PEIE = 1;
    
    //Enable timer1 interruptions
    PIR1bits.TMR1IF = 1;
    // Set timer1 interrupt as hight priority
    IPR1bits.TMR1IP = 1;
}


#pragma interrupt handle_timer1_interrupt
void handle_timer1_interrupt(void)
{
    counter_timer1 ++;
    
    if(counter_timer1 < 62)
        acceleration_mode();
    if(counter_timer1 >= 62 && counter_timer1 <= 162)
        constant_speed_mode();
    if(counter_timer1 >= 162 && counter_timer1 <= 224 )
        decceleration_mode();
    
    if (INTCON3bits.INT1IF)
    {
        INTCON3bits.INT1IF = 0;
    }
}

#pragma code HighVector=0x08
void IntHighVector(void)
{
    _asm goto handle_timer1_interrupt _endasm
}

void acceleration_mode(void)
{
    if(duty_cycle_incr <=200)
    {
        
        duty_cycle_incr ++;
    
        update_rc1_pwm_duty_cycle(duty_cycle_incr);
        update_rc2_pwm_duty_cycle(duty_cycle_incr);  
    }

}

void decceleration_mode(void)
{
    if(duty_cycle_incr >=0)
    {
        duty_cycle_incr --;
    
        update_rc1_pwm_duty_cycle(duty_cycle_incr);
        update_rc2_pwm_duty_cycle(duty_cycle_incr);
        
    }
}

void constant_speed_mode(void)
{
    update_rc1_pwm_duty_cycle(200);
    update_rc2_pwm_duty_cycle(200);
}



void main(void)
{
    init_pwm();
    for (i = 0; i < 10000; i++)
    {
        /* NOP */
    }
//    update_rc1_pwm_duty_cycle(200);
//    update_rc2_pwm_duty_cycle(200);
    while(1)
    {
        /* NOP */
    }
}
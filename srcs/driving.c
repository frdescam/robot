/*
 * File:   driving.c
 * Author: Descamps Francois & Alexis Gioda
 *
 * Created on 26 septembre 2022, 12:26
 */

#include <p18f2520.h>
#include "pwm.h"

unsigned short duty_cycle_incr = 0;
int motor_mode_OFF = 0;
int counter_timer1 = 0;

void init_direction_gpio(void)
{
    // Pin RA6 as output (right motor)
    TRISAbits.RA6 = 0;
    // Pin RA7 as output (left motor)
    TRISAbits.RA7 = 0;
}

void set_direction_forward(void)
{
    // Right motor forward
    PORTAbits.RA6 = 1;
    // Left motor forward
    PORTAbits.RA7 = 1;
}

void set_direction_backward(void)
{
    // Right motor backward
    PORTAbits.RA6 = 0;
    // Left motor backward
    PORTAbits.RA7 = 0;
}

void init_timer1(void)
{
    motor_mode_OFF = 0;
    // Enable Timer 1
    T1CONbits.TMR1ON = 1;
    // Use internal clock
    T1CONbits.TMR1CS = 0;
    //Timer1 Oscillator Enable
    T1CONbits.T1OSCEN = 0;
    // Use /1 prescaler => interruption period = 0,065535 s
    T1CONbits.T1CKPS = 0b00;
    // Use internal clock
    T1CONbits.T1RUN = 0;
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
    PIE1bits.TMR1IE = 1;
    //Enable interruptions priority
    RCONbits.IPEN = 1;
    // Set timer1 interrupt as hight priority
    IPR1bits.TMR1IP = 1;
}

void acceleration_mode(void)
{
    if(duty_cycle_incr <=200)
    {
        duty_cycle_incr = duty_cycle_incr + 5;
    
        update_rc1_pwm_duty_cycle(duty_cycle_incr);
        update_rc2_pwm_duty_cycle(duty_cycle_incr);
    }
}

void decceleration_mode(void)
{
    if(duty_cycle_incr >=0)
    {
        duty_cycle_incr = duty_cycle_incr - 5;
    
        update_rc1_pwm_duty_cycle(duty_cycle_incr);
        update_rc2_pwm_duty_cycle(duty_cycle_incr);
        
    }
}

void stop_motor(void)
{
    update_rc1_pwm_duty_cycle(0);
    update_rc2_pwm_duty_cycle(0);
    duty_cycle_incr = 0;
    
    motor_mode_OFF = 1;
}

void constant_speed_mode(void)
{
    update_rc1_pwm_duty_cycle(200);
    update_rc2_pwm_duty_cycle(200);
}

void update_motor_speed(void)
{
    if(!motor_mode_OFF) 
    {
        counter_timer1 ++;
        if(counter_timer1 <= 62)
            acceleration_mode();
        if(counter_timer1 >= 162 && counter_timer1 <= 200)
            constant_speed_mode();
        if(counter_timer1 >= 200 && counter_timer1 <= 262 )
            decceleration_mode();
        if(counter_timer1 >= 262)
        {
            stop_motor();
            counter_timer1 = 0;
        }
    }
}

void start_driving_procedure(void)
{
    init_direction_gpio();
    set_direction_forward();
    init_pwm();
    init_timer1();
    enable_timer1_interrupt();
}

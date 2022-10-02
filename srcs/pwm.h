/* 
 * File:   pwm.h
 * Author: Descamps Francois & Alexis Gioda
 *
 * Created on September 24, 2022, 5:48 PM
 */

#ifndef PWM_HELPER_H
#define	PWM_HELPER_H

/*
 * Init PWM on RC1 and RC2 at 10 kHz frequency with duty cycle at 0%
 */

void init_pwm(void);

/*
 * Update PWM duty cycle to 'new_duty_cycle'
 * 
 * 'new_duty_cycle' should be unsigned short computed that way :
 * 
 * (DC in % * fosc) / (100 * prescaler * fpwm)
 * 
 * Example with 50% duty cycle :
 * => (50 * 4 000 000) / (100 * 10 000) = 200
 * 
 * /!\ PWM should have been initialized by 'init_pwm' before calling this function
 */

void update_rc1_pwm_duty_cycle(unsigned short new_duty_cycle);
void update_rc2_pwm_duty_cycle(unsigned short new_duty_cycle);

#endif


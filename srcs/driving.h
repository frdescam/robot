/* 
 * File:   driving.h
 * Author: Descamps Francois et Gioda Alexis
 *
 * Created on September 26, 2022, 12:27 PM
 */

#ifndef DRIVING_H
#define	DRIVING_H

void constant_speed_mode(void);
void stop_motor(void);
void decceleration_mode(void);
void acceleration_mode(void);
void enable_timer1_interrupt(void);
void init_timer1(void);

#endif


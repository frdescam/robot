/* 
 * File:   driving.h
 * Author: Descamps Francois & Gioda Alexis
 *
 * Created on September 26, 2022, 12:27 PM
 */

#ifndef DRIVING_H
#define	DRIVING_H
/*
 * This function will configure the driving of the motors
 * for reproducing the following move :
 * 
 *        speed ^
 *              |  __________
 *              | /          \
 *              |/            \
 *              '---------------->
 *                            time
 *               ^^|^^^^^^^^|^^
 * Acceleration -'      |    |
 *                      |    |
 * Constant speed ------'    |
 *                           |
 * Deceleration -------------'
 * 
 */
void start_driving_procedure(void);

/*
 * This function is regularly called by the interruption for automatically
 * updating the motors speed to fit the above graph
 */
void update_motor_speed(void);

#endif


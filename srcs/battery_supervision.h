/* 
 * File:   battery_supervision.h
 * Author: Descamps Francois & Alexis Gioda
 *
 * Created on September 25, 2022, 12:39 PM
 */

#ifndef BATTERY_SUPERVISION_H
#define	BATTERY_SUPERVISION_H

/*
 * Configure and start the battery supervision system
 * 
 * Every 15 s, an Analog to Digital conversion is Done on pin AN2
 * If the battery tension is bellow 140, the LED on pin RB5 is turned on
 */

void start_battery_supervision(void);

#endif


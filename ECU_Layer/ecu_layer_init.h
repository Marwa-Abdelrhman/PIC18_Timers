/* 
 * File:   ecu_layer_init.h
 * Author: Marwa Abdelrahman
 *
 * Created on September 2, 2024, 2:18 PM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H

/*.....................................Includes.....................................*/
#include "LED/ecu_led.h"
#include "BUTTON/ecu_button.h"
#include "RELAY/ecu_relay.h"
#include "DC_Motor/ecu_dc_motor.h"
#include "7_Segment_Display/ecu_seven_seg.h"
#include "KeyPad/ecu_keypad.h"
#include "Char_LCD/ecu_char_LDC.h"
/*.....................................Macros Declarations.....................................*/



/*.....................................Macros Functions Declarations.....................................*/



/*.....................................Data Types Declarations.....................................*/

extern led_t led_4;
extern led_t led_5;
extern led_t led_6;
extern led_t led_7;

/*.....................................Functions Declarations.....................................*/
void ecu_layer_initialize(void);

#endif	/* ECU_LAYER_INIT_H */


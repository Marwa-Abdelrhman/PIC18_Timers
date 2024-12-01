/* 
 * File:   ecu_keypad.h
 * Author: Marwa Abdelrahman
 *
 * Created on September 2, 2024, 2:15 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H


/*.....................................Includes.....................................*/


#include "ecu_keypad_cfg.h"
#include"../../MCAL_Layer/GPIO/hal_gpio.h"
/*.....................................Macros Declarations.....................................*/

#define KEYPAD_ROWS       4
#define KEYPAD_COLUMNS    4


/*.....................................Macros Functions Declarations.....................................*/

typedef struct{
    pin_config_t keypad_rows_pins[KEYPAD_ROWS];
    pin_config_t keypad_columns_pins[KEYPAD_COLUMNS];
}keypad_t;
/*.....................................Data Types Declarations.....................................*/




/*.....................................Functions Declarations.....................................*/
Std_RetrunType keypad_init(const keypad_t *keypad_obj);
Std_RetrunType keypad_get_key_pressed(const keypad_t *keypad_obj,uint8 *value);






#endif	/* ECU_KEYPAD_H */


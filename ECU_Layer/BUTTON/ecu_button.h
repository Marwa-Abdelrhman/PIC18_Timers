/* 
 * File:   ecu_button.h
 * Author: Marwa Abdelrahman
 *
 * Created on August 19, 2024, 1:32 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/*.....................................Includes.....................................*/
#include "ecu_button_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"



/*.....................................Macros Declarations.....................................*/



/*.....................................Macros Functions Declarations.....................................*/



/*.....................................Data Types Declarations.....................................*/
typedef enum{
    BUTTON_RELEASED=0,
    BUTTON_PRESSED
}button_state_t;

typedef enum{
    BUTTON_ACTIVE_LOW=0,
    BUTTON_ACTIVE_HIGH
        
}button_acvtive_state_t;

typedef struct{
    pin_config_t btn_pin;
    button_state_t btn_state;
    button_acvtive_state_t btn_connection_typ;
}button_t;



/*.....................................Functions Declarations.....................................*/
Std_RetrunType button_init(const button_t *btn_obj);

Std_RetrunType button_read_state(const button_t *btn_obj,button_state_t *btn_st);
#endif	/* ECU_BUTTON_H */


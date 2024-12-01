/* 
 * File:   ecu_dc_motor.h
 * Author: Marwa Abdelrahman
 *
 * Created on August 24, 2024, 1:47 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/*.....................................Includes.....................................*/
#include "ecu_dc_motor_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"



/*.....................................Macros Declarations.....................................*/
#define DC_MOTOR_ON_STATE               0x01U
#define DC_MOTOR_OFF_STATE              0x00U

#define DC_MOTOR_PIN_1                  0x00U
#define DC_MOTOR_PIN_2                  0x01U
/*.....................................Macros Functions Declarations.....................................*/



/*.....................................Data Types Declarations.....................................*/

typedef struct{
    pin_config_t dc_motor_pin[2];
}dc_motor_t;
/*.....................................Functions Declarations.....................................*/
Std_RetrunType dc_motor_init(const dc_motor_t *dc_motor_obj);
Std_RetrunType dc_motor_move_right(const dc_motor_t *dc_motor_obj);
Std_RetrunType dc_motor_move_left(const dc_motor_t *dc_motor_obj);
Std_RetrunType dc_motor_stop(const dc_motor_t *dc_motor_obj);

#endif	/* ECU_DC_MOTOR_H */


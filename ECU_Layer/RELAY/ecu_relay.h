/* 
 * File:   ecu_relay.h
 * Author: Marwa Abdelrahman
 *
 * Created on August 22, 2024, 12:43 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/*.....................................Includes.....................................*/
#include "ecu_relay_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/*.....................................Macros Declarations.....................................*/

#define RELAY_ON_STATE     0x01U
#define RELAY_OFF_STATE    0x00U

/*.....................................Macros Functions Declarations.....................................*/



/*.....................................Data Types Declarations.....................................*/

typedef struct{
    uint8 relay_port:4;
    uint8 relay_pin:3;
    uint8 relay_state:1;
    
}relay_t;
/*.....................................Functions Declarations.....................................*/
Std_RetrunType relay_init(const relay_t * relay_obj);
Std_RetrunType relay_on(const relay_t * relay_obj);
Std_RetrunType relay_off(const relay_t * relay_obj);
Std_RetrunType relay_toggle(const relay_t * relay_obj);

#endif	/* ECU_RELAY_H */


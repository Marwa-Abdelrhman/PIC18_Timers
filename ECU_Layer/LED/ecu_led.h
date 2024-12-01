/* 
 * File:   ecu_led.h
 * Author: Marwa Abdelrahman
 *
 * Created on August 1, 2024, 2:10 AM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/*.....................................Includes.....................................*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"



/*.....................................Macros Declarations.....................................*/



/*.....................................Macros Functions Declarations.....................................*/



/*.....................................Data Types Declarations.....................................*/
typedef enum {
    LED_OFF=0,
    LED_ON
}led_state_t;


typedef struct{
    uint8 port_name:3;
    uint8 pin:3;
    uint8 led_state:1;
    uint8 reserved:1;
}led_t;



/*.....................................Functions Declarations.....................................*/
Std_RetrunType led_init(const led_t *led);

Std_RetrunType led_on(const led_t *led);

Std_RetrunType led_off(const led_t *led);

Std_RetrunType led_toggle(const led_t *led);
#endif	/* ECU_LED_H */


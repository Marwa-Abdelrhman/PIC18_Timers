/* 
 * File:   hal_gpio.h
 * Author: Marwa Abdelrahman
 *
 * Created on August 1, 2024, 01:11 AM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/*.....................................Includes.....................................*/
#include "../mcal_std_types.h"
#include "../proc/pic18f4620.h"
#include "../device_config.h"
#include "../mcal_std_types.h"
#include "hal_gpio_cfg.h"
#include <stdlib.h>


/*.....................................Macros Declarations.....................................*/
#define BIT_MASK                             (uint8) 1
#define PORT_MASK                            0XFF  
#define HWREG8(__X)                          (*((volatiel uint8 *)(__X) ))


#define SET_BIT(REG,BIT_POSN)                (REG |=  (BIT_MASK<<BIT_POSN))
#define CLEAR_BIT(REG,BIT_POSN)              (REG &=~ (BIT_MASK<<BIT_POSN))
#define TOGGLE_BIT(REG,BIT_POSN)             (REG ^=  (BIT_MASK<<BIT_POSN))  
#define READ_BIT(REG,BIT_POSN)               ((REG>>BIT_POSN) & BIT_MASK)

#define PORTA_REG_ADDRESS                    (*(volatiel uint8 * (0xF80) ))


#define PORT_INDEX_MAX_NUMBER                5
#define PIN_INDEX_MAX_NUMBER                 8



/*.....................................Macros Functions Declarations.....................................*/
typedef enum{
    GPIO_DIRECTION_OUTPUT=0,
    GPIO_DIRECTION_INPUT        
}direction_t;

typedef enum{
    GPIO_STATE_LOW=0,
    GPIO_STATE_HIGH
}state_t;

typedef enum{
    GPIO_PIN0=0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
          
}pin_t;

typedef enum{
    PORTA_INDEX=0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
            
        
}port_t;

typedef struct{
    
    uint8 port:3;
    uint8 pin:3;
    uint8 direction:1;
    uint8 state:1;
    
}pin_config_t;
        


/*.....................................Data Types Declarations.....................................*/
volatile uint8 * tris_reg[]={&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};        /*direction registers to control INPUT/OUTPUT, we can write and read to it*//* Reference to the Data Direction Control Registers */
volatile uint8 * lat_reg[]={&LATA,&LATB,&LATC,&LATD,&LATE};              /*data registers to R/W*//* Reference to the Data Latch Register (Read and Write to Data Latch) */
volatile uint8 * port_reg[]={&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};        /* Reference to the Port Status Register  */

/*.....................................Functions Declarations.....................................*/


Std_RetrunType gpio_pin_direction_init(const pin_config_t *pin_confg);
Std_RetrunType gpio_pin_get_direction_status(const pin_config_t *pin_confg,direction_t *pin_dir);
Std_RetrunType gpio_pin_write(const pin_config_t *pin_confg,state_t pin_state);
Std_RetrunType gpio_pin_read(const pin_config_t *pin_confg,state_t *pin_state);
Std_RetrunType gpio_pin_toggle(const pin_config_t *pin_confg);
Std_RetrunType gpio_pin_init(const pin_config_t *pin_confg);





Std_RetrunType gpio_port_direction_init(port_t port_confg,uint8 port_dir);
Std_RetrunType gpio_port_get_direction_status(port_t port_confg,uint8 *port_dir);
Std_RetrunType gpio_port_write(port_t port_confg,uint8 port_state);
Std_RetrunType gpio_port_read(port_t port_confg,uint8 *port_state);
Std_RetrunType gpio_port_toggle(port_t port_confg);





#endif	/* HAL_GPIO_H */


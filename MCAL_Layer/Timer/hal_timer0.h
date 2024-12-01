/* 
 * File:   hal_timer0.h
 * Author: Marwa Abdelrahman
 *
 * Created on November 18, 2024, 1:57 PM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H


/*.....................................Includes.....................................*/
#include "../GPIO/hal_gpio.h"
#include "../proc/pic18f4620.h"
#include"../Interrupt/mcal_internal_interrupt.h"
#include"../mcal_std_types.h"
/*.....................................Macros Declarations.....................................*/
#define TIMER0_COUNTER_MODE_ON         0 /*@RA4 pin on pic18f4620*/
#define TIMER0_TIMER_MODE_ON           1
#define TIMER0_16_BIT_REG_SIZE         0
#define TIMER0_8_BIT_REG_SIZE          1
#define TIMER0_FALLING_EDGE_CFG        0
#define TIMER0_RISING_EDGE_CFG         1
#define TIMER0_ENABLE_PRESCALER_CFG    1
#define TIMER0_DISABLE_PRESCALER_CFG   0

/*.....................................Macros Functions Declarations.....................................*/

#define TIMER0_ENABLE()                             (T0CONbits.TMR0ON=1)
#define TIMER0_STOP()                               (T0CONbits.TMR0ON=0)
#define TIMER0_16_BIT_REG()                         (T0CONbits.T08BIT=0)
#define TIMER0_8_BIT_REG()                          (T0CONbits.T08BIT=1)
#define TIMER0_SELECT_TIMER_MODE()                  (T0CONbits.T0CS=0)
#define TIMER0_SELECT_COUNTER_MODE()                (T0CONbits.T0CS=1)
#define TIMER0_COUNTER_ON_RISING_EDGE()             (T0CONbits.T0SE=0)
#define TIMER0_COUNTER_ON_FALLING_EDGE()            (T0CONbits.T0SE=1)
#define TIMER0_PRESCALER_ON()                       (T0CONbits.PSA=0)
#define TIMER0_PRESCALER_OFF()                      (T0CONbits.PSA=1)

/*.....................................Data Types Declarations.....................................*/
typedef enum{
    PRECALER_VALUE_DIV_2=0,
    PRECALER_VALUE_DIV_4,
    PRECALER_VALUE_DIV_8,
    PRECALER_VALUE_DIV_16,
    PRECALER_VALUE_DIV_32,
    PRECALER_VALUE_DIV_64,
    PRECALER_VALUE_DIV_128,
    PRECALER_VALUE_DIV_256
}timer0_prescaler_select_t;



typedef struct{
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
     void (* TIMER0_Interrupt_Handler)(void);
     interrupt_priority_cfg timer0_priority;
#endif    
    uint16 timer0_preload_val;
    timer0_prescaler_select_t prescaler_value;
    uint8 prescaler_cfg:1;
    uint8 timer0_mode:1;
    uint8 timer0_reg_size:1;
    uint8 counter_edge_cfg:1;
    uint8 reserved_bits:4;
    
}timer0_t;


Std_RetrunType TIMER0_Init(const timer0_t  *timer0_obj);
Std_RetrunType TIMER0_DeInit(const timer0_t  *timer0_obj);
Std_RetrunType TIMER0_read_value(const timer0_t  *timer0_obj,uint16 *timer0_val);
Std_RetrunType TIMER0_write(const timer0_t  *timer0_obj,uint16 timer0_val);

/*.....................................Functions Declarations.....................................*/

#endif	/* HAL_TIMER0_H */


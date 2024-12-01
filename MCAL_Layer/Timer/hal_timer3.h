/* 
 * File:   hal_timer3.h
 * Author: Marwa Abdelrahman
 *
 * Created on November 22, 2024, 2:51 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H


/*.....................................Includes.....................................*/
#include "../GPIO/hal_gpio.h"
#include "../proc/pic18f4620.h"
#include"../Interrupt/mcal_internal_interrupt.h"
#include"../mcal_std_types.h"
/*.....................................Macros Declarations.....................................*/
#define TIMER3_COUNTER_MODE_ON                       1 /*@RC0 pin on pic18f4620*/
#define TIMER3_TIMER_MODE_ON                         0
#define TIMER3_16_BIT_REG_RW                         1
#define TIMER3_8_BIT_REG_RW                          0
#define TIMER3_COUNTER_SYNC_CFG                      0
#define TIMER3_COUNTER_ASYNC_CFG                     1
#define TIMER3_PRESCALER_DIV_1                       0
#define TIMER3_PRESCALER_DIV_2                       1
#define TIMER3_PRESCALER_DIV_4                       2
#define TIMER3_PRESCALER_DIV_8                       3
/*.....................................Macros Functions Declarations.....................................*/

#define TIMER3_ENABLE()                             (T3CONbits.TMR3ON=1)
#define TIMER3_DISABLE()                            (T3CONbits.TMR3ON=0)

#define TIMER3_SELECT_TIMER_MODE()                  (T3CONbits.TMR3CS=0)
#define TIMER3_SELECT_COUNTER_MODE()                (T3CONbits.TMR3CS=1)

#define TIMER3_COUNTER_SYNC_MODE()                  (T3CONbits.T3SYNC=0)
#define TIMER3_COUNTER_ASYNC_MODE()                 (T3CONbits.T3SYNC=1)

#define TIMER3_SET_PRESCALER_VALUE(_PRES_VAL)       (T3CONbits.T3CKPS=_PRES_VAL)

#define TIMER3_8_BIT_REG_RW_MODE()                  (T3CONbits.RD16=0)
#define TIMER3_16_BIT_REG_RW_MODE()                 (T3CONbits.RD16=1)






/*.....................................Data Types Declarations.....................................*/

typedef struct{
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
     void (* TIMER3_Interrupt_Handler)(void);
     interrupt_priority_cfg timer3_priority;
#endif    
    uint16 timer3_preload_val;
    uint8 prescaler_value:2;
    uint8 timer3_mode:1;
    uint8 timer3_reg_size:1;
    uint8 counter_mode:1;
    uint8 reserved_bits:3;
    
}timer3_t;
/*.....................................Functions Declarations.....................................*/
Std_RetrunType TIMER3_Init(const timer3_t  *tmr3_obj);
Std_RetrunType TIMER3_DeInit(const timer3_t  *tmr3_obj);
Std_RetrunType TIMER3_read_value(const timer3_t  *tmr3_obj,uint16 *tmr3_val);
Std_RetrunType TIMER3_write(const timer3_t  *tmr3_obj,uint16 tmr3_val);			
#endif	/* HAL_TIMER3_H */


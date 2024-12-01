/* 
 * File:   hal_timer1.h
 * Author: Marwa Abdelrahman
 *
 * Created on November 20, 2024, 11:22 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H


/*.....................................Includes.....................................*/
#include "../GPIO/hal_gpio.h"
#include "../proc/pic18f4620.h"
#include"../Interrupt/mcal_internal_interrupt.h"
#include"../mcal_std_types.h"
/*.....................................Macros Declarations.....................................*/
#define TIMER1_COUNTER_MODE_ON                       1 /*@RC0 pin on pic18f4620*/
#define TIMER1_TIMER_MODE_ON                         0
#define TIMER1_16_BIT_REG_RW                         1
#define TIMER1_8_BIT_REG_RW                          0
#define TIMER1_COUNTER_SYNC_CFG                      0
#define TIMER1_COUNTER_ASYNC_CFG                     1
#define TIMER1_ENABLE_OSCILLATOR_CLK                 1
#define TIMER1_DISABLE_OSCILLATOR_CLK                0
#define TIMER1_PRESCALER_DIV_1                       0
#define TIMER1_PRESCALER_DIV_2                       1
#define TIMER1_PRESCALER_DIV_4                       2
#define TIMER1_PRESCALER_DIV_8                       3
/*.....................................Macros Functions Declarations.....................................*/

#define TIMER1_ENABLE()                             (T1CONbits.TMR1ON=1)
#define TIMER1_DISABLE()                            (T1CONbits.TMR1ON=0)
#define TIMER1_8_BIT_REG_RW_MODE()                  (T1CONbits.RD16=0)
#define TIMER1_16_BIT_REG_RW_MODE()                 (T1CONbits.RD16=1)
#define TIMER1_READ_CLK_STATUS()                    (T1CONbits.T1RUN)
#define TIMER1_SET_PRESCALER_VALUE(_PRES_VAL)       (T1CONbits.T1CKPS=_PRES_VAL)
#define TIMER1_OSCILLATOR_CLK_SRC_ON()              (T1CONbits.T1OSCEN=1)
#define TIMER1_OSCILLATOR_CLK_SRC_OFF()             (T1CONbits.T1OSCEN=0)
#define TIMER1_SELECT_TIMER_MODE()                  (T1CONbits.TMR1CS=0)
#define TIMER1_SELECT_COUNTER_MODE()                (T1CONbits.TMR1CS=1)
#define TIMER1_COUNTER_SYNC_MODE()                  (T1CONbits.T1SYNC=0)
#define TIMER1_COUNTER_ASYNC_MODE()                 (T1CONbits.T1SYNC=1)


/*.....................................Data Types Declarations.....................................*/

typedef struct{
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
     void (* TIMER1_Interrupt_Handler)(void);
     interrupt_priority_cfg timer1_priority;
#endif    
    uint16 timer1_preload_val;
    uint8 prescaler_value:2;
    uint8 timer1_mode:1;
    uint8 timer1_reg_size:1;
    uint8 counter_clk:1;
    uint8 timer1_osc_cfg:1;
    uint8 reserved_bits:2;
    
}timer1_t;
/*.....................................Functions Declarations.....................................*/
Std_RetrunType TIMER1_Init(const timer1_t  *tmr1_obj);
Std_RetrunType TIMER1_DeInit(const timer1_t  *tmr1_obj);
Std_RetrunType TIMER1_read_value(const timer1_t  *tmr1_obj,uint16 *tmr1_val);
Std_RetrunType TIMER1_write(const timer1_t  *tmr1_obj,uint16 tmr1_val);
#endif	/* HAL_TIMER1_H */


/* 
 * File:   hal_timer2.h
 * Author: Marwa Abdelrahman
 *
 * Created on November 22, 2024, 2:51 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H


/*.....................................Includes.....................................*/
#include "../GPIO/hal_gpio.h"
#include "../proc/pic18f4620.h"
#include"../Interrupt/mcal_internal_interrupt.h"
#include"../mcal_std_types.h"
/*.....................................Macros Declarations.....................................*/
#define TIMER2_PRESCALER_DIV_1                         0
#define TIMER2_PRESCALER_DIV_4                         1
#define TIMER2_PRESCALER_DIV_16                        2

#define TIMER2_POSTSSCALER_DIV_1                       0
#define TIMER2_POSTSSCALER_DIV_2                       1
#define TIMER2_POSTSSCALER_DIV_3                       2
#define TIMER2_POSTSSCALER_DIV_4                       3
#define TIMER2_POSTSSCALER_DIV_5                       4
#define TIMER2_POSTSSCALER_DIV_6                       5
#define TIMER2_POSTSSCALER_DIV_7                       6
#define TIMER2_POSTSSCALER_DIV_8                       7
#define TIMER2_POSTSSCALER_DIV_9                       8
#define TIMER2_POSTSSCALER_DIV_10                      9
#define TIMER2_POSTSSCALER_DIV_11                      10
#define TIMER2_POSTSSCALER_DIV_12                      11
#define TIMER2_POSTSSCALER_DIV_13                      12
#define TIMER2_POSTSSCALER_DIV_14                      13
#define TIMER2_POSTSSCALER_DIV_15                      14
#define TIMER2_POSTSSCALER_DIV_16                      15

#define TIMER2_ENABLE()                             (T2CONbits.TMR2ON=1)
#define TIMER2_DISABLE()                            (T2CONbits.TMR2ON=0)
/*.....................................Macros Functions Declarations.....................................*/

#define TIMER2_SET_PRESCALER_VALUE(_PRE_VAL)       (T2CONbits.T2CKPS=_PRE_VAL)
#define TIMER2_SET_POSTSCALER_VALUE(_POST_VAL)     (T2CONbits.TOUTPS=_POST_VAL)

/*.....................................Data Types Declarations.....................................*/

typedef struct{
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
     void (* TIMER2_Interrupt_Handler)(void);
     interrupt_priority_cfg timer2_priority;
#endif    
    uint8 timer2_preload_val;
    uint8 prescaler_value:2;
    uint8 postscaler_value:4;
    uint8 reserved_bits:2;
    
}timer2_t;
/*.....................................Functions Declarations.....................................*/
Std_RetrunType TIMER2_Init(const timer2_t  *tmr2_obj);
Std_RetrunType TIMER2_DeInit(const timer2_t  *tmr2_obj);
Std_RetrunType TIMER2_read_value(const timer2_t  *tmr2_obj,uint8 *tmr2_val);
Std_RetrunType TIMER2_write(const timer2_t  *tmr2_obj,uint8 tmr2_val);			

#endif	/* HAL_TIMER2_H */


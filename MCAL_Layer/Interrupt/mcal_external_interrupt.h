/* 
 * File:   mcal_external_interrupt.h
 * Author: Marwa Abdelrahman
 *
 * Created on September 29, 2024, 2:37 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H



/*.....................................Includes.....................................*/

#include "mcal_interrupt_config.h"
/*.....................................Macros Declarations.....................................*/



/*.....................................Macros Functions Declarations.....................................*/
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE


#define EXTERNAL_INT0_INTERRUPT_ENABLE()            (INTCONbits.INT0IE=1)
#define EXTERNAL_INT0_INTERRUPT_DISABLE()           (INTCONbits.INT0IE=0)
#define EXTERNAL_INT0_INTERRUPT_FLAG_ENABLE()       (INTCONbits.INT0IF=1)
#define EXTERNAL_INT0_INTERRUPT_FLAG_CLEAR()        (INTCONbits.INT0IF=0)
#define EXTERNAL_INT0_RISING_EDGE()                 (INTCON2bits.INTEDG0=1)
#define EXTERNAL_INT0_FALLING_EDGE()                (INTCON2bits.INTEDG0=0)


#define EXTERNAL_INT1_INTERRUPT_ENABLE()            (INTCON3bits.INT1IE=1)
#define EXTERNAL_INT1_INTERRUPT_DISABLE()           (INTCON3bits.INT1IE=0)
#define EXTERNAL_INT1_INTERRUPT_FLAG_ENABLE()       (INTCON3bits.INT1IF=1)
#define EXTERNAL_INT1_INTERRUPT_FLAG_CLEAR()        (INTCON3bits.INT1IF=0)
#define EXTERNAL_INT1_RISING_EDGE()                 (INTCON2bits.INTEDG1=1)
#define EXTERNAL_INT1_FALLING_EDGE()                (INTCON2bits.INTEDG1=0)


#define EXTERNAL_INT2_INTERRUPT_ENABLE()            (INTCON3bits.INT2IE=1)
#define EXTERNAL_INT2_INTERRUPT_DISABLE()           (INTCON3bits.INT2IE=0)
#define EXTERNAL_INT2_INTERRUPT_FLAG_ENABLE()       (INTCON3bits.INT2IF=1)
#define EXTERNAL_INT2_INTERRUPT_FLAG_CLEAR()        (INTCON3bits.INT2IF=0)
#define EXTERNAL_INT2_RISING_EDGE()                 (INTCON2bits.INTEDG2=1)
#define EXTERNAL_INT2_FALLING_EDGE()                (INTCON2bits.INTEDG2=0)

 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine set the INT1 External Interrupt Priority to be High priority */
#define EXTERNAL_INT1_HighPrioritySet()             (INTCON3bits.INT1IP = 1)
/* This routine set the INT1 External Interrupt Priority to be Low priority */
#define EXTERNAL_INT1_LowPrioritySet()              (INTCON3bits.INT1IP = 0)
/* This routine set the INT2 External Interrupt Priority to be High priority */
#define EXTERNAL_INT2_HighPrioritySet()             (INTCON3bits.INT2IP = 1)
/* This routine set the INT2 External Interrupt Priority to be Low priority */
#define EXTERNAL_INT2_LowPrioritySet()              (INTCON3bits.INT2IP = 0)
#endif
#endif


#if EXTERNAL_INTERRUPT_RBx_OnCahnge_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define EXTERNAL_ON_CHANGE_RBx_INTERRUPT_ENABLE()               (INTCONbits.RBIE=1)
#define EXTERNAL_ON_CHANGE_RBx_INTERRUPT_DISABLE()              (INTCONbits.RBIE=0)
#define EXTERNAL_ON_CHANGE_RBx_INTERRUPT_FLAG_CLEAR()           (INTCONbits.RBIF=0)



#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

#define EXTERNAL_ON_CHANGE_RBx_HighPrioritySet()                (INTCON2bits.RBIP=1)
#define EXTERNAL_ON_CHANGE_RBx_LowPrioritySet()                 (INTCON2bits.RBIP=0)

#endif
#endif




/*.....................................Data Types Declarations.....................................*/
typedef void (* interrupt_handler) (void);


typedef enum{
    INTERRUPT_FALLING_EDGE=0,
    INTERRUPT_RISING_EDGE
}interrupt_INTx_edge_t;


typedef enum{
    INTERRUPT_INT0=0,
    INTERRUPT_INT1,
    INTERRUPT_INT2
}interrupt_INTx_source_t;

typedef struct{
    pin_config_t intx_pin;
    interrupt_INTx_edge_t edge;
    interrupt_INTx_source_t src;
    interrupt_priority_cfg priority;
    void (* external_interrupt_handler) (void);
}interrupt_INTx_t;

typedef struct{
    pin_config_t rbx_pin;
    interrupt_priority_cfg priority;
    void (* external_High_interrupt_handler) (void);
    void (* external_Low_interrupt_handler) (void);
}interrupt_RBx_t;

/*typedef struct{
    pin_config_t rbx_pin;
    interrupt_priority_cfg priority;
    void (* external_interrupt_handler) (void);
}interrupt_RBx_t;*/


Std_RetrunType interrupt_INTx_Init(const interrupt_INTx_t *intr_obj);

Std_RetrunType interrupt_INTx_DeInit(const interrupt_INTx_t *intr_obj);

Std_RetrunType interrupt_RBx_Init(const interrupt_RBx_t *intr_obj);

Std_RetrunType interrupt_RBx_DeInit(const interrupt_RBx_t *intr_obj);

/*.....................................Functions Declarations.....................................*/
#endif	/* MCAL_EXTERNAL_INTERRUPT_H */


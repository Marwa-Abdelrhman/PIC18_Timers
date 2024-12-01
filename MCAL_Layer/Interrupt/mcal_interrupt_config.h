/* 
 * File:   mcal_interrupt_config.h
 * Author: Marwa Abdelrahman
 * Brief: this file contains declarations for High and Low priority interrupts
 * Created on September 29, 2024, 2:36 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H


/*.....................................Includes.....................................*/

#include <xc.h>
//#include "../proc/pic18f46k20.h"
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "mcal_interrupt_generated_cfg.h"
/*.....................................Macros Declarations.....................................*/

#define INTERRUPT_ENABLE             1
#define INTERRUPT_DISABLE            0
#define INTERRUPT_FLAG_OCCUR         1
#define INTERRUPT_FLAG_NOT_OCCUR     0
#define INTERRUPT_PRIORITY_ENABLE    1
#define INTERRUPT_PRIORITY_DISABLE   0


/*.....................................Macros Functions Declarations.....................................*/

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

#define INTERRUPT_ENABLE_GLOBAL_HIGH_PRIORITY_INTERRUPTS()           (INTCONbits.GIEH=1)
#define INTERRUPT_DISABLE_GLOBAL_HIGH_PRIORITY_INTERRUPTS()          (INTCONbits.GIEH=0)


#define INTERRUPT_ENABLE_GLOBAL_LOW_PRIORITY_INTERRUPTS()            (INTCONbits.GIEL=1)
#define INTERRUPT_DISABLE_GLOBAL_LOW_PRIORITY_INTERRUPTS()           (INTCONbits.GIEL=0)

#define INTERRUPT_ENABLE_PRIORITY_LEVELS_INTERRUPTS()                (RCONbits.IPEN=1)
#define INTERRUPT_DISABLE_PRIORITY_LEVELS_INTERRUPTS()               (RCONbits.IPEN=1)

#else

#define INTERRUPT_ENABLE_GLOBAL_INTERRUPTS()                         (INTCONbits.GIE=1)
#define INTERRUPT_DISABLE_GLOBAL_INTERRUPTS()                        (INTCONbits.GIE=0)

#define INTERRUPT_ENABLE_PERIPHERAL_INTERRUPTS()                     (INTCONbits.PEIE=1)
#define INTERRUPT_DISABLE_PERIPHERAL_INTERRUPTS()                    (INTCONbits.PEIE=0)
#endif

/*.....................................Data Types Declarations.....................................*/
typedef enum{
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY        
}interrupt_priority_cfg;
/*.....................................Functions Declarations.....................................*/

#endif	/* MCAL_INTERRUPT_CONFIG_H */


/* 
 * File:   mcal_internal_interrupt.h
 * Author: Marwa Abdelrahman
 *
 * Created on September 29, 2024, 2:36 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H






/*.....................................Includes.....................................*/
#include "mcal_interrupt_config.h"

/*.....................................Macros Declarations.....................................*/
/*configure ADC interrupt*/
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define ADC_INTERRUPT_ENABLE()             (PIE1bits.ADIE=1)
#define ADC_INTERRUPT_DISABLE()            (PIE1bits.ADIE=0)
#define ADC_INTERRUPT_FLAG_CLEAR()         (PIR1bits.ADIF=0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  == INTERRUPT_FEATURE_ENABLE
#define ADC_INTERRUPT_HighPrioritySet()    (IPR1bits.ADIP=1)
#define ADC_INTERRUPT_LowPrioritySet()     (IPR1bits.ADIP=0)
#endif
#endif

/*configure timer0 interrupt*/
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define TIMER0_INTERRUPT_ENABLE()             (INTCONbits.TMR0IE=1)
#define TIMER0_INTERRUPT_DISABLE()            (INTCONbits.TMR0IE=0)
#define TIMER0_INTERRUPT_FLAG_CLEAR()         (INTCONbits.TMR0IF=0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  == INTERRUPT_FEATURE_ENABLE
#define TIMER0_INTERRUPT_HighPrioritySet()    (INTCON2bits.TMR0IP=1)
#define TIMER0_INTERRUPT_LowPrioritySet()     (INTCON2bits.TMR0IP=0)
#endif
#endif

/*configure timer1 interrupt*/
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define TIMER1_INTERRUPT_ENABLE()             (PIE1bits.TMR1IE=1)
#define TIMER1_INTERRUPT_DISABLE()            (PIE1bits.TMR1IE=0)
#define TIMER1_INTERRUPT_FLAG_CLEAR()         (PIR1bits.TMR1IF=0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  == INTERRUPT_FEATURE_ENABLE
#define TIMER1_INTERRUPT_HighPrioritySet()    (IPR1bits.TMR1IP=1)
#define TIMER1_INTERRUPT_LowPrioritySet()     (IPR1bits.TMR1IP=0)
#endif
#endif

/*configure timer2 interrupt*/
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUPT_ENABLE()             (PIE1bits.TMR2IE=1)
#define TIMER2_INTERRUPT_DISABLE()            (PIE1bits.TMR2IE=0)
#define TIMER2_INTERRUPT_FLAG_CLEAR()         (PIR1bits.TMR2IF=0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  == INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUPT_HighPrioritySet()    (IPR1bits.TMR2IP=1)
#define TIMER2_INTERRUPT_LowPrioritySet()     (IPR1bits.TMR2IP=0)
#endif
#endif


/*configure timer3 interrupt*/
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define TIMER3_INTERRUPT_ENABLE()             (PIE2bits.TMR3IE=1)
#define TIMER3_INTERRUPT_DISABLE()            (PIE2bits.TMR3IE=0)
#define TIMER3_INTERRUPT_FLAG_CLEAR()         (PIR2bits.TMR3IF=0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  == INTERRUPT_FEATURE_ENABLE
#define TIMER3_INTERRUPT_HighPrioritySet()    (IPR2bits.TMR3IP=1)
#define TIMER3_INTERRUPT_LowPrioritySet()     (IPR2bits.TMR3IP=0)
#endif
#endif

/*.....................................Macros Functions Declarations.....................................*/



/*.....................................Data Types Declarations.....................................*/
/*.....................................Functions Declarations.....................................*/
#endif	/* MCAL_INTERNAL_INTERRUPT_H */


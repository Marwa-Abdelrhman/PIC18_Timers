/* 
 * File:   mcal_interrupt_manager.h
 * Author: Marwa Abdelrahman
 *
 * Created on September 29, 2024, 2:35 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H



/*.....................................Includes.....................................*/


#include "mcal_interrupt_config.h"
//#include "mcal_external_interrupt.h"
/*.....................................Macros Declarations.....................................*/


/*.....................................Macros Functions Declarations.....................................*/



/*.....................................Data Types Declarations.....................................*/
/*.....................................Functions Declarations.....................................*/

/*INTx ISR*/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
//void  RB4_ISR_trial(void);
/*RBx ISR*/

void RB4_ISR(uint8 state);
void RB5_ISR(uint8 state);
void RB6_ISR(uint8 state);
void RB7_ISR(uint8 state);


void ADC_ISR(void);
void TIMER0_ISR(void);
void TIMER1_ISR(void);
void TIMER2_ISR(void);
void TIMER3_ISR(void);
#endif	/* MCAL_INTERRUPT_MANAGER_H */


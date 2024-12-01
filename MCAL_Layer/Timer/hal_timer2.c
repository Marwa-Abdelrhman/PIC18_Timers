/* 
 * File:   hal_timer2.c
 * Author: Marwa Abdelrahman
 *
 * Created on November 22, 2024, 2:51 PM
 */

#include "hal_timer2.h"
static uint8 timer2Preload_val;

#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
  static void (* TIMER2_Set_Interrupt_Handler)(void) =NULL;
#endif
  
  
/*.....................................Function Definitions.....................................*/
Std_RetrunType TIMER2_Init(const timer2_t  *tmr2_obj){
    Std_RetrunType ret = E_NOK;
    if(tmr2_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
       TIMER2_DISABLE();
       TIMER2_SET_PRESCALER_VALUE(tmr2_obj->prescaler_value);
       TIMER2_SET_POSTSCALER_VALUE(tmr2_obj->postscaler_value);
       TMR2=(uint8)(tmr2_obj->timer2_preload_val);
       timer2Preload_val=tmr2_obj->timer2_preload_val;
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
     TIMER2_Set_Interrupt_Handler = tmr2_obj->TIMER2_Interrupt_Handler;
     TIMER2_INTERRUPT_ENABLE();
     TIMER2_INTERRUPT_FLAG_CLEAR();
     
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  == INTERRUPT_FEATURE_ENABLE
     INTERRUPT_ENABLE_PRIORITY_LEVELS_INTERRUPTS();
    if(tmr2_t->timer2_priority == INTERRUPT_HIGH_PRIORITY){
        TIMER2_INTERRUPT_HighPrioritySet();  
        INTERRUPT_ENABLE_GLOBAL_HIGH_PRIORITY_INTERRUPTS();
    }
    else if(tmr2_t->timer1_priority == INTERRUPT_LOW_PRIORITY){
         TIMER2_INTERRUPT_LowPrioritySet();
         INTERRUPT_ENABLE_GLOBAL_LOW_PRIORITY_INTERRUPTS();
    }
    else{/*NoThing*/}
#else    
 INTERRUPT_ENABLE_GLOBAL_INTERRUPTS();
 INTERRUPT_ENABLE_PERIPHERAL_INTERRUPTS();
#endif
#endif 
       TIMER2_ENABLE();
        ret=E_OK;
    }
    
    
    return ret;
}

Std_RetrunType TIMER2_DeInit(const timer2_t  *tmr2_obj){
    Std_RetrunType ret = E_NOK;
    if(tmr2_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
       TIMER2_DISABLE();
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    TIMER2_INTERRUPT_DISABLE();
#endif 
       
        ret=E_OK;
    }
    
    
    return ret;
}

Std_RetrunType TIMER2_read_value(const timer2_t  *tmr2_obj,uint8 *tmr2_val){
    Std_RetrunType ret = E_NOK;
    
    if(tmr2_obj == NULL || tmr2_val==NULL )
    {
        ret=E_NOK;
    }
    else
    {
        *tmr2_val=(uint8)TMR2;
       
        ret=E_OK;
    }
    
    
    return ret;
}


Std_RetrunType TIMER2_write(const timer2_t  *tmr2_obj,uint8 tmr2_val){
    Std_RetrunType ret = E_NOK;
    if(tmr2_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        TMR2=tmr2_val;
        ret=E_OK;
    }
    
    
    return ret;
}

void TIMER2_ISR(void){
    TIMER2_INTERRUPT_FLAG_CLEAR();
    TMR2=timer2Preload_val;
    if(TIMER2_Set_Interrupt_Handler){
        TIMER2_Set_Interrupt_Handler();
    }
}
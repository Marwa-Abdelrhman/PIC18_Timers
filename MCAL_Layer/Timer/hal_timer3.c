/* 
 * File:   hal_timer3.c
 * Author: Marwa Abdelrahman
 *
 * Created on November 22, 2024, 2:51 PM
 */

#include "hal_timer3.h"


static uint16 timer3Preload_val;

#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
  static void (* TIMER3_Set_Interrupt_Handler)(void) =NULL;
#endif
  
  
/*.....................................Function Definitions.....................................*/
Std_RetrunType TIMER3_Init(const timer3_t  *tmr3_obj){
    Std_RetrunType ret = E_NOK;
    if(tmr3_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
       TIMER3_DISABLE();
       TIMER3_SET_PRESCALER_VALUE(tmr3_obj->prescaler_value);
       TMR3H=(tmr3_obj->timer3_preload_val)>>8;
       TMR3L=(uint8)(tmr3_obj->timer3_preload_val);
       timer3Preload_val=tmr3_obj->timer3_preload_val;
       
       if(tmr3_obj->timer3_mode == TIMER3_TIMER_MODE_ON){
           TIMER3_SELECT_TIMER_MODE();
       }
       else if(tmr3_obj->timer3_mode == TIMER3_COUNTER_MODE_ON){
           TIMER3_SELECT_COUNTER_MODE();
            if(tmr3_obj->counter_mode == TIMER3_COUNTER_SYNC_CFG){
                 TIMER3_COUNTER_SYNC_MODE();
            }
            else if(tmr3_obj->counter_mode == TIMER3_COUNTER_ASYNC_CFG){
                 TIMER3_COUNTER_ASYNC_MODE();
            }
      
       }
      
       if(tmr3_obj->timer3_reg_size == TIMER3_16_BIT_REG_RW){
            TIMER3_16_BIT_REG_RW_MODE();
       }
       else if(tmr3_obj->timer3_reg_size == TIMER3_8_BIT_REG_RW){
            TIMER3_8_BIT_REG_RW_MODE();
       }
       
     
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
     TIMER3_Set_Interrupt_Handler = tmr3_obj->TIMER3_Interrupt_Handler;
     TIMER3_INTERRUPT_ENABLE();
     TIMER3_INTERRUPT_FLAG_CLEAR();
     
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  == INTERRUPT_FEATURE_ENABLE
     INTERRUPT_ENABLE_PRIORITY_LEVELS_INTERRUPTS();
    if(tmr3_t->timer3_priority == INTERRUPT_HIGH_PRIORITY){
        TIMER3_INTERRUPT_HighPrioritySet();  
        INTERRUPT_ENABLE_GLOBAL_HIGH_PRIORITY_INTERRUPTS();
    }
    else if(tmr3_t->timer1_priority == INTERRUPT_LOW_PRIORITY){
         TIMER3_INTERRUPT_LowPrioritySet();
         INTERRUPT_ENABLE_GLOBAL_LOW_PRIORITY_INTERRUPTS();
    }
    else{/*NoThing*/}
#else    
 INTERRUPT_ENABLE_GLOBAL_INTERRUPTS();
 INTERRUPT_ENABLE_PERIPHERAL_INTERRUPTS();
#endif
#endif 
       TIMER3_ENABLE();
       ret=E_OK;
    }
    
    
    return ret;
}


Std_RetrunType TIMER3_DeInit(const timer3_t  *tmr3_obj){
    Std_RetrunType ret = E_NOK;
    if(tmr3_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
       TIMER3_DISABLE();
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    TIMER3_INTERRUPT_DISABLE();
#endif 
       
        ret=E_OK;
    }
    
    
    return ret;
}

Std_RetrunType TIMER3_read_value(const timer3_t  *tmr3_obj,uint16 *tmr3_val){
    Std_RetrunType ret = E_NOK;
    uint8 l_timer3_L=ZERO,l_timer3_H=ZERO;
    
    if(tmr3_obj == NULL || tmr3_val==NULL )
    {
        ret=E_NOK;
    }
    else
    {
        l_timer3_L=TMR3L;
        l_timer3_H=TMR3H;
        *tmr3_val=(uint16)((l_timer3_H<<8)+l_timer3_L);
       
        ret=E_OK;
    }
    
    
    return ret;
}



Std_RetrunType TIMER3_write(const timer3_t  *tmr3_obj,uint16 tmr3_val){
    Std_RetrunType ret = E_NOK;
    if(tmr3_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
       TMR3H=tmr3_val>>8;
       TMR3L=(uint8)tmr3_val;
        ret=E_OK;
    }
    
    
    return ret;
}

void TIMER3_ISR(void){
    TIMER3_INTERRUPT_FLAG_CLEAR();
    TMR3H=(timer3Preload_val>>8);
    TMR3L=(uint8)(timer3Preload_val);
    if(TIMER3_Set_Interrupt_Handler){
        TIMER3_Set_Interrupt_Handler();
    }
}
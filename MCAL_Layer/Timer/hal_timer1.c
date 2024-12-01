/* 
 * File:   hal_timer1.c
 * Author: Marwa Abdelrahman
 *
 * Created on November 20, 2024, 11:22 PM
 */

#include "hal_timer1.h"



static uint16 timer1Preload_val;

#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
  static void (* TIMER1_Set_Interrupt_Handler)(void) =NULL;
#endif
  
  
/*.....................................Function Definitions.....................................*/
Std_RetrunType TIMER1_Init(const timer1_t  *tmr1_obj){
    Std_RetrunType ret = E_NOK;
    if(tmr1_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
       TIMER1_DISABLE();
       TIMER1_SET_PRESCALER_VALUE(tmr1_obj->prescaler_value);
       TMR1H=(tmr1_obj->timer1_preload_val)>>8;
       TMR1L=(uint8)(tmr1_obj->timer1_preload_val);
       timer1Preload_val=tmr1_obj->timer1_preload_val;
       
       if(tmr1_obj->timer1_mode == TIMER1_TIMER_MODE_ON){
           TIMER1_SELECT_TIMER_MODE();
       }
       else if(tmr1_obj->timer1_mode == TIMER1_COUNTER_MODE_ON){
           TIMER1_SELECT_COUNTER_MODE();
            if(tmr1_obj->counter_clk == TIMER1_COUNTER_SYNC_CFG){
                 TIMER1_COUNTER_SYNC_MODE();
            }
            else if(tmr1_obj->counter_clk == TIMER1_COUNTER_ASYNC_CFG){
                 TIMER1_COUNTER_ASYNC_MODE();
            }
      
       }
      
       if(tmr1_obj->timer1_reg_size == TIMER1_16_BIT_REG_RW){
            TIMER1_16_BIT_REG_RW_MODE();
       }
       else if(tmr1_obj->timer1_reg_size == TIMER1_8_BIT_REG_RW){
            TIMER1_8_BIT_REG_RW_MODE();
       }
       if(tmr1_obj->timer1_osc_cfg == TIMER1_ENABLE_OSCILLATOR_CLK){
           TIMER1_OSCILLATOR_CLK_SRC_ON();
       }
       else if(tmr1_obj->timer1_osc_cfg == TIMER1_DISABLE_OSCILLATOR_CLK){
           TIMER1_OSCILLATOR_CLK_SRC_OFF();
       }
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
     TIMER1_Set_Interrupt_Handler = tmr1_obj->TIMER1_Interrupt_Handler;
     TIMER1_INTERRUPT_ENABLE();
     TIMER1_INTERRUPT_FLAG_CLEAR();
     
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  == INTERRUPT_FEATURE_ENABLE
     INTERRUPT_ENABLE_PRIORITY_LEVELS_INTERRUPTS();
    if(tmr1_t->timer1_priority == INTERRUPT_HIGH_PRIORITY){
        TIMER1_INTERRUPT_HighPrioritySet();  
        INTERRUPT_ENABLE_GLOBAL_HIGH_PRIORITY_INTERRUPTS();
    }
    else if(tmr1_t->timer1_priority == INTERRUPT_LOW_PRIORITY){
         TIMER1_INTERRUPT_LowPrioritySet();
         INTERRUPT_ENABLE_GLOBAL_LOW_PRIORITY_INTERRUPTS();
    }
    else{/*NoThing*/}
#else    
 INTERRUPT_ENABLE_GLOBAL_INTERRUPTS();
 INTERRUPT_ENABLE_PERIPHERAL_INTERRUPTS();
#endif
#endif 
       TIMER1_ENABLE();
        ret=E_OK;
    }
    
    
    return ret;
}

Std_RetrunType TIMER1_DeInit(const timer1_t  *tmr1_obj){
    Std_RetrunType ret = E_NOK;
    if(tmr1_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
       TIMER1_DISABLE();
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    TIMER1_INTERRUPT_DISABLE();
#endif 
       
        ret=E_OK;
    }
    
    
    return ret;
}
/**
 * 
 * @param tmr1_obj
 * @param tmr1_val
 * @return 
 */
Std_RetrunType TIMER1_read_value(const timer1_t  *tmr1_obj,uint16 *tmr1_val){
    Std_RetrunType ret = E_NOK;
    uint8 l_timer1_L=ZERO,l_timer1_H=ZERO;
    
    if(tmr1_obj == NULL || tmr1_val==NULL )
    {
        ret=E_NOK;
    }
    else
    {
        l_timer1_L=TMR1L;
        l_timer1_H=TMR1H;
        *tmr1_val=(uint16)((l_timer1_H<<8)+l_timer1_L);
       
        ret=E_OK;
    }
    
    
    return ret;
}


/**
 * 
 * @param tmr1_obj
 * @param tmr1_val
 * @return 
 */
Std_RetrunType TIMER1_write(const timer1_t  *tmr1_obj,uint16 tmr1_val){
    Std_RetrunType ret = E_NOK;
    if(tmr1_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
       TMR1H=tmr1_val>>8;
       TMR1L=(uint8)tmr1_val;
        ret=E_OK;
    }
    
    
    return ret;
}

void TIMER1_ISR(void){
    TIMER1_INTERRUPT_FLAG_CLEAR();
    TMR1H=(timer1Preload_val>>8);
    TMR1L=(uint8)(timer1Preload_val);
    if(TIMER1_Set_Interrupt_Handler){
        TIMER1_Set_Interrupt_Handler();
    }
}
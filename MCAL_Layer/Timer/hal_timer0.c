/* 
 * File:   hal_timer0.c
 * Author: Marwa Abdelrahman
 *
 * Created on November 18, 2024, 1:57 PM
 */

#include"hal_timer0.h"


/**
 * 
 * @param timer0_obj
 * @return 
 */

static uint16 timer0Preload_val;

#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
  static void (* TIMER0_Set_Interrupt_Handler)(void) =NULL;
#endif

static inline void configure_timer0_prescaler_value(const timer0_t  *timer0_obj);
static inline void configure_timer0_mode(const timer0_t  *timer0_obj);
static inline void configure_timer0_reg_size(const timer0_t  *timer0_obj);


 
Std_RetrunType TIMER0_Init(const timer0_t  *timer0_obj){
    Std_RetrunType ret = E_NOK;
    if(timer0_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        TIMER0_STOP();
        configure_timer0_prescaler_value(timer0_obj);
        configure_timer0_mode(timer0_obj);
        configure_timer0_reg_size(timer0_obj);
        TMR0H=(timer0_obj->timer0_preload_val)>>8;
        TMR0L=(uint8)(timer0_obj->timer0_preload_val);
        timer0Preload_val=timer0_obj->timer0_preload_val;
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
     TIMER0_Set_Interrupt_Handler = timer0_obj->TIMER0_Interrupt_Handler;
     TIMER0_INTERRUPT_ENABLE();
     TIMER0_INTERRUPT_FLAG_CLEAR();
     
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  == INTERRUPT_FEATURE_ENABLE
     INTERRUPT_ENABLE_PRIORITY_LEVELS_INTERRUPTS();
    if(timer0_t->timer0_priority == INTERRUPT_HIGH_PRIORITY){
        TIMER0_INTERRUPT_HighPrioritySet();  
        INTERRUPT_ENABLE_GLOBAL_HIGH_PRIORITY_INTERRUPTS();
    }
    else if(timer0_t->timer0_priority == INTERRUPT_LOW_PRIORITY){
         TIMER0_INTERRUPT_LowPrioritySet();
         INTERRUPT_ENABLE_GLOBAL_LOW_PRIORITY_INTERRUPTS();
    }
    else{/*NoThing*/}
#else    
 INTERRUPT_ENABLE_GLOBAL_INTERRUPTS();
 INTERRUPT_ENABLE_PERIPHERAL_INTERRUPTS();
#endif
#endif 
       TIMER0_ENABLE();
        ret=E_OK;
    }
    
    
    return ret;
}
Std_RetrunType TIMER0_DeInit(const timer0_t  *timer0_obj){
    Std_RetrunType ret = E_NOK;
    if(timer0_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
       TIMER0_STOP();
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    TIMER0_INTERRUPT_DISABLE();
#endif 
       
        ret=E_OK;
    }
    
    
    return ret;
}
Std_RetrunType TIMER0_read_value(const timer0_t  *timer0_obj,uint16 *timer0_val){
    Std_RetrunType ret = E_NOK;
    uint8 l_timer0_L=ZERO,l_timer0_H=ZERO;
    
    if(timer0_obj == NULL || timer0_val==NULL )
    {
        ret=E_NOK;
    }
    else
    {
        l_timer0_L=TMR0L;
        l_timer0_H=TMR0H;
        *timer0_val=(uint16)((l_timer0_H<<8)+l_timer0_L);
       
        ret=E_OK;
    }
    
    
    return ret;
}
Std_RetrunType TIMER0_write(const timer0_t  *timer0_obj,uint16 timer0_val){
    Std_RetrunType ret = E_NOK;
    if(timer0_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
       TMR0H=timer0_val>>8;
       TMR0L=(uint8)timer0_val;
        ret=E_OK;
    }
    
    
    return ret;
}


void TIMER0_ISR(void){
    
    TIMER0_INTERRUPT_FLAG_CLEAR();
    TMR0H=(timer0Preload_val>>8);
    TMR0L=(uint8)(timer0Preload_val);
    if(TIMER0_Set_Interrupt_Handler){
        TIMER0_Set_Interrupt_Handler();
    }
}

static inline void configure_timer0_prescaler_value(const timer0_t  *timer0_obj){
    if(timer0_obj->prescaler_cfg==TIMER0_ENABLE_PRESCALER_CFG){
        TIMER0_PRESCALER_ON();
        T0CONbits.T0PS=timer0_obj->prescaler_value;
    }
    else if(timer0_obj->prescaler_cfg==TIMER0_DISABLE_PRESCALER_CFG){
        TIMER0_PRESCALER_OFF();
    }
    else{/*NoThing*/}
    
}
static inline void configure_timer0_mode(const timer0_t  *timer0_obj){
    if(timer0_obj->timer0_mode == TIMER0_TIMER_MODE_ON){
        TIMER0_SELECT_TIMER_MODE();
    }
    else if(timer0_obj->timer0_mode == TIMER0_COUNTER_MODE_ON){
        TIMER0_SELECT_COUNTER_MODE();
        /*select egde*/
        if(timer0_obj->counter_edge_cfg==TIMER0_FALLING_EDGE_CFG){
            TIMER0_COUNTER_ON_RISING_EDGE();
        }
        else if(timer0_obj->counter_edge_cfg==TIMER0_FALLING_EDGE_CFG){
            TIMER0_COUNTER_ON_FALLING_EDGE();
        }
    }
    else{/*NoThing*/}
}
static inline void configure_timer0_reg_size(const timer0_t  *timer0_obj){
    if(timer0_obj->timer0_reg_size == TIMER0_16_BIT_REG_SIZE){
        TIMER0_16_BIT_REG();
    }
    else  if(timer0_obj->timer0_reg_size == TIMER0_8_BIT_REG_SIZE){
        TIMER0_8_BIT_REG();
    }
    else{/*NoThing*/}
}
/* 
 * File:   hal_adc.c
 * Author: Marwa Abdelrahman
 *
 * Created on October 25, 2024, 3:47 PM
 */


#include "hal_adc.h"


#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
  static void (* ADC_Set_Interrupt_Handler)(void) =NULL;
#endif

  
static inline void configure_adc_volatage_ref(const adc_t *adc_obj);
static inline void configure_adc_result_format(const adc_t *adc_obj);
static inline void configure_adc_channel_port(adc_channel_t adc_ch);
  
  
/**
 * 
 * @brief
 * @param adc_obj pointer to ADC object defined @ref adc_t
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType ADC_Init(const adc_t *adc_obj){
    Std_RetrunType ret = E_NOK;
    if(adc_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        ADC_DISABLE();
        ADCON2bits.ADCS=adc_obj->conv_clk;
        ADCON2bits.ACQT=adc_obj->acqui_time;
        ADCON0bits.CHS=adc_obj->chnl;
        configure_adc_channel_port(adc_obj->chnl);
      
        
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_ENABLE();
        ADC_INTERRUPT_FLAG_CLEAR();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_ENABLE_PRIORITY_LEVELS_INTERRUPTS();
        if(adc_obj->adc_priority == INTERRUPT_HIGH_PRIORITY){
            INTERRUPT_ENABLE_GLOBAL_HIGH_PRIORITY_INTERRUPTS()  
            ADC_INTERRUPT_HighPrioritySet();
        }
        else if(adc_obj->adc_priority == INTERRUPT_LOW_PRIORITY){
            INTERRUPT_ENABLE_GLOBAL_LOW_PRIORITY_INTERRUPTS();  
            ADC_INTERRUPT_LowPrioritySet();
        }
        else{/*NoThing*/}
#else
      
        INTERRUPT_ENABLE_GLOBAL_INTERRUPTS();
        INTERRUPT_ENABLE_PERIPHERAL_INTERRUPTS();  
#endif
        ADC_Set_Interrupt_Handler=adc_obj->ADC_Interrupt_Handler;
#endif
        configure_adc_volatage_ref(adc_obj);
        configure_adc_result_format(adc_obj);

        ADC_ENABLE();

        ret=E_OK;
    }
    
    
    return ret;
}
/**
 * @brief
 * @param adc_obj pointer to ADC object defined @ref adc_t
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType ADC_DeInit(const adc_t *adc_obj){
    Std_RetrunType ret = E_NOK;
    if(adc_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        /* Disable the ADC */
        ADC_DISABLE();
        /* Disable the interrupt */
        #if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_DISABLE();
        #endif
        ret=E_OK;
    }
    
    
    return ret;
}
/**
 * @brief
 * @param adc_obj pointer to ADC object defined @ref adc_t
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType ADC_start_conversion(const adc_t *adc_obj){
    Std_RetrunType ret = E_NOK;
    if(adc_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        ADC_START_CONVERSION();
       
        ret=E_OK;
    }
    
    
    return ret;   
}
/**
 * @brief
 * @param adc_obj pointer to ADC object defined @ref adc_t
 * @param adc_conv_status
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType ADC_is_conversion_done(const adc_t *adc_obj,uint8 *adc_conv_status){
    Std_RetrunType ret = E_NOK;
    if(adc_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        
       *adc_conv_status= (uint8)(!(ADCON0bits.GODONE));  
        ret=E_OK;
    }
    
    
    return ret;
}
/**
 * @brief
 * @param adc_obj pointer to ADC object defined @ref adc_t
 * @param chanel
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType ADC_select_channel(const adc_t *adc_obj,adc_channel_t chanel){
    Std_RetrunType ret = E_NOK;
    if(adc_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        /* Configure the default channel */
        ADCON0bits.CHS=chanel;
        configure_adc_channel_port(chanel);
       
        ret=E_OK;
    }
    
    
    return ret;
}
/**
 * @brief
 * @param adc_obj pointer to ADC object defined @ref adc_t
 * @param adc_result
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType ADC_get_conversion_result(const adc_t *adc_obj,uint16 *adc_result){
    Std_RetrunType ret = E_NOK;
    if(adc_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        if(adc_obj->result_format == ADC_RESULT_TO_LEFT)
        {
            *adc_result=(uint16)(ADRESH+((ADRESL>>6)<<8));
        
        }
        else if(adc_obj->result_format == ADC_RESULT_TO_RIGHT)
        {
            *adc_result=(uint16)((ADRESH<<8)+ADRESL);
        }
        else
        {
            *adc_result=(uint16)((ADRESH<<8)+ADRESL);
        } 
       
        ret=E_OK;
    }
    
    
    return ret;    
}
/**
 * @brief
 * @param adc_obj pointer to ADC object defined @ref adc_t
 * @param chanel
 * @param adc_result
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType ADC_get_conversion_result_blocking(const adc_t *adc_obj,adc_channel_t chanel,uint16 *adc_result){
    Std_RetrunType ret = E_NOK;
    if(adc_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        ret= ADC_select_channel(adc_obj,chanel);
        ret&=ADC_start_conversion(adc_obj);
        while(ADCON0bits.GODONE != 0);
        ret&=ADC_get_conversion_result(adc_obj,adc_result);
       
        ret=E_OK;
    }
    
    
    return ret;    
}
/**
 * @brief
 * @param adc_obj pointer to ADC object defined @ref adc_t
 * @param chanel
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType ADC_get_conversion_result_interrupt(const adc_t *adc_obj,adc_channel_t chanel){
    Std_RetrunType ret = E_NOK;
    if(adc_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        #if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_FLAG_CLEAR();
        #endif
        ret= ADC_select_channel(adc_obj,chanel);
        ret&=ADC_start_conversion(adc_obj);
       
        ret=E_OK;
    }
    
    
    return ret;   
}

    /*Helper Function*/
static inline void configure_adc_volatage_ref(const adc_t *adc_obj){
    if(adc_obj->voltage_cfg == ADC_ENABLE_VOLT_REF){
       /*VREF- and VREF+*/
        ADC_ENABLE_VOLATAGE_REF();
    }
    else if(adc_obj->voltage_cfg == ADC_DISABLE_VOLT_REF){
        /*VDD and VSS*/
        ADC_DISABLE_VOLATAGE_REF();
    }
    else{/*NoThing*/}
}



static inline void configure_adc_result_format(const adc_t *adc_obj){
    if(adc_obj->result_format == ADC_RESULT_TO_LEFT){
        ADC_RESULT_LEFT_JUSTIFIED();
    }
    else if(adc_obj->result_format == ADC_RESULT_TO_RIGHT){
         ADC_RESULT_RIHGT_JUSTIFIED();
    }
    else{/*NoThing*/} 
}



static inline void configure_adc_channel_port(adc_channel_t adc_ch){
    switch(adc_ch){
        case ADC_CHANNEL_AN0:SET_BIT(TRISA,_TRISA_RA0_POSITION);break;
        case ADC_CHANNEL_AN1:SET_BIT(TRISA,_TRISA_RA1_POSITION);break;
        case ADC_CHANNEL_AN2:SET_BIT(TRISA,_TRISA_RA2_POSITION);break;      
        case ADC_CHANNEL_AN3:SET_BIT(TRISA,_TRISA_RA3_POSITION);break;
        case ADC_CHANNEL_AN4:SET_BIT(TRISA,_TRISA_RA5_POSITION);break;
        case ADC_CHANNEL_AN5:SET_BIT(TRISE,_TRISE_RE0_POSITION);break;
        case ADC_CHANNEL_AN6:SET_BIT(TRISA,_TRISE_RE1_POSITION);break;      
        case ADC_CHANNEL_AN7:SET_BIT(TRISA,_TRISE_RE2_POSITION);break;
        case ADC_CHANNEL_AN8:SET_BIT(TRISB,_TRISB_RB2_POSITION);break;
        case ADC_CHANNEL_AN9:SET_BIT(TRISA,_TRISB_RB3_POSITION);break;
        case ADC_CHANNEL_AN10:SET_BIT(TRISA,_TRISB_RB1_POSITION);break;      
        case ADC_CHANNEL_AN11:SET_BIT(TRISA,_TRISB_RB4_POSITION);break;
        case ADC_CHANNEL_AN12:SET_BIT(TRISA,_TRISB_RB0_POSITION);break;
    }
}
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void ADC_ISR(void){
    ADC_INTERRUPT_FLAG_CLEAR();
    if(ADC_Set_Interrupt_Handler){
         ADC_Set_Interrupt_Handler();
    }
       
}
#endif
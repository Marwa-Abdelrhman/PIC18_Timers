/* 
 * File:   ecu_relay.c
 * Author: Marwa Abdelrahman
 *
 * Created on August 22, 2024, 12:43 PM
 */


#include "ecu_relay.h"

/*.....................................Functions Declarations.....................................*/



/**
 * @brief  initialize relay object to be an output 
 * @param  relay_obj pointer to relay struct @ref relay_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType relay_init(const relay_t * relay_obj){
    Std_RetrunType ret=E_NOK;
    if(NULL == relay_obj)
    {
        ret=E_NOK;
    }
    else
    {
        pin_config_t pin_obj={.port=relay_obj->relay_port,.pin=relay_obj->relay_pin,
                              .direction=GPIO_DIRECTION_OUTPUT,.state=relay_obj->relay_state};
        ret=gpio_pin_init(&(pin_obj));
        
    }
    return ret;
}
/**
 * @brief  turn on relay object  
 * @param  relay_obj pointer to relay struct @ref relay_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType relay_on(const relay_t * relay_obj){
    Std_RetrunType ret=E_NOK;
    if(NULL == relay_obj)
    {
        ret=E_NOK;
    }
    else
    {
        pin_config_t pin_obj={.port=relay_obj->relay_port,.pin=relay_obj->relay_pin,
                              .direction=GPIO_DIRECTION_OUTPUT,.state=relay_obj->relay_state};
        ret=gpio_pin_write(&(pin_obj),GPIO_STATE_HIGH);
        
        
    }
    return ret;
}
/**
 * @brief  turn off relay object  
 * @param  relay_obj pointer to relay struct @ref relay_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType relay_off(const relay_t * relay_obj){
    Std_RetrunType ret=E_NOK;
    if(NULL == relay_obj)
    {
        ret=E_NOK;
    }
    else
    {
        pin_config_t pin_obj={.port=relay_obj->relay_port,.pin=relay_obj->relay_pin,
                              .direction=GPIO_DIRECTION_OUTPUT,.state=relay_obj->relay_state};
        ret=gpio_pin_write(&(pin_obj),GPIO_STATE_LOW);
        
    }
    return ret;
}
/**
 * @brief  toggle relay object state
 * @param  relay_obj pointer to relay struct @ref relay_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType relay_toggle(const relay_t * relay_obj){
    Std_RetrunType ret=E_NOK;
    if(NULL == relay_obj)
    { 
        ret=E_NOK;
    }
    else
    {
        pin_config_t pin_obj={.port=relay_obj->relay_port,.pin=relay_obj->relay_pin,
                              .direction=GPIO_DIRECTION_OUTPUT,.state=relay_obj->relay_state};
        ret=gpio_pin_toggle(&(pin_obj));
        
    }
    return ret;
}


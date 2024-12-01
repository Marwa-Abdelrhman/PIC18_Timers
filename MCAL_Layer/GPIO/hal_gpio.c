/* 
 * File:   hal_gpio.c
 * Author: Marwa Abdelrahman
 *
 * Created on August 1, 2024, 01:10 AM
 */

#include "hal_gpio.h"

#if GPIO_PIN_CONFIGURATIONS  == CONFIG_ENABLE 
/*.....................................Functions Declarations.....................................*/
/**
 * @brief  Initialize the direction of a specific pin @ref direction_t 
 * @param  pin_confg pointer to pin congfigurations struct @ref pin_config_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType gpio_pin_direction_init(const pin_config_t *pin_confg){
    Std_RetrunType ret = E_OK;
    if(pin_confg == NULL || (pin_confg->pin > PIN_INDEX_MAX_NUMBER-1))
    {
        ret=E_NOK;
    }
    else
    {
        switch(pin_confg->direction)
        {
            case GPIO_DIRECTION_OUTPUT:
                CLEAR_BIT(*tris_reg[pin_confg->port],pin_confg->pin);
                break;
            case GPIO_DIRECTION_INPUT:
                SET_BIT(*tris_reg[pin_confg->port],pin_confg->pin);
                break;
            default:ret= E_NOK;
               
        
        }
                
    }
    
    
    return ret;
    
}
#endif

#if GPIO_PIN_CONFIGURATIONS  == CONFIG_ENABLE 
/**
 * @brief get direction status of pin 
 * @param pin_confg pointer to pin congfigurations struct @ref pin_config_t
 * @param pin_dir pointer to struct @ref direction_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType gpio_pin_get_direction_status(const pin_config_t *pin_confg,direction_t *pin_dir){
    Std_RetrunType ret = E_OK;
    if(pin_confg == NULL ||pin_dir ==NULL  ||(pin_confg->pin > PIN_INDEX_MAX_NUMBER-1))
    {
        ret=E_NOK;
    }
    else
    {
        *pin_dir= READ_BIT(*tris_reg[pin_confg->port],pin_confg->pin);
    }
    
    
    return ret;
    
}
#endif
#if GPIO_PIN_CONFIGURATIONS  == CONFIG_ENABLE 
/**
 * @brief write logic high or low (1/0) on pin 
 * @param pin_confg pointer to pin congfigurations struct @ref pin_config_t
 * @param pin_state pointer to pin state struct @ref state_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue
 */

Std_RetrunType gpio_pin_write(const pin_config_t *pin_confg,state_t pin_state){
    Std_RetrunType ret = E_OK;
    if(pin_confg == NULL ||(pin_confg->pin > PIN_INDEX_MAX_NUMBER-1))
    {
        ret=E_NOK;
    }
    else
    {
        switch(pin_state)
        {
            case GPIO_STATE_LOW:
                CLEAR_BIT(*lat_reg[pin_confg->port],pin_confg->pin);
                break;
            case GPIO_STATE_HIGH:
                SET_BIT(*lat_reg[pin_confg->port],pin_confg->pin);
                break;
            default:ret= E_NOK;
                
            
        }
    }
    
    
    return ret;
    
}
#endif
#if GPIO_PIN_CONFIGURATIONS  == CONFIG_ENABLE 
/**
 * @brief read logic high or low (1/0) on pin 
 * @param pin_confg pointer to pin congfigurations struct @ref pin_config_t
 * @param pin_state pointer to pin state struct @ref state_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType gpio_pin_read(const pin_config_t *pin_confg,state_t *pin_state){
    Std_RetrunType ret = E_OK;
       if(pin_confg == NULL ||pin_state ==NULL  ||(pin_confg->pin > PIN_INDEX_MAX_NUMBER-1))
    {
        ret=E_NOK;
    }
    else
    {
           *pin_state=READ_BIT(*port_reg[pin_confg->port],pin_confg->pin);
    }
    
    
    return ret;
    
}
#endif
#if GPIO_PIN_CONFIGURATIONS  == CONFIG_ENABLE 
/**
 * @brief toggle logic on pin
 * @param pin_confg pointer to pin congfigurations struct @ref pin_config_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType gpio_pin_toggle(const pin_config_t *pin_confg){
    Std_RetrunType ret = E_OK;
    if(pin_confg == NULL ||(pin_confg->pin > PIN_INDEX_MAX_NUMBER-1))
    {
        ret=E_NOK;
    }
    else
    {
        TOGGLE_BIT(*lat_reg[pin_confg->port],pin_confg->pin);
    }
    
    
    return ret;
    
    
}
#endif


#if GPIO_PIN_CONFIGURATIONS  == CONFIG_ENABLE 
/**
 * @brief initialize the direction input/output and write logic high or low on pin
 * @param pin_confg pointer to pin congfigurations struct @ref pin_config_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType gpio_pin_init(const pin_config_t *pin_confg){
    Std_RetrunType ret = E_OK;
    if(pin_confg == NULL ||(pin_confg->pin > PIN_INDEX_MAX_NUMBER-1))
    {
        ret=E_NOK;
    }
    else
    {
        ret=gpio_pin_direction_init(pin_confg);
        ret=gpio_pin_write(pin_confg,pin_confg->state);
    }
    
    
    return ret;
}

#endif

#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
/**
 * @brief initialize the direction of port
 * @param port_confg index of port passed to determine port A,B,C,D,E. @refport_t
 * @param port_dir define the direction of port input/output
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType gpio_port_direction_init(port_t port_confg,uint8 port_dir){
    Std_RetrunType ret = E_OK;
    if(port_confg > PORT_INDEX_MAX_NUMBER-1)
    {
        ret = E_NOK;
    }
    else
    {
        *tris_reg[port_confg]=port_dir;
    }
    return ret;
}
#endif

#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
/**
 * @brief read the direction on port 
 * @param port_confg index of port passed to determine port A,B,C,D,E. @refport_t
 * @param port_dir pointer to define the direction of port input/output
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType gpio_port_get_direction_status(port_t port_confg,uint8 *port_dir){
    Std_RetrunType ret = E_OK;
      if(port_confg > PORT_INDEX_MAX_NUMBER-1)
    {
        ret = E_NOK;
    }
    else
    {
          *port_dir=*tris_reg[port_confg];
    }
    return ret;
}
#endif

#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
/**
 * @brief write the logic on port 
 * @param port_confg index of port passed to determine port A,B,C,D,E. @refport_t
 * @param port_state write the logic on port 
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType gpio_port_write(port_t port_confg,uint8 port_state){
    Std_RetrunType ret = E_OK;
      if(port_confg > PORT_INDEX_MAX_NUMBER-1)
    {
        ret = E_NOK;
    }
    else
    {
          *lat_reg[port_confg]=port_state;
    }
    return ret;
}
#endif

#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
/**
 * @brief read the logic on port 
 * @param port_confg index of port passed to determine port A,B,C,D,E. @refport_t
 * @param port_state pointer to the logic on port 
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType gpio_port_read(port_t port_confg,uint8 *port_state){
    Std_RetrunType ret = E_OK;
      if(port_confg > PORT_INDEX_MAX_NUMBER-1)
    {
        ret = E_NOK;
    }
    else
    {
          *port_state=*lat_reg[port_confg];
    }
    return ret;
}
#endif

#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
/**
 * @brief toggle the logic on port 
 * @param port_confg index of port passed to determine port A,B,C,D,E. @refport_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType gpio_port_toggle(port_t port_confg){
    Std_RetrunType ret = E_OK;
      if(port_confg > PORT_INDEX_MAX_NUMBER-1)
    {
        ret = E_NOK;
    }
    else
    {
          *lat_reg[port_confg] ^= PORT_MASK;
    }
    return ret;
}
#endif


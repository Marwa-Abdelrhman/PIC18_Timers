/* 
 * File:   ecu_led.c
 * Author: Marwa Abdelrahman
 *
 * Created on August 1, 2024, 02:10 AM
 */


#include "ecu_led.h"



/**
 * @breif initialize the led on pin 
 * @param led pointer to led struct @ref led_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType led_init(const led_t *led){
    Std_RetrunType ret=E_OK;
    if(NULL == led)
    {
        ret=E_NOK;
    }
    else
    {
        pin_config_t pin_cfg={.port=led->port_name,.pin=led->pin,
                              .direction=GPIO_DIRECTION_OUTPUT,.state=led->led_state};
        gpio_pin_init(&pin_cfg);
    }
    return ret;
}
/**
 * @breif turn led on 
 * @param led pointer to led struct @ref led_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType led_on(const led_t *led){
    Std_RetrunType ret=E_OK;
    if(NULL == led)
    {
        ret=E_NOK;
    }
    else
    {
          pin_config_t pin_cfg={.port=led->port_name,.pin=led->pin,
                              .direction=GPIO_DIRECTION_OUTPUT,.state=led->led_state};
          gpio_pin_write(&pin_cfg,GPIO_STATE_HIGH);
    }
    return ret;
}
/**
 * @breif turn led off 
 * @param led pointer to led struct @ref led_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType led_off(const led_t *led){
    Std_RetrunType ret=E_OK;
    if(NULL == led)
    {
        ret=E_NOK;
    }
    else
    {
        pin_config_t pin_cfg={.port=led->port_name,.pin=led->pin,
                              .direction=GPIO_DIRECTION_OUTPUT,.state=led->led_state};
        gpio_pin_write(&pin_cfg,GPIO_STATE_LOW);
        
    }
    return ret;
}
/**
 * @breif toggle led state 
 * @param led pointer to led struct @ref led_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType led_toggle(const led_t *led){
    Std_RetrunType ret=E_OK;
    if(NULL == led)
    {
        ret=E_NOK;
    }
    else
    {
        pin_config_t pin_cfg={.port=led->port_name,.pin=led->pin,
                              .direction=GPIO_DIRECTION_OUTPUT,.state=led->led_state};
        gpio_pin_toggle(&pin_cfg);
    }
    return ret;
}
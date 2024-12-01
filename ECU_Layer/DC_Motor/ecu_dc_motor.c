/* 
 * File:   ecu_dc_motor.c
 * Author: Marwa Abdelrahman
 *
 * Created on August 24, 2024, 1:47 PM
 */


#include "ecu_dc_motor.h"





/**
 * 
 * @param dc_motor_obj pointer to dc motor struct @ref dc_motor_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType dc_motor_init(const dc_motor_t *dc_motor_obj){
    Std_RetrunType ret=E_NOK;
    if(NULL == dc_motor_obj)
    { 
        ret=E_NOK;
    }
    else
    {
        gpio_pin_init(&(dc_motor_obj->dc_motor_pin[DC_MOTOR_PIN_1]));
        gpio_pin_init(&(dc_motor_obj->dc_motor_pin[DC_MOTOR_PIN_2]));
       
       
        
    }
    return ret;
    
}
/**
 * 
 * @param dc_motor_obj pointer to dc motor struct @ref dc_motor_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType dc_motor_move_right(const dc_motor_t *dc_motor_obj){
    Std_RetrunType ret=E_NOK;
    if(NULL == dc_motor_obj)
    { 
        ret=E_NOK;
    }
    else
    {
        gpio_pin_write(&(dc_motor_obj->dc_motor_pin[DC_MOTOR_PIN_1]),GPIO_STATE_HIGH);
        gpio_pin_write(&(dc_motor_obj->dc_motor_pin[DC_MOTOR_PIN_2]),GPIO_STATE_LOW);

        
        
    }
    return ret;  
}
/**
 * 
 * @param dc_motor_obj pointer to dc motor struct @ref dc_motor_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType dc_motor_move_left(const dc_motor_t *dc_motor_obj){
    Std_RetrunType ret=E_NOK;
    if(NULL == dc_motor_obj)
    { 
        ret=E_NOK;
    }
    else
    {
        gpio_pin_write(&(dc_motor_obj->dc_motor_pin[DC_MOTOR_PIN_1]),GPIO_STATE_LOW);
        gpio_pin_write(&(dc_motor_obj->dc_motor_pin[DC_MOTOR_PIN_2]),GPIO_STATE_HIGH);
       
        
    }
    return ret;
}
/**
 * 
 * @param dc_motor_obj pointer to dc motor struct @ref dc_motor_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType dc_motor_stop(const dc_motor_t *dc_motor_obj){
    Std_RetrunType ret=E_NOK;
    if(NULL == dc_motor_obj)
    { 
        ret=E_NOK;
    }
    else
    {
       
        gpio_pin_write(&(dc_motor_obj->dc_motor_pin[DC_MOTOR_PIN_1]),GPIO_STATE_LOW);
        gpio_pin_write(&(dc_motor_obj->dc_motor_pin[DC_MOTOR_PIN_2]),GPIO_STATE_LOW);
        
    }
    return ret;
}
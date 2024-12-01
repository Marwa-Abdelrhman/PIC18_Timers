/* 
 * File:   ecu_seven_seg.c
 * Author: Marwa Abdelrahman
 *
 * Created on August 29, 2024, 6:09 AM
 */


#include"ecu_seven_seg.h"

/**
 * @brief initialize pins of seven segment display 
 * @param segment_obj pointer to seven segment struct @ref segment_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType seven_segment_init(const segment_t *segment_obj ){
    Std_RetrunType ret=E_NOK;
    if(NULL == segment_obj)
    { 
        ret=E_NOK;
    }
    else
    {
         ret=gpio_pin_init(&(segment_obj->segment_pins[SEGMENT_PIN0]));
         ret=gpio_pin_init(&(segment_obj->segment_pins[SEGMENT_PIN1]));
         ret=gpio_pin_init(&(segment_obj->segment_pins[SEGMENT_PIN2]));
         ret=gpio_pin_init(&(segment_obj->segment_pins[SEGMENT_PIN3]));
        
    }
    return ret;
}
/**
 * @brief write numbers on seven segment display 
 * @param segment_obj pointer to seven segment struct @ref segment_t
 * @param number the value to be displayed on seven segment display 
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType seven_segment_display_number(const segment_t *segment_obj, uint8 number ){
    Std_RetrunType ret=E_NOK;
    if((NULL == segment_obj) || (number > 9))
    { 
        ret=E_NOK;
    }
    else
    {
        
         ret=gpio_pin_write(&(segment_obj->segment_pins[SEGMENT_PIN0]),(number) & 0x01);
         ret=gpio_pin_write(&(segment_obj->segment_pins[SEGMENT_PIN1]),(number>>1) & 0x01);
         ret=gpio_pin_write(&(segment_obj->segment_pins[SEGMENT_PIN2]),(number>>2) & 0x01);
         ret=gpio_pin_write(&(segment_obj->segment_pins[SEGMENT_PIN3]),(number>>3) & 0x01);
       
        
    }
    return ret;
}

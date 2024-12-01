/* 
 * File:   ecu_button.c
 * Author: Marwa Abdelrahman
 *
 * Created on August 19, 2024, 1:32 PM
 */


#include "ecu_button.h"



/**
 * @brief initialize button object  
 * @param btn_obj pointer to button struct @ref button_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue  
 */
Std_RetrunType button_init(const button_t *btn_obj){
    Std_RetrunType ret=E_NOK;
    if(NULL == btn_obj)
    {
        ret=E_NOK;
    }
    else
    {
        ret=gpio_pin_direction_init(&(btn_obj->btn_pin));
        
    }
    return ret;
}
/**
 * @brief read button object state according to its connection type
 * @param btn_obj pointer to button struct @ref button_t
 * @param btn_state state of button @ref button_state_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue  
 */
Std_RetrunType button_read_state(const button_t *btn_obj,button_state_t *btn_st){
    Std_RetrunType ret=E_NOK;
    state_t pin_state=GPIO_STATE_LOW;
    if((NULL == btn_obj) || (NULL == btn_st) )
    {
        ret=E_NOK;
    }
    else
    {
       ret=gpio_pin_read(&(btn_obj->btn_pin),&(pin_state)); 
      
       switch(btn_obj->btn_connection_typ)
        {
            case BUTTON_ACTIVE_HIGH:
                if(pin_state == GPIO_STATE_HIGH )
                {
                    *btn_st=BUTTON_PRESSED;
                }
                else
                {
                    *btn_st=BUTTON_RELEASED;
                }
                break;
            case BUTTON_ACTIVE_LOW:
                if(pin_state == GPIO_STATE_HIGH )
                {
                    *btn_st=BUTTON_RELEASED;
                }
                else
                {
                    *btn_st=BUTTON_PRESSED;
                }
                break;
            default:break;/* Nothing */
            
        }
       /*if(btn_obj->btn_connection_typ == BUTTON_ACTIVE_HIGH )
       {
         if(pin_state == GPIO_STATE_HIGH )
                {
                    *btn_st=BUTTON_PRESSED;
                }
                else
                {
                    *btn_st=BUTTON_RELEASED;
                }
       }
        else if(btn_obj->btn_connection_typ == BUTTON_ACTIVE_LOW )
        {
               if(pin_state == GPIO_STATE_HIGH )
                {
                    *btn_st=BUTTON_RELEASED;
                }
                else
                {
                    *btn_st=BUTTON_PRESSED;
                }

        }
         else {  }*/
       
        
    }
    return ret;
}
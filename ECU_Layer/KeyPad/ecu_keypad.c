/* 
 * File:   ecu_keypad.c
 * Author: Marwa Abdelrahman
 *
 * Created on September 2, 2024, 2:15 PM
 */


#include"ecu_keypad.h"


static const uint8 keypad_buttons[KEYPAD_ROWS][KEYPAD_COLUMNS]={
                                                                {'7','8','9','/'},
                                                                {'4','5','6','*'},
                                                                {'1','2','3','-'},
                                                                {'#','0','=','+'}
                                                               };



/**
 * @brief initialize pins of keypad
 * @param keypad_obj pointer to keypad struct @ref keypad_t
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType keypad_init(const keypad_t *keypad_obj){
    Std_RetrunType ret=E_NOK;
    uint8 row_count=ZERO,column_count=ZERO;
    if(NULL == keypad_obj)
    { 
        ret=E_NOK;
    }
    else
    {
        for(row_count=ZERO;row_count<KEYPAD_ROWS;row_count++)
        {
            ret=gpio_pin_init(&(keypad_obj->keypad_rows_pins[row_count]));
        }
        for(column_count=ZERO;column_count<KEYPAD_COLUMNS;column_count++)
        {
            ret=gpio_pin_direction_init(&(keypad_obj->keypad_columns_pins[column_count]));
        }
        
    }
    return ret;
}


/**
 * @brief get value of the button pressed at keypad
 * @param keypad_obj pointer to keypad struct @ref keypad_t
 * @param value the button pressed at keypad
 * @return status of function call
 *         (E_OK) the function call is successfull 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType keypad_get_key_pressed(const keypad_t *keypad_obj,uint8 *value){
    Std_RetrunType ret=E_NOK;
     uint8 l_row_count=ZERO,l_column_count=ZERO,l_count=ZERO;
     state_t col_pin_state=ZERO;
     uint8 num=0;
    if((NULL == keypad_obj) || (value == NULL))
    { 
        ret=E_NOK;
    }
    else
    {
        
        for(l_row_count=ZERO;l_row_count<KEYPAD_ROWS;l_row_count++)
        {
            for(l_count=ZERO;l_count<KEYPAD_ROWS;l_count++)
            {
                ret=gpio_pin_write(&(keypad_obj->keypad_rows_pins[l_count]),GPIO_STATE_LOW);
            }
           ret=gpio_pin_write(&(keypad_obj->keypad_rows_pins[l_row_count]),GPIO_STATE_HIGH);
           __delay_ms(50);
           for(l_column_count=ZERO;l_column_count<KEYPAD_COLUMNS;l_column_count++)
            {
                ret=gpio_pin_read(&(keypad_obj->keypad_columns_pins[l_column_count]),&col_pin_state);
                 if(col_pin_state == GPIO_STATE_HIGH)
                 {
                     *value=keypad_buttons[l_row_count][l_column_count];
                     num=*value;
                 }
            }
        }
    
        
       
    }
    return ret;
}
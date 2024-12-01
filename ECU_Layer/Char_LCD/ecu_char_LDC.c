/* 
 * File:   ecu_char_LDC.c
 * Author: Marwa Abdelrahman
 *
 * Created on September 5, 2024, 5:25 PM
 */

#include "ecu_char_LDC.h"




static Std_RetrunType lcd_send_bits(const lcd_t *lcd_obj,uint8 data_cmd);
static Std_RetrunType lcd_send_enable_signal(const lcd_t *lcd_obj);


/**
 * @brief initialize lcd 4-bit and 8-bit modes
 * @param lcd_obj pointer to lcd struct @ref lcd_t
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType lcd_init(const lcd_t * lcd_obj){
    Std_RetrunType ret=E_NOK;
    uint8 l_count=0;
    if(NULL == lcd_obj)
    { 
        ret=E_NOK;
    }
    else
    {
        ret=gpio_pin_init(&(lcd_obj->rs_pin));
        ret=gpio_pin_init(&(lcd_obj->en_pin));
        #if ACTIVATE_4_BIT_CHAR_LCD
            for(l_count=0;l_count< _4BIT;l_count++)
            {
                ret=gpio_pin_init(&(lcd_obj->lcd_4bit_pins[l_count]));
            }
          
   
        #elif  ACTIVATE_8_BIT_CHAR_LCD
            for(l_count=0;l_count< _8BIT;l_count++)
            {
                ret=gpio_pin_init(&(lcd_obj->lcd_8bit_pins[l_count]));
            }
            
    
        #endif
         __delay_ms(20);
        ret=lcd_send_command(lcd_obj, _LCD_8_BIT_MODE_2_LINE_DIPLAY); 
        
        __delay_ms(5);
        ret=lcd_send_command(lcd_obj, _LCD_8_BIT_MODE_2_LINE_DIPLAY); 
        
        __delay_us(150);
        ret=lcd_send_command(lcd_obj, _LCD_8_BIT_MODE_2_LINE_DIPLAY);
        
        ret=lcd_send_command(lcd_obj, _LCD_CLEAR_DISPLAY);
        ret=lcd_send_command(lcd_obj, _LCD_RETURN_HOME);
        ret=lcd_send_command(lcd_obj, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret=lcd_send_command(lcd_obj, _LCD_DIPLAY_ON_CURSOR_OFF);
        
        #if ACTIVATE_4_BIT_CHAR_LCD
            ret=lcd_send_command(lcd_obj, _LCD_4_BIT_MODE_2_LINE_DIPLAY);
            ret=lcd_send_command(lcd_obj, _LCD_DDRAM_START);
   
        #elif  ACTIVATE_8_BIT_CHAR_LCD
            ret=lcd_send_command(lcd_obj, _LCD_8_BIT_MODE_2_LINE_DIPLAY);
            ret=lcd_send_command(lcd_obj, _LCD_DDRAM_START);
    
        #endif
    }
    return ret;
}
/**
 * @brief send command to status register at lcd
 * @param lcd_obj lcd_obj pointer to lcd struct @ref lcd_t
 * @param cmd command to be sent
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType lcd_send_command(const lcd_t * lcd_obj,uint8 cmd){
    Std_RetrunType ret=E_NOK;
    uint8 l_count=0;
    if(NULL == lcd_obj)
    { 
        ret=E_NOK;
    }
    else
    {   
        ret=gpio_pin_write(&(lcd_obj->rs_pin),GPIO_STATE_LOW);
        #if  ACTIVATE_4_BIT_CHAR_LCD
            ret=lcd_send_bits(lcd_obj,cmd>>4);
            ret=lcd_send_enable_signal(lcd_obj);
            ret=lcd_send_bits(lcd_obj,cmd);
            ret=lcd_send_enable_signal(lcd_obj);
   
        #elif  ACTIVATE_8_BIT_CHAR_LCD
            ret=lcd_send_bits(lcd_obj,cmd);
            ret=lcd_send_enable_signal(lcd_obj);
    
        #endif
        
    }
    return ret;
}
/**
 * @brief send data to data register at lcd
 * @param lcd_obj lcd_obj pointer to lcd struct @ref lcd_t
 * @param data to be sent
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType lcd_send_char_data(const lcd_t * lcd_obj,uint8 data){
    Std_RetrunType ret=E_NOK;
    if(NULL == lcd_obj)
    { 
        ret=E_NOK;
    }
    else
    {
        #if  ACTIVATE_4_BIT_CHAR_LCD
        
            ret=gpio_pin_write(&(lcd_obj->rs_pin),GPIO_STATE_HIGH);
            ret=lcd_send_bits(lcd_obj,data>>4);
            ret=lcd_send_enable_signal(lcd_obj);
            ret=lcd_send_bits(lcd_obj,data);
            ret=lcd_send_enable_signal(lcd_obj);
   
        #elif  ACTIVATE_8_BIT_CHAR_LCD

            ret=gpio_pin_write(&(lcd_obj->rs_pin),GPIO_STATE_HIGH);
            ret=lcd_send_bits(lcd_obj,data);
            ret=lcd_send_enable_signal(lcd_obj);
    
        #endif
    }
    return ret; 
}
/**
 * @brief display char at specific position on lcd 
 * @param lcd_obj lcd_obj pointer to lcd struct @ref lcd_t
 * @param data the char value
 * @param row number of row
 * @param col number of col
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType lcd_send_char_data_position(const lcd_t * lcd_obj,uint8 data,uint8 row,uint8 col){
    Std_RetrunType ret=E_NOK;
    if(NULL == lcd_obj)
    { 
        ret=E_NOK;
    }
    else
    {
        ret=lcd_set_cursor_position(lcd_obj,row,col);
        ret=lcd_send_char_data(lcd_obj,data);
   
        
    }
    return ret;  
}
/**
 * @brief display string on lcd
 * @param lcd_obj lcd_obj pointer to lcd struct @ref lcd_t
 * @param str the string to be displayed
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType lcd_send_string_data(const lcd_t * lcd_obj,uint8 *str){
    Std_RetrunType ret=E_NOK;
    if(NULL == lcd_obj)
    { 
        ret=E_NOK;
    }
    else
    {
        while(*str != '\0')
        {
            ret=lcd_send_char_data(lcd_obj,*str++);
        }
     
    }
    return ret; 
}
/**
 * @brief display string at specific position on lcd 
 * @param lcd_obj lcd_obj pointer to lcd struct @ref lcd_t
 * @param str the string to be displayed
 * @param row number of row
 * @param col number of col
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType lcd_send_string_data_position(const lcd_t * lcd_obj,uint8 *str,uint8 row,uint8 col){
    Std_RetrunType ret=E_NOK;
    if(NULL == lcd_obj)
    { 
        ret=E_NOK;
    }
    else
    {
        ret=lcd_set_cursor_position(lcd_obj,row,col);
        ret=lcd_send_string_data(lcd_obj,str);
   
     
        
    }
    return ret; 
}
/**
 * @brief adjust cursor position on lcd
 * @param lcd_obj lcd_obj pointer to lcd struct @ref lcd_t
 * @param row number of row
 * @param col number of col
 * @return  status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType lcd_set_cursor_position(const lcd_t * lcd_obj,uint8 row,uint8 col){
    Std_RetrunType ret=E_NOK;
    if(NULL == lcd_obj)
    { 
        ret=E_NOK;
    }
    else
    {
        col--;
        switch(row)
        {
            case ROW_1:lcd_send_command(lcd_obj,(0x80+col));break;
            case ROW_2:lcd_send_command(lcd_obj,(0xc0+col));break;
            case ROW_3:lcd_send_command(lcd_obj,(0x94+col));break;
            case ROW_4:lcd_send_command(lcd_obj,(0xd4+col));break;
            default:break;
                
        }
       
    }
    return ret; 
}

/**
 * @brief display user defined char on lcd 
 * @param lcd_obj lcd_obj pointer to lcd struct @ref lcd_t
 * @param data array of char to fit 5*11 dots
 * @param row number of row
 * @param col number of col
 * @param mem_pos location to store char in memory the CGROM
 * @return 
 */
 Std_RetrunType lcd_send_custom_char(const lcd_t * lcd_obj,const uint8 data[],uint8 row,uint8 col,uint8 mem_pos){

    Std_RetrunType ret=E_NOK;
    uint8 count=ZERO;
    if(NULL == lcd_obj)
    { 
        ret=E_NOK;
    }
    else
    {
        ret=lcd_send_command(lcd_obj,_LCD_CGRAM_START+(mem_pos*8));
        for(count=0;count<7;count++)
        {
         ret=lcd_send_char_data(lcd_obj,data[count]);   
        }
        ret=lcd_send_char_data_position(lcd_obj,mem_pos,row,col);
        
        
        
    }
    return ret; 
}

/**
 * @brief write bits on lcd pins
 * @param lcd_obj lcd_obj pointer to lcd struct @ref lcd_t
 * @param data_cmd the bits
 * @return status of function call
 *         (E_OK) the function call is successful
 *         (E_NOK) the function call has issue 
 */
static Std_RetrunType lcd_send_bits(const lcd_t *lcd_obj,uint8 data_cmd){
        
     Std_RetrunType ret=E_NOK;
     uint8 l_count=0;
 
        #if  ACTIVATE_4_BIT_CHAR_LCD
            
            for(l_count=0;l_count < _4BIT; l_count++)
            {
                ret=gpio_pin_write(&(lcd_obj->lcd_4bit_pins[l_count]),(data_cmd >> l_count) & (uint8)0x01);
            }
   
        #elif  ACTIVATE_8_BIT_CHAR_LCD
            for(l_count=0;l_count < _8BIT; l_count++)
            {
                ret=gpio_pin_write(&(lcd_obj->lcd_8bit_pins[l_count]),(data_cmd >> l_count) & (uint8)0x01);
            }
        #endif

 
   return ret; 
    
}
/**
 * @brief send enable signal for settings in lcd
 * @param lcd_obj lcd_obj pointer to lcd struct @ref lcd_t
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue 
 */
static Std_RetrunType lcd_send_enable_signal(const lcd_t *lcd_obj)
{
    Std_RetrunType ret=E_NOK;
    
    ret=gpio_pin_write(&(lcd_obj->en_pin),GPIO_STATE_HIGH);
    __delay_us(5);
    ret=gpio_pin_write(&(lcd_obj->en_pin),GPIO_STATE_LOW);
    
    return ret; 
}


/**
 * @brief convert uint8 to string to be displayed on lcd 
 * @param value the value of uint8
 * @param str the converted string
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType convert_uint8_to_string(uint8 value,uint8 *str){
    Std_RetrunType ret=E_NOK;
    if(NULL == str)
    { 
        ret=E_NOK;
    }
    else
    {
        memset(str,'\0',4);
        sprintf(str,"%i",value);
        
    }
    return ret; 
}
/**
 * @brief convert uint16 to string to be displayed on lcd 
 * @param value the value of uint16
 * @param str the converted string
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType convert_uint16_to_string(uint16 value,uint8 *str){
    Std_RetrunType ret=E_NOK;
    if(NULL == str)
    { 
        ret=E_NOK;
    }
    else
    {
       
        memset(str,'\0',6);
        sprintf(str,"%i",value);
        
    }
    return ret;   
}
/**
 * @brief convert uint32 to string to be displayed on lcd 
 * @param value the value of uint32
 * @param str the converted string
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue 
 */
Std_RetrunType convert_uint32_to_string(uint32 value,uint8 *str){
   Std_RetrunType ret=E_NOK;
    if(NULL == str)
    { 
        ret=E_NOK;
    }
    else
    {
       
        memset(str,'\0',11);
        sprintf(str,"%i",value);
        
    }
    return ret;    
}
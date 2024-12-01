 /* 
 * File:   ecu_char_LDC.h
 * Author: Marwa Abdelrahman
 *
 * Created on September 5, 2024, 5:25 PM
 */

#ifndef ECU_CHAR_LDC_H
#define	ECU_CHAR_LDC_H


/*.....................................Includes.....................................*/
#include "ecu_char_LDC_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/*.....................................Macros Declarations.....................................*/
#define ROW_1   1
#define ROW_2   2
#define ROW_3   3
#define ROW_4   4

#define _4BIT    4
#define _8BIT    8

#define ACTIVATE_4_BIT_CHAR_LCD  0         
#define ACTIVATE_8_BIT_CHAR_LCD  1        



#define _LCD_CLEAR_DISPLAY              0x01
#define _LCD_RETURN_HOME                0x02

#define _LCD_ENTRY_MODE_DEC_SHIFT_OFF   0x04
#define _LCD_ENTRY_MODE_DEC_SHIFT_ON    0x05
#define _LCD_ENTRY_MODE_INC_SHIFT_OFF   0x06
#define _LCD_ENTRY_MODE_INC_SHIFT_ON    0x07


#define _LCD_DIPLAY_ON_CURSOR_OFF              0x0C
#define _LCD_DIPLAY_ON_CURSOR_ON               0x0D
#define _LCD_DIPLAY_ON_UNDERLINE_ON_CURSOR_OFF 0x0E
#define _LCD_DIPLAY_ON_UNDERLINE_ON_CURSOR_ON  0x0F


#define _LCD_CURSOR_MOVE_SHIFT_LEFT     0x10
#define _LCD_CURSOR_MOVE_SHIFT_RIGHT    0x14
#define _LCD_SHIFT_DISPLAY_LEFT         0x18
#define _LCD_SHIFT_DISPLAY_RIGHT        0x1C

#define _LCD_4_BIT_MODE_2_LINE_DIPLAY   0x28
#define _LCD_8_BIT_MODE_2_LINE_DIPLAY   0x38

#define _LCD_CGRAM_START                0x40
#define _LCD_DDRAM_START                0x80


/*.....................................Macros Functions Declarations.....................................*/



/*.....................................Data Types Declarations.....................................*/
typedef struct{
    pin_config_t rs_pin;
    pin_config_t en_pin;
    
#if ACTIVATE_4_BIT_CHAR_LCD
    pin_config_t lcd_4bit_pins[4];
#elif  ACTIVATE_8_BIT_CHAR_LCD
    pin_config_t lcd_8bit_pins[8];
#endif
    
}lcd_t;

/*.....................................Functions Declarations.....................................*/
Std_RetrunType lcd_init(const lcd_t * lcd_obj);
Std_RetrunType lcd_send_command(const lcd_t * lcd_obj,uint8 cmd);
Std_RetrunType lcd_send_char_data(const lcd_t * lcd_obj,uint8 data);
Std_RetrunType lcd_send_char_data_position(const lcd_t * lcd_obj,uint8 data,uint8 row,uint8 col);
Std_RetrunType lcd_send_string_data(const lcd_t * lcd_obj,uint8 *str);
Std_RetrunType lcd_send_string_data_position(const lcd_t * lcd_obj,uint8 *str,uint8 row,uint8 col);
Std_RetrunType lcd_set_cursor_position(const lcd_t * lcd_obj,uint8 row,uint8 col);
Std_RetrunType lcd_send_custom_char(const lcd_t * lcd_obj,const uint8 data[],uint8 row,uint8 col,uint8 mem_pos);


Std_RetrunType convert_uint8_to_string(uint8 value,uint8 *str);

Std_RetrunType convert_uint16_to_string(uint16 value,uint8 *str);

Std_RetrunType convert_uint32_to_string(uint32 value,uint8 *str);


#endif	/* ECU_CHAR_LDC_H */


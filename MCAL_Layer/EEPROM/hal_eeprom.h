/* 
 * File:   hal_eeprom.h
 * Author: Marwa Abdelrahman
 *
 * Created on October 21, 2024, 5:08 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H


/*.....................................Includes.....................................*/
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/*.....................................Macros Declarations.....................................*/
#define ACCESS_FLASH_PROGRAM_MEMORY          1
#define ACCESS_DATA_EEPROM_MEMORY            0
#define ACCESS_CONFIG_REGISTERS              1
#define ACCESS_FLASH_EEPROM_MEMORY           0
#define ALLOW_WRITE_CYCLE_TO_EEPROM          1
#define INHIBIT_WRITE_CYCLE_TO_EEPROM         0
#define INIT_DATA_EEPROM_WRITE_ERASE_CYCLE   1
#define WRITE_CYCLE_TO_EEPROM_COMPLETE       0
#define INITIATE_DATA_EEPROM_READ         1

/*.....................................Macros Functions Declarations.....................................*/



/*.....................................Data Types Declarations.....................................*/
/*.....................................Functions Declarations.....................................*/

Std_RetrunType eeprom_write_data(uint16 addr,uint8 data);
Std_RetrunType eeprom_read_data(uint16 addr,uint8 *data);

#endif	/* HAL_EEPROM_H */


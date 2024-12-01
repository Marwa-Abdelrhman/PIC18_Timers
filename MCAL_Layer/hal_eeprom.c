/* 
 * File:   hal_eeprom.c
 * Author: Marwa Abdelrahman
 *
 * Created on October 21, 2024, 5:08 PM
 */


#include "EEPROM/hal_eeprom.h"


/**
 * @brief write data at specific location on EEPROM
 * @param addr the address to write data
 * @param data the data to be written
 * @return status of function call
 *         (E_OK) the function call is successful
 *         (E_NOK) the function call has issue
 */
Std_RetrunType eeprom_write_data(uint16 addr,uint8 data){
    Std_RetrunType ret = E_NOK;
    uint8 intr_status;
    
    /*store interrupt status*/
    intr_status=INTCONbits.GIE;
    /*write an EEPROM data location*/
    EEADRH=(uint8)((addr>>8)&0x03);
    EEADR=(uint8)((addr)&0xFF);
    /*Update the Data Register*/
     EEDATA=data;
      /*Point to DATA memory*/
     EECON1bits.EEPGD=ACCESS_DATA_EEPROM_MEMORY;
     /*Access EEPROM*/
     EECON1bits.CFGS=ACCESS_FLASH_EEPROM_MEMORY;
     /*Enable writes*/
      EECON1bits.WREN=ALLOW_WRITE_CYCLE_TO_EEPROM;
     /*disable interrupts*/
     INTERRUPT_DISABLE_GLOBAL_INTERRUPTS();
    /*initiate the write cycle.*/
    EECON2=0x55;
    EECON2=0x0AA;
    /*set WR bit to Initiates a data EEPROM erase/write cycle*/
    EECON1bits.WR=INIT_DATA_EEPROM_WRITE_ERASE_CYCLE;
    /*wait for write to complete*/
    while(EECON1bits.WR != 0);
    /* Inhibits write cycles to Flash program/data EEPROM */
    EECON1bits.WREN=INHIBIT_WRITE_CYCLE_TO_EEPROM;
    /*restore interrupt status*/
    INTCONbits.GIE= intr_status;
    return ret;
}
/**
 * @brief read data from specific location on EEPROM
 * @param addr the address to read data
 * @param data the data to be read
 * @return status of function call
 *         (E_OK) the function call is successful
 *         (E_NOK) the function call has issue
 */
Std_RetrunType eeprom_read_data(uint16 addr,uint8 *data){
    Std_RetrunType ret = E_NOK;
    if(data == NULL)
    {
        ret=E_NOK;
    }
    else
    {
        /*write an EEPROM data location to read data from it*/
        EEADRH=(uint8)((addr>>8)&0x03);
        EEADR=(uint8)((addr)&0xFF);
        /*Select Access data EEPROM memory*/
         EECON1bits.EEPGD=ACCESS_DATA_EEPROM_MEMORY ;
         /*Access EEPROM*/
         EECON1bits.CFGS=ACCESS_FLASH_EEPROM_MEMORY;
        /*set control bit to Initiates a data EEPROM read cycle*/
         EECON1bits.RD=INITIATE_DATA_EEPROM_READ;
         NOP();/* NOPs may be required for latency at high frequencies */
         NOP();
         /*read data*/
         *data=EEDATA;
         
         
        ret=E_OK;
    }
    return ret;
}
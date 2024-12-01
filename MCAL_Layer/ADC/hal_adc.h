/* 
 * File:   hal_adc.h
 * Author: Marwa Abdelrahman
 *
 * Created on October 25, 2024, 3:47 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/*.....................................Includes.....................................*/
#include "hal_adc_cfg.h"
#include "../GPIO/hal_gpio.h"
#include "../proc/pic18f4620.h"
#include"../Interrupt/mcal_internal_interrupt.h"
#include"../mcal_std_types.h"

/*.....................................Macros Declarations.....................................*/


/* A/D Port Configuration Control bits:Analog and Digital
 * @note  When ADC_AN4_ANALOG_FUNCTIONALITY is configured, this means
 *        AN4,AN3,AN2,AN1,AN0 are Analog functionality.
 */
#define ADC_ALL_ANALOG_PIN     0x00
#define ADC_ALL_DIGITAL_PIN    0x0F
#define ADC_AN0_ANALOG_PIN     0x0E
#define ADC_AN1_ANALOG_PIN     0x0D
#define ADC_AN2_ANALOG_PIN     0x0C
#define ADC_AN3_ANALOG_PIN     0x0B
#define ADC_AN4_ANALOG_PIN     0x0A
#define ADC_AN5_ANALOG_PIN     0x09
#define ADC_AN6_ANALOG_PIN     0x08
#define ADC_AN7_ANALOG_PIN     0x07
#define ADC_AN8_ANALOG_PIN     0x06
#define ADC_AN9_ANALOG_PIN     0x05
#define ADC_AN10_ANALOG_PIN    0x04
#define ADC_AN11_ANALOG_PIN    0x03
#define ADC_AN12_ANALOG_PIN    0x02


#define ADC_RESULT_TO_LEFT     0U
#define ADC_RESULT_TO_RIGHT    1U

#define ADC_ENABLE_VOLT_REF    1U
#define ADC_DISABLE_VOLT_REF   0U


/*.....................................Macros Functions Declarations.....................................*/

/*A/D Conversion Status bit*/
#define ADC_START_CONVERSION()    (ADCON0bits.GODONE=1)
#define ADC_CONVERSION_STATUS()   (ADCON0bits.GO_nDONE)

/*Enable and disable ADC feature*/
#define ADC_ENABLE()              (ADCON0bits.ADON=1)
#define ADC_DISABLE()             (ADCON0bits.ADON=0)


/*select Voltage Reference Configuration */
/*VREF- and VREF+*/
#define ADC_ENABLE_VOLATAGE_REF()   do{ADCON1bits.VCFG1=1;\
                                     ADCON1bits.VCFG0=1;\
                                    }while(0);
/*VDD and VSS*/
#define ADC_DISABLE_VOLATAGE_REF()  do{ADCON1bits.VCFG1=0;\
                                     ADCON1bits.VCFG0=0;\
                                    }while(0);

/**
 * @brief  ADC Port Configuration Control
 * @note   Example : ADC_PORT_CONFIGURATION_ANALOG_DIGITAL(ADC_AN4_ANALOG_PIN);
		   When ADC_AN4_ANALOG_pin is configured, this means
 *         AN4,AN3,AN2,AN1,AN0 are Analog functionality.
 *         @ref A/D Port Configuration Control bits
 */
#define ADC_PORT_CONFIGURATION_ANALOG_DIGITAL(cfg)  (ADCON1bits.PCFG=cfg)

/*A/D Result Format Select bit*/
#define ADC_RESULT_RIHGT_JUSTIFIED()    (ADCON2bits.ADFM=1)
#define ADC_RESULT_LEFT_JUSTIFIED()     (ADCON2bits.ADFM=0)
/*.....................................Data Types Declarations.....................................*/

/**
 * @brief Analog Channel Select
 */
typedef enum{
    ADC_CHANNEL_AN0=0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,        
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,         
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,        
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,        
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12
            
}adc_channel_t;


/*
 * @brief A/D Acquisition Time Select 
 */

typedef enum{
    ADC_0_TAD=0,
    ADC_2_TAD,
    ADC_4_TAD,        
    ADC_6_TAD,
    ADC_8_TAD, 
    ADC_12_TAD,        
    ADC_16_TAD,
    ADC_20_TAD
            
}adc_aquicision_time_t;


/*
 * @brief A/D Conversion Clock Select 
 * If the A/D FRC clock source is selected, a delay of one TCY (instruction cycle) is added before the A/D
 * clock starts. This allows the SLEEP instruction to be executed before starting a conversion
 */
typedef enum{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2=0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,        
    ADC_CONVERSION_CLOCK_FOSC_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,        
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64 
            
}adc_conversion_clk_t;

typedef struct{
    #if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* ADC_Interrupt_Handler)(void);
    interrupt_priority_cfg adc_priority;
    #endif
    adc_conversion_clk_t conv_clk;
    adc_aquicision_time_t acqui_time;
    adc_channel_t chnl;
    uint8 result_format:1;
    uint8 voltage_cfg:1;
    uint8 adc_reserved:6;
    
}adc_t;
/*.....................................Functions Declarations.....................................*/

Std_RetrunType ADC_Init(const adc_t *adc_obj);
Std_RetrunType ADC_DeInit(const adc_t *adc_obj);
Std_RetrunType ADC_start_conversion(const adc_t *adc_obj);
Std_RetrunType ADC_is_conversion_done(const adc_t *adc_obj,uint8 *adc_conv_status);
Std_RetrunType ADC_select_channel(const adc_t *adc_obj,adc_channel_t chanel);
Std_RetrunType ADC_get_conversion_result(const adc_t *adc_obj,uint16 *adc_result);
Std_RetrunType ADC_get_conversion_result_blocking(const adc_t *adc_obj,adc_channel_t chanel,uint16 *adc_result);
Std_RetrunType ADC_get_conversion_result_interrupt(const adc_t *adc_obj,adc_channel_t chanel);


#endif	/* HAL_ADC_H */


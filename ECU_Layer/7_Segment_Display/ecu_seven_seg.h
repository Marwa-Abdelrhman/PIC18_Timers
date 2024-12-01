/* 
 * File:   ecu_seven_seg.h
 * Author: Marwa Abdelrahman
 *
 * Created on August 29, 2024, 6:09 AM
 */

#ifndef ECU_SEVEN_SEG_H
#define	ECU_SEVEN_SEG_H

/*.....................................Includes.....................................*/

#include"ecu_seven_seg_cfg.h"
#include"../../MCAL_Layer/GPIO/hal_gpio.h"


/*.....................................Macros Declarations.....................................*/

#define SEGMENT_PIN0     0X00U
#define SEGMENT_PIN1     0X01U
#define SEGMENT_PIN2     0X02U
#define SEGMENT_PIN3     0X03U

/*.....................................Macros Functions Declarations.....................................*/
typedef enum {
    
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type_t;

typedef struct{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;


/*.....................................Data Types Declarations.....................................*/
/*.....................................Functions Declarations.....................................*/
Std_RetrunType seven_segment_init(const segment_t *segment_obj );
Std_RetrunType seven_segment_display_number(const segment_t *segment_obj, uint8 number );


#endif	/* ECU_SEVEN_SEG_H */


/* 
 * File:   application.c
 * Author: Marwa Abdelrahman
 *
 * Created on August 1, 2024, 12:53 AM
 */


#include"application.h"
#include"MCAL_Layer/Timer/hal_timer0.h"
#include"MCAL_Layer/Timer/hal_timer1.h"
#include"MCAL_Layer/Timer/hal_timer2.h"
#include"MCAL_Layer/Timer/hal_timer3.h"
#include"MCAL_Layer/Interrupt/mcal_internal_interrupt.h"




void timer0_interrupt_ISR(void);
void timer1_interrupt_ISR(void);
void timer2_interrupt_ISR(void);
void timer3_interrupt_ISR(void);




volatile uint8 tmr0_tick,tmr1_tick,tmr2_tick,tmr3_tick;
led_t led_0={.port_name=PORTD_INDEX,.pin=GPIO_PIN0,.led_state=GPIO_STATE_LOW};
led_t led_1={.port_name=PORTD_INDEX,.pin=GPIO_PIN1,.led_state=GPIO_STATE_LOW};
led_t led_2={.port_name=PORTD_INDEX,.pin=GPIO_PIN2,.led_state=GPIO_STATE_LOW};
led_t led_3={.port_name=PORTD_INDEX,.pin=GPIO_PIN3,.led_state=GPIO_STATE_LOW};

//250ms
timer0_t timer0_obj={
    .TIMER0_Interrupt_Handler=timer0_interrupt_ISR,
    .prescaler_cfg=TIMER0_ENABLE_PRESCALER_CFG,
    .prescaler_value=PRECALER_VALUE_DIV_4,
    .timer0_mode=TIMER0_TIMER_MODE_ON,
    .timer0_reg_size=TIMER0_16_BIT_REG_SIZE,
    .timer0_preload_val=3036
};
//250ms
timer1_t timer1_obj={
    .TIMER1_Interrupt_Handler=timer1_interrupt_ISR,
    .prescaler_value=PRECALER_VALUE_DIV_4,
    .timer1_mode=TIMER1_TIMER_MODE_ON,
    .timer1_reg_size=TIMER1_16_BIT_REG_RW,
    .timer1_preload_val=3036
};
//25ms
timer2_t timer2_obj={
    .TIMER2_Interrupt_Handler=timer2_interrupt_ISR, 
    .prescaler_value=PRECALER_VALUE_DIV_16,
    .postscaler_value=TIMER2_POSTSSCALER_DIV_7,
    .timer2_preload_val=223
};
//250ms
timer3_t timer3_obj={
    .TIMER3_Interrupt_Handler=timer3_interrupt_ISR,
    .prescaler_value=PRECALER_VALUE_DIV_4,
    .timer3_mode=TIMER3_TIMER_MODE_ON,
    .timer3_reg_size=TIMER3_16_BIT_REG_RW,
    .timer3_preload_val=3036
};
Std_RetrunType ret=E_NOK;


int main() {
    app_init();
    while(1){                  
       
       
    }
        return (EXIT_SUCCESS);
}

void app_init(void){
 
  TIMER0_Init(&timer0_obj);
  led_init(&led_0); 
  
  TIMER1_Init(&timer1_obj);
  led_init(&led_1);
  
  TIMER2_Init(&timer2_obj);
  led_init(&led_2);
  
  TIMER3_Init(&timer3_obj);
  led_init(&led_3);
    //ecu_layer_initialize();

     
}
//toggle after 1000 ms
void timer0_interrupt_ISR(void){
  
     tmr0_tick++;
    if(tmr0_tick == 4)
        {
            ret=led_toggle(&led_0);
            tmr0_tick=0;
        }
       
       
}
//toggle after 500 ms
void timer1_interrupt_ISR(void){
   
      tmr1_tick++;
    if(tmr1_tick == 2)
        {
            ret=led_toggle(&led_1);
            tmr1_tick=0;
        }
       
}
//toggle after 250 ms
void timer2_interrupt_ISR(void){
    tmr2_tick++;
    if(tmr2_tick == 10)
        {
            ret=led_toggle(&led_2);
            tmr2_tick=0;
        }
}
//toggle after 1000 ms
void timer3_interrupt_ISR(void){
      tmr3_tick++;
    if(tmr3_tick == 4)
        {
            ret=led_toggle(&led_3);
            tmr3_tick=0;
        }
       
    
}
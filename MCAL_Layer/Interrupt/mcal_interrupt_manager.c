/* 
 * File:   mcal_interrupt_manger.c
 * Author: Marwa Abdelrahman
 *
 * Created on September 29, 2024, 2:35 PM
 */

#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_Flag = 1, RB5_Flag = 1, RB6_Flag = 1, RB7_Flag = 1;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
 void __interrupt() Interrupt_Manager_High(void){
    if((INTERRUPT_ENABLE==INTCONbits.INT0IE) && (INTERRUPT_FLAG_OCCUR==INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else{/*nothing*/}
     
    if((INTERRUPT_ENABLE==INTCON3bits.INT2IE) && (INTERRUPT_FLAG_OCCUR==INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    else{/*nothing*/}
 }
 
 
  void __interrupt(low_priority) Interrupt_Manager_High(void){
    if((INTERRUPT_ENABLE==INTCON3bits.INT1IE) && (INTERRUPT_FLAG_OCCUR==INTCON3bits.INT1IF)){
        INT1_ISR();
    }
    else{/*nothing*/}
 }
 
     
#else
void __interrupt() General_Interrupt_Manager(void){
    
    /* ============ INTx External Interrupt Start ============ */
    
    if((INTERRUPT_ENABLE==INTCONbits.INT0IE) && (INTERRUPT_FLAG_OCCUR==INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else{/*nothing*/}
    if((INTERRUPT_ENABLE==INTCON3bits.INT1IE) && (INTERRUPT_FLAG_OCCUR==INTCON3bits.INT1IF)){
        INT1_ISR();
    }
    else{/*nothing*/}
    if((INTERRUPT_ENABLE==INTCON3bits.INT2IE) && (INTERRUPT_FLAG_OCCUR==INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    else{/*nothing*/}
    
    /* ============ INTx External Interrupt End ============ */
    /*if((INTERRUPT_ENABLE==INTCONbits.RBIE) && (INTERRUPT_FLAG_OCCUR==INTCONbits.RBIF)&& (PORTBbits.RB4==GPIO_STATE_HIGH) )
    {
      RB4_ISR_trial();
    }*/
    
    /* ============ PortB External On Change Interrupt Start ============ */
    /*RB4*/
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) && (INTERRUPT_FLAG_OCCUR==INTCONbits.RBIF) && (PORTBbits.RB4==GPIO_STATE_HIGH) 
            &&(RB4_Flag==1))
    {
        RB4_Flag=0;
        RB4_ISR(1);
        
    }
    else{/*nothing*/}
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) && (INTERRUPT_FLAG_OCCUR==INTCONbits.RBIF)&& (PORTBbits.RB4==GPIO_STATE_LOW) 
            &&(RB4_Flag==0))
    {
        RB4_Flag=1;
        RB4_ISR(0);
        
    }
    else{/*nothing*/}
    
    
    
    /*RB5*/
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) && (INTERRUPT_FLAG_OCCUR==INTCONbits.RBIF) && (PORTBbits.RB5==GPIO_STATE_HIGH) 
            &&(RB5_Flag==1)){
        RB5_Flag=0;
        RB5_ISR(1);
        
    }
    else{/*nothing*/}
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) && (INTERRUPT_FLAG_OCCUR==INTCONbits.RBIF) && (PORTBbits.RB5==GPIO_STATE_LOW) 
            &&(RB5_Flag==0)){
        RB5_Flag=1;
        RB5_ISR(0);
        
    }
    else{/*nothing*/}
    
    
    /*RB6*/
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) && (INTERRUPT_FLAG_OCCUR==INTCONbits.RBIF) && (PORTBbits.RB6==GPIO_STATE_HIGH) 
            &&(RB6_Flag==1)){
        RB6_Flag=0;
        RB6_ISR(1);
        
    }
    else{/*nothing*/}
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) && (INTERRUPT_FLAG_OCCUR==INTCONbits.RBIF) && (PORTBbits.RB6==GPIO_STATE_LOW) 
            &&(RB6_Flag==0)){
        RB6_Flag=1;
        RB6_ISR(0);
        
    }
    else{/*nothing*/}
    
    
    /*RB7*/
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) && (INTERRUPT_FLAG_OCCUR==INTCONbits.RBIF) && (PORTBbits.RB7==GPIO_STATE_HIGH) 
            &&(RB7_Flag==1)){
        RB7_Flag=0;
        RB7_ISR(1);
        
    }
    else{/*nothing*/}
    if((INTERRUPT_ENABLE==INTCONbits.RBIE) && (INTERRUPT_FLAG_OCCUR==INTCONbits.RBIF) && (PORTBbits.RB7==GPIO_STATE_LOW) 
            &&(RB7_Flag==0)){
        RB7_Flag=1;
        RB7_ISR(0);
        
    }
    else{/*nothing*/}
        
    /* ============ PortB External On Change Interrupt End ============ */
    
    
    /* ============ ADC Interrupt Start ============ */
    if((INTERRUPT_ENABLE==PIE1bits.ADIE)&&(INTERRUPT_FLAG_OCCUR==PIR1bits.ADIF)){
        ADC_ISR();
    }
    else{/*nothing*/}
        
    /* ============ ADC Interrupt End ============ */
    
    
    
    /* ============ TIMER0 Interrupt Start ============ */
    if((INTERRUPT_ENABLE==INTCONbits.TMR0IE)&&(INTERRUPT_FLAG_OCCUR==INTCONbits.TMR0IF)){
        TIMER0_ISR();
    }
    else{/*nothing*/}
    /* ============ TIMER0 Interrupt End ============ */ 
    
    /* ============ TIMER1 Interrupt Start ============ */
    if((INTERRUPT_ENABLE==PIE1bits.TMR1IE)&&(INTERRUPT_FLAG_OCCUR==PIR1bits.TMR1IF)){
        TIMER1_ISR();
    }
    else{/*nothing*/}
    /* ============ TIMER1 Interrupt End ============ */ 
    
    
    /* ============ TIMER2 Interrupt Start ============ */
    if((INTERRUPT_ENABLE==PIE1bits.TMR2IE)&&(INTERRUPT_FLAG_OCCUR==PIR1bits.TMR2IF)){
        TIMER2_ISR();
    }
    else{/*nothing*/}
    /* ============ TIMER2 Interrupt End ============ */ 
    
      /* ============ TIMER3 Interrupt Start ============ */
    if((INTERRUPT_ENABLE==PIE2bits.TMR3IE)&&(INTERRUPT_FLAG_OCCUR==PIR2bits.TMR3IF)){
        TIMER3_ISR();
    }
    else{/*nothing*/}
    /* ============ TIMER3 Interrupt End ============ */ 
}

#endif
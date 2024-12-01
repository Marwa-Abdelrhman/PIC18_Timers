/* 
 * File:   mcal_external_interrupt.c
 * Author: Marwa Abdelrahman
 *
 * Created on September 29, 2024, 2:37 PM
 */


#include"mcal_external_interrupt.h"


/*pointer to function to hold callback for INTx */

static interrupt_handler INT0_InterruptHandler=NULL;
static interrupt_handler INT1_InterruptHandler=NULL;
static interrupt_handler INT2_InterruptHandler=NULL;
//static interrupt_handler RB4_InterruptHandler=NULL;


/*pointer to function to hold callback for RBx */
//static void (*RB4_InterruptHandler)(void)=NULL;
static void (*RB4_High_InterruptHandler)(void)=NULL;
static void (*RB4_Low_InterruptHandler)(void)=NULL;

static interrupt_handler RB5_High_InterruptHandler=NULL;
static interrupt_handler RB5_Low_InterruptHandler=NULL;

static interrupt_handler RB6_High_InterruptHandler=NULL;
static interrupt_handler RB6_Low_InterruptHandler=NULL;

static interrupt_handler RB7_High_InterruptHandler=NULL;
static interrupt_handler RB7_Low_InterruptHandler=NULL;

/*helper functions for INTx interrupts main functions to enable driver portability*/

static Std_RetrunType interrupt_INTx_Enable(const interrupt_INTx_t *intr_obj);
static Std_RetrunType interrupt_INTx_Disable(const interrupt_INTx_t *intr_obj);
//static Std_RetrunType interrupt_INTx_priority_set(const interrupt_INTx_t *intr_obj);
static Std_RetrunType interrupt_INTx_edge_set(const interrupt_INTx_t *intr_obj);
static Std_RetrunType interrupt_INTx_clear_flag(const interrupt_INTx_t *intr_obj);
static Std_RetrunType interrupt_INTx_pin_cfg(const interrupt_INTx_t *intr_obj);

static Std_RetrunType INT0_set_interrupt_handler(void(*interrupt_handler)(void));
static Std_RetrunType INT1_set_interrupt_handler(void(*interrupt_handler)(void));
static Std_RetrunType INT2_set_interrupt_handler(void(*interrupt_handler)(void));
static Std_RetrunType interrupt_INTx_set_interrupt_handler(const interrupt_INTx_t *intr_obj);

/*INTx ISR*/

void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR_trial(void);
/*RBx ISR*/

void RB4_ISR(uint8 state);
void RB5_ISR(uint8 state);
void RB6_ISR(uint8 state);
void RB7_ISR(uint8 state);



/**
 * @brief 
 * @param intr_obj
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType interrupt_INTx_Init(const interrupt_INTx_t *intr_obj){
     Std_RetrunType ret = E_NOK;
    if(intr_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        /*disable the external interrupt*/
        ret=interrupt_INTx_Disable(intr_obj);
        /*clear interrupt flag: the ext intr didn't occur*/
        ret=interrupt_INTx_clear_flag(intr_obj);
        /*configure intr edge*/
        ret=interrupt_INTx_edge_set(intr_obj);
        /*config intr pin @ MCU*/
        ret=interrupt_INTx_pin_cfg(intr_obj);
        /*config intr callback*/
        ret=interrupt_INTx_set_interrupt_handler(intr_obj);
        /*enable the external interrupt*/
        ret=interrupt_INTx_Enable(intr_obj);
             
    }
    
    
    return ret;
}
/**
 * @brief 
 * @param intr_obj
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType interrupt_INTx_DeInit(const interrupt_INTx_t *intr_obj){
    Std_RetrunType ret = E_OK;
    if(intr_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        ret=interrupt_INTx_Disable(intr_obj);
        
    }
    
    
    return ret;
}
/**
 * @brief 
 * @param intr_obj
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType interrupt_RBx_Init(const interrupt_RBx_t *intr_obj){
    Std_RetrunType ret = E_OK;
    if(intr_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
         /*disable the external interrupt*/
        //EXTERNAL_ON_CHANGE_RBx_INTERRUPT_DISABLE();
        //(INTCONbits.RBIE=0);
        /*clear interrupt flag: the ext intr didn't occur*/
        EXTERNAL_ON_CHANGE_RBx_INTERRUPT_FLAG_CLEAR();
        INTCONbits.RBIF=0;
        (INTCONbits.RBIE=0);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_ENABLE_PRIORITY_LEVELS_INTERRUPTS();
        if(intr_obj->priority == INTERRUPT_HIGH_PRIORITY){ 
            INTERRUPT_ENABLE_GLOBAL_HIGH_PRIORITY_INTERRUPTS();
            EXTERNAL_ON_CHANGE_RBx_HighPrioritySet();
            }
        else if(intr_obj->priority == INTERRUPT_LOW_PRIORITY){
            INTERRUPT_ENABLE_GLOBAL_LOW_PRIORITY_INTERRUPTS();
            EXTERNAL_ON_CHANGE_RBx_LowPrioritySet(); 
            }
        else{/*nothing*/}
#else
        INTERRUPT_ENABLE_GLOBAL_INTERRUPTS();
        INTERRUPT_ENABLE_PERIPHERAL_INTERRUPTS();
#endif
        /*config intr pin @ MCU*/
        ret=gpio_pin_direction_init(&(intr_obj->rbx_pin));
        /*config intr callback*/
        switch(intr_obj->rbx_pin.pin){
            case GPIO_PIN4:
                //RB4_InterruptHandler=intr_obj->external_interrupt_handler;
              RB4_High_InterruptHandler=intr_obj->external_High_interrupt_handler;
              RB4_Low_InterruptHandler=intr_obj->external_Low_interrupt_handler;
              break;
            case GPIO_PIN5:
              RB5_High_InterruptHandler=intr_obj->external_High_interrupt_handler;
              RB5_Low_InterruptHandler=intr_obj->external_Low_interrupt_handler;
              break;
            case GPIO_PIN6:
              RB6_High_InterruptHandler=intr_obj->external_High_interrupt_handler;
              RB6_Low_InterruptHandler=intr_obj->external_Low_interrupt_handler;
              break;
            case GPIO_PIN7:
              RB7_High_InterruptHandler=intr_obj->external_High_interrupt_handler;
              RB7_Low_InterruptHandler=intr_obj->external_Low_interrupt_handler;
              break;
            default:ret = E_NOK;
    
        }
        //ADCON1 = 0x0F;//set RB to digital I/O pins
        //IOCBbits=0xFF;
        
        /*enable the external interrupt*/
        EXTERNAL_ON_CHANGE_RBx_INTERRUPT_ENABLE();
        //INTCONbits.RBIF=1;
        ret = E_OK;
    
                
    }
    
    
    return ret;
}
/**
 * @brief 
 * @param intr_obj
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue
 */
Std_RetrunType interrupt_RBx_DeInit(const interrupt_RBx_t *intr_obj){
    Std_RetrunType ret = E_OK;
    if(intr_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
         EXTERNAL_ON_CHANGE_RBx_INTERRUPT_DISABLE();
         EXTERNAL_ON_CHANGE_RBx_INTERRUPT_FLAG_CLEAR();
    
                
    }
    
    
    return ret;   
}




static Std_RetrunType interrupt_INTx_Enable(const interrupt_INTx_t *intr_obj){
    Std_RetrunType ret = E_OK;
    if(intr_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        switch(intr_obj->src)
        {
            case INTERRUPT_INT0:
                EXTERNAL_INT0_INTERRUPT_ENABLE();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_ENABLE_GLOBAL_HIGH_PRIORITY_INTERRUPTS();
#else
                INTERRUPT_ENABLE_GLOBAL_INTERRUPTS();
                INTERRUPT_ENABLE_PERIPHERAL_INTERRUPTS();
#endif
                ret=E_OK;
                break;
            case INTERRUPT_INT1:
                EXTERNAL_INT1_INTERRUPT_ENABLE();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                if(intr_obj->priority == INTERRUPT_HIGH_PRIORITY){ 
                    INTERRUPT_ENABLE_GLOBAL_HIGH_PRIORITY_INTERRUPTS();
                }
                else if(intr_obj->priority == INTERRUPT_LOW_PRIORITY){
                    INTERRUPT_ENABLE_GLOBAL_LOW_PRIORITY_INTERRUPTS();
                }
                else{/*nothing*/}
#else
                INTERRUPT_ENABLE_GLOBAL_INTERRUPTS();
                INTERRUPT_ENABLE_PERIPHERAL_INTERRUPTS();
#endif
        
                ret=E_OK;
                break;
            case INTERRUPT_INT2:
                EXTERNAL_INT2_INTERRUPT_ENABLE();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                if(intr_obj->priority == INTERRUPT_HIGH_PRIORITY){ 
                    INTERRUPT_ENABLE_GLOBAL_HIGH_PRIORITY_INTERRUPTS();
                }
                else if(intr_obj->priority == INTERRUPT_LOW_PRIORITY){
                    INTERRUPT_ENABLE_GLOBAL_LOW_PRIORITY_INTERRUPTS();
                }
                else{/*nothing*/}
#else
                INTERRUPT_ENABLE_GLOBAL_INTERRUPTS();
                INTERRUPT_ENABLE_PERIPHERAL_INTERRUPTS();
#endif
        
                ret=E_OK;
            break;
            default:ret= E_NOK;
               
        
        }
                
    }
    
    
    return ret;
}
/**
 * @brief 
 * @param intr_obj
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue
 */
static Std_RetrunType interrupt_INTx_Disable(const interrupt_INTx_t *intr_obj){
        Std_RetrunType ret = E_OK;
    if(intr_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        switch(intr_obj->src)
        {
            case INTERRUPT_INT0:
                EXTERNAL_INT0_INTERRUPT_DISABLE();
                ret=E_OK;
                break;
            case INTERRUPT_INT1:
                EXTERNAL_INT1_INTERRUPT_DISABLE();
                ret=E_OK;
                break;
            case INTERRUPT_INT2:
                EXTERNAL_INT2_INTERRUPT_DISABLE();
                ret=E_OK;
            break;
            default:ret= E_NOK;
               
        
        }
                
    }
    
    
    return ret;
}
/**
 * @brief 
 * @param intr_obj
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue
 */
/*static Std_RetrunType interrupt_INTx_priority_set(const interrupt_INTx_t *intr_obj){
            Std_RetrunType ret = E_OK;
    if(intr_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        switch(intr_obj->src)
        {
            case INTERRUPT_INT0:
                ret=E_OK;
                break;
            case INTERRUPT_INT1:
                ret=E_OK;
                break;
            case INTERRUPT_INT2:
                ret=E_OK;
            break;
            default:ret= E_NOK;
               
        
        }
                
    }
    
    
    return ret;
}*/
/**
 * @brief 
 * @param intr_obj
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue
 */
static Std_RetrunType interrupt_INTx_edge_set(const interrupt_INTx_t *intr_obj){
    Std_RetrunType ret = E_OK;
    if(intr_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        switch(intr_obj->src)
        {
            case INTERRUPT_INT0:
                if(intr_obj->edge == INTERRUPT_FALLING_EDGE){
                    EXTERNAL_INT0_FALLING_EDGE(); 
                }
                else if(intr_obj->edge == INTERRUPT_RISING_EDGE){
                    EXTERNAL_INT0_RISING_EDGE();
                }
                else{/*nothing*/}
                ret=E_OK;
                break;
            case INTERRUPT_INT1:
                if(intr_obj->edge == INTERRUPT_FALLING_EDGE){
                    EXTERNAL_INT1_FALLING_EDGE(); 
                }
                else if(intr_obj->edge == INTERRUPT_RISING_EDGE){
                    EXTERNAL_INT1_RISING_EDGE();
                }
                else{/*nothing*/}
                ret=E_OK;
                break;
            case INTERRUPT_INT2:
                if(intr_obj->edge == INTERRUPT_FALLING_EDGE){
                    EXTERNAL_INT2_FALLING_EDGE(); 
                }
                else if(intr_obj->edge == INTERRUPT_RISING_EDGE){
                    EXTERNAL_INT2_RISING_EDGE();
                }
                else{/*nothing*/}
                ret=E_OK;
            break;
            default:ret= E_NOK;
               
        
        }
                
    }
    
    
    return ret;
}
/**
 * @brief 
 * @param intr_obj
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue
 */
static Std_RetrunType interrupt_INTx_clear_flag(const interrupt_INTx_t *intr_obj){
    Std_RetrunType ret = E_OK;
    if(intr_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        switch(intr_obj->src)
        {
            case INTERRUPT_INT0:
                EXTERNAL_INT0_INTERRUPT_FLAG_CLEAR();
                ret=E_OK;
                break;
            case INTERRUPT_INT1:
                EXTERNAL_INT1_INTERRUPT_FLAG_CLEAR();
                ret=E_OK;
                break;
            case INTERRUPT_INT2:
                EXTERNAL_INT2_INTERRUPT_FLAG_CLEAR();
                ret=E_OK;
            break;
            default:ret= E_NOK;
               
        
        }
                
    }
    
    
    return ret;
}
/**
 * @brief 
 * @param intr_obj
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue
 */
static Std_RetrunType interrupt_INTx_pin_cfg(const interrupt_INTx_t *intr_obj){
    Std_RetrunType ret = E_NOK;
    if(intr_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
      /*initialize the needed pin for external interrupts*/
        ret=gpio_pin_direction_init(&(intr_obj->intx_pin));
    }
    
    
    return ret;
}
/**
 * 
 * @param interrupt_handler
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue 
 */
static Std_RetrunType INT0_set_interrupt_handler(void(*interrupt_handler)(void)){
    
    Std_RetrunType ret = E_NOK;
    if(interrupt_handler == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        INT0_InterruptHandler = interrupt_handler;
        ret=E_OK;
    }
    
    
    return ret;
}

/**
 * 
 * @param interrupt_handler
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue 
 */
static Std_RetrunType INT1_set_interrupt_handler(void(*interrupt_handler)(void)){
    Std_RetrunType ret = E_NOK;
    if(interrupt_handler == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        INT1_InterruptHandler = interrupt_handler;
        ret=E_OK;
    }
    
    
    return ret;
}
/**
 * 
 * @param interrupt_handler
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue 
 */
static Std_RetrunType INT2_set_interrupt_handler(void(*interrupt_handler)(void)){
    Std_RetrunType ret = E_NOK;
    if(interrupt_handler == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        INT2_InterruptHandler = interrupt_handler;
        ret=E_OK;
    }
    
    
    return ret;
}
/**
 * @brief 
 * @param intr_obj
 * @return status of function call
 *         (E_OK) the function call is successful 
 *         (E_NOK) the function call has issue
 */
static Std_RetrunType interrupt_INTx_set_interrupt_handler(const interrupt_INTx_t *intr_obj){
               Std_RetrunType ret = E_OK;
    if(intr_obj == NULL )
    {
        ret=E_NOK;
    }
    else
    {
        switch(intr_obj->src)
        {
            case INTERRUPT_INT0:
                /*didn't pass by addr because it is a rvalue*/
                INT0_set_interrupt_handler(intr_obj->external_interrupt_handler);
                ret=E_OK;
                break;
            case INTERRUPT_INT1:
                ret=E_OK;
                INT1_set_interrupt_handler(intr_obj->external_interrupt_handler);
                break;
            case INTERRUPT_INT2:
                INT2_set_interrupt_handler(intr_obj->external_interrupt_handler);
                ret=E_OK;
            break;
            default:ret= E_NOK;
               
        
        }
                
    }
    
    
    return ret;
}
/**
 * @brief to be called @ interrupt_manager
 */
void INT0_ISR (void){
    EXTERNAL_INT0_INTERRUPT_FLAG_CLEAR();
    if(INT0_InterruptHandler != NULL){
        INT0_InterruptHandler();
    }
    else{/*nothing*/}
}
/**
 * @brief to be called @ interrupt_manager
 */
void INT1_ISR (void){
    EXTERNAL_INT1_INTERRUPT_FLAG_CLEAR();
    if(INT1_InterruptHandler){
        INT1_InterruptHandler();
    }
    else{/*nothing*/}
}
/**
 * @brief to be called @ interrupt_manager 
 */
void INT2_ISR (void){
    EXTERNAL_INT2_INTERRUPT_FLAG_CLEAR();
    if(INT2_InterruptHandler){
        INT2_InterruptHandler();
    }
    else{/*nothing*/}
}
/*void RB4_ISR_trial(void){
    EXTERNAL_ON_CHANGE_RBx_INTERRUPT_FLAG_CLEAR();
     if(RB4_InterruptHandler){
            RB4_InterruptHandler();
         }
}*/
/**
 * @brief to be called @ interrupt_manager 
 */
void RB4_ISR(uint8 state){
    EXTERNAL_ON_CHANGE_RBx_INTERRUPT_FLAG_CLEAR();
    if(state==0){
         /*configure change of voltage on pin from high to low == LOW HANDLER*/
        if(RB4_Low_InterruptHandler){
            RB4_Low_InterruptHandler();
         }
        else{/*nothing*/}
    }
    else if(state==1){
        /*configure change of voltage on pin from low to high == HIGH HANDLER */
        if(RB4_High_InterruptHandler){
            RB4_High_InterruptHandler();
        }
        else{/*nothing*/}
    
    }
   
    
}
/**
 * @brief to be called @ interrupt_manager 
 */
void RB5_ISR(uint8 state){
    EXTERNAL_ON_CHANGE_RBx_INTERRUPT_FLAG_CLEAR();
    if(state==0){
         /*configure change of voltage on pin from high to low == LOW HANDLER*/
        if(RB5_Low_InterruptHandler){
            RB5_Low_InterruptHandler();
         }
        else{/*nothing*/}
    }
    else if(state==1){
        /*configure change of voltage on pin from low to high == HIGH HANDLER */
        if(RB5_High_InterruptHandler){
            RB5_High_InterruptHandler();
        }
        else{/*nothing*/}
    
    }
    
}
/**
 * @brief to be called @ interrupt_manager 
 */
void RB6_ISR(uint8 state){
    EXTERNAL_ON_CHANGE_RBx_INTERRUPT_FLAG_CLEAR();
    if(state==0){
         /*configure change of voltage on pin from high to low == LOW HANDLER*/
        if(RB6_Low_InterruptHandler){
            RB6_Low_InterruptHandler();
         }
        else{/*nothing*/}
    }
    else if(state==1){
        /*configure change of voltage on pin from low to high == HIGH HANDLER */
        if(RB6_High_InterruptHandler){
            RB6_High_InterruptHandler();
        }
        else{/*nothing*/}
    
    }
    
}
/**
 * @brief to be called @ interrupt_manager 
 */
void RB7_ISR(uint8 state){
     EXTERNAL_ON_CHANGE_RBx_INTERRUPT_FLAG_CLEAR();
    if(state==0){
         /*configure change of voltage on pin from high to low == LOW HANDLER*/
        if(RB7_Low_InterruptHandler){
            RB7_Low_InterruptHandler();
         }
        else{/*nothing*/}
    }
    else if(state==1){
        /*configure change of voltage on pin from low to high == HIGH HANDLER */
        if(RB7_High_InterruptHandler){
            RB7_High_InterruptHandler();
        }
        else{/*nothing*/}
    
    }
   
}
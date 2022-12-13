

/* 
 * File:   oc1.c
 * Author: nestorj
 *
 * Module to configure & control OC1 using timer 3 - SFR Version
 * Created on September 26, 2019, 2:48 PM
 */

#include "oc1_plib.h"
#include <xc.h>
#include <plib.h>
    
    void oc1_init_plib(uint16_t duty) {
        OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_32,  62500);    //T2_PS_1_32,  0xffff  z_servo
        OpenOC1(OC_ON | OC_TIMER_MODE16| OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 
                duty, duty);  
        // only OC1RS (2rd arg) matters in this example
        PPSOutput(1, RPB7, OC1);  // map to RPB7 (pin 16)
    }    
    
    void oc1_setduty_plib(uint16_t duty) {
        SetDCOC1PWM(duty);
    }
    
    void oc2_init_plib(uint16_t duty) {
        OpenTimer3(T3_ON | T3_SOURCE_INT | T2_PS_1_16, 25000);  //T3_PS_1_8, 33333
        OpenOC2(OC_ON | OC_TIMER_MODE16 | OC_TIMER3_SRC | OC_PWM_FAULT_PIN_DISABLE, 
                duty, duty);  
        // only OC1RS (2rd arg) matters in this example
        PPSOutput(2, RPB8, OC2);  // map to RPB7 (pin 16)
    }    
    
     void oc2_setduty_plib(uint16_t duty) {
        SetDCOC2PWM(duty);
    }
   


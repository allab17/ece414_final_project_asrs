#include <xc.h>
#include <plib.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config_clk.h"
#include "uart1.h"
#include "oc1_plib.h"
#include "ztimer4.h"

#define _SUPPRESS_PLIB_WARNING 1

// Convenient defines for width and height of display
#define DW          320
#define DH          240
#define MAX_RAD     50

float z_servo_duty;


float y_servo_duty;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////



















uint8_t set_f;
 


static enum cntrl_states {init, ctrl} cntrl_state;

void tickFct_cntrl_fsm() {
    switch(cntrl_state) {
        case init:
            cntrl_state = ctrl;
        break;
        case ctrl:
            oc1_setduty_plib((uint16_t)z_servo_duty);
            oc2_setduty_plib((uint16_t)y_servo_duty);
            
            
            cntrl_state = ctrl;
        break;
        default: cntrl_state = init;
            
        break;
    }
}

 

static enum comm_states {idle, set_z_servo_duty, set_y_servo_duty} comm_state;

char c[5];
int i;
char cha;
char buffer[50];

void tickFct_comm_fsm() {
    switch(comm_state) {
        case idle:;
            memset(c,0,5);
            i=0;
            
            if (uart1_rxrdy()) {
                cha = uart1_rxread();
                if (cha == 'z') {
                    cha = '\0';
                    comm_state = set_z_servo_duty; 
                    uart1_txwrite('z');
                    set_f = 1;
                } else if (cha == 'y') {
                    cha = '\0';
                    comm_state = set_y_servo_duty; 
                    uart1_txwrite('y');
                    set_f = 1;
                } else if (cha == 'e') {
                    cha = '\0';
                    comm_state = idle; 
                    uart1_txwrite('e');
                    LATBbits.LATB15 = 0;
                    set_f = 1;
                } else if (cha == 'd') {
                    cha = '\0';
                    comm_state = idle; 
                    uart1_txwrite('d');
                    LATBbits.LATB15 = 1;
                    set_f = 1;
                } else if (cha == 'i') {
                    cha = '\0';
                    comm_state = idle; 
                    uart1_txwrite('i');
                    LATBbits.LATB9 = 1;
                    set_f = 1;
                } else if (cha == 's') {
                    cha = '\0';
                    comm_state = idle; 
                    uart1_txwrite('s');
                    LATBbits.LATB9 = 0;
                    set_f = 1;
                }
            } else comm_state = idle;
            
        break;
        case set_z_servo_duty:
                if (uart1_rxrdy()) {
                    cha = uart1_rxread();
                    if (cha == '\r') {
                        cha = '\0';
                        sscanf(c, "%f", &z_servo_duty);
                        set_f = 0;
                        comm_state = idle;
                    } else {
                        comm_state = set_z_servo_duty;
                        c[i] = cha;
                        uart1_txwrite(c[i]);
                        cha='\0';
                        i++;
                    }
                } else comm_state = set_z_servo_duty;
        break;
        case set_y_servo_duty:
                if (uart1_rxrdy()) {
                    cha = uart1_rxread();
                    if (cha == '\r') {
                        cha = '\0';
                        sscanf(c, "%f", &y_servo_duty);
                        set_f = 0;
                        comm_state = idle;
                    } else {
                        comm_state = set_y_servo_duty;
                        c[i] = cha;
                        uart1_txwrite(c[i]);
                        cha='\0';
                        i++;
                    }
                } else comm_state = set_y_servo_duty;
        break;
        default:
            comm_state = idle;
        break;
    }
}

uint16_t t;

uint16_t t_max = 240;  //each pixel on LCD corresponds to one time tick

uint16_t scale(uint16_t val,uint16_t min, uint16_t max, uint16_t a, uint16_t b) {
    uint16_t scale;
    scale = ((b - a)*(val - min) / (max - min)) + a;
        return scale;
}


int main() {  
    
    ANSELB = 0;
    TRISB = 0;
    
    uint16_t t1, t2;
    zTimerOn();
    zTimerSet(100);
    oc1_init_plib(0x4000);
    oc2_init_plib(0x4000);
    INTEnableSystemMultiVectoredInt();
   
    t1 = zTimerReadms();
    t=0;
    set_f = 0;
    

        uart1_init(9600);
        
        comm_state = idle;
        cntrl_state = init;
        
     
    while (1) {
        
        
        
        if (zTimerReadFlag()) {
            tickFct_cntrl_fsm();
            tickFct_comm_fsm();
            
            if (!set_f) {
                printf("z_servo: %f\n\r", z_servo_duty);
                printf("y_servo: %f\n\r", y_servo_duty);
            }
        }
    }

}






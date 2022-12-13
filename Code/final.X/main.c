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
#include "timer1.h"

#include "tft_master.h"
#include "tft_gfx.h"
#include "adc_intf.h"
#include "ts_lcd.h"
#include "Touchscreen.h"

#define _SUPPRESS_PLIB_WARNING 1

// Convenient defines for width and height of display
#define DH          320
#define DW          240
#define MAX_RAD     50


 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint16_t sys_op; //current operation of the system { 0 - storing, 1 - retrieving} gives input throughout fsm
uint16_t item_index;

uint16_t step_x;  //set corresponding to number of steps to get to pos
uint16_t step_c; //counting steps for stepper motor

uint16_t s_c;   //counter for the servos
const uint16_t t_z_ex = 181;  //timing to extend for 10ms period
const uint16_t t_z_re = 231;  //timing to retract for 10ms period
const uint16_t sensor_bias_t = 100; //should be about 1/4 to 1/2 what we need to retract
const uint16_t sensor_bias_ex_t = 90;

const uint16_t z_servo_ex_d = 1920; //3%   
const uint16_t z_servo_re_d = 1650; //2.7%

const uint16_t y_servo_d_h = 2500;  //25%
const uint16_t y_servo_d_lo = 6000;  //5%
const uint16_t t_y = 300;  //3 seconds for y_servo to finish
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t num_items_s;
uint8_t num_items_r;

struct Item {
    char name[50];
    int pos;
};

struct Item items_store[3] = { 
                        {"Apples"}, 
                        {"Bananas"}, 
                        {"Pistacios"}  
    
                  };

struct Item items_in_sys_retrievable[3];


struct Pos {
    uint8_t isEmpty;
    uint16_t steps;
};

struct Pos pos[3];



//touchscreen
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint16_t x_ref = 0;
uint16_t y_ref = 0;

//cursor pos
 uint16_t xpos, ypos;
 
 uint16_t btn_s_w = DW;
 uint16_t btn_s_h = 100;

uint16_t btn_s_x;
uint16_t btn_s_y;
uint16_t btn_r_x;
uint16_t btn_r_y;
uint16_t btn_1_x;
uint16_t btn_1_y;
uint16_t btn_2_x;
uint16_t btn_2_y;
uint16_t btn_3_x;
uint16_t btn_3_y;
uint16_t btn_4_x;
uint16_t btn_4_y;

uint16_t btn_b_x;
uint16_t btn_b_y;

uint8_t btn_s = 0;
uint8_t btn_r = 0;

uint8_t btn_1 = 0;
uint8_t btn_2 = 0;
uint8_t btn_3 = 0;
uint8_t btn_4 = 0;
uint8_t btn_b = 0;

void init_button_dim() {
    btn_s_x = x_ref;
    btn_s_y = y_ref;
    btn_r_x = x_ref;
    btn_r_y = y_ref+0.5*DH;
    btn_1_x = x_ref;
    btn_1_y = y_ref;  
    btn_2_x = x_ref;
    btn_2_y = y_ref + btn_s_h;
    btn_3_x = x_ref;
    btn_3_y = y_ref + 2*btn_s_h;
    btn_4_x = x_ref;
    btn_4_y = y_ref + 3*btn_s_h;
    btn_b_x = x_ref;
    btn_b_y = btn_s_h + DH;
}

//two separate button listeners to flag buttons depending on the state of the asrs display
uint8_t btn_item_listener() {
    if (btn_1 || btn_2 || btn_3 || btn_4 || btn_b) return 1;
	else return 0;
}

uint8_t btn_s_r_listener() {
    if (btn_s || btn_r) return 1;
	else return 0;
}

void deflag() {
    btn_s = 0;
    btn_r = 0;
    btn_1 = 0;
    btn_2 = 0;
    btn_3 = 0;
    btn_4 = 0;
    btn_b = 0;
}

void flag_item_button(uint16_t xpos, uint16_t ypos) {
		if ((xpos > btn_1_x) && (xpos < (btn_1_x + btn_s_w)) && (ypos > btn_1_y) && (ypos < (btn_1_y + btn_s_h))) {
            btn_1 = 1;
        } else if ((xpos > btn_2_x) && (xpos < (btn_2_x + btn_s_w)) && (ypos > btn_2_y) && (ypos < (btn_2_y + btn_s_h))) {
            btn_2 = 1;
        } else if ((xpos > btn_3_x) && (xpos < (btn_3_x + btn_s_w)) && (ypos > btn_3_y) && (ypos < (btn_3_y + btn_s_h))) {
            btn_3 = 1;
        } else if ((xpos > btn_4_x) && (xpos < (btn_4_x + btn_s_w)) && (ypos > btn_4_y) && (ypos < (btn_4_y + btn_s_h))) {
            btn_4 = 1;
        } else if ((xpos > btn_b_x) && (xpos < (btn_b_x + btn_s_w)) && (ypos > btn_b_y) && (ypos < (btn_b_y + btn_s_h))) {
            btn_b = 1;
        } 
}

uint8_t get_item_btn_index() {
    if (btn_1) return 0;
    else if (btn_2) return 1;
    else if (btn_3) return 2;
}

void flag_s_r_button(uint16_t xpos, uint16_t ypos) {
        if ((xpos > btn_s_x) && (xpos < (btn_s_x + btn_s_w)) && (ypos > btn_s_y) && (ypos < (btn_s_y + 0.5*DH))) {
            btn_s = 1;
        } else if ((xpos > btn_r_x) && (xpos < (btn_r_x + btn_s_w)) && (ypos > btn_r_y) && (ypos < (btn_r_y + 0.5*DH))) {
            btn_r = 1;
        }
}

uint8_t btn_listener() { //button listener
    if (ts_lcd_get_ts(&xpos, &ypos)) { //if there is pressure on the screen
            ts_lcd_get_ts(&xpos, &ypos); //x and y will be updated with the touch pos
            return 1;
    } else return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void print_items_store_lcd() {
    int i;
    for(i=0; i<num_items_s; i++) {
        uint16_t scale;
        scale = y_ref + i*btn_s_h;
            tft_drawRect(x_ref, scale, btn_s_w, btn_s_h, ILI9341_WHITE);
            tft_setCursor(x_ref, scale+5);
            tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
            tft_setTextSize(2);
            tft_writeString(items_store[i].name);
    }
}

void print_items_in_sys_retrievable_lcd() {
    int i;
    for(i=0; i<num_items_r; i++) {
        uint16_t scale;
        scale = y_ref + i*btn_s_h;
            tft_drawRect(x_ref, scale, btn_s_w, btn_s_h, ILI9341_WHITE);
            tft_setCursor(x_ref,scale+5);
            tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
            tft_setTextSize(2);
            tft_writeString(items_in_sys_retrievable[i].name);
    }
}

uint8_t is_pos_free() {
    //returns true if there is a free pos in pos[]
    int i;
    for (i=0; i<sizeof(pos); i++) {
        if (pos[i].isEmpty) return 1;
    }
    return 0;
}

uint8_t get_empty_pos() {
    int i;
    for (i=0; i<sizeof(pos); i++) {
        if (pos[i].isEmpty) {
            return i;
        }
    }
}

//methods used to draw the simulation on the lcd when the mechanical device is moving
uint16_t scale(uint16_t val,uint16_t min, uint16_t max, uint16_t a, uint16_t b) {
    uint16_t scale;
    scale = ((b - a)*(val - min) / (max - min)) + a;
        return scale;
}

static enum asrs_states {idle, display_items, step, step_bias, bias_arm_ex, z_servo_ext, y_servo, bias_arm_re, z_servo_ret, y_servo_bias, step_home, step_bias_home} asrs_state;

void draw() {
        uint16_t st_x;
        //scale the target position to screen size 
        st_x = scale(step_x, 0,2000,0,DW);
        
        tft_drawRect(st_x,0.5*DW,20,20,ILI9341_RED);
        tft_fillRect(st_x,0.5*DW,20,20,ILI9341_RED);
             
        int i;
        for (i=0; i<sizeof(pos); i++) {
            uint16_t pos_s;
            pos_s = scale(pos[i].steps, 0,2000,0,DW);
            
//            tft_drawRect(0,0.5*DW,20,20,ILI9341_BLUE);
//            tft_fillRect(0,0.5*DW,20,20,ILI9341_BLUE);
            
            tft_drawRect(pos_s,0.5*DW,20,20,ILI9341_RED);
            
//            if (!pos[i].isEmpty) {
//                //if the pos is not empty than we want to draw a blue square to represent the item
//                tft_drawCircle(pos_s+9,0.5*DW+10,3,ILI9341_WHITE);
//                tft_fillCircle(pos_s+9,0.5*DW+10,3,ILI9341_WHITE);
//            }
        }
//    
        tft_drawRect(0,0.5*DW,40,20,ILI9341_BLACK);
        tft_fillRect(0,0.5*DW,40,20,ILI9341_BLACK);
}

void draw_simulation() {
        //scale the step count to screen size
        uint16_t st_c;
        uint16_t st_x;
        st_c = scale(step_c, 0,2000,0,DW);
        //scale the target position to screen size 
        st_x = scale(step_x, 0,2000,0,DW);
        
        if (asrs_state == step_home) {
            //moving from the rack position
            tft_drawCircle(st_x + 9 - st_c,0.5*DW+20, 1, ILI9341_GREEN);
            tft_fillCircle(st_x + 9 - st_c,0.5*DW+20, 1, ILI9341_GREEN);
        } else {
            //we are going to the rack position
            tft_drawCircle(st_c+9,0.5*DW+20, 1, ILI9341_GREEN);
            tft_fillCircle(st_c+9,0.5*DW+20, 1, ILI9341_GREEN);
        }
        
         tft_drawRect(0,0.2*DW,20,20,ILI9341_BLACK);
        tft_fillRect(0,0.2*DW,20,20,ILI9341_BLACK);
        
}


void tickFct_asrs() {
    switch (asrs_state) {
        case idle:
            if (btn_s_r_listener()) {
                //store or retrieve was pressed, we want to transition to displaying the appropriate array, either items_store or items_in_sys_retrievable
                //set sys_op depending on which was pressed
                if (btn_s) sys_op = 0;
                else sys_op = 1; 
                deflag();
                
                tft_fillScreen(ILI9341_BLACK);
                
                //display the contents of either items_store or items_in_sys_retrievable
                if (!sys_op) { //the user has selected storage and thus we print available items to store
                    print_items_store_lcd();
                } else {
                    print_items_in_sys_retrievable_lcd();
                }
                
                if (!sys_op && num_items_s == 0) {
                    tft_setCursor(5,0.5*DH-20);
                    tft_setTextColor(ILI9341_RED);
                    tft_setTextSize(2);
                    tft_writeString("System full...");
                    
                    
                    //display s, r buttons
                    tft_drawRect(btn_s_x, btn_s_y, btn_s_w, 0.5*DH, ILI9341_WHITE);
                    tft_setCursor((btn_s_x + ((DW/2)-25)),(btn_s_y + (DH/4)-5));
                    tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
                    tft_setTextSize(2);
                    tft_writeString("Store");
                    tft_drawRect(btn_r_x, btn_r_y, btn_s_w, 0.5*DH, ILI9341_WHITE);
                    tft_setCursor((btn_r_x + ((DW/2)-45)), (btn_r_y + (DH/4)-5));
                    tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
                    tft_setTextSize(2);
                    tft_writeString("Retrieve");

                    asrs_state = idle;
                } else if (sys_op && num_items_r == 0) {
                    tft_setCursor(5,0.5*DH+5);
                    tft_setTextColor(ILI9341_RED);
                    tft_setTextSize(2);
                    tft_writeString("System empty...");
                    
                    
                    //display s, r buttons
                    tft_drawRect(btn_s_x, btn_s_y, btn_s_w, 0.5*DH, ILI9341_WHITE);
                    tft_setCursor((btn_s_x + ((DW/2)-25)),(btn_s_y + (DH/4)-5));
                    tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
                    tft_setTextSize(2);
                    tft_writeString("Store");
                    tft_drawRect(btn_r_x, btn_r_y, btn_s_w, 0.5*DH, ILI9341_WHITE);
                    tft_setCursor((btn_r_x + ((DW/2)-45)), (btn_r_y + (DH/4)-5));
                    tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
                    tft_setTextSize(2);
                    tft_writeString("Retrieve");

                    asrs_state = idle;
                } else asrs_state = display_items;
            } else {
                asrs_state = idle;
            }
        break;

        case display_items:
            if (btn_item_listener()) { //button was pressed, we initiate transition to step
                //first get index of button press, corresponds to index of item
                if (btn_b) { //the user pressed to go back to home screen
                    deflag();
                    //refresh screen
                    tft_fillScreen(ILI9341_BLACK);
                    //display s, r buttons
                    tft_drawRect(btn_s_x, btn_s_y, btn_s_w, 0.5*DH, ILI9341_WHITE);
                    tft_setCursor((btn_s_x + ((DW/2)-25)),(btn_s_y + (DH/4)-5));
                    tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
                    tft_setTextSize(2);
                    tft_writeString("Store");
                    tft_drawRect(btn_r_x, btn_r_y, btn_s_w, 0.5*DH, ILI9341_WHITE);
                    tft_setCursor((btn_r_x + ((DW/2)-45)), (btn_r_y + (DH/4)-5));
                    tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
                    tft_setTextSize(2);
                    tft_writeString("Retrieve");

                    asrs_state = idle;
                } else {
                    item_index = get_item_btn_index();
                    deflag();

                    if (!sys_op) { //storing
                        //if the index passed is greater than the size of the array, the user pressed beyond the scope of the array    
                        if (item_index < num_items_s && item_index < sizeof(items_store) && num_items_s > 0) {
                            if (is_pos_free()) { //position free in the rack
                                //get the steps that we need depending on the free positions steps field
                                uint8_t empty_pos_index;
                                empty_pos_index = get_empty_pos();
                                step_x = pos[empty_pos_index].steps;
                                items_in_sys_retrievable[empty_pos_index] = items_store[item_index];
                                items_in_sys_retrievable[empty_pos_index].pos = empty_pos_index;
                                
                                num_items_s--;
                                num_items_r++;
                                
                                if (item_index != num_items_s) {
                                    int i;
                                    for (i=0; i<num_items_s; i++) {
                                        if (i >= item_index) {
                                            items_store[i] = items_store[i+1];
                                        }
                                    }
                                }
                                
                                pos[empty_pos_index].isEmpty = 0; //set the pos to be occupied so that we can not store anything there until we retrieve the item at that pos
                                //we are ready to go to step state
                                //refresh screen
                                tft_fillScreen(ILI9341_BLACK);

                                tft_setCursor(0,0.5*DH);
                                tft_setTextColor(ILI9341_WHITE);
                                tft_setTextSize(2);
                                tft_writeString("Standby...storing...");
                                
                                draw();

                                oc2_setduty_plib(y_servo_d_h);  //we are storing, move y_servo up at the start
                                
                                asrs_state = step;
                                step_c = 0;
                                //set DIR for storing
                                LATBbits.LATB9 = 1;
                                //enable stepper motor
                                LATBbits.LATB15 = 0;
                            } else {
                                tft_setCursor(5,0.5*DH-10);
                                tft_drawRect(0,0,300,50,ILI9341_BLACK);
                                tft_fillRect(0,0,300,50,ILI9341_BLACK);
                                tft_setTextColor(ILI9341_RED);
                                tft_setTextSize(2);
                                tft_writeString("System full...");

                                asrs_state = display_items;
                            }
                        } else {
                            //no such item at the button press
                            asrs_state = display_items;
                        }
                    } else if (sys_op) { //user must have clicked retrieval
                        //check if there is an item to retrieve at the index specified depending on the item pressed
                        if (item_index < num_items_r && num_items_r > 0) { //the item index from the button press must be within bounds of retrievable array or not valid
                                //get the steps to get to the retrievable item
                                //remove item from items_in_sys_re and add back to items_store
                                //get the index of the button press
                                //get the item because the index reflects the item then look at the index field to get the actual position
                            
                                step_x = pos[items_in_sys_retrievable[item_index].pos].steps;
                                items_store[num_items_s] = items_in_sys_retrievable[item_index];
                                    
                                num_items_r--;
                                num_items_s++;
                                
                                if (item_index != num_items_r) {
                                    int i;
                                    for (i=0; i<num_items_r; i++) {
                                        if (i >= item_index) {
                                            items_in_sys_retrievable[i] = items_in_sys_retrievable[i+1];
                                        }
                                    }
                                }
                                
                                pos[items_in_sys_retrievable[item_index].pos].isEmpty = 1; //we have retrieved item and thus the position is available for storage
                                //refresh screen
                                tft_fillScreen(ILI9341_BLACK);

                                tft_setCursor(0,0.5*DH);
                                tft_setTextColor(ILI9341_WHITE);
                                tft_setTextSize(2);
                                tft_writeString("Standby...retrieving...");
                                
                                draw();
                                
                                 oc2_setduty_plib(y_servo_d_lo); //we are retrieving move y_servo down
                                
                                //now we mechanically retrieve
                                asrs_state = step;
                                step_c = 0;
                                //set DIR for storing
                                LATBbits.LATB9 = 1;
                                //enable stepper motor
                                LATBbits.LATB15 = 0;
                        } else {
                            asrs_state = display_items;  //not a valid button press, essentially do nothing
                        }
                    }
                }
            } else {
                asrs_state = display_items;
            }

        break;
        //in step state, we enable the stepper to step until the step_x is reached, we initialize step_c to zero on transition and then increment 
        //it with each tick as long as step_c < step_x
        case step:
            if (step_c >= step_x) {
                
                asrs_state = step_bias;
            } else {
                step_c++;

                //scale the size of the device in terms of timing with the screen and print
                //a green progress bar complete with mini ASRS system in RED, fill
                //in the desired pos in blue
                draw_simulation();

                asrs_state = step;
            }
        break;
        
        case step_bias:
            if (!PORTBbits.RB10) {
                //disable stepper
                LATBbits.LATB15 = 1;
                s_c=0;
                oc1_setduty_plib(z_servo_ex_d);
                
                asrs_state = bias_arm_ex;
            } else {
                asrs_state = step_bias;
            }
            break;
        
        case bias_arm_ex:
            if (s_c >= sensor_bias_ex_t) {
                asrs_state = z_servo_ext;
            } else {
                s_c++;
                asrs_state = bias_arm_ex;
            }
        break;
        

        case z_servo_ext:
            if (!PORTBbits.RB13) {
                oc1_setduty_plib(0);
                s_c=0;

                if (!sys_op) oc2_setduty_plib(y_servo_d_lo);  //we are storing, move y_servo down
                else oc2_setduty_plib(y_servo_d_h); //we are retrieving move y_servo up

                

                asrs_state = y_servo;
            } else {
                asrs_state = z_servo_ext;
            }
        break;

        case y_servo:
            if (s_c >= t_y) {
                oc2_setduty_plib(0);
                oc1_setduty_plib(z_servo_re_d);
                s_c=0;

                asrs_state = bias_arm_re;
            } else {
                s_c++;
                asrs_state = y_servo;
            }
        break;
        
        case bias_arm_re:
            if (s_c >= sensor_bias_t) {
                oc2_setduty_plib(0);
                oc1_setduty_plib(z_servo_re_d);

                asrs_state = z_servo_ret;
            } else {
                s_c++;
                asrs_state = bias_arm_re;
            }
        break;
        
        

        case z_servo_ret:
            if (!PORTBbits.RB13) { 
                oc1_setduty_plib(0); //stop retracting, set the duty to be in between the two duty cycles
                asrs_state = y_servo_bias;
                
                s_c=0;
            } else {
                //we need some minute time delay before we start resampling so that we don't get a double tap of the sensor readout on the paint
                asrs_state = z_servo_ret;
            }
        break;

        case y_servo_bias:
            if (s_c >= t_y) {
                s_c=0;

                //refresh the screen to clear the progress getting to pos
                tft_fillScreen(ILI9341_BLACK);
                oc1_setduty_plib(0);
                oc2_setduty_plib(0);
                
                
                tft_setCursor(0,0.5*DH);
                tft_setTextColor(ILI9341_WHITE);
                tft_setTextSize(2);
                tft_writeString("Standby...bias home...");
                
                draw();
                
                
                asrs_state = step_home;

                step_c = 0;
                //reverse DIR
                //enable stepper
                //set DIR for home movement
                LATBbits.LATB9 = 0;
                //LATBbits.LATB9 = 1;
                //enable stepper motor
                LATBbits.LATB15 = 0;
            } else {
                s_c++;
                asrs_state = y_servo_bias;
                
            }

        break;

        case step_home:
            if (step_c >= step_x) {
                step_c=0;

                asrs_state = step_bias_home;
            } else {
                step_c++;

                draw_simulation();

                asrs_state = step_home;
            }
        break;
        
        case step_bias_home:
            if (!PORTBbits.RB10) {
                //disable stepper
                LATBbits.LATB15 = 1;

                tft_fillScreen(ILI9341_BLACK);

                //display s, r buttons
                    tft_drawRect(btn_s_x, btn_s_y, btn_s_w, 0.5*DH, ILI9341_WHITE);
                    tft_setCursor((btn_s_x + ((DW/2)-25)),(btn_s_y + (DH/4)-5));
                    tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
                    tft_setTextSize(2);
                    tft_writeString("Store");
                    tft_drawRect(btn_r_x, btn_r_y, btn_s_w, 0.5*DH, ILI9341_WHITE);
                    tft_setCursor((btn_r_x + ((DW/2)-45)), (btn_r_y + (DH/4)-5));
                    tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
                    tft_setTextSize(2);
                    tft_writeString("Retrieve");

                    asrs_state = idle;
            } else {
                asrs_state = step_bias_home;
            }

        break;
    } 
}

static enum DEBP1_States {DEBP1_NOPUSH, DEBP1_MAYBENOPUSH, DEBP1_MAYBEPUSH, DEBP1_PUSHED} DEBP1_state;


void tickFct_DEBP1() {
    switch(DEBP1_state) {
        case DEBP1_NOPUSH:
            if (btn_listener()) {
                DEBP1_state = DEBP1_MAYBEPUSH;
            } else {
                DEBP1_state = DEBP1_NOPUSH;
            }
            break;
        case DEBP1_MAYBEPUSH:
            if (btn_listener()) {
                uint16_t x;
                uint16_t y;
                x=xpos;
                y=ypos;
                if (asrs_state == idle) {
                    //the fsm is currently in initial state, use button flag for s, r buttons
                    flag_s_r_button(x, y);
                } else if (asrs_state == display_items) {
                    //the fsm is currently in the display state, use button flag for items buttons
                    flag_item_button(x, y);
                }
                DEBP1_state = DEBP1_PUSHED;
            } else {
                DEBP1_state = DEBP1_NOPUSH;
            }
            break;
        case DEBP1_PUSHED:
            if (btn_listener()) {
                DEBP1_state = DEBP1_PUSHED;
            } else {
                DEBP1_state = DEBP1_MAYBENOPUSH;
            }
            break;
        case DEBP1_MAYBENOPUSH:
            if (btn_listener()) {
                DEBP1_state = DEBP1_PUSHED;
            } else {
                DEBP1_state = DEBP1_NOPUSH;
            }
            break;
        default:
            DEBP1_state = DEBP1_NOPUSH;
            break;
    }
}

void init() { 
    //create each pos, with adequate steps to reach each
    struct Pos pos1; 
    pos1.isEmpty = 1;
    pos1.steps = 600;  //612
    struct Pos pos2;
    pos2.isEmpty = 1;
    pos2.steps = 800;  //876
    struct Pos pos3;
    pos3.isEmpty = 1;
    pos3.steps = 1000;  //1131

    //add each pos to a pos array
    pos[0] = pos1;
    pos[1] = pos2;
    pos[2] = pos3;
    
    
    num_items_s = 3;
    num_items_r = 0;
    
    

    
    //motor, stepper init
     LATBbits.LATB15 = 1;
     //direction init for stepper
     LATBbits.LATB9 = 1;
     //LATBbits.LATB9 = 0;
     
     s_c = 0;
     step_c = 0;


    init_button_dim();

    //display s, r buttons
     tft_drawRect(btn_s_x, btn_s_y, btn_s_w, 0.5*DH, ILI9341_WHITE);
     tft_setCursor((btn_s_x + ((DW/2)-25)),(btn_s_y + (DH/4)-5));
     tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
     tft_setTextSize(2);
     tft_writeString("Store");
     tft_drawRect(btn_r_x, btn_r_y, btn_s_w, 0.5*DH, ILI9341_WHITE);
     tft_setCursor((btn_r_x + ((DW/2)-45)), (btn_r_y + (DH/4)-5));
     tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
     tft_setTextSize(2);
     tft_writeString("Retrieve");
}


int main() {
    configureADC();
    
    ANSELA = 0;
    ANSELB = 0;
    
    TRISBbits.TRISB15 = 0;
    TRISBbits.TRISB9 = 0;
    TRISBbits.TRISB13 = 1;
    
    // Turn off comparator functions
    CM1CON = 0; 
    CM2CON = 0;

    

    tft_init_hw();
    tft_begin();
    tft_setRotation(4);  // Landscape mode.  Use 1 for portrait.
    tft_fillScreen(ILI9341_BLACK);
    
    oc1_init_plib(0);
    oc2_init_plib(0);
    INTEnableSystemMultiVectoredInt();

    init();

    DEBP1_state = DEBP1_NOPUSH;
    asrs_state = idle;

    const uint16_t PERIOD_ASRS = 10;
    const uint16_t PERIOD_DEB = 50;
    uint16_t ta1, ta2, tb1, tb2;
    timer1_init();
    ta1 = tb1 = timer1_read();
    while (1)
    {   
        ta2 = tb2 = timer1_read();
        
        if (timer1_ms_elapsed(ta1, ta2) >= PERIOD_ASRS) {
            ta1 = ta2;
            tickFct_asrs();
        }
        if (timer1_ms_elapsed(tb1, tb2) >= PERIOD_DEB) {
            tb1 = tb2;
            tickFct_DEBP1();
        }
    } 
}




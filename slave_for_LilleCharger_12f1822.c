/* 
 * File:   slave_for_LilleCharger_12f1822.c
 * Author: -----
 *
 * Created on 2015/08/04, 15:55
 */

/*********************************************
 *  compiler    MPLAB XC8(v1.34)             *
 *  PIC         PIC12F1822                   *
 *  clock        16MHz(INTIO)                *
 *                                           *
 *  use_port                                 *
 *                __________                 *
 *          Vdd---|1  ●   8|---Vss          *
 *(RA5)Switch_1---|2       7|---Switch_2(RA0)*
 *   (RA4)Motor---|3       6|---SCL(RA1)     *
 *      (RA3)×---|4       5|---SDA(RA2)     *
 *                ==========                 *
 ********************************************/
//#define

#include <xc.h>
#include "I2C_slave.h"

#pragma config CLKOUTEN = OFF
#pragma config WDTE     = OFF
#pragma config PWRTE    = ON
#pragma config CP       = OFF
#pragma config BOREN    = ON
#pragma config FCMEN    = OFF
#pragma config MCLRE    = ON
#pragma config CPD      = OFF
#pragma config IESO     = OFF
#pragma config FOSC     = INTOSC

#pragma config LVP      = ON

#define _XTAL_FREQ 16000000
#define A_MODE 5
#define B_MODE 7


void init();
int Which_Mode = 0;

int main(void) {
    init();
    I2C_init();

    while (1) {
        if(Which_Mode == A_MODE){
            RA4 = 1;
            while(1){
                if(RA5 == 1){
                    RA4 = 0;
                    Which_Mode = 0;
                    break;
                }
            }
        }else if(Which_Mode == B_MODE){
            RA4 = 1;
            while(1){
                if(RA0 == 1){
                    RA4 = 0;
                    Which_Mode = 0;
                    break;
                }
            }
        }else ;
    }

    return (0);
}

void init() {
    OSCCONbits.IRCF = 0b1111;       //Set oscillator 16MHz
    ANSELA  = 0x00;                 //Set RA pins digital
    TRISA0 = 1;
    TRISA5 = 1;
    TRISA4 = 0;
    
    RA4 = 0;
    
    PORTA = 0x00;                   //Set PORTA Low
    return;
}

static void interrupt forinterrupt(){
    #include "I2C_slave_int.h"
    Which_Mode = reseaved_data[0];
}

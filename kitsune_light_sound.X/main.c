/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC16F1705
        Driver Version    :  2.00
 */

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
 */

#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "main.h"

/*
                         Main application
 */

uint16_t led = 0;
uint8_t play = 0;
uint8_t walz = 0;
uint32_t delay_time = 0;
uint8_t walk = 0;

unsigned char scale[] = {

    //    NOTE_D1, NOTE_E1, NOTE_G1, NOTE_A1, 
    //NOTE_B1,
    //    NOTE_D2, NOTE_E2, NOTE_G2, NOTE_A2, NOTE_B2,
    //    NOTE_D3, NOTE_E3, NOTE_G3, NOTE_A3, NOTE_B3,
    //    NOTE_D4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_B4,
    //    NOTE_D5, NOTE_E5, 
    NOTE_G5, NOTE_A5, NOTE_B5,
    NOTE_D6, NOTE_E6, NOTE_G6, 
    NOTE_A6, NOTE_B6,
    //NOTE_D7 ,NOTE_E7, NOTE_G7, //NOTE_A7, NOTE_B7,

    //    NOTE_CS2, NOTE_DS2, NOTE_FS2, NOTE_GS2, NOTE_AS2,
    //    NOTE_CS3, NOTE_DS3, NOTE_FS3, NOTE_GS3, NOTE_AS3,
    //        NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_AS4,
    //        NOTE_CS5, NOTE_DS5, NOTE_FS5, 
    //        NOTE_GS5, NOTE_AS5,
    //        NOTE_CS6, NOTE_DS6, NOTE_FS6, NOTE_GS6, NOTE_AS6,
    //        NOTE_CS7,
    //    NOTE_DS7, NOTE_FS7, NOTE_GS7, NOTE_AS7,

    //        NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5,
    //        NOTE_C6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_G6, NOTE_A6, NOTE_B6,

    // NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_GS5, NOTE_B5,
    // NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_G6, NOTE_GS6, NOTE_B6,

    //             NOTE_D1, NOTE_E1, NOTE_F1, NOTE_G1, NOTE_GS1, NOTE_AS1,
    //             NOTE_D2, NOTE_E2, NOTE_F2, NOTE_G2, NOTE_GS2, NOTE_AS2,
    //             NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_GS3, NOTE_AS3,
    //             NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_GS4, NOTE_AS4,
    //             NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_GS5, NOTE_AS5,
    //             NOTE_C6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_G6, NOTE_GS6,
    //             NOTE_C7, NOTE_D7, NOTE_E7, NOTE_F7, NOTE_G7, NOTE_GS7,


};

void soundPlay(char c, char onkai) {
    if (c == 0) {
        dat_d0 = onkai_d[onkai];
        dat_f0 = onkai_f[onkai];
        env0 = 0;
        envelopeCount0 = 0;
    } else {
        dat_d1 = onkai_d[onkai];
        dat_f1 = onkai_f[onkai];
        env1 = 0;
        envelopeCount1 = 0;
    }
}

static long randomx;

void randomSeed(long val) {
    unsigned int temp;

    if (val == 0) {
        while (1) {
            GO_nDONE = 1;
            while (GO_nDONE);
            temp = (ADRESH << 8) | ADRESL;
            if (temp > 0) break;
        }
        randomx = temp;
    } else randomx = val;
}

long random(long min, long max) {
    long d;

    d = ((randomx = randomx * 1103515245L + 12345) >> 16) & 077777;
    return min + d % (max - min + 1);
}

uint8_t s = 0;
int8_t sd = 1;

void walz_play() {
    uint8_t s_max = sizeof (scale) / sizeof (unsigned char);
    count++;
//    s= random(0, s_max);
//    if (s >= s_max) s = s_max;
    s += sd; 
    if (s >= s_max) {
        s = s_max;
        sd = -1;
    } else if (s <= 0) {
        s = 0;
        sd = 1;

    }
    soundPlay(count % 2, scale[s]);
    led = 1023;
}

void main(void) {
    // initialize the device
    SYSTEM_Initialize();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    ENV_DELAY = 100;

    uint8_t status = 0;
    randomSeed(0);
    uint8_t last_state;



    while (1) {
        now_state = IO_RC0_GetValue();

        if (last_state != now_state) {
            __delay_ms(5);
            now_state = IO_RC0_GetValue();
            if (last_state != now_state) {
                if (status == 0) {
                    status = 1;

                    if (play == 0) {
                        play = 1;

                        walz = 0;
                        delay_time = 0;
                    }
                }
            }

        } else {
            status = 0;
        }

        last_state = now_state;

        if (led > 0) {
            led--;
        }

        PWM1_LoadDutyValue(led);
        __delay_us(1);


        if (play == 1) {
            if (delay_time % 250 == 0) {
                walz_play();
                walz++;
            }
            if (walz >= 3) {
                play = 0;
            }
        } else {
            __delay_us(150);
        }
        delay_time++;

    }
}
/**
 End of File
 */
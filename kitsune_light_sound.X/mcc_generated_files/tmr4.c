/**
  TMR4 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr4.c

  @Summary
    This is the generated driver implementation file for the TMR4 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for TMR4.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC16F1705
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB 	          :  MPLAB X 4.15
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "tmr4.h"
#include "pwm3.h"
#include "../main.h"
#include "../wavetable.h"

/**
  Section: Global Variables Definitions
*/

void (*TMR4_InterruptHandler)(void);

/**
  Section: TMR4 APIs
*/

void TMR4_Initialize(void)
{
    // Set TMR4 to the options selected in the User Interface

    // PR4 255; 
    PR4 = 0xFF;

    // TMR4 0; 
    TMR4 = 0x00;

    // Clearing IF flag before enabling the interrupt.
    PIR2bits.TMR4IF = 0;

    // Enabling TMR4 interrupt.
    PIE2bits.TMR4IE = 1;

    // Set Default Interrupt Handler
    TMR4_SetInterruptHandler(TMR4_DefaultInterruptHandler);

    // T4CKPS 1:1; T4OUTPS 1:2; TMR4ON on; 
    T4CON = 0x0C;
}

void TMR4_StartTimer(void)
{
    // Start the Timer by writing to TMRxON bit
    T4CONbits.TMR4ON = 1;
}

void TMR4_StopTimer(void)
{
    // Stop the Timer by writing to TMRxON bit
    T4CONbits.TMR4ON = 0;
}

uint8_t TMR4_ReadTimer(void)
{
    uint8_t readVal;

    readVal = TMR4;

    return readVal;
}

void TMR4_WriteTimer(uint8_t timerVal)
{
    // Write to the Timer4 register
    TMR4 = timerVal;
}

void TMR4_LoadPeriodRegister(uint8_t periodVal)
{
   PR4 = periodVal;
}

void TMR4_ISR(void)
{

    // clear the TMR4 interrupt flag
    PIR2bits.TMR4IF = 0;

    if(TMR4_InterruptHandler)
    {
        TMR4_InterruptHandler();
    }
}


void TMR4_SetInterruptHandler(void (* InterruptHandler)(void)){
    TMR4_InterruptHandler = InterruptHandler;
}

void TMR4_DefaultInterruptHandler(void) {
    uint8_t tmp;

    envelopeCount0--;
    if (!envelopeCount0) {
        if (env0 != 255) {
            env0++;
            envelopeCount0 = ENV_DELAY;
        }
    }

    pos_d0 += dat_d0;
    pos_f0 += dat_f0;
    tmp = pos_f0 >> 8;
    pos0 = pos_d0 + tmp;

    tmp = envelopeTable[env0];
    evp0 = pos0 + tmp;
    envelopeValue0 = waveTable[evp0];

    waveData0 = waveTable[pos0] + envelopeValue0;
    waveData0 >>= 6;


    envelopeCount1--;
    if (!envelopeCount1) {
        if (env1 != 255) {
            env1++;
            envelopeCount1 = ENV_DELAY;
        }
    }

    pos_d1 += dat_d1;
    pos_f1 += dat_f1;
    tmp = pos_f1 >> 8;
    pos1 = pos_d1 + tmp;

    tmp = envelopeTable[env1];
    evp1 = pos1 + tmp;
    envelopeValue1 = waveTable[evp1];


    waveData1 = waveTable[pos1] + envelopeValue1;
    waveData1 >>= 6;
    
    PWM3_LoadDutyValue(waveData0 + waveData1);
//    PWM3DCH = waveData0 + waveData1;
}

/**
  End of File
*/
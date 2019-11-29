/**
   COG1 Generated Driver File
 
   @Company
     Microchip Technology Inc.
 
   @File Name
     cog1.c
 
   @Summary
     This is the generated driver implementation file for the COG1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs
 
   @Description
     This source file provides implementations for driver APIs for COG1.
     Generation Information :
         Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
         Device            :  PIC16F1705
         Driver Version    :  2.01
     The generated drivers are tested against the following:
         Compiler          :  XC8 1.45
         MPLAB             :  MPLAB X 4.15
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
#include "cog1.h"

/**
  Section: COG1 APIs
*/

void COG1_Initialize(void)
{
    // Reset double buffered register COG1CON0
    COG1CON0 = 0x00;

    // Set the COG to the options selected in PIC10 / PIC12 / PIC16 / PIC18 MCUs
    // G1POLA Active low; G1POLB Active high; G1POLC Active high; G1POLD Active high; G1FDBS COGx_clock and COGxDBF; G1RDBS COGx_clock and COGxDBR; 
    COG1CON1 = 0x01;

    // G1RIS0 disabled; G1RIS1 disabled; G1RIS2 disabled; G1RIS3 disabled; G1RIS4 disabled; G1RIS5 disabled; G1RIS6 enabled; 
    COG1RIS = 0x40;

    // G1RSIM0 Level Trigger; G1RSIM1 Level Trigger; G1RSIM2 Level Trigger; G1RSIM3 Level Trigger; G1RSIM4 Level Trigger; G1RSIM5 Level Trigger; G1RSIM6 Edge Trigger; 
    COG1RSIM = 0x40;

    // G1FIS0 disabled; G1FIS1 disabled; G1FIS2 disabled; G1FIS3 disabled; G1FIS4 disabled; G1FIS5 disabled; G1FIS6 enabled; 
    COG1FIS = 0x40;

    // G1FSIM0 Level Trigger; G1FSIM1 Level Trigger; G1FSIM2 Level Trigger; G1FSIM3 Level Trigger; G1FSIM4 Level Trigger; G1FSIM5 Level Trigger; G1FSIM6 Edge Trigger; 
    COG1FSIM = 0x40;

    // G1ASDAC tri-stated; G1ASDBD tri-stated; G1ARSEN disabled; G1ASE not shutdown; 
    COG1ASD0 = 0x14;

    // G1AS0E disabled; G1AS1E disabled; G1AS2E disabled; G1AS3E disabled; 
    COG1ASD1 = 0x00;

    // G1STRA waveform; G1STRB waveform; G1STRC waveform; G1STRD waveform; G1SDATA static data low; G1SDATB static data low; G1SDATC static data low; G1SDATD static data low; 
    COG1STR = 0x0F;

    // G1DBR 0; 
    COG1DBR = 0x00;

    // G1DBF 0; 
    COG1DBF = 0x00;

    // G1BLKR 0; 
    COG1BLKR = 0x00;

    // G1BLKF 0; 
    COG1BLKF = 0x00;

    // G1PHR 0; 
    COG1PHR = 0x00;

    // G1PHF 0; 
    COG1PHF = 0x00;

    // G1MD steered PWM mode; G1CS FOSC; G1LD transfer complete; G1EN enabled; 
    COG1CON0 = 0x88;

}

void COG1_AutoShutdownEventSet()
{
    // Setting the GxASDE bit of COGxASD register
    COG1ASD0bits.G1ASE = 1;
}

void COG1_AutoShutdownEventClear()
{
    // Clearing the GxASDE bit of COGxASD register
    COG1ASD0bits.G1ASE = 0;
}
/**
 End of File
*/


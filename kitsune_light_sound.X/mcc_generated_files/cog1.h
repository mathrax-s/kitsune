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

#ifndef COG1_H
#define COG1_H

/**
  Section: Included Files
*/

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: COG1 APIs
*/

/**
  @Summary
    Initializes the COG1

  @Description
    This routine configures the COG1 specific control registers and input clock

  @Preconditions
    None

  @Returns
    None

  @Param
    None

  @Comment

  @Example
    <code>
    COG1_Initialize();
    </code>
*/
void COG1_Initialize(void);

/**
  @Summary
    Software generated Shutdown

  @Description
    This function forces the COG into Shutdown state.

  @Preconditions
    COG1_Initialize() function should have been called before calling this function

  @Returns
    None

  @Param
    None

  @Example
    <code>
    COG1_initialize();

    // Do something

    COG1_AutoShutdownEventSet();
    </code>
*/
void COG1_AutoShutdownEventSet();

/**
  @Summary
    This function makes the COG to resume its operations from the software
    generated shutdown state.

  @Description
    When auto-restart is disabled, the shutdown state will persist as long as the
    GxASE bit is set and hence to resume operations, this function should be used.

    However when auto-restart is enabled, the GxASE bit will clear automatically
    and resume operation on the next rising edge event. In that case, there is no
    need to call this function.

  @Preconditions
    COG1_Initialize() and COG1_AutoShutdownEventSet() functions should have been called before calling this function

  @Returns
    None

  @Param
    None

  @Example
    <code>
    COG1_initialize();

    // Do something

    COG1_AutoShutdownEventSet();

    // Do something

    COG1_AutoShutdownEventClear();
    </code>
*/
void COG1_AutoShutdownEventClear();


#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  //COG1_H
/**
 End of File
*/

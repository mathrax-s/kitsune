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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
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

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */

uint16_t timeout[8];
int8_t state[8];
int8_t last_state[8];

void main(void) {
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1) {
        MTOUCH_Service_Mainloop();

        state[0] = MTOUCH_Button_isPressed(Button0);
        state[1] = MTOUCH_Button_isPressed(Button1);
        state[2] = MTOUCH_Button_isPressed(Button2);
        state[3] = MTOUCH_Button_isPressed(Button3);
        state[4] = MTOUCH_Button_isPressed(Button4);


        EUSART_Write(255);

        for (int i = 0; i < 5; i++) {
            EUSART_Write(state[i]);

            last_state[i] = state[i];

            if (last_state[i] == state[i]) {
                timeout[i]++;
                if (timeout[i] % 1000 == 0) {
                    MTOUCH_Sensor_Sampled_ResetAll();
                }
            }
        }
        //        EUSART_Write(MTOUCH_Proximity_Deviation_Get(Proximity0));

        //        printf("%d,\t%d,\t%d,\t%d,\t%d,\n",
        //                MTOUCH_Button_isPressed(Button0),
        //                MTOUCH_Button_isPressed(Button1),
        //                MTOUCH_Button_isPressed(Button2),
        //                MTOUCH_Button_isPressed(Button3),
        //                MTOUCH_Proximity_Deviation_Get(Proximity0)
        //        );


    }
}
/**
 End of File
 */
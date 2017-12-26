// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************
#include <xc.h>          /* Defines special function registers, CP0 regs  */
#include <stdint.h>          /* For uint32_t definition                       */
#include <sys/attribs.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "user.h"            /* variables/params used by user.c               */
#include "OLED.h"
#include "OledChar.h"
#include "OledGrph.h"
#include "UART.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************


/******************************************************************************/
/* User Functions                                                             */

/******************************************************************************/

void InitGPIO(void) {
    // LED output
    // Disable analog mode for G6
    ANSELGbits.ANSG6 = 0;
    // Set direction to output for G6
    TRISGbits.TRISG6 = 0;

    // Initialize outputs for other LEDs
    ANSELBbits.ANSB11 = 0;
    ANSELGbits.ANSG15 = 0;

    TRISBbits.TRISB11 = 0;
    TRISGbits.TRISG15 = 0;
    TRISDbits.TRISD4 = 0;

    // Turn off LEDs for initialization
    LD1_PORT_BIT = 0;
    LD2_PORT_BIT = 0;
    LD3_PORT_BIT = 0;
    LD4_PORT_BIT = 0;

    // Initilalize input for BTN1
    // Disable analog mode
    ANSELAbits.ANSA5 = 0;
    // Set direction to input
    TRISAbits.TRISA5 = 1;

    // Initialize input for BTN2
    TRISAbits.TRISA4 = 1;
}

void InitBIOSGPIO(void) {
    /* Setup functionality and port direction */
    // LED outputs
    // Disable analog mode
    // Set directions to output
    TRISE = 0;
   
    // Test LEDs
    LATE = 0xff;        
    
    // Turn off LEDs for initialization
    LATE = 0;

    // Button inputs
    ANSELEbits.ANSE8 = 0;
    ANSELEbits.ANSE9 = 0;
    
    // Set directions to input
    TRISAbits.TRISA3 = 1;
    TRISDbits.TRISD5 = 1;
    TRISFbits.TRISF1 = 1;
    TRISAbits.TRISA2 = 1;
    TRISEbits.TRISE8 = 1;
    TRISEbits.TRISE9 = 1;
}

void InitApp(void) {
    // Initialize peripherals
    InitGPIO();
    InitBIOSGPIO();
    
    OledHostInit();
    OledDspInit();
    OledDvrInit();
    
    // TODO: Add UART4 Initialization call here
    UART4_init();
}

void Task1(void * pvParameters) {
    xSemaphoreTake(xMutexOLED, portMAX_DELAY);
    char buffer[32];
    int x = 96;
    int y = 16;
    int n;
    /* Initialize I/O 
     * and Peripherals
     * for application */
    InitApp();
    
    OledDvrInit();
    xSemaphoreGive(xMutexOLED);
    
    while (1) {
        // TODO: Take mutex here
        xSemaphoreTake(xMutexOLED, portMAX_DELAY);
         if (SW1) // if switch is on
        {
            OledSetDrawColor(1); //set white color
        }
        
        if (!SW1) // if switch is off
        {
            OledSetDrawColor(0); //set black color
            if (SW2) // if switch is on, then clear part of screen
            {
                OledMoveTo(65,0);
                OledFillRect(127, 31);
                OledMoveTo(x,y);
            }
            
        }
        OledUpdate();
        // TODO: Give mutex here
        xSemaphoreGive(xMutexOLED);
        vTaskDelay(9);     
    }
}

void Task2(void * pvParameters) {
    xSemaphoreTake(xMutexOLED, portMAX_DELAY);
    //int n=0; 
    char buffer[32];
    int x = 96;
    int y = 16;
    int n;
    int stb3 = 0;
    int stb2 = 0;
    int stb4 = 0;
    int stb1 = 0;
    /* Initialize I/O 
     * and Peripherals
     * for application */
    InitApp();
    
    OledDvrInit();
    
    OledSetDrawColor(1); //set white color
    
    OledMoveTo(x,y); // setup initial coordinates for painting
    xSemaphoreGive(xMutexOLED);
    while (1) {
        // TODO: Add trigger code here    
        // TODO: Take mutex here
        xSemaphoreTake(xMutexOLED, portMAX_DELAY);
       if (BTN2) // go to the right pixel if the button was pressed
        {
            if(!stb2)
            {
                stb2 = !stb2;
                OledMoveRight();
            }
        }
        
        if (!BTN2)
        {
                stb2 = 0;
        }
        
         if (BTN3) // go to the left pixel if the button was pressed
        {
            if(!stb3)
            {
                stb3 = !stb3;
                OledMoveLeft();
            }
        }
        
        if (!BTN3)
        {
                stb3 = 0;
        }
        
        if (BTN4) // go to the top pixel if the button was pressed
        {
            if(!stb4)
            {
                stb4 = !stb4;
                OledMoveUp();
            }
        }
        
        if (!BTN4)
        {
                stb4 = 0;
        }
        
          if (BTN1) // go to the lower pixel if the button was pressed
        {
            if(!stb1)
            {
                stb1 = !stb1;
                OledMoveDown();
            }
        }
        
        if (!BTN1) 
        {
                stb1 = 0;
        }
        OledDrawPixel(); // draw pixel with the selected color
        OledUpdate();
        xSemaphoreGive(xMutexOLED);
         //vTaskDelay(10);
    }
}

// TODO: Define function ClockTask here


// TODO: Define SerialInTask here

void DelayMs(int t) {
    volatile long int count = t*33356;
    
    while (count--)
        ;
}
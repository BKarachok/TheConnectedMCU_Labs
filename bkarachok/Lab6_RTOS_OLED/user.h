#ifndef USER_H
#define USER_H

#include "FreeRTOS.h"
#include "semphr.h"

/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

// Add I/O name macros here
#define LD1_PORT_BIT        LATGbits.LATG6
#define LD2_PORT_BIT        LATDbits.LATD4
#define LD3_PORT_BIT        LATBbits.LATB11
#define LD4_PORT_BIT        LATGbits.LATG15

// Basic I/O Shield 
#define BIOS_LD1_PORT_BIT        LATEbits.LATE0
#define BIOS_LD2_PORT_BIT        LATEbits.LATE1
#define BIOS_LD3_PORT_BIT        LATEbits.LATE2
#define BIOS_LD4_PORT_BIT        LATEbits.LATE3
#define BIOS_LD5_PORT_BIT        LATEbits.LATE4
#define BIOS_LD6_PORT_BIT        LATEbits.LATE5
#define BIOS_LD7_PORT_BIT        LATEbits.LATE6
#define BIOS_LD8_PORT_BIT        LATEbits.LATE7

#define SW1                      PORTEbits.RE8
#define SW2                      PORTEbits.RE9
#define BTN1                     PORTAbits.RA3
#define BTN2                     PORTDbits.RD5
#define BTN3                     PORTFbits.RF1
#define BTN4                     PORTAbits.RA2


/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/
void InitApp(void);         /* I/O and Peripheral Initialization */

void Task1 ( void * pvParameters);
void Task2 ( void * pvParameters);

void DelayMs(int t);

// TODO: Declare function ClockTask here
void ClockTask ( void * pvParameters);
// TODO: Declare function SerialInTask here
// TODO: Declare semaphore handle here
SemaphoreHandle_t xSemTrigger;

#endif // USER_H
#include <xc.h>
#include "UART.h"
#include "config.h"
#include <stdio.h>

// Define the PWM frequency to drive the motor
#define PWM_FREQ 2000
#define PWM_RANGE (_XTAL_FREQ / 16) / PWM_FREQ

// Define pin connect to the motor driver
#define DC1 RD0
#define DC2 RD1

// Define the command to control the motor using Bluetooth
#define Brake 48
#define Direc 50
#define Speedup 52
#define Speeddown 54

// Declare variables
char rcvStr[17];
uint8_t command = 0;
uint16_t dc = 200;

// Function to configure PWM mode for CCP1
void PWM_Init(void){
    // Configure RC2 as output pin
    TRISC2 = 0;
    // Configure PWM mode in CCPCON
    CCP1M3 = 1;
    CCP1M2 = 1;
}

// Function to configure Timer2 
void Timer2_Init(void){
    // Assign the PWM frequency to be 2kHz at pre-scaler 16
    PR2 = (PWM_RANGE/4) - 1;
    // Use pre-scaler 1:16
    T2CKPS1 = 1;
    T2CKPS0 = 1;
}

// Function to control the speed of the motor by varying the PWM duty cycle 
void DC_Speed(uint16_t dutyCycle){
    if(dutyCycle <= PWM_RANGE){
        // Get the 2 LSB-bit
        CCP1CONbits.CCP1Y = (dutyCycle) & 1;
        CCP1CONbits.CCP1X = (dutyCycle) & 2;
        // Move 8 MSB-bit to CCPRL
        CCPR1L = (dutyCycle) >> 2;
        // Activate Timer 2
        TMR2ON = 1;
    }
    else
    {
        UART_sendString("Invalid duty cycle\r\n");
    }
}

// Function to handle the command sending through Bluetooth
void Command_Handling(uint8_t com)
{
    // Case brake the motor
    if(com == Brake)
    {
        DC_Speed(0);
    }
    // Case change the direction of the motor
    else if(com == Direc)
    {
        DC1 = ~DC1;
        DC2 = ~DC2;
    }
    // Case speed up the motor
    else if(com == Speedup)
    {
        dc += 100;
        DC_Speed(dc);
    }
    // Case decrease the speed of the motor
    else if(com == Speeddown)
    {
        dc -= 100;
        DC_Speed(dc);
    }
    else
    {
        UART_sendString("Invalid command\r\n");
    }
}

// Function handle interrupt service routine
void __interrupt() ISR(void)
{
    // UART interrupt
    if(RCIF)
    {
        // Error handling
        if (OERR) 
        {
            CREN = 0; 
            CREN = 1;  
        }
        command = RCREG;
        sprintf(rcvStr, "Received: %c\r\n", command);
        UART_sendString(rcvStr);
        Command_Handling(command);
    }
}

void main(void) {
    // GPIO Initialization
    TRISD0 = 0;
    TRISD1 = 0;
    // System initialization
    PWM_Init();
    Timer2_Init();
    UART_Init();
    __delay_ms(50);
    UART_sendString("System is ready\r\n");
    // Start the motor
    DC1 = 1;
    DC2 = 0;
    DC_Speed(dc);
    // Main duty
    while(1)
    {    
    }
    return;
}

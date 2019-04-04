/* 
 * File:   main.c
 * Author: ginst
 *
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "peripherals.h"
//#include "adcdrv.h"
#include <p33FJ128MC802.h>

#define EXIT_SUCCESS 0 //added for delay funct
// FBS
#pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)
#pragma config RBS = NO_RAM             // Boot Segment RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WRPROTECT_OFF     // Secure Segment Program Write Protect (Secure segment may be written)
#pragma config SSS = NO_FLASH           // Secure Segment Program Flash Code Protection (No Secure Segment)
#pragma config RSS = NO_RAM             // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
#pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
#pragma config FNOSC = FRCPLL          // Oscillator Mode (Internal Fast RC (FRC) w/ PLL)
#pragma config IESO = ON                // Internal External Switch Over Mode (Start-up device with FRC, then automatically switch to user-selected oscillator source when ready)

// FOSC
#pragma config POSCMD = HS              // Primary Oscillator Source (HS Oscillator Mode)
#pragma config OSCIOFNC = ON            // OSC2 Pin Function (OSC2 pin has digital I/O function)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow Only One Re-configuration)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler (1:32,768)
#pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF              // Watchdog Timer Enable (Watchdog timer always enabled)

// FPOR
#pragma config FPWRT = PWR128           // POR Timer Value (128ms)
#pragma config ALTI2C = OFF             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)
#pragma config LPOL = ON                // Motor Control PWM Low Side Polarity bit (PWM module low side output pins have active-high output polarity)
#pragma config HPOL = ON                // Motor Control PWM High Side Polarity bit (PWM module high side output pins have active-high output polarity)
#pragma config PWMPIN = ON              // Motor Control PWM Module Pin Mode bit (PWM module pins controlled by PORT register at device Reset)

// FICD
#pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)


int global_ctr = 0;
int global_delay_val = 100; //variables for led signal


int main(){
    /*Configure Oscillator to operate the device at Fdev
     Fosc = Fin*M/(N1/N2), Fcy=Fosc/2
     * 
     */
    //configure PLL prescaler, PLL postscaler, PLL divisor
    
     PLLFBD = 32;                      //M = 32
     
     CLKDIVbits.PLLPOST= 0;           //N2= 2
     CLKDIVbits.PLLPRE= 0;            //N1= 2
     

    //Initiate Clock Switch to Primary Oscillator with PLL
    __builtin_write_OSCCONH(0x01);      //New Oscillator w/PLL
    __builtin_write_OSCCONL(0x01);      //Enable Switch
    
    
    //Wait for Clock Switch to occur
     while (OSCCONbits.COSC!= 0b001);   //Wait for new Oscillator to become FRC w/ PLL
     while (OSCCONbits.LOCK!=1);         //Wait for PLL to Lock
     

     
     ACLKCONbits.SELACLK = 1;           //Auxiliary Oscillator provides clock source for PWM and ADC
     ACLKCONbits.APSTSCLR = 7;          //Divide Auxiliary Clock by 1
     
     
     TRISAbits.TRISA4 = 0;              //set as digital output
     TRISBbits.TRISB13 = 0;           //added but hasn't been checked yet 
    
     LATAbits.LATA4 = 1;                
     LATBbits.LATB13 = 1;             //added but hasn't been checked yet
     
     //initadc1();   //ad converter 
     init_PWM();   //calls pwm function
     
     LATA = 0;  //for led switching
     TRISA = 0;
     
    while (1) {
         //loop to run LED
    
    delay(global_delay_val);
    LATA = 0x0001;
    
    if (PDC1 < 4808)
        PDC1 = PDC1 + 1;
    else
        PDC1 = 0;
        
    delay(global_delay_val);
    LATA = 0x0000;   

    global_ctr++;
}
return(EXIT_SUCCESS);
   
     
     }
    
        

  
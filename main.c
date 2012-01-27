/*********************************************************************
Date: 24-9-2011 
Project: #MG
Version: 0.5 DanUp
File: main.c
Compiler: MPLAB C18
Processor: 18F4550
Company: LightYourselUp
Contact: we@lightyourselfup.com
Comments: Firmware version for 7x7 pixels table
*********************************************************************/

#ifndef MAIN_C
#define MAIN_C

/* Files included ***************************************************/

#include <p18F4550.h>
#include "timers.h"
#include "ISR.h"
#include "content.h"
#include "draw.h"
#include "transitions.h"
#include "animations.h"

/* Device setup ******************************************************/

        #pragma config PLLDIV   = 5         // (20 MHz crystal on PICDEM FS USB board)
        #pragma config CPUDIV   = OSC1_PLL2   
        #pragma config USBDIV   = 2         // Clock source from 96MHz PLL/2
        #pragma config FOSC     = HSPLL_HS
        #pragma config FCMEN    = OFF
        #pragma config IESO     = OFF
        #pragma config PWRT     = OFF
        #pragma config BOR      = ON
        #pragma config BORV     = 3
        #pragma config VREGEN   = ON      //USB Voltage Regulator
        #pragma config WDT      = OFF
        #pragma config WDTPS    = 32768
        #pragma config MCLRE    = OFF
        #pragma config LPT1OSC  = OFF
        #pragma config PBADEN   = OFF
//      #pragma config CCP2MX   = ON
        #pragma config STVREN   = ON
        #pragma config LVP      = OFF
//      #pragma config ICPRT    = OFF       // Dedicated In-Circuit Debug/Programming
        #pragma config XINST    = OFF       // Extended Instruction Set
        #pragma config CP0      = OFF
        #pragma config CP1      = OFF
//      #pragma config CP2      = OFF
//      #pragma config CP3      = OFF
        #pragma config CPB      = OFF
//      #pragma config CPD      = OFF
        #pragma config WRT0     = OFF
        #pragma config WRT1     = OFF
//      #pragma config WRT2     = OFF
//      #pragma config WRT3     = OFF
        #pragma config WRTB     = OFF       // Boot Block Write Protection
        #pragma config WRTC     = OFF
//      #pragma config WRTD     = OFF
        #pragma config EBTR0    = OFF
        #pragma config EBTR1    = OFF
//      #pragma config EBTR2    = OFF
//      #pragma config EBTR3    = OFF
        #pragma config EBTRB    = OFF
	

#pragma code
void main(void){

	unsigned char i,j;
	
	/* Output configurations */

	ADCON1 |= 0x0F;	// All possible analog input pins config as digital I/O
	CMCON = 0x07;	// Comparators disabled 
	
	/* Natural interaction expansion port configuration	*/
	TRISAbits.TRISA4 = 1;	// A4 Botton 3
	TRISAbits.TRISA3 = 1;	// A3 Botton 2
	TRISAbits.TRISA2 = 1;	// A2 Botton 1
	TRISAbits.TRISA1 = 1;	// A1 Potentiometer 2
	TRISAbits.TRISA0 = 1;	// A0 Potentiometer 1

	// Hunting random reset-nonstarting bug
	//TRISA = 0;
	//PORTA = 0; 

	TRISB = 0;	// B0..B6	Serial input for the Shift Registers
	TRISD = 0;	// D0..D3	Shift Registers control inputs: SCK, RCK, _SCL, _G
	TRISEbits.TRISE0 = 1; //Input button PORTEbits.RE0

	LATA = 0;	// Disable expansion port
	_SCL = 1;	// Disable Shift Register _SCL (Global Clear)
	_G = 0;		// Enables Shift Regusters outputs _G

	//Resetting variables
	for(i = 0; i <= MAX_INDEX_G_BUFFER_GREYSCALE; i++) {gBufferGreyscale[i] = 0; gPreBufferGreyscale[i] = 0;
	}
	for(i = 0; i <= MAX_INDEX_M_BUFFER_MATRIX; i++) {mBufferMatrix[i] = RESET_M_BUFFER_MATRIX;}
	iGreyscale = 0; iTimer1 = 0; iMenu = 0; booleanMenu = 0; pwm = 0;

	/* Timer 0 Configuration */
	// Used to trigger the refresh matrix printed data routine
	OpenTimer0(TIMER_INT_ON & T0_8BIT & T0_SOURCE_INT & T0_PS_1_1);
	WriteTimer0(0);

	/* Timer 1 Configuration */
	// Used to periodically check the input data (external buttons)
	OpenTimer1(TIMER_INT_ON & T1_SOURCE_INT &  T1_PS_1_8 & T1_OSC1EN_OFF & T1_SYNC_EXT_OFF);
	WriteTimer1( 0x00 & 0x00 );
	
	/* Timer 3 Configuration */
	// Used to create delays within the different menus without blocking with delays
	OpenTimer3( TIMER_INT_ON & T3_16BIT_RW & T3_SOURCE_INT & T3_PS_1_8 & T3_SYNC_EXT_OFF);
	WriteTimer3( 0x00 & 0x00 );	

	/* A/D configuration */
	//ADCON1
	ADCON1bits.VCFG1 = 0;	// Voltage Reference Configuration bit (Vref-) = Vss 
	ADCON1bits.VCFG0 = 0;	// Voltage Reference Configuration bit (Vref+) = Vdd
	ADCON1bits.PCFG3 = 1;	// PCFG = "1110" enables AN0 and AN1
	ADCON1bits.PCFG2 = 1;
	ADCON1bits.PCFG1 = 1;
	ADCON1bits.PCFG0 = 0;

	//ADCON0
	ADCON0bits.ADON = 1;	// A/D converter module is enabled 
	ADCON0bits.CHS0 = 0;	// CHS = "0000" AN0 selected
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS3 = 0;

	//ADCON2
	ADCON2bits.ADCS0 = 0;	// A/D Adquisition Clock Select bits
	ADCON2bits.ADCS1 = 1;	// Tad = conversion time per bit. The A/D conversion requires 11 Tad
	ADCON2bits.ADCS2 = 0;	// "010" = 32 * Tosc

	ADCON2bits.ACQT0 = 0;	// A/D Adquisition time bits	"000" = Manual adquisition
	ADCON2bits.ACQT1 = 0;
	ADCON2bits.ACQT2 = 0;
	ADCON2bits.ADFM = 0;	// Left justified 	. . .ADRESH . . : . . ADRESL. . .
							//					7 6 5 4 3 2 1 0 : 7 6 5 4 3 2 1 0
							//					X X X X X X X X . X X . . . . . . <-Left Justified


	/* Enabling interrups */
	INTCONbits.TMR0IE = 1;	// Enables interrupts for TIMER0
	PIE1bits.TMR1IE = 1;	// Enables interrupts for TIMER1
	PIE2bits.TMR3IE = 1;	// Enables interrupts for TIMER3
	INTCONbits.PEIE = 1;	// Peripherial interrupt enabled
	INTCONbits.GIE = 1;	// Global interrupt enabled

	/* Main Loop */			
   	while(1) 
   	{
		
		/******************************************************************/
		/* 0 - Fixed light dimmed with external control                   */
		/******************************************************************/
/*
		drawLine(1,1,1,7,pwm);	//dirty way to draw the all pixels at the same time
		drawLine(2,1,2,7,pwm);
		drawLine(3,1,3,7,pwm);
		drawLine(4,1,4,7,pwm);
		drawLine(5,1,5,7,pwm);
		drawLine(6,1,6,7,pwm);
		drawLine(7,1,7,7,pwm);	
*/


		/******************************************************************/
		/* 2 - Space invaders                                             */
		/******************************************************************/
		
		


	}// End while

CloseTimer0();
CloseTimer1();
}//end main
#endif

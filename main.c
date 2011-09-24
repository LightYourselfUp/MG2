/*********************************************************************
Date: 24-9-2011 
Project: #MG
Version: 0.5 DanUp
File: main.c
Compiler: MPLAB C18
Processor: 18F4550
Company: LightYourselUp
Contact: we@lightyourselfup.com
Comments: 
*********************************************************************/

#ifndef MAIN_C
#define MAIN_C

/* Files included ***************************************************/

#include <p18F4550.h>
#include "timers.h"
#include "delays.h"
#include "ISR.h"
#include "draw.h"

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
	
	TRISA = 0;	// A0..A5	Expansion port
	TRISB = 0;	// B0..B6	Serial input for the Shift Registers
	TRISD = 0;	// D0..D3	Shift Registers control inputs: SCK, RCK, _SCL, _G
	TRISEbits.TRISE0 = 1; //Input button PORTEbits.RE0

	LATA = 0;	// Disable expansion port
	_SCL = 1;	// Disable Shift Register _SCL (Global Clear)
	_G = 0;		// Enables Shift Regusters outputs _G

	//Resetting variables
	for(i = 0; i <= MAX_INDEX_G_BUFFER_GREYSCALE; i++) {gBufferGreyscale[i] = 0; gPreBufferGreyscale[i] = 0;}
	for(i = 0; i<= MAX_INDEX_M_BUFFER_MATRIX; i++) {mBufferMatrix[i] = RESET_M_BUFFER_MATRIX;}
	iGreyscale = 0; iTimer1 = 0; iMenu = 0; FIRST = 0; SECOND = 0; THIRD = 0; FOURTH = 0; FIFTH = 0; 

	/* Timer 0 Configuration */
	// Used to trigger the refresh matrix printed data routine
	OpenTimer0(TIMER_INT_ON & T0_8BIT & T0_SOURCE_INT & T0_PS_1_1);
	WriteTimer0(0);

	/* Configurar Timer 1 */
	// Used to periodically check the input data (external buttons)
	OpenTimer1(TIMER_INT_ON & T1_SOURCE_INT &  T1_PS_1_8 & T1_OSC1EN_OFF & T1_SYNC_EXT_OFF); //
	WriteTimer1(0x00 & 0x00);

	/* Enabling interrups */
	INTCONbits.PEIE = 1;	// Peripherial interrupt enabled
	INTCONbits.GIE = 1;	// Global interrupt enabled

	/* Main Loop */			
   while(1) 
   {
		/*	Main MENU includes the different modes that the table can show
			Switching between menus is done using external button(RE0):
		
				0 - Fixed light dimmed with external control (NOT IMPLEMENTED)
				1 - Slow square
				2 - Slow wave (NOT IMPLMENTED)
				3 - Message mode (NOT IMPLMENTED)
				4 - Party mode (NOT IMPLMENTED)
		
		*/	
		switch(iMenu){

			/******************************************************************/
			/* 0 - Fixed light dimmed with external control (NOT IMPLEMENTED) */
			/******************************************************************/
			case 0:
					if (FIRST == 0){deleteMatrix(); drawLine(1,1,5,4,55);}
					(FIRST = 1);
					break;

			/******************/	
			/* 1- Slow square */
			/******************/
			case 1:

					for(j = 130, i = 254; j<=254; j++, i--){	
						drawSquare(1,1,5,5,j);
						drawSquare(2,2,4,4,i);
						drawPoint(3,3,j);
						Delay10KTCYx(100);
						if(iMenu != 1){break;}	
					}
						if(iMenu != 1){break;}	
					for(j = 130, i = 254; j<=254; j++, i--){		
						drawSquare(1,1,5,5,i);
						drawSquare(2,2,4,4,j);
						drawPoint(3,3,i);
						Delay10KTCYx(100);
						if(iMenu != 1){break;}
					}
						if(iMenu != 1){break;}	// It allows to break the case during the executation	
			
			/*********************************/
			/* 2- Slow wave (NOT IMPLMENTED) */
			/*********************************/
			case 2:
					if (THIRD == 0){deleteMatrix(); drawLine(1,3,5,3,150);}
					(THIRD = 1);
					break;

			/************************************/
			/* 3- Message mode (NOT IMPLMENTED) */
			/************************************/
			case 3:
					if (FOURTH == 0){deleteMatrix(); drawLine(1,4,5,4,200);}
					(FOURTH = 1);
					break;

			/**********************************/
			/* 4- Party mode (NOT IMPLMENTED) */
			/**********************************/
			case 4:
					if (FIFTH == 0){deleteMatrix(); drawLine(1,5,5,5,254);}
					
					//SOLVES A BUG: because when TMR1F is called from this case, FIFTH is 
					//reset but when we come back is set one because we are in case 4 not 1, 
					if (iMenu == 4)(FIFTH = 1);	
					break;			
			
			default:
					drawPoint(3,3, 180);
			
		}// End switch iMenu
	}// End while

CloseTimer0();
CloseTimer1();
}//end main
#endif

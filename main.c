// Date: 16-9-2011 
// Project: #MG v0.5
// File: main.c
// Versión: 002
// Características: Primera versión del firmware para v0.5

#ifndef MAIN_C
#define MAIN_C

#include <p18F4550.h>
#include "timers.h"
#include "delays.h"
#include "ISR.h"

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
	

/** DECLARATIONS ***************************************************/
#pragma code
void main(void){

	unsigned char i;
	rom unsigned char *address;
	//configurar salidas de control de los SRs
	ADCON1 |= 0x0F;   // Todos las salidas AN como digitales
	CMCON = 0x07;	// Desconecta los comparadores 
	//Todos los puertos como salídas
	TRISA = 0;	//OK	Puerto de expansión 0..4
	TRISB = 0;	//OK	Salida de datos 0..4
	TRISC = 0;	//OK	nada
	TRISD = 0;	//OK	control del los SRs 0..3
	TRISE = 0; 	//OK	led de pruebas 0

	LATA = 0;	// Deshabilitamos salidas puerto expansión
	_SCL = 1;	//deshabilitamos clear de de los SRs
	_G = 0;		//habilitamos salidas de los SRs

	//Resetting ISR varibles
	for(i = 0; i<=24; i++) {gBufferGreyscale[i] = i;}
	for(i = 0; i<=4; i++) {mBufferMatrix[i] = 0xFF;}
	iGreyscale = 0; iBufferMatrix = 0; iISR = 0; columnISR = 0; rowISR = 0; 

	// Configurar Timer 0
	OpenTimer0(TIMER_INT_ON & T0_8BIT & T0_SOURCE_INT & T0_PS_1_1); //Ejecución cada ~50uS
	//Habilitar Interrupciones
	INTCONbits.PEIE = 1;		// peripherial interrupt enabled
	INTCONbits.GIE = 1;	// global interrupt enabled
	//Write timer0
	WriteTimer0(0);
	
   while(1) 
   {
		for(i = 0; i<=24; i++) {gBufferGreyscale[i] = i;}

	}//end while

CloseTimer0();
}//end main
#endif

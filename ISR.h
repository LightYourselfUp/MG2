// Date: 22 - 08 - 2011 
// Project: #MG v0.4 Ginebra(La convención)
// File: ISR.h
// Versión: 01
// Características: Cabecera de descripción de ISR

#ifndef ISR_H //Esto evita reincluir multiples veces el mismo archivo
#define ISR_H

/* Inclusión de archivos */
#include <p18cxxx.h>
#include <p18f4550.h>
//#include    <p18f4550.inc>
//#include "draw.h"
#include "timers.h"

#define RCK LATDbits.LATD5
#define aRCK 5
#define _G LATDbits.LATD4
#define SCK LATDbits.LATD6
#define aSCK 6
#define _SCL LATDbits.LATD7

#define SI1 LATBbits.LATB0
#define SI2 LATBbits.LATB1
#define SI3 LATBbits.LATB2
#define SI4 LATBbits.LATB3
#define SI5 LATBbits.LATB4

//Used in assembly assignations
#define aSI1 0
#define aSI2 1
#define aSI3 2
#define aSI4 3
#define aSI5 4

#define	TIME_MAX	255
#define	TIME_MID	24
#define	TIME_LOW	10

#define MAX_NUM_PIXELS	25
#define MAX_NUM_COLUMNS	5
#define MAX_NUM_GREYSCALE	255

#define BRIGHTNESS_MIN 1
#define BRIGHTNESS_MID 127
#define BRIGHTNESS_MAX 254

//assembly definitions
#define	W	0
#define	F	1
#define ACCESS	0
#define BANKED	1
#define	WREG	0xFE8
#define INDF0	0xFEF
#define FSR0	0xFE9
#define FSR0H	0xFEA
#define	POSTINC0	0xFEE
#define	FSR1	0xFE1
#define	FSR1H	0xFE2
#define	INDF1	0xFE7
#define FSR2	0xFD9
#define FSR2H	0xFDA

//data memory addresses for ISR variables
#define ADDRESS_G_BUFFER_GREYSCALE_0	0x00
#define ADDRESS_M_BUFFER_MATRIX_0	0x19
#define ADDRESS_M_BUFFER_MATRIX_1	0x1A
#define ADDRESS_M_BUFFER_MATRIX_2	0x1B
#define ADDRESS_M_BUFFER_MATRIX_3	0x1C
#define ADDRESS_M_BUFFER_MATRIX_4	0x1D
#define ADDRESS_I_GREYSCALE	0x1E
#define	ADDRESS_I_BUFFER_MATRIX	0x1F
#define ADDRESS_I_ISR	0x20
#define ADDRESS_COLUMN_ISR	0x21
#define ADDRESS_ROW_ISR	0x22
#define SAVE_SFR0	0x23			
#define SAVE_SFR0H	0x24
#define SAVE_SFR1	0x25
#define SAVE_SFR1H	0x26
#define SAVE_SFR2	0x27
#define SAVE_SFR2H	0x28
	
#define REMAPPED_RESET_VECTOR_ADDRESS			0x1000
#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x1008
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x1018

/* Definición variables */
extern ram near unsigned char gBufferGreyscale[25];
extern ram near unsigned char mBufferMatrix[5];
extern ram near unsigned char iGreyscale; //indice que se encarga de determinar a que nivel de intensidad
				//estamos activando los leds frames de 256 pasos.
extern ram near unsigned char iBufferMatrix; // indice que permite recorrer gBufferGreyscale
extern near ram unsigned char iISR, columnISR, rowISR; //Guardan el valor de fila y columna decodificado de iBufferMatrix
extern near ram unsigned char sFSR0, sFSR0H, sFSR1, sFSR1H, sFSR2, sFSR2H, sBSR;
extern near ram unsigned char gPreBufferGreyscale[25];

/* Definicion de funciones */
void YourHighPriorityISRCode();
void YourLowPriorityISRCode();
extern void _startup (void);        // See c018i.c in your C18 compiler dir
void rutina_ISR(void);

#endif
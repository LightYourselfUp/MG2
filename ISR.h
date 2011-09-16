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
#include "draw.h"
#include "timers.h"

#define RCK LATDbits.LATD5
#define _G LATDbits.LATD4
#define SCK LATDbits.LATD6
#define _SCL LATDbits.LATD7

#define SI1 LATBbits.LATB0
#define SI2 LATBbits.LATB1
#define SI3 LATBbits.LATB2
#define SI4 LATBbits.LATB3
#define SI5 LATBbits.LATB4

#define	TIME_MAX	255
#define	TIME_MID	24
#define	TIME_LOW	10

#define iGreyscaleMAX 32
	
#define REMAPPED_RESET_VECTOR_ADDRESS			0x1000
#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x1008
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x1018

/* Definición variables */

/* Definicion de funciones */
void YourHighPriorityISRCode();
void YourLowPriorityISRCode();
extern void _startup (void);        // See c018i.c in your C18 compiler dir

void rutina_ISR(void);

#endif
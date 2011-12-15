/*********************************************************************
Date: 24-9-2011 
Project: #MG
Version: 0.5 DanUp
File: ISR.h
Compiler: MPLAB C18
Processor: 18F4550
Company: LightYourselUp
Contact: we@lightyourselfup.com
Comments: 
*********************************************************************/

#ifndef ISR_H
#define ISR_H


/* Files included ***************************************************/
#include <p18cxxx.h>
#include <p18f4550.h>
#include "timers.h"


/* Definitions ******************************************************/
// Shift Register control pins definitions. "a" prefix is us to define the bit number to use in assembly
#define	RCK		LATDbits.LATD5
#define	aRCK	5
#define	_G		LATDbits.LATD4
#define	SCK		LATDbits.LATD6
#define aSCK	6
#define	_SCL	LATDbits.LATD7

// Shift Register Inputs definitions. "a" prefix is us to define the bit number to use in assembly
#define SI1 LATBbits.LATB0
#define SI2 LATBbits.LATB1
#define SI3 LATBbits.LATB2
#define SI4 LATBbits.LATB3
#define SI5 LATBbits.LATB4
#define SI6 LATBbits.LATB5
#define SI7 LATBbits.LATB6
#define aSI1 0
#define aSI2 1
#define aSI3 2
#define aSI4 3
#define aSI5 4
#define aSI6 5
#define aSI7 6


// Bootloader button definitoins
#define BOOTLOADER_BUTTON	PORTAbits.RA2//PORTEbits.RE0
#define ON_BOOT_BUTTON	0

// A/D definitions
#define AD_GO 1
#define AD_DONE 0

// Maximum values and reset definitions
#define MAX_MENU	6
#define MAX_NUM_PIXELS	49
#define MAX_NUM_COLUMNS	7
#define MAX_NUM_ROWS	7
#define MAX_NUM_GREYSCALE	128
#define MAX_INDEX_G_BUFFER_GREYSCALE	48
#define MAX_INDEX_M_BUFFER_MATRIX	6
#define RESET_M_BUFFER_MATRIX	0xFF
#define CHANGE_MODE_DELAY_MULTIPLIER	6

// Assembly definitions
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


// Data memory addresses for ISR variables
#define ADDRESS_G_BUFFER_GREYSCALE_0	0x00
#define ADDRESS_M_BUFFER_MATRIX_0	0x31
#define ADDRESS_M_BUFFER_MATRIX_1	0x32
#define ADDRESS_M_BUFFER_MATRIX_2	0x33
#define ADDRESS_M_BUFFER_MATRIX_3	0x34
#define ADDRESS_M_BUFFER_MATRIX_4	0x35
#define ADDRESS_M_BUFFER_MATRIX_5	0x36
#define ADDRESS_M_BUFFER_MATRIX_6	0x37
#define ADDRESS_G_PRE_BUFFER_GREYSCALE_0	0x60

// Interrupt vector addresses for boatloader remapping 	
#define REMAPPED_RESET_VECTOR_ADDRESS			0x1000
#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x1008
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x1018


/* Extern variables *************************************************/
extern near ram unsigned char gBufferGreyscale[MAX_NUM_PIXELS];	// Used to draw the information that we want to display in the matrix.
extern near ram unsigned char mBufferMatrix[MAX_NUM_ROWS];	// Buffered used to decode gBufferGreyscale brightness and send "firmware" PWM through SIx
extern near ram unsigned char iGreyscale;	// Index used to control the brightness step for the "firmware" pwm
extern near ram unsigned char iMenu;	// Keeps the main MENU value
extern near ram unsigned char iTimer1;	// Used to generate a forced delay between each time iMenu can be increment after pressing the bootloader button
extern near ram unsigned char booleanMenu; // These variables are used as boolean to executed just once the corresponding MENU value
extern near ram unsigned char pwm;	// Controlled brightness with A/D conversion
extern ram unsigned char gPreBufferGreyscale[MAX_NUM_PIXELS];	//Used to pre draw the information that we want to display in the matrix. 

/* Functions prototypes *********************************************/
void YourHighPriorityISRCode();
void YourLowPriorityISRCode();
void rutina_ISR(void);
extern void _startup (void);        // See c018i.c in your C18 compiler dir

#endif

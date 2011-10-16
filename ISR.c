/*********************************************************************
Date: 24-9-2011 
Project: #MG
Version: 0.5 DanUp
File: ISR.c
Compiler: MPLAB C18
Processor: 18F4550
Company: LightYourselUp
Contact: we@lightyourselfup.com
Comments: 
*********************************************************************/


/* Files included ***************************************************/
#include "ISR.h"


/* Variables ********************************************************/
//Defining variables in access ram section 0x00..0x5F
#pragma udata access accessram
near ram unsigned char gBufferGreyscale[25];	// Used to draw the information that we want to display in the matrix.
near ram unsigned char mBufferMatrix[5];	// Buffered used to decode gBufferGreyscale brightness and send "firmware" PWM through SIx
near ram unsigned char iGreyscale;	// Index used to control the brightness step for the "firmware" pwm
near ram unsigned char columnISR, rowISR; // Used to decode the gGrescale vector position(0..24) into rows(1..5) and columns(1..5)
near ram unsigned char sFSR0, sFSR0H, sFSR1, sFSR1H;	// Used to save FSRs values during TIMER0 interrupt execution
near ram unsigned char gPreBufferGreyscale[25];	//Used to pre draw the information that we want to display in the matrix. 
near ram unsigned char iMenu;	// Keeps the main MENU value
near ram unsigned char iTimer1;	// Used to generate a forced delay between each time iMenu can be increment after pressing the bootloader button
near ram unsigned char FIRST, SECOND, THIRD, FOURTH, FIFTH; // These variables are used as boolean to executed just once the corresponding MENU value
near ram unsigned char pwm; // Controlled brightness with A/D conversion

 /* Remapping ISRs **************************************************/

//This part is to avoid overlapping the interrupt vectors with the bootloaders code
#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS
void _reset (void){
    _asm goto _startup _endasm
}
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
void Remapped_High_ISR (void)	{
     _asm goto YourHighPriorityISRCode _endasm
}
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS
void Remapped_Low_ISR (void){
     _asm goto YourLowPriorityISRCode _endasm
}
	
#pragma code HIGH_INTERRUPT_VECTOR = 0x08
void High_ISR (void)	{
     _asm goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS _endasm
}
#pragma code LOW_INTERRUPT_VECTOR = 0x18
void Low_ISR (void){
     _asm goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS _endasm
}

#pragma code
#pragma interrupt YourHighPriorityISRCode
/* High priority interrupt routines */
void YourHighPriorityISRCode()	{
// Each time the TMR0 flag is "1", gBufferGreyscale is compared with one level of brightness (from 0 to 256). Translated to serial value on
// mBufferMatrix and send through SIx. Every 256 TMR0 routines execution one whole pwm image is showed in the matrix display
	if(INTCONbits.TMR0IF==1){
				//This routine has been recode in assembly in order to speed up its executation
				_asm 
						// Saving previous routin value of FSR0 and FSR1 to recover them at the end of the routine						
						MOVFF	FSR0, sFSR0
						NOP		
						MOVFF	FSR0H, sFSR0H
						NOP
						MOVFF	FSR1, sFSR1
						NOP
						MOVFF	FSR1H, sFSR1H
						NOP

						// Initializing serveral registers						
						CLRF	FSR0, ACCESS // FSR0 is used as an index to scan G_BUFFER_MATRIX
						CLRF	FSR0H, ACCESS
						CLRF	FSR1, ACCESS
						CLRF	FSR1H, ACCESS
						CLRF	columnISR, ACCESS
						CLRF	rowISR, ACCESS

				// This loop scans all gBufferGreyscale value (one per pixel) compare them to the actual value of iGreyscale and if it matchs, 
				// turn off the pixel in the mBufferMatrix (which is the serial output file) 		
				SCAN_G_BUFFER_MATRIX:
						//FSR0 iterates over gBufferGreyscale
						MOVFF	POSTINC0, WREG
						NOP
						SUBWF	iGreyscale, W, ACCESS
						BNZ		UPDATE_COLUMN_ROW

						/* If iGreyscale = gBufferGreyscale[FSR0], the corresponding pixel is reset in mBufferMatrix */
						// Adding the actual rowISR value to the address of mBufferMatrix[0] selects the proper mBufferMatrix byte that
						// represents the row where the pixel to reset is saved
						MOVLW	ADDRESS_M_BUFFER_MATRIX_0
						ADDWF	rowISR, W, ACCESS
						//now we have the desired mBufferMatrix vector on WREG			
						MOVFF	WREG, FSR1
						NOP
						
						// The next instructions check out the different possible position of the pixel inside of the row,
						// whenever it matchs is reset
						MOVLW	0
						XORWF	columnISR, W, ACCESS
						BNZ		COLUMN_ISR_1		
						BCF		INDF1, 0, ACCESS
						BRA		UPDATE_COLUMN_ROW

				COLUMN_ISR_1:

						MOVLW	1
						XORWF	columnISR, W, ACCESS
						BNZ		COLUMN_ISR_2		
						BCF		INDF1, 1, ACCESS
						BRA		UPDATE_COLUMN_ROW

				COLUMN_ISR_2:

						MOVLW	2
						XORWF	columnISR, W, ACCESS
						BNZ		COLUMN_ISR_3		
						BCF		INDF1, 2, ACCESS
						BRA		UPDATE_COLUMN_ROW

				COLUMN_ISR_3:

						MOVLW	3
						XORWF	columnISR, W, ACCESS
						BNZ		COLUMN_ISR_4		
						BCF		INDF1, 3, ACCESS
						BRA		UPDATE_COLUMN_ROW

				COLUMN_ISR_4:

						BCF		INDF1, 4, ACCESS
				
				// The rowISR and columnISR values are updated
				UPDATE_COLUMN_ROW:		

						INCF	columnISR, F, ACCESS
						MOVF	columnISR, W, ACCESS
						SUBLW	MAX_NUM_COLUMNS
						
						BNZ		LOOP_SCAN_G_BUFFER_MATRIX
						CLRF	columnISR, ACCESS
						INCF	rowISR, F, ACCESS
				
				// Checking if the all the values of gBufferGreyscale have been iterated
				LOOP_SCAN_G_BUFFER_MATRIX:
				
						MOVLW	MAX_NUM_PIXELS
						SUBWF	FSR0, W, ACCESS
						BC		PWM_GENERATOR
						BRA		SCAN_G_BUFFER_MATRIX

				/* The second part of the TMR0 routine generates the PWM values through SIx, and regist them in the shift registers */
				PWM_GENERATOR:

					CLRF	LATB, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_0, 0, ACCESS
					BSF		LATB, aSI1, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_1, 0, ACCESS
					BSF		LATB, aSI2, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_2, 0, ACCESS
					BSF		LATB, aSI3, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_3, 0, ACCESS
					BSF		LATB, aSI4, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_4, 0, ACCESS
					BSF		LATB, aSI5, ACCESS
					//SCK clock 4SRs_0
					BSF		LATD, aSCK, ACCESS
					BCF		LATD, aSCK, ACCESS

					CLRF	LATB, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_0, 1, ACCESS
					BSF		LATB, aSI1, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_1, 1, ACCESS
					BSF		LATB, aSI2, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_2, 1, ACCESS
					BSF		LATB, aSI3, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_3, 1, ACCESS
					BSF		LATB, aSI4, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_4, 1, ACCESS
					BSF		LATB, aSI5, ACCESS
					//SCK clock 4SRs_1
					BSF		LATD, aSCK, ACCESS
					BCF		LATD, aSCK, ACCESS

					CLRF	LATB, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_0, 2, ACCESS
					BSF		LATB, aSI1, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_1, 2, ACCESS
					BSF		LATB, aSI2, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_2, 2, ACCESS
					BSF		LATB, aSI3, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_3, 2, ACCESS
					BSF		LATB, aSI4, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_4, 2, ACCESS
					BSF		LATB, aSI5, ACCESS
					//SCK clock 4SRs_2
					BSF		LATD, aSCK, ACCESS
					BCF		LATD, aSCK, ACCESS

					CLRF	LATB, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_0, 3, ACCESS
					BSF		LATB, aSI1, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_1, 3, ACCESS
					BSF		LATB, aSI2, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_2, 3, ACCESS
					BSF		LATB, aSI3, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_3, 3, ACCESS
					BSF		LATB, aSI4, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_4, 3, ACCESS
					BSF		LATB, aSI5, ACCESS
					//SCK clock 4SRs_3
					BSF		LATD, aSCK, ACCESS
					BCF		LATD, aSCK, ACCESS

					CLRF	LATB, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_0, 4, ACCESS
					BSF		LATB, aSI1, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_1, 4, ACCESS
					BSF		LATB, aSI2, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_2, 4, ACCESS
					BSF		LATB, aSI3, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_3, 4, ACCESS
					BSF		LATB, aSI4, ACCESS
					BTFSC	ADDRESS_M_BUFFER_MATRIX_4, 4, ACCESS
					BSF		LATB, aSI5, ACCESS
					//SCK clock 4SRs_4
					BSF		LATD, aSCK, ACCESS
					BCF		LATD, aSCK, ACCESS

					//RCK clock 4SRs				
					BSF		LATD, aRCK, ACCESS
					BCF		LATD, aRCK, ACCESS


					/* Resetting iGreyscale after iterating all the steps of the PWM */
					INCF	iGreyscale, F, ACCESS
					MOVLW	MAX_NUM_GREYSCALE
					XORWF	iGreyscale, W, ACCESS
					BNZ		END
					CLRF	iGreyscale, ACCESS
					
					CLRF	FSR0, ACCESS	//Address for gBufferGreyscale is 0x00
					MOVLW	ADDRESS_G_PRE_BUFFER_GREYSCALE_0
					MOVWF	FSR1, ACCESS
					NOP
					
					/*	After each whole PWM image is displayed, the gBufferGreyscale is updated with the gPreBufferGreyscale value 
						this isolates possible problems of overlaping values */
			LOOP_COPYING_BUFFERS:
		
					MOVLW	MAX_NUM_PIXELS
					SUBWF	FSR0, W, ACCESS
					MOVFF	POSTINC1, POSTINC0
					NOP
					BC		RESET_ALL_M_BUFFER_MATRIX
					BRA		LOOP_COPYING_BUFFERS
					
					/*	Resetting mBufferMatrix to start the next PWM iteration. The reset value is 0xFF. Because all bits start on and
						later are turn of depending on the gBufferGreyscale value */
			RESET_ALL_M_BUFFER_MATRIX:
		
				//_asm
					MOVLW	0xFF
					MOVWF	ADDRESS_M_BUFFER_MATRIX_0, ACCESS
					MOVWF	ADDRESS_M_BUFFER_MATRIX_1, ACCESS
					MOVWF	ADDRESS_M_BUFFER_MATRIX_2, ACCESS
					MOVWF	ADDRESS_M_BUFFER_MATRIX_3, ACCESS
					MOVWF	ADDRESS_M_BUFFER_MATRIX_4, ACCESS
			END:
				_endasm
	
	// Reactivating TMR0 interrupt		
	INTCONbits.TMR0IF = 0;
	TMR0L = 0x2F;
	TMR0H = 0;

				_asm
					// Recovering FSR0 and FSR1 saved values		
					MOVFF	sFSR0, FSR0
					NOP	
					MOVFF	sFSR0H, FSR0H
					NOP
					MOVFF	sFSR1, FSR1
					NOP
					MOVFF	sFSR1H, FSR1H
					NOP
				_endasm

	}// End if tmr0

// Each time the TMR1 flag is "1". The value of the Bootloader button is checked in order to know if it is requested to switch the MENU mode
// at the same time iTimer1 is used as a delay between each time iMenu can be increment, in this way we avoid having unwanted bounce detections
	if(PIR1bits.TMR1IF==1){

			// Trying to use A/D
			if (ADCON0bits.GO_DONE == AD_DONE){
				pwm = ADRESH;
				ADCON0bits.GO_DONE = AD_GO;
			}
				
		if (iTimer1 == 0){
			if(BOOTLOADER_BUTTON == ON_BOOT_BUTTON){
				iTimer1++;
				iMenu++;
			}//if
			// Resetting variables is used, to just execute once the code inside the MENU (this is just for static frames)
			if (iMenu == MAX_MENU){
				iMenu = 0;
				FIRST = 0;
				SECOND = 0;
				THIRD = 0;
				FOURTH = 0;
				FIFTH = 0;
			}		
		}
		else{
			if (iTimer1 < 6)iTimer1++;
			else iTimer1 = 0;
		}	

		// Reactivating TMR1 interrupt	
		PIR1bits.TMR1IF=0;
		WriteTimer1(0x00 & 0x00);		
	} // End if TMR1
}	//This return will be a "retfie fast", since this is in a #pragma interrupt section 

#pragma interruptlow YourLowPriorityISRCode
void YourLowPriorityISRCode()	{
}	//This return will be a "retfie", since this is in a #pragma interruptlow section 

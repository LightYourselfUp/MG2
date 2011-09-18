// Date: 22 - 08 - 2011 
// Project: #MG v0.4 Ginebra(La convención)
// File: ISR.c
// Versión: 01
// Características: rutina ISR controla las interrupciones del timer

#include "ISR.h"
#pragma udata access accessram
near ram unsigned char gBufferGreyscale[25];
near ram unsigned char mBufferMatrix[5];
near ram unsigned char iGreyscale; //indice que se encarga de determinar a que nivel de intensidad
				//estamos activando los leds frames de 256 pasos.
near ram unsigned char iBufferMatrix; // indice que permite recorrer gBufferGreyscale
near ram unsigned char iISR, columnISR, rowISR; //Guardan el valor de fila y columna decodificado de iBufferMatrix
near ram unsigned char sFSR0, sFSR0H, sFSR1, sFSR1H, sFSR2, sFSR2H, sBSR;

 //
 //******************************************************//
 //    Remapping ISRs
 //******************************************************//
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
 //
 //******************************************************//
 //    Rutina de Interrupcion
 //******************************************************//
 //

#pragma code
	
#pragma interrupt YourHighPriorityISRCode
void YourHighPriorityISRCode()	{
	if(INTCONbits.TMR0IF==1){

	// 1r part. gBufferGreyscale to mBufferMatrix
		// 1.1. Compare gBufferGreyscale with iGreyscale
			// 1.1.1. Scan all the positions of gBufferGreyscale
				_asm 
						
						MOVFF	BSR, sBSR
						NOP
						MOVFF	FSR0, sFSR0
						NOP		
						MOVFF	FSR0H, sFSR0H
						NOP
						MOVFF	FSR1, sFSR1
						NOP
						MOVFF	FSR1H, sFSR1H
						NOP
						MOVFF	FSR2, sFSR2
						NOP
						MOVFF	FSR2H, sFSR2H
						NOP
						
						CLRF	FSR0, ACCESS // FSR0 is used as an index to scan G_BUFFER_MATRIX
						CLRF	FSR0H, ACCESS
						CLRF	FSR1, ACCESS
						CLRF	FSR1H, ACCESS
						CLRF	columnISR, ACCESS
						CLRF	rowISR, ACCESS

				SCAN_G_BUFFER_MATRIX:
						//ADDRESS_I_BUFFER_MATRIX represents directly the memory address for G_BUFFER_MATRIX
						MOVFF	POSTINC0, WREG
						NOP
						SUBWF	ADDRESS_I_GREYSCALE, W, ACCESS
						BNZ		UPDATE_COLUMN_ROW

						// 1.1.X. If equal turn off the pixel , everything is on until it detects samevalue
						// ----_---__--___-____
						// Reset the corresponding value
						
						MOVLW	ADDRESS_M_BUFFER_MATRIX_0
						ADDWF	rowISR, W, ACCESS
						//now we have the deserid mBufferMatrix vector on WREG			
						MOVFF	WREG, FSR1
						NOP
						//MOVF	columnISR, W, ACCESS
						//SUBLW	
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
				
				// 1.3. Calcualting rowISR and columnISR 
				UPDATE_COLUMN_ROW:		

						INCF	ADDRESS_COLUMN_ISR, F, ACCESS
						MOVF	ADDRESS_COLUMN_ISR, W, ACCESS
						SUBLW	MAX_NUM_COLUMNS
						
						BNZ		LOOP_SCAN_G_BUFFER_MATRIX
						CLRF	ADDRESS_COLUMN_ISR, ACCESS
						INCF	ADDRESS_ROW_ISR, F, ACCESS
				
				LOOP_SCAN_G_BUFFER_MATRIX:
				
						MOVLW	MAX_NUM_PIXELS
						SUBWF	FSR0, W, ACCESS
						BC		PWM_GENERATOR
						BRA		SCAN_G_BUFFER_MATRIX

				// 2n part. Firmware PWM through SI1..5; mBufferMatrix 2 PORTB 
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
					//SCK clock 4SRs
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
					//SCK clock 4SRs
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
					//SCK clock 4SRs
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
					//SCK clock 4SRs
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
					//SCK clock 4SRs
					BSF		LATD, aSCK, ACCESS
					BCF		LATD, aSCK, ACCESS


					//RCK clock 4SRs				
					BSF		LATD, aRCK, ACCESS
					BCF		LATD, aRCK, ACCESS

		// 1.2. Control, increment and reset of iGreyscale of mBufferMatrix
					INCF	ADDRESS_I_GREYSCALE, F, ACCESS
					MOVLW	MAX_NUM_GREYSCALE
					XORWF	ADDRESS_I_GREYSCALE, W, ACCESS
					BNZ		END
					CLRF	ADDRESS_I_GREYSCALE, ACCESS
					MOVLW	0xFF
					ADDWF	ADDRESS_M_BUFFER_MATRIX_0, F, ACCESS
					ADDWF	ADDRESS_M_BUFFER_MATRIX_1, F, ACCESS
					ADDWF	ADDRESS_M_BUFFER_MATRIX_2, F, ACCESS
					ADDWF	ADDRESS_M_BUFFER_MATRIX_3, F, ACCESS
					ADDWF	ADDRESS_M_BUFFER_MATRIX_4, F, ACCESS
			END:
				_endasm
			
	INTCONbits.TMR0IF = 0;
	TMR0H = 0;
	TMR0H = 0;

	_asm
						MOVFF	sBSR, BSR
						NOP
						MOVFF	sFSR0, FSR0
						NOP	
						MOVFF	sFSR0H, FSR0H
						NOP
						MOVFF	sFSR1, FSR1
						NOP
						MOVFF	sFSR1H, FSR1H
						NOP
						MOVFF	sFSR2, FSR2
						NOP
						MOVFF	sFSR2H, FSR2H
						NOP
	_endasm
	}//if tmr0

	
}	//This return will be a "retfie fast", since this is in a #pragma interrupt section 

#pragma interruptlow YourLowPriorityISRCode
void YourLowPriorityISRCode()	{

}	//This return will be a "retfie", since this is in a #pragma interruptlow section 

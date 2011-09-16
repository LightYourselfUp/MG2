// Date: 22 - 08 - 2011 
// Project: #MG v0.4 Ginebra(La convención)
// File: ISR.c
// Versión: 01
// Características: rutina ISR controla las interrupciones del timer

#include "ISR.h"

static unsigned char mBufferMatrix[5] = {0x00,0x00,0x00,0x00,0x00};
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

	static unsigned char iGreyscale = 0; //indice que se encarga de determinar a que nivel de intensidad
				//estamos activando los leds frames de 256 pasos.
	unsigned char iBufferMatrix = 0; // indice que permite recorrer gBufferGreyscale
	unsigned char i, column = 0, row = 0; //Guardan el valor de fila y columna decodificado de iBufferMatrix
	if(INTCONbits.TMR0IF==1){
		
		iGreyscale++; //definir si al principio o la minar
		if(iGreyscale==iGreyscaleMAX){
			for(i = 0; i < 5; i++){
				mBufferMatrix[i] = 0x00; //
				iGreyscale = 0;
			}
		}
		else{
			for(iBufferMatrix = 0; iBufferMatrix < 25; iBufferMatrix++){
	
				//Detección de si debemos activar un pixel en función de su valor de gBG
				if(gBufferGreyscale[iBufferMatrix] == iGreyscale){
					mBufferMatrix[row]= mBufferMatrix[row] | ( 0x10 >> (column) );
				}
			
				//convertimos el indice en valores de filas y columnas
				column ++;
				if(column == 5){
					column = 0;
					row++;
				}
			}//for iBufferMatrix
		}		

		//sacar por serie valor mBufferMatrix

		//_G = 1;

		for(i = 0; i < 5; i++){
			//Sacando por SI los valores correspondientes por filas
			SI1 = (mBufferMatrix[0]>>i);//& 0x01;
			SI2 = (mBufferMatrix[1]>>i);//& 0x01;
			SI3 = (mBufferMatrix[2]>>i);//& 0x01;
			SI4 = (mBufferMatrix[3]>>i);//& 0x01;
			SI5 = (mBufferMatrix[4]>>i);//& 0x01;
		
			//Golpe del SCK para cargar el valor en los puertos SIx
			SCK = 1;
			SCK = 0;	
		}
		// Registrar el estado de los SRs
		RCK = 1;
		RCK = 0;
	
		//Habilitamos los SRs
		//_G = 0;
	

		//resetear mBufferMatrix al desbordar iGreyscale

		/* Reconfiguracion Timer0 */
		INTCONbits.TMR0IF = 0;
		WriteTimer0(0);

	}//if tmr0

	
}	//This return will be a "retfie fast", since this is in a #pragma interrupt section 

#pragma interruptlow YourLowPriorityISRCode
void YourLowPriorityISRCode()	{

}	//This return will be a "retfie", since this is in a #pragma interruptlow section 

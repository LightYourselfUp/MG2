/*********************************************************************
Date: 21-10-2011 
Project: #MG
Version: 0.5 DanUp
File: transitions.C
Compiler: MPLAB C18
Processor: 18F4550
Company: LightYourselUp
Contact: we@lightyourselfup.com
Comments: 
*********************************************************************/

/* Files included ***************************************************/
#include "transitions.h"

/* Variables ********************************************************/
unsigned char gBufferTransition[5] = {0x00,0x00,0x00,0x00,0x00};


/* Functions ********************************************************/
/* Transition right to left */
void transRight2Left(rom unsigned char *frame1, rom unsigned char *frame2){
	unsigned char i;
	
	//1. cargo primerframe en buffer 
	for ( i = 0; i <= 4; i++ ){
		gBuffer5x5[i] = *frame1++;
		gBufferTransition[i] = *frame2++;
		}
	draw5x5to25();
	Delay10KTCYx(30);
	//2. Desplazamos gBuffer5x5 1 posición a la izquierda
	for ( i = 0; i <= 4; i++ ){
		gBuffer5x5[i] = ( gBuffer5x5[i]<<1 ) ;
		}
	draw5x5to25();
	Delay10KTCYx(30);
	//3. Desplazamos gBuffer i sumamos la primera del siguente carácter
	for ( i = 0; i <= 4; i++ ){
		gBuffer5x5[i] = ( gBuffer5x5[i] << 1 )| ( gBufferTransition[i]>>4 );
		}
	draw5x5to25();
	Delay10KTCYx(30);
	//4. Desplazamos gBuffer i sumamos la primera del siguente carácter
	for ( i = 0; i <= 4; i++ ){
		gBuffer5x5[i] = ( gBuffer5x5[i] << 1 )| ( gBufferTransition[i]>>3 );
		}
	draw5x5to25();
	Delay10KTCYx(30);
	//5. Desplazamos gBuffer i sumamos la primera del siguente carácter
	for ( i = 0; i <= 4; i++ ){
		gBuffer5x5[i] = ( gBuffer5x5[i] << 1 )| ( gBufferTransition[i]>>2 );
		}
	draw5x5to25();
	Delay10KTCYx(30);
	//6. Desplazamos gBuffer i sumamos la primera del siguente carácter
	for ( i = 0; i <= 4; i++ ){
		gBuffer5x5[i] = ( gBufferTransition[i]>>1 );
		}
	draw5x5to25();
	Delay10KTCYx(30);
	//7. Desplazamos gBuffer i sumamos la primera del siguente carácter
	/*El último paso de la transición(comentado), lo que hace que cuando se
	 encadenan transiciones el ultímo desplazamiento de una transición y el
	 primero de la siguente(mismo caracter) solapen sus tiempos y transimitan
	 el efecto de que la letra se para.*/

	//for ( i = 0; i <= 4; i++ ){
	//	gBuffer5x5[i] = gBufferTransition[i];
	//	}
	//draw5x5to25();
	//Delay10KTCYx(TIME_MID);
}

/* Transition Down to Top */
void transButton2Top(rom unsigned char *frame1, rom unsigned char *frame2){
	unsigned char i, j;
	//1. cargo primer frame en buffer 
	for ( i = 0; i <= 4; i++ ){
		gBuffer5x5[i] = *frame1++;
		}
	draw5x5to25();
	//Delay10KTCYx(TIME_MID);

	//2. Desplazamos gBuffer5x5 1 posición a hacia el cielo!
	for ( i = 0; i <= 3; i++ ){
		gBuffer5x5[i] = gBuffer5x5[i+1];
		}
	gBuffer5x5[4] = 0x0;
	draw5x5to25();
	//Delay10KTCYx(TIME_MID);

	//3-4-5-6-7. Desplazamos gBuffer5x5 1 posición a hacia el cielo y añadimos a 5x5[0] la parte top de frame2!
	/*El cuatro comentado (convertido a 3) elimina el último paso de la transición,
	 lo que hace que cuando se encadenan transiciones el ultímo desplazamiento de
	 una transición y el primero de la siguente solapen sus tiempos y transimitan
	 el efecto de que la letra se para.*/
	for ( j = 0; j <= 3/*4*/; j++ ){
		for ( i = 0; i <= 3; i++ ){
			gBuffer5x5[i] = gBuffer5x5[i+1];
			}
		gBuffer5x5[4] = *frame2++;
		draw5x5to25();
	//	Delay10KTCYx(TIME_MID);
	}
}
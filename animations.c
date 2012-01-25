/*********************************************************************
Date: 24-10-2011 
Project: #MG
Version: 0.5 DanUp
File: animations.c
Compiler: MPLAB C18
Processor: 18F4550
Company: LightYourselUp
Contact: we@lightyourselfup.com
Comments: 
*********************************************************************/

/* Files included ***************************************************/
#include "animations.h"

/* Functions ********************************************************/
/* Convert ASCII characters to MGs */
unsigned char ascii2MG(unsigned char convert){
	switch(convert){
		case SPACEBAR_ASCII:
			// detecta SPACEBAR
			return SPACEBAR_MG;
			break;
		case SLASH_ASCII:
			// detecta / hacer un fin guapo
			return BREAK_MG;
			break;
		default:	
			//suponemos que son letras mayúsculas;
			return convert - CONVERTION_ASCII_2_MG;
			
	}//end switch
}

/* Function to choose between different transitions */
void selectTransition(unsigned char char1, unsigned char char2, unsigned char trans){
	switch(trans){
		case TRANS_RIGHT_2_LEFT:
			// detecta SPACEBAR
			transRight2Left((rom unsigned char *)&letters[char1][0],(rom unsigned char *)&letters[char2][0]);

			break;
		case TRANS_BUTTON_2_TOP:
			transButton2Top((rom unsigned char *)&letters[char1][0],(rom unsigned char *)&letters[char2][0]);
			break;

		/*Here might be added new transitions*/
		
		default:	
			transRight2Left((rom unsigned char *)&letters[char1][0],(rom unsigned char *)&letters[char2][0]);
			break;
			
	}//end switch
}

/* Scrolls text using different transitions */
void scrollText(rom unsigned char *text, unsigned char trans){
	unsigned char char1, char2;
	
	//Guardo dos primeros caracters en código ASCII
	char1 = *text++;
	char2 = *text++;
	
	//ASCII to MG letters chars
	char1 = ascii2MG(char1);
	char2 = ascii2MG(char2);
	//transicion que toque pasando los chars "traducidos"
	selectTransition(char1, char2, trans);

	/*siguente transicion*/	
	while(1){
		char1 = char2;
		char2 = *text++;
		//ASCII to MG letters chars
		if( (char2 = ascii2MG(char2)) == BREAK_MG){return;}
		selectTransition(char1, char2, trans);
	}//end while
}

/* knightRider Lights! */
void knightRider(unsigned char loop){
	unsigned char i, j;
	rom unsigned char * michael;
	michael = &knightRiderKITT[0][0];

	for(i = 0 ; i <= KNIGHT_RIDER_FRAMES; i++){
		if (loop >=1 && i == KNIGHT_RIDER_LOOP_END){
			loop--;
			i = KNIGHT_RIDER_LOOP_START;
		}
		for(j = 0; j<=4 ; j++){
			gPreBufferGreyscale[j] = knightRiderKITT[i][j];
			gPreBufferGreyscale[j+5] = knightRiderKITT[i][j];
			gPreBufferGreyscale[j+10] = knightRiderKITT[i][j];
			gPreBufferGreyscale[j+15] = knightRiderKITT[i][j];
			gPreBufferGreyscale[j+20] = knightRiderKITT[i][j];
			
			//gBufferGreyscale[j] = *michael++;
		}
			Delay10KTCYx(KNIGHT_RIDER_DELAY);
	}
}
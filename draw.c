/*********************************************************************
Date: 24-9-2011 
Project: #MG
Version: 0.5 DanUp
File: draw.c
Compiler: MPLAB C18
Processor: 18F4550
Company: LightYourselUp
Contact: we@lightyourselfup.com
Comments: 
*********************************************************************/


/* Files included ***************************************************/
#include "draw.h"

/* Variables ********************************************************/
volatile unsigned char gBuffer5x5[5] = {0x00,0x00,0x00,0x00,0x00};


/* Functions prototypes *********************************************/
// Converts a lineal brightness value to a gamma corrected value for the LEDs in the matrix
unsigned char gammaCorrection(unsigned char brightness);
// Converts frames[5] to gBufferGreyscale[25]
void draw5x5to25(void);

// Returns the absolute value of a number
signed char abs(signed char number);


/* Functions ********************************************************/
/* Delete Matrix function */
void deleteMatrix(){
unsigned char j;
	for(j = 0; j < MAX_NUM_PIXELS; j++){
		gPreBufferGreyscale[j]=0x00;
	}
}

/* Draw point */
void drawPoint(unsigned char x, unsigned char y, unsigned char brightness){

	gPreBufferGreyscale[(x - 1) * MAX_NUM_ROWS + y - 1] = gammaCorrection(brightness);
}

/* Draw line based on Bressenham Algorithm */
void drawLine(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,
				unsigned char brightness){
unsigned short int altura=0,base=0,n=0,m=0,xRef=0,yRef=0,x=0,y=0,p=0;
signed char d=0, steep, t, deltax, deltay, error, ystep;

//Calcule of base, height and line's reference point
if (x1 < x2){altura = x2 - x1;
               xRef = x1;}
else{altura = x1-x2;
     xRef = x2;}
if (y1 < y2){base = y2 - y1;
               yRef = y1;}
else{base = y1-y2;
     yRef = y2;}

//Draw horizontal lines
if (altura == 0){for(n=0; n <= base; n++){drawPoint( xRef, yRef + n,brightness);}}

//Draw vertical lines
else if(base == 0){for(n=0; n <= altura; n++){drawPoint( xRef + n, yRef, brightness);}}
else{

	// Bressenham algorithim
	steep = abs(y2 - y1) > abs(x2 - x1);
	if ( steep ){ // swap x and y
    	t = x1; x1 = y1; y1 = t;
    	t = x2; x2 = y2; y2 = t;
    }
	if (x1 > x2){ // swap ends
    	t = x1; x1 = x2; x2 = t;
    	t = y1; y1 = y2; y2 = t;
    }
	deltax = x2 - x1;
	deltay = abs(y2 - y1);
	error = 0;
	y = y1;
	if (y1 < y2) ystep = 1;
	else ystep = -1;
	for (x = x1; x <= x2; x++){
    	if (steep)
       	drawPoint( y, x, brightness);
    	else
       	drawPoint( x, y,brightness);
    	error += deltay;
    	if ( (error<<1) >= deltax){
      		y += ystep;
      		error -= deltax;
      }	// End if
	}	// End for
}//else
}

/* Draw square */
void drawSquare (unsigned char xBottom, unsigned char yBottom, unsigned char xTop, unsigned char yTop, unsigned char brightness){
	unsigned char base, altura;
	base = yTop - yBottom;
	altura = xTop - xBottom;
	drawLine( xBottom, yBottom, xBottom, yBottom + base, brightness);
	drawLine( xBottom, yBottom, xBottom + altura, yBottom, brightness);
	drawLine( xTop, yTop, xTop, yTop - base, brightness);
	drawLine( xTop, yTop, xTop - altura, yTop, brightness);
}

/* This vector contains the data table to convert lineal brightness value to LEDs non linear values */
const rom unsigned char gammaCorrectionVector[]={
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,
3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,7,7,7,7,7,7,8,8,8,8,8,8,9,
9,9,9,9,10,10,10,10,11,11,11,11,12,12,12,12,13,13,13,14,14,14,14,15,15,16,16,16,17,17,17,18,18,19,19,
19,20,20,21,21,22,22,23,23,24,24,25,25,26,26,27,28,28,29,29,30,31,32,32,33,34,34,35,36,37,38,38,39,40,
41,42,43,44,45,46,47,48,49,50,51,52,53,54,56,57,58,59,61,62,64,65,66,68,69,71,72,74,76,77,79,81,82,84,
86,88,90,92,94,96,98,100,103,105,107,109,112,114,117,119,122,125,128,130,133,136,139,142,145,148,152,
155,158,162,165,169,173,177,181,184,189,193,197,201,206,210,215,219,224,229,234,239,245,250,253,254};

/* Gamma correction */
unsigned char gammaCorrection(unsigned char brightness){
return gammaCorrectionVector[brightness];
}

/* Absolute value */
signed char abs(signed char number){
if(number >= 0)
	return number;
else
 	return 0-number;
}

/* This function allows to convert 5x5 frames[5] to gBufferGreyscale[25]; if a pixel is '1' his greyscale value is PWM (AN0) */
void draw5x5to25(){
	unsigned char i, j, k = 0;
	for(i = INITIAL_ROW; i <= FINAL_ROW; i++){
		for(j = INITIAL_COLUMN; j <= FINAL_COLUMN; j++){
			if( ( ( gBuffer5x5[i] >> j ) & 1 ) == 1 ){
				gPreBufferGreyscale[k++] = pwm;
				}
			else{
				gPreBufferGreyscale[k++] = 0;
				}
		}//for j
	}//for i
}

/* Draw a frame from content */
void drawFrame(rom unsigned char *frame){
	unsigned char i;
	for ( i = INITIAL_ROW; i <= FINAL_ROW; i++ ){
		gBuffer5x5[i] = *frame++;
		}
	draw5x5to25();
}
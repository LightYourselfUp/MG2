/*********************************************************************
Date: 20-10-2011 
Project: #MG
Version: 0.5 DanUp
File: draw.h
Compiler: MPLAB C18
Processor: 18F4550
Company: LightYourselUp
Contact: we@lightyourselfup.com
Comments: 
*********************************************************************/

#ifndef DRAW_H
#define DRAW_H

/* Files included ***************************************************/
#include <p18f4550.h>
#include "ISR.h"
#include "content.h"

/* Definitions ******************************************************/
#define INITIAL_COLUMN 0
#define FINAL_COLUMN 7-1
#define INITIAL_ROW 0
#define FINAL_ROW 7-1


extern volatile unsigned char gBuffer7x7[7];

/* Functions prototypes *********************************************/

// Delete all the data content in the actual image displayed
//7x7 OK
void deleteMatrix(void);

//Draw a point with coordinates (x,y), also the brigtness is controllable
//7x7 OK
void drawPoint( unsigned char x, unsigned char y, unsigned char brightness);

//Draw a line with coordinates (x1,x1 & y2,y2), also the brigtness is controllable
//7x7 OK
void drawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char brightness);

//Draw a square with coordinates (xBottom, yBottom & xTop, yTop), also the brigtness is controllable
//7x7 OK
void drawSquare(unsigned char xBottom, unsigned char yBotton, unsigned char xTop, unsigned char yTop, unsigned char brightness);

//Draw a frame from content
void drawFrame(rom unsigned char *frame);

//Converts frames from 7bytes to 49 bytes
void draw7x7to49(void);

//Only to avoid collateral errors, will be delte when whole code is ported to 7x7
void draw5x5to25(void);
#endif //DRAW_H
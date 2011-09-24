/*********************************************************************
Date: 24-9-2011 
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

/* Functions prototypes *********************************************/

// Delete all the data content in the actual image displayed
void deleteMatrix(void);

//Draw a point with coordinates (x,y), also the brigtness is controllable
void drawPoint(const unsigned char x, const unsigned char y, const unsigned char brightness);

//Draw a line with coordinates (x1,x1 & y2,y2), also the brigtness is controllable
void drawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char brightness);

//Draw a square with coordinates (xBottom, yBottom & xTop, yTop), also the brigtness is controllable
void drawSquare(unsigned char xBottom,const unsigned char yBotton,const unsigned char xTop,const unsigned char yTop, const unsigned char brightness);

#endif //DRAW_H
/*********************************************************************
Date: 24-10-2011 
Project: #MG
Version: 0.5 DanUp
File: animations.h
Compiler: MPLAB C18
Processor: 18F4550
Company: LightYourselUp
Contact: we@lightyourselfup.com
Comments: 
*********************************************************************/
#ifndef ANIMATIONS_H
#define ANIMATIONS_H

/* Files included ***************************************************/
#include "draw.h"
#include "ISR.h"
#include "delays.h"
#include "transitions.h"

/* Definitions ******************************************************/
#define SPACEBAR_ASCII 32
//Slash bar is detected to finish the scrolling routine, therfore, all strings, must end with "/"
#define SLASH_ASCII 47
#define SPACEBAR_MG 0
#define BREAK_MG 128
#define CONVERTION_ASCII_2_MG 65+1

//Transitions names definitions
#define	TRANS_RIGHT_2_LEFT 0
#define	TRANS_BOTTOM_2_TOP 1

/* Functions prototypes *********************************************/
void scrollText(rom unsigned char *text, unsigned char transition);
void knightRider(unsigned char loop);
#endif
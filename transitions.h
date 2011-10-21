/*********************************************************************
Date: 21-10-2011 
Project: #MG
Version: 0.5 DanUp
File: transitions.h
Compiler: MPLAB C18
Processor: 18F4550
Company: LightYourselUp
Contact: we@lightyourselfup.com
Comments: 
*********************************************************************/

#ifndef TRANSITIONS_H
#define TRANSITIONS_H

/* Files included ***************************************************/
#include "draw.h"
#include "ISR.h"
#include "delays.h"

/* Extern variables *************************************************/
extern unsigned char gBufferTransition[5];

/* Functions prototypes *********************************************/
void transRight2Left(rom unsigned char *frame1, rom unsigned char *frame2);
void transButton2Top(rom unsigned char *frame1, rom unsigned char *frame2);

#endif
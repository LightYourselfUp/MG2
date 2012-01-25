/*********************************************************************
Date: 20-10-2011 
Project: #MG
Version: 0.5 DanUp
File: content.h
Compiler: MPLAB C18
Processor: 18F4550
Company: LightYourselUp
Contact: we@lightyourselfup.com
Comments: 
*********************************************************************/

#ifndef CONTENT_H
#define CONTENT_H

/* Definitions ******************************************************/
/* Invaders */
#define	DELAY_INVADERS	110
#define INVADERS_PAIR_REPETITIONS 3

/* Knight rider */
#define	KNIGHT_RIDER_MAX 0xFF
#define	KNIGHT_RIDER_4 164
#define	KNIGHT_RIDER_3 108
#define	KNIGHT_RIDER_2 56
#define	KNIGHT_RIDER_1 24
#define	KNIGHT_RIDER_OFF 0
#define KNIGHT_RIDER_FRAMES	20 //21 sin contar el 0
#define KNIGHT_RIDER_LOOP_START 5
#define KNIGHT_RIDER_LOOP_END 15
#define KNIGHT_RIDER_DELAY	30

/* Extern variables *************************************************/
extern rom const unsigned char letters[][5];
extern rom const unsigned char numbers[][5];
extern rom const unsigned char invaders[][5];
extern rom const unsigned char welcome[];
extern rom const unsigned char BandC[];
extern rom const unsigned char MarcManel[];
extern rom const unsigned char Llevadme[];
extern rom const unsigned char Laborda[];
extern rom const unsigned char Hazlo[];
extern rom const unsigned char Force[];
extern rom const unsigned char Nino[];
extern rom const unsigned char knightRiderKITT[][5];

#endif
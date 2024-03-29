/*********************************************************************
Date: 20-10-2011 
Project: #MG
Version: 0.5 DanUp
File: content.c
Compiler: MPLAB C18
Processor: 18F4550
Company: LightYourselUp
Contact: we@lightyourselfup.com
Comments: 
*********************************************************************/

#include "content.h"

rom const unsigned char letters[][5] ={ 
{0x0, 0x0, 0x0, 0x0, 0x0}, //SPACE BAR
{0x1F, 0x11, 0x1F, 0x11, 0x11}, //A
{0x1E, 0x11, 0x1E, 0x11, 0x1E}, //B
{0x1F, 0x10, 0x10, 0x10, 0x1F}, //C
{0x1E, 0x11, 0x11, 0x11, 0x1E}, //D
{0x1F, 0x10, 0x1E, 0x10, 0x1F}, //E
{0x1F, 0x10, 0x1E, 0x10, 0x10}, //F
{0x1F, 0x10, 0x17, 0x11, 0x1F}, //G
{0x11, 0x11, 0x1F, 0x11, 0x11}, //H
{0x1F, 0x04, 0x04, 0x04, 0x1F}, //I
{0x1F, 0x04, 0x04, 0x14, 0x1C}, //J
{0x11, 0x12, 0x1C, 0x12, 0x11}, //K
{0x10, 0x10, 0x10, 0x10, 0x1F}, //L
{0x11, 0x1B, 0x15, 0x11, 0x11}, //M
{0x11, 0x19, 0x15, 0x13, 0x11}, //N
{0x1F, 0x11, 0x11, 0x11, 0x1F}, //0
{0x1F, 0x11, 0x1F, 0x10, 0x10}, //P
{0x1F, 0x11, 0x11, 0x13, 0x1F}, //Q
{0x1F, 0x11, 0x1F, 0x12, 0x11}, //R
{0x1F, 0x10, 0x1F, 0x01, 0x1F}, //S
{0x1F, 0x04, 0x04, 0x04, 0x04}, //T
{0x11, 0x11, 0x11, 0x11, 0x1F}, //U
{0x11, 0x11, 0x0A, 0x0A, 0x04}, //V
{0x11, 0x11, 0x11, 0x15, 0x1B}, //W
{0x11, 0x0A, 0x04, 0x0A, 0x11}, //X
{0x11, 0x0A, 0x04, 0x04, 0x04}, //Y
{0x1F, 0x02, 0x04, 0x08, 0x1F}, //Z
};

rom const unsigned char numbers[][5] ={ 
{0x0E, 0x11, 0x11, 0x11, 0x0E}, //0
{0x0C, 0x04, 0x04, 0x04, 0x04}, //1
{0x0E, 0x11, 0x06, 0x08, 0x1F}, //2
{0x1F, 0x01, 0x0F, 0x01, 0x1F}, //3
{0x11, 0x11, 0x1F, 0x01, 0x01}, //4
{0x0F, 0x10, 0x1F, 0x01, 0x1F}, //5
{0x1F, 0x10, 0x1F, 0x11, 0x1F}, //6
{0x1F, 0x01, 0x02, 0x04, 0x04}, //7
{0x1F, 0x11, 0x1F, 0x11, 0x1F}, //8
{0x1F, 0x11, 0x1F, 0x01, 0x1F}, //9
};

rom const unsigned char invaders[][5] = {

//  ***
// * * *
// *****
//  ***
// * * *
{0x0E, 0x15, 0x1F, 0x0E, 0x15},
//  ***
// * * *
// *****
//  ***
//  * *
{0x0E, 0x15, 0x1F, 0x0E, 0x0A},

//   *
//  ***
// * * *
// *****
//  * *
{0x04, 0x0E, 0x15, 0x1F, 0x0A},
//   *
//  ***
// * * *
// *****
// * * *
{0x04, 0x0E, 0x15, 0x1F, 0x15},

// *  *
//  *  *
//  ****
// * * *
//  ***
{0x12, 0x09, 0x0F, 0x15, 0x0E},
//  *  *
// *  *
// ****
// * * *
//  ***
{0x09, 0x12, 0x1E, 0x15, 0x0E},
};

rom const unsigned char welcome[] = " LYU MOLA /";
rom const unsigned char BandC[] = " BARCOS Y PERMUTAS /";
rom const unsigned char MarcManel[] = " NATA I ALBERT VOUS ME MANQUEZ /";
rom const unsigned char Llevadme[] = " LLEVADME A CASA /";
rom const unsigned char Laborda[] = " LABORDA TIO BUENO HAZME TUYA /";
rom const unsigned char Hazlo[] = " HAZLO O NO LO HAGAS PERO NO LO INTENTES /";
rom const unsigned char Force[] = " MAY THE FORCE BE WITH YOU SON /";
rom const unsigned char Nino[] = " NINO VIVE /";

/* KNIGHT RIDER KITT */

rom const unsigned char knightRiderKITT[][5] = {
{KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF},//0
{KNIGHT_RIDER_MAX, KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF},//1
{KNIGHT_RIDER_4, KNIGHT_RIDER_MAX, KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF},//2
{KNIGHT_RIDER_3, KNIGHT_RIDER_4, KNIGHT_RIDER_MAX, KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF},//3
{KNIGHT_RIDER_2, KNIGHT_RIDER_3, KNIGHT_RIDER_4, KNIGHT_RIDER_MAX, KNIGHT_RIDER_OFF},//4
{KNIGHT_RIDER_1, KNIGHT_RIDER_2, KNIGHT_RIDER_3, KNIGHT_RIDER_4, KNIGHT_RIDER_MAX},//5

{KNIGHT_RIDER_OFF, KNIGHT_RIDER_1, KNIGHT_RIDER_2, KNIGHT_RIDER_3, KNIGHT_RIDER_MAX},//6
{KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF, KNIGHT_RIDER_1, KNIGHT_RIDER_MAX, KNIGHT_RIDER_4},//7
{KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF, KNIGHT_RIDER_MAX, KNIGHT_RIDER_4, KNIGHT_RIDER_3},//8
{KNIGHT_RIDER_OFF, KNIGHT_RIDER_MAX, KNIGHT_RIDER_4, KNIGHT_RIDER_3, KNIGHT_RIDER_2},//9
{KNIGHT_RIDER_MAX, KNIGHT_RIDER_4, KNIGHT_RIDER_3, KNIGHT_RIDER_2, KNIGHT_RIDER_1},//10

{KNIGHT_RIDER_MAX, KNIGHT_RIDER_3, KNIGHT_RIDER_2, KNIGHT_RIDER_1, KNIGHT_RIDER_OFF},//11
{KNIGHT_RIDER_4, KNIGHT_RIDER_MAX, KNIGHT_RIDER_1, KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF},//12
{KNIGHT_RIDER_3, KNIGHT_RIDER_4, KNIGHT_RIDER_MAX, KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF},//13
{KNIGHT_RIDER_2, KNIGHT_RIDER_3, KNIGHT_RIDER_4, KNIGHT_RIDER_MAX, KNIGHT_RIDER_OFF},//14
{KNIGHT_RIDER_1, KNIGHT_RIDER_2, KNIGHT_RIDER_3, KNIGHT_RIDER_4, KNIGHT_RIDER_MAX},//15

{KNIGHT_RIDER_OFF, KNIGHT_RIDER_1, KNIGHT_RIDER_2, KNIGHT_RIDER_3, KNIGHT_RIDER_MAX},//16
{KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF, KNIGHT_RIDER_1, KNIGHT_RIDER_2, KNIGHT_RIDER_MAX},//17
{KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF, KNIGHT_RIDER_1, KNIGHT_RIDER_MAX},//18
{KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF, KNIGHT_RIDER_MAX},//19
{KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF, KNIGHT_RIDER_OFF},//20
};
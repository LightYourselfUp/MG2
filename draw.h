// Date: 20-09-2011 
// Project: #MG v0.5
// File: draw.h
// Versión: 01
// Características: Adapting file to version 0.5

#ifndef DRAW_H //Esto evita reincluir multiples veces el mismo archivo
#define DRAW_H

/* Inclusión de archivos */
#include <p18f4550.h>
#include "ISR.h"

/* Definicion de funciones */
void deleteMatrix(void);
void drawPoint(const unsigned char fila, const unsigned char columna, const unsigned int pwm);
void drawLine(unsigned char F_1,unsigned char C_1,unsigned char F_2,unsigned char C_2, unsigned int pwm);
void drawSquare(unsigned char F_inf,const unsigned char C_inf,const unsigned char F_sup,const unsigned char C_sup, const unsigned int pwm);
#endif
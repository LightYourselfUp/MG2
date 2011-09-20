// Date: 20 - 09 - 2011 
// Project: #MG v0.5
// File: draw.c
// Version: 03
// Comments: Adapting file to version 0.5

#include "draw.h"

/* Definición variables */


/* Definicion de funciones */
const unsigned char gammaCorrection(const unsigned char pwm);

/* Borrar matriz */
void deleteMatrix(){
unsigned char j;
	for(j=0;j<25;j++){
		gBufferGreyscale[j]=0x00;
	}
}

/* Funcion para obtener el valor absoluto */
signed char abs(signed char numero){
if(numero >= 0)
	return numero;
else
 	return 0-numero;
}


/* Pintar punto */
void drawPoint(const unsigned char fila, const unsigned char columna, const unsigned char pwm){

	gPreBufferGreyscale[(fila-1) * 5 + columna - 1] = gammaCorrection(pwm);
}

/* Pintar linia Algoritmo homie Bressenhal */
void drawLine(unsigned char F_1,unsigned char C_1,unsigned char F_2,unsigned char C_2,
				unsigned char pwm){
unsigned short int altura=0,base=0,n=0,m=0,F_Ref=0,C_Ref=0,x=0,y=0,p=0;
signed char d=0, x1=0, steep, t, deltax, deltay, error, ystep;

//Calculem base i altura i el punt de referencia de la recta
if (F_1 < F_2){altura = F_2-F_1;
               F_Ref = F_1;}
else{altura = F_1-F_2;
     F_Ref = F_2;}
if (C_1 < C_2){base = C_2-C_1;
               C_Ref = C_1;}
else{base = C_1-C_2;
     C_Ref = C_2;}

//Pintar linia horitzontal
if (altura == 0){for(n=0;n<=base;n++){drawPoint(F_Ref,C_Ref+n,pwm);}}
//Pintar linia vertical
else if(base == 0){for(n=0;n<=altura;n++){drawPoint(F_Ref+n,C_Ref,pwm);}}
else{
//Algoritmo de Bresenhal
steep = abs(C_2 - C_1) > abs(F_2 - F_1);
if ( steep ){ // swap x and y
    t = F_1; F_1 = C_1; C_1 = t;
    t = F_2; F_2 = C_2; C_2 = t;
    }
if (F_1 > F_2){ // swap ends
    t = F_1; F_1 = F_2; F_2 = t;
    t = C_1; C_1 = C_2; C_2 = t;
    }
deltax = F_2 - F_1;
deltay = abs(C_2 - C_1);
error = 0;
y = C_1;
if (C_1 < C_2) ystep = 1;
else ystep = -1;
for (x = F_1; x <= F_2; x++){
    if ( steep)
       drawPoint(y,x,pwm);
    else
       drawPoint(x,y,pwm);
    error += deltay;
    if ( (error<<1) >= deltax){
      y += ystep;
      error -= deltax;
      } // if
} // for

}//else
}

/* Pintar cuadrado */
void drawSquare (unsigned char F_inf,const unsigned char C_inf,const unsigned char F_sup,const unsigned char C_sup, const unsigned char pwm){
	unsigned char base, altura;
	base = C_sup - C_inf;
	altura = F_sup - F_inf;
	drawLine(F_inf, C_inf,F_inf, C_inf+base, pwm);
	drawLine(F_inf, C_inf,F_inf+altura, C_inf, pwm);
	drawLine(F_sup, C_sup,F_sup, C_sup-base, pwm);
	drawLine(F_sup, C_sup,F_sup-altura, C_sup, pwm);
}

const rom unsigned char gammaCorrectionVector[]={
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
3,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
5,
5,
5,
5,
5,
5,
5,
5,
6,
6,
6,
6,
6,
6,
6,
7,
7,
7,
7,
7,
7,
8,
8,
8,
8,
8,
8,
9,
9,
9,
9,
9,
10,
10,
10,
10,
11,
11,
11,
11,
12,
12,
12,
12,
13,
13,
13,
14,
14,
14,
14,
15,
15,
16,
16,
16,
17,
17,
17,
18,
18,
19,
19,
19,
20,
20,
21,
21,
22,
22,
23,
23,
24,
24,
25,
25,
26,
26,
27,
28,
28,
29,
29,
30,
31,
32,
32,
33,
34,
34,
35,
36,
37,
38,
38,
39,
40,
41,
42,
43,
44,
45,
46,
47,
48,
49,
50,
51,
52,
53,
54,
56,
57,
58,
59,
61,
62,
64,
65,
66,
68,
69,
71,
72,
74,
76,
77,
79,
81,
82,
84,
86,
88,
90,
92,
94,
96,
98,
100,
103,
105,
107,
109,
112,
114,
117,
119,
122,
125,
128,
130,
133,
136,
139,
142,
145,
148,
152,
155,
158,
162,
165,
169,
173,
177,
181,
184,
189,
193,
197,
201,
206,
210,
215,
219,
224,
229,
234,
239,
245,
250,
253,
254,
/* 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,2,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,7,7,7,8,8,9,9,9,10,10,10,
11,11,12,12,13,13,14,14,15,15,16,16,17,17,18,18,19,19,20,20,21,21,22,23,23,24,25,25,26,26,27,28,28,29,
30,30,31,32,33,33,34,35,36,36,37,38,39,39,40,41,42,43,43,44,45,46,47,48,49,49,50,51,52,53,54,55,56,57,58,
59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,81,82,83,84,85,86,87,89,90,91,92,93,
95,96,97,98,100,101,102,103,105,106,107,108,110,111,112,114,115,116,118,119,121,122,123,125,126,127,
129,130,132,133,135,136,138,139,141,142,144,145,147,148,150,151,153,154,156,157,159,160,162,164,165,
167,169,170,172,173,175,177,178,180,182,183,185,187,189,190,192,194,196,197,199,201,203,204,206,208,
210,212,213,215,217,219,221,223,225,226,228,230,232,234,236,238,240,242,244,246,248,250,252,254,255*/};

const unsigned char gammaCorrection(const unsigned char pwm){
return gammaCorrectionVector[pwm];
}

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
void drawPoint(const unsigned char fila, const unsigned char columna, const unsigned int pwm){

	gPreBufferGreyscale[(fila-1) * 5 + columna - 1] = gammaCorrection(pwm);
}

/* Pintar linia Algoritmo homie Bressenhal */
void drawLine(unsigned char F_1,unsigned char C_1,unsigned char F_2,unsigned char C_2,
				unsigned int pwm){
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
void drawSquare (unsigned char F_inf,const unsigned char C_inf,const unsigned char F_sup,const unsigned char C_sup, const unsigned int pwm){
	unsigned char base, altura;
	base = C_sup - C_inf;
	altura = F_sup - F_inf;
	drawLine(F_inf, C_inf,F_inf, C_inf+base, pwm);
	drawLine(F_inf, C_inf,F_inf+altura, C_inf, pwm);
	drawLine(F_sup, C_sup,F_sup, C_sup-base, pwm);
	drawLine(F_sup, C_sup,F_sup-altura, C_sup, pwm);
}

const rom unsigned int gammaCorrectionVector[]={
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
4,
5,
5,
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
6,
7,
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
9,
10,
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
18,
19,
19,
20,
20,
20,
21,
21,
22,
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
27,
28,
28,
29,
29,
30,
30,
31,
32,
32,
33,
33,
34,
35,
35,
36,
37,
38,
38,
39,
40,
41,
41,
42,
43,
44,
45,
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
55,
56,
57,
58,
59,
60,
62,
63,
64,
65,
67,
68,
69,
70,
72,
73,
75,
76,
77,
79,
80,
82,
84,
85,
87,
88,
90,
92,
94,
95,
97,
99,
101,
103,
105,
107,
109,
111,
113,
115,
118,
120,
122,
124,
127,
129,
132,
134,
137,
139,
142,
145,
147,
150,
153,
156,
159,
162,
165,
168,
172,
175,
178,
182,
185,
189,
192,
196,
200,
203,
207,
211,
215,
219,
224,
228,
232,
237,
241,
246,
250,
255,
260,
265,
270,
275,
280,
286,
291,
297,
300,
};

const unsigned char gammaCorrection(const unsigned char pwm){
return gammaCorrectionVector[pwm];
}

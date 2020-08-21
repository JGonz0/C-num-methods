#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    José Gonzalo Palomares Gutiérrez
    Centro de Investigación en Matemáticas (CIMAT)
    Maestría en Ciencias de la computación y matemáticas industriales

*/

// Asumiendo una resolución de 640 x 480

#define ndata 101 // Número de pares xi yi
#define Px 640
#define Py 480
#define xshift 10
#define yshift 10

float function(float x){
    return pow(x,2) + 10;
}


float *y_tabular(float x[]){
    static float y[ndata];

    for(int i = 0; i < ndata; i++){
        y[i] = function(x[i]);
    }

    return y; 
}


float y_max(float *y){
    float result = -9999;

    for(int i = 0; i < ndata; i++){
        if(*(y + i) > result){
            result = *(y+i);
        }
    }

    return result;
}


float y_min(float *y){
    float result = 9999;

    for(int i = 0; i < ndata; i++){
        if(*(y + i) < result){
            result = *(y+i);
        }
    }

    return result;
}



int * pos_to_pixels(float x[]){
    static int values[ndata];

    for(int i=0; i < ndata; i++){
        values[i] = i*(Px-2*xshift)/(ndata -1) + 10;
    }

    return values;
}

int * y_pos_to_pixels(float x[]){
    static int values[ndata];

    for(int i=0; i < ndata; i++){
        values[i] = i*(Py-2*yshift)/(ndata -1) + 10;
    }

    return values;
}

int main(){
    float x[ndata], *y;
    float a_int = 1 , b_int = 2, c_int;
    float delta_x = (b_int - a_int)/(ndata - 1);

    x[0] = a_int;

    for(int i = 1; i < ndata; i++){
        x[i] = x[i-1] + delta_x;
    }

    y = y_tabular(x);

    /* printf("%.2f\n", x[100]);
    printf("%.2f\n", y[100]);
    printf("%.2f\n", y_max(y));
    printf("%.2f\n", y_min(y)); */

    // Asignando pixeles

    int *pos_x, *pos_y;

    pos_x = pos_to_pixels(x);
    pos_y = pos_to_pixels(y);

    printf("%d", pos_y[100]);
}
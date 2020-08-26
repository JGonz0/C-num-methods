#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ndata 3

// Función de prueba
double function(double x){
    return pow(x,2) + 10;
}

// Generación de  los puntos yi
void y_tabular(double *x, double *y){

    for(int i = 0; i < ndata; i++){
        y[i] = function(x[i]);
    }

    return;
}

void double2char(double *x, char *labels){

    for(int i = 0; i < ndata; i++){
        labels[i] = (char)x[i];
    }
    return;
}

double max_value(double *y){
    
    double max_value = y[0];

    // Se recorre el arreglo desde el segundo elemento y
    // se compara cada elemento con el valor máximo actual
    for(int i = 1; i < ndata; i++){
        if(y[i] > max_value){
            max_value = y[i];
        }
    }

    return max_value;
}
int main(){
    double x = 2.01;
    char result[ndata][10];

    for(int i = 0; i < ndata; i++){
        sprintf(result[i], "%0.3lf", x);
    }

    for(int i = 0; i < ndata; i++){
        printf("Numero %s \n", result[i]);
    }

    double delta_x = (2 - 1)/ 
}

double line_equation_y(double axis, double max_val, double vector){
    return vector*axis/max_val;
}

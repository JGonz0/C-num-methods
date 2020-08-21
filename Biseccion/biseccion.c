#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int iterations = 1;

float function(float x){
    return 9*pow(x,3)+sin(x)+2*exp(x);
}

float bisection(float a, float b, float epsilon){
    float fa = function(a), fb = function(b);
    float c = (a+b)/2, fc = function(c);

    if(fabsf(fc) <= epsilon){
        return c;
    }else{
        if(fa*fc < 0){
            printf("Numero de iteracion: %d\n", iterations);
            iterations++;
            return bisection(a, c, epsilon);
        }else{
            printf("Numero de iteracion: %d\n", iterations);
            iterations++;
            return bisection(c, b, epsilon);
        }
    }
}


int main(){
    float a = -0.5, b = -0.2;
    float epsilon = 0.0001;

    printf("%f", bisection(a,b,epsilon));
}
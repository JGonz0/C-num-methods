#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double function(double x){
    return x*x*x - x - 2;
}

double derive(double (*func)(double), double x0){
    double delta = 1.0e-6;
    return (func(x0 + delta) - func(x0))/delta;
}

double newton_method(double x0, float epsilon){
    int iter = 1;
    double delta = -function(x0)/derive(function,x0);
    double x1 = x0 + delta;
    
    while(epsilon <= fabs(function(x1))){
        iter++;
        delta = -function(x1)/derive(function,x1);
        x1 = x1 + delta;
    }
    
    printf("El numero de iteraciones es: %d", iter);
    printf("El valor de la raíz es: %lf \n", x1);
    printf("El valor de la funcion en la raiz es: %lf \n", function(x1));
    return x1;
}

int main(){
    double init = 1;
    float epsilon = 0.001;
    newton_method(init,epsilon);
}
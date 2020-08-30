#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Función de prueba
double function(double x){
    return x*x*x - x - 2;
}

// Funcion para calcular el error relativo, donde
// p* es una aproximación al valor p.
double relative_error(double p, double p_star){
    if(p == 0.0){
        // Se evitan indeterminacionesx
        return fabs(p - p_star)/fabs(p+1);
    }else{
        return fabs(p-p_star)/fabs(p);
    }
}

// Imprime y devuelve los valores 
double bisection(double a, double b, double epsilon){
    int iter = 1;
    double fa = function(a), fb = function(b);
    double c  = (a+b)/2, fc = function(c);
    double relative_p = 1.5214;

    if(fa*fb > 0){
        printf("Limites no validos para el metodo\n");
        return 0;
    }

    while(fabs(fc) >= epsilon){

        if(fa*fc < 0){
            b = c;
        }else{
            a = c;
        }

        iter++;
        c = (a+b)/2;
        fc = function(c);
    }

    printf("Numero de iteraciones: %d\n", iter);
    printf("El valor de la raíz es: %lf \n", c);
    printf("El valor de la funcion en la raiz es: %lf \n", fc);
    printf("El error relativo es: %lf \n", relative_error(relative_p, c));
    return c;
}

int main(){
    double a = 1, b = 2;
    double epsilon = 0.0001;

    bisection(a,b,epsilon);
}
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double function(double x){
    return 9*pow(x,2)-10;
}

double derive(double (*f)(double), double x0)
{
    const double delta = 1.0e-6; //
    double x1 = x0 - delta;
    double x2 = x0 + delta;
    double y1 = f(x1);
    double y2 = f(x2);
    return (y2 - y1) / (x2 - x1);
}

double newton_method(double x0, float epsilon){
    double x1;

    x1 = x0 - function(x0)/derive(function,x0);
    printf("%f \n", x1);

    if(fabsf(x1) < epsilon){
        printf("%f", x1);
        return x1;
    }else{
        printf("ayuwoki\n");
        return newton_method(x1,epsilon);
    }
}

int main(){
    double init = 10;
    float epsilon = 0.01;
    newton_method(init,epsilon);
}
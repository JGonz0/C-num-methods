#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int row = 3;

void fill_square_matrix(double matrix[row][row]){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < row; j++){
            printf("Fila %d, Columna %d \n", i+1, j+1);
            scanf("%lf", &matrix[i][j]);
        }
    }
    return;
}

void print_matrix(double matrix[row][row]){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < row; j++){
            printf("%0.2lf ", matrix[i][j]);
        }
        printf("\n");
    }
    return;
}

int main(){
    double matrix[row][row];

    fill_square_matrix(matrix);
    print_matrix(matrix);
}
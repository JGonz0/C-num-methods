#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double **fill_square_matrix(){
    static int row;
    
    printf("Numero de filas/columnas: " );
    scanf("%d", &row);
    printf("\n");

    double **matrix;
    matrix = malloc(row*sizeof(double*));
    
    for(int i = 0; i < row; i++) {
        matrix[i] = malloc(row*sizeof(double*));
    }

    for(int i = 0; i < row; i++){
        for(int j = 0; j < row; j++){
            printf("Fila: %d, Columna: %d \n", i, j);
            scanf("%lf", &matrix[i][j]);
        }
    }

    return matrix;
}

void print_matrix(double **matrix){
    int row, col;
    row = 3;
    col = 3;

    for(int i = 0; i < row; i++){
            for(int j = 0; j < row; j++){
                printf("%0.2ld   ", matrix[i][j]);
            }
        printf("\n");
        }
    
    return;
}

int main(){
    double **take;

    take = fill_square_matrix();
    print_matrix(take);
}
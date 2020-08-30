#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <cairo/cairo.h>

#ifndef MYPLOT_H
#define MYPLOT_H

// Número de pares xi yi
#define NDATA 200
#define P_SPACES 15.0

// Medidas del monitor (pixeles)
#define WIDTH 640
#define HEIGHT 480

// Función de prueba
double sample_function(double x){
    return pow(x,3) + pow(x,2) - 4;
}


// Generación de  los puntos yi
void y_tabular(double *x, double *y, double (*func)(double)){
    for(int i = 0; i < NDATA; i++){
        y[i] = func(x[i]);

        // Condicional para evitar discontinuidades a inf
        if(y[i] == INFINITY){
            y[i] = func(0.0001);
        }
        
        // Condicional para evitar discontinuidades a -inf
        else if(y[i] == -INFINITY){
            y[i] = func(-0.0001);
        }

        // Condicional para cambiar NaN a 0
        if(isnan(y[i])){
            y[i] = 0;
        }
    }
    return;
}


// Función para obtener el valor máximo en un arreglo
double max_value(double *y){
    
    double max_value = y[0];

    // Se recorre el arreglo desde el segundo elemento y
    // se compara cada elemento con el valor máximo actual
    for(int i = 1; i < NDATA; i++){
        if(y[i] > max_value){
            max_value = y[i];
        }
    }

    return max_value;
}


// Función para obtener el valor mínimo en un arreglo
double min_value(double *y){
    
    double min_value = y[0];

    // Se recorre el arreglo desde el segundo elemento y
    // se compara cada elemento con el valor mínimo actual
    for(int i = 1; i < NDATA; i++){
        if(y[i] < min_value){
            min_value = y[i];
        }
    }
    return min_value;
}

// Separación de dos valores en espacios equitativamente distantes
void linspace(double a, double b, double *x){

    // Se define el incremento y el primer elemento
    // NDATA - 1 para considerar el punto b dentro del arreglo
    double delta_x = (b - a)/(NDATA - 1);
    x[0] = a;

    for(int i = 1; i < NDATA; i++){
        x[i] = x[i - 1] + delta_x;
    }
    return;
}


// Función para establecer la relación valor - pixel
double line_equation(double axis, double origin,  double max_val, double min_val, double vector){

    // diff_px indica la diferencia entre el punto final e inicial del eje, en pixeles
    // diff_val indica la diferencia entre el valor mínimo y valor máximo
    double diff_px = axis-origin;
    double diff_val = max_val - min_val;

    return (max_val - vector)*diff_px/diff_val + origin;
}

// Genera la gráfica solamente estableciendo los límites y la función
void plot_graph(double lim_a, double lim_b, double (*func)(double), char *name_label, char *plot_name){
    double x[NDATA]; 
    double y[NDATA];

    linspace(lim_a, lim_b, x);
    y_tabular(x, y, func);

    // Asignación de variables auxiliares
    double x_aux;
    double y_aux;

    // Obtención de los valores máximos y mínimos
    double y_max = max_value(y);
    double y_min = min_value(y);
    double x_max = x[NDATA - 1];
    double x_min = x[0];

    // Lienzo
    cairo_surface_t *surface;
    cairo_t *cr;
    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,WIDTH,HEIGHT);
    cr = cairo_create(surface);

    // Fondo
    cairo_pattern_t *pat;
    pat = cairo_pattern_create_linear(WIDTH/2, 0.0, WIDTH/2, HEIGHT);
    cairo_pattern_add_color_stop_rgb(pat, 0.0, 0.9, 0.9, 0.9);
    cairo_pattern_add_color_stop_rgb(pat, 1.0, 0.6, 0.6, 0.6);
    cairo_rectangle(cr, 0, 0, WIDTH, HEIGHT);
    cairo_set_source(cr, pat);
    cairo_fill(cr);
    
    // Ejes x, y
    double x_axis = WIDTH - (WIDTH/8);
    double y_axis = HEIGHT/8;
    double x_origin = WIDTH/8;
    double y_origin = HEIGHT - (HEIGHT/8);
    
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_set_line_width(cr, 3);
    cairo_move_to(cr, x_origin, y_origin);  cairo_line_to(cr, x_axis, y_origin);
    cairo_move_to(cr, x_origin, y_origin);  cairo_line_to(cr, x_origin, y_axis);
    cairo_stroke(cr);

    // Rejilla (Grid)
    double x_metric = (x_axis - x_origin)/P_SPACES;
    double y_metric = (y_origin - y_axis)/P_SPACES;

    for(int i = 1; i < P_SPACES + 1; i++){
        cairo_set_source_rgb(cr, 0.4, 0.4, 0.4);
        cairo_set_line_width(cr, 0.5);
        // Lineas verticales
        cairo_move_to(cr, (x_origin + (x_metric * i)), y_origin);
        cairo_line_to(cr,(x_origin + (x_metric * i)), y_axis);
        // Lineas horizontales
        cairo_move_to(cr, x_origin, (y_axis + (y_metric * (i-1))));
        cairo_line_to(cr, x_axis, (y_axis + (y_metric * (i-1))));
        cairo_stroke(cr);
    }

    // Labels eje x
    char x_label[8];

    for (int i = 0; i < P_SPACES + 1; i++){
        cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 10.0);
        cairo_move_to(cr, (x_origin + (x_metric * i)), (y_origin + 10));
        cairo_save(cr);
        cairo_rotate(cr, 45.0); 

        // Double a texto
        x_aux = (x_max - x_min)/P_SPACES;
        sprintf(x_label, "%0.2lf", x[0] + i*x_aux);

        cairo_show_text(cr, x_label);
        cairo_restore(cr);
    }

    // Labels eje y
    char y_label[8];

    for (int i = 0; i < P_SPACES + 1; i++){
        cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 10.0);
        cairo_move_to(cr, (x_origin - 50), (y_origin - (y_metric * i)));
        cairo_save(cr);

        // Double a texto
        y_aux = (y_max - y_min)/P_SPACES;
        sprintf(y_label, "%0.2lf", y_min + i*y_aux);

        cairo_show_text(cr, y_label);
        cairo_restore(cr);
    }

    // Label del nombre
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, (y_axis/3.0));
    cairo_move_to(cr, WIDTH/2.5, y_axis/2.0);
    cairo_show_text(cr, name_label);

    // Plotting
    for(int i = 0; i < NDATA; i++){
        
        // Asignación de cada punto en la gráfica
        double x_val = line_equation(x_axis, x_origin, x_min, x_max, x[i]);
        double y_val = line_equation(y_axis, y_origin, y_min, y_max, y[i]);

        if(i >= 1){
            cairo_set_source_rgba(cr, 0.29, 0, 0.51,0.5);
            cairo_set_line_width(cr, 1.8);
            cairo_move_to(cr, x_aux, y_aux);
            cairo_line_to(cr, x_val, y_val);
            cairo_stroke(cr);
        }

        x_aux = x_val;
        y_aux = y_val;
    }

    //Dibuja un eje en 0
    y_aux = line_equation(y_axis, y_origin, y_min, y_max, 0);
    cairo_set_source_rgba(cr, 1, 0.0, 0.0, 0.25);
    cairo_set_line_width(cr, 2);
     cairo_move_to(cr, x_origin, y_aux);  cairo_line_to(cr, x_axis, y_aux);
    cairo_stroke(cr); 

    // Liberación de memoria
    cairo_surface_write_to_png(surface, strcat(plot_name,".png"));
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    return;
}

#endif
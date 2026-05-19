#include "shape_render.h"
#include "font_render.h"

void draw_rect(double x, double y, double width, double height, unsigned short int color){
    double h_width = width / 2;
    double h_height = height / 2;
    for (int xx = x - h_width; xx < x + h_width; xx++){
        for (int yy = y - h_height; yy < y + h_height; yy++ ){
            draw_pixel(xx, yy, color);
        }
    }
}
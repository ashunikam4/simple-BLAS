#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "constants.h"
#include "drawing/algo.h"
#include "../solver/solver.h"

char** getWorkSpace(int plt_h, int plt_w){
    char** ws = (char**)malloc(plt_h * sizeof(char*));
    for(int y = 0; y < plt_h; y++) {
        ws[y] = (char*) malloc(plt_w * sizeof(char));
        for(int x = 0; x < plt_w; x++)
            ws[y][x] = ' ';
    }
    return ws;
}

void draw(char** ws, int plt_h, int plt_w, double coeff[3], int algo, char sym) {
    
    switch(algo){
        case DSC:
            directScanConversion(ws, coeff, plt_h, plt_w, sym);
            break;
        case DDA:
            digitalDifferentialAnalyzer(ws, coeff, plt_h, plt_w, sym);
            break;
        case BRS:
            break;
    }
}

void show(char** ws, int plt_h, int plt_w, double res[2], double scale_x, double scale_y) {
    int ystride = plt_h / 5;
    for(int j = 0; j < plt_h; j++) {
        if((plt_h - 1 - j) % ystride == 0) 
            printf("%c|", 'p' + (plt_h - 1 - j) / ystride);
        else 
            printf(" |"); 
        for(int i = 0; i < plt_w; i++)
            printf("%c", ws[plt_h - 1 - j][i]);
        printf("\n");
    }

    printf(" |");
    for(int i = 0; i < plt_w; i++) 
        printf("_");
    printf("\n");
    int xstride = plt_w / 5;
    printf("  ");
    for(int i = 0; i < plt_w; i++) {
        if(i % xstride == 0) 
            printf("%c", 'a' + i / xstride);
        else printf(" ");
    }
    printf("\n\n");

    double y0 = res[1] - (scale_y * plt_h / 2);  
    for(int j = 0; j < plt_h; j += ystride)
        printf(" %c : %11.4lf\n", 'p' + j/ystride, y0 + (scale_y * j));
    printf("\n\n");

    double x0 = res[0] - (scale_x * plt_w / 2);  
    for(int i = 0; i < plt_w; i += xstride)
        printf(" %c : %11.4lf\n", 'a' + i / xstride, x0 + (scale_x * i));
    printf("\n\n");
}

void plot(double acoeff[3], double bcoeff[3], double res[2], enum solve_rflag resFlag, 
            enum draw_algo algo, int plt_h, int plt_w, double scale_x, double scale_y) {

    if(plt_h == -1) plt_h = DEF_PLT_HEIGHT;
    if(plt_w == -1) plt_w = DEF_PLT_WIDTH;
    if(scale_x == -1) scale_x = DEF_PLT_SCALEX;
    if(scale_y == -1) scale_y = DEF_PLT_SCALEY;

    if(resFlag == NO_SOL) {
        printf("Skipping the plotter execution...\n");
        return;
    }

    printf("Plotting the lines on cartesian plane ...\n");
    printf("1 : %0.4lf x + %0.4lf y = %0.4lf\n", acoeff[0], acoeff[1], acoeff[2]);
    printf("2 : %0.4lf x + %0.4lf y = %0.4lf\n\n\n", bcoeff[0], bcoeff[1], bcoeff[2]);

    if(resFlag == INF_SOL) {
        if(acoeff[0] == 0 && acoeff[1] == 0) {
                if(bcoeff[0] == 0 && bcoeff[1] == 0) {
                    printf("Plotting Error: cannot plot lines with all coefficients equal to 0.\n");
                    return;
                }
                acoeff[0] = bcoeff[0];
                acoeff[1] = bcoeff[1];
                acoeff[2] = bcoeff[2];
            }

        if(acoeff[1]) {
            res[0] = 0;
            res[1] = acoeff[2] / acoeff[1];
        }
        else {
            res[1] = 0;
            res[0] = acoeff[2] / acoeff[0];
        }
    }
    char** ws = getWorkSpace(plt_h, plt_w);
    
    acoeff[0] = scale_x * acoeff[0];
    acoeff[1] = scale_y * acoeff[1];
    bcoeff[0] = scale_x * bcoeff[0];
    bcoeff[1] = scale_y * bcoeff[1];

    double x0 = res[0] / scale_x - plt_w / 2;
    double y0 = res[1] / scale_y - plt_h / 2;
    acoeff[2] -= (acoeff[0] * x0 + acoeff[1] * y0);
    bcoeff[2] -= (bcoeff[0] * x0 + bcoeff[1] * y0);

    switch(resFlag) {
        case SGL_SOL: 
            draw(ws, plt_h, plt_w, acoeff, algo, '1');
            draw(ws, plt_h, plt_w, bcoeff, algo, '2');
            break;
        case INF_SOL:
            draw(ws, plt_h, plt_w, acoeff, algo, '1');       
    }
    show(ws, plt_h, plt_w, res, scale_x, scale_y);
}




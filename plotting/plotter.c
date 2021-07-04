/*
    Plotter implementation
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "constants.h"
#include "drawing/algo.h" // line-drawing algorithms
#include "../solver/solver.h" 

/*
     getWorkSpace : create a workspace memory for storing the plot
*/
char** getWorkSpace(int plt_h, int plt_w){
    char** ws = (char**)malloc(plt_h * sizeof(char*));
    for(int y = 0; y < plt_h; y++) {
        ws[y] = (char*) malloc(plt_w * sizeof(char));
        for(int x = 0; x < plt_w; x++)
            ws[y][x] = ' ';
    }
    return ws;
}

/*
    draw : takes workspace as input, and uses specified algo to 
            draw single line equation specified by coeff
*/ 
void draw(char** ws, int plt_h, int plt_w, double coeff[3], int algo, char sym) {
    
    switch(algo){
        case DSC:
            directScanConversion(ws, coeff, plt_h, plt_w, sym);
            break;
        case DDA:
            digitalDifferentialAnalyzer(ws, coeff, plt_h, plt_w, sym);
            break;
        case BRS:
            bresenhamAlgorithm(ws, coeff, plt_h, plt_w, sym);
    }
}

/*
    show : displays the plot on console after drawing the lines
*/
void show(char** ws, int plt_h, int plt_w, double res[2], double scale_x, double scale_y) {
    
    // we display 5 markings along both x and y axis
    // irrespective of plot configs 
    int ystride = plt_h / 5;
    for(int j = 0; j < plt_h; j++) {
        // draw y-axis
        // 'p', 'q', 'r', 's', 't' labels are used to mark y-axis
        // the exact values corresponding to these labels, are displayed below
        // graph. 
        if((plt_h - 1 - j) % ystride == 0) 
            printf("%c|", 'p' + (plt_h - 1 - j) / ystride);
        else 
            printf(" |"); 

        // display the plot flipped horizontally
        for(int i = 0; i < plt_w; i++)
            printf("%c", ws[plt_h - 1 - j][i]);
        printf("\n");
    }

    // draw x-axis
    // 'a', 'b', 'c', 'd', 'e' labels are used to mark y-axis
    // the exact values corresponding to these labels, are displayed below
    // graph. 
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

    // printing values for y-axis markings
    double y0 = res[1] - (scale_y * plt_h / 2);  
    for(int j = 0; j < plt_h; j += ystride)
        printf(" %c : %11.4lf\n", 'p' + j/ystride, y0 + (scale_y * j));
    printf("\n\n");

    // printing values for x-axis markings
    double x0 = res[0] - (scale_x * plt_w / 2);  
    for(int i = 0; i < plt_w; i += xstride)
        printf(" %c : %11.4lf\n", 'a' + i / xstride, x0 + (scale_x * i));
    printf("\n\n");
}

/*
    plot : main plotter interface function

    * Accepts the systems of equations, their solution and plot attributes.
    * Does some preprocessing before executing line-drawing algo.

*/
void plot(double acoeff[3], double bcoeff[3], double res[2], enum solve_rflag resFlag, 
            enum draw_algo algo, int plt_h, int plt_w, double scale_x, double scale_y) {

    // using default plot attributes
    if(plt_h == -1) plt_h = DEF_PLT_HEIGHT;
    if(plt_w == -1) plt_w = DEF_PLT_WIDTH;
    if(scale_x == -1) scale_x = DEF_PLT_SCALEX;
    if(scale_y == -1) scale_y = DEF_PLT_SCALEY;

    // For no solution, no graph is plotted
    // (*as mentioned in problem statment*)
    if(resFlag == NO_SOL) {
        printf("Skipping the plotter execution...\n");
        return;
    }

    printf("Plotting the lines on cartesian plane ...\n");

    // For system with infinite solutions, we have overlapping lines.
    // So, plot only one of them
    if(resFlag == INF_SOL) {
        // if equation 1 is 0 = 0, plot the equation 2
        if(acoeff[0] == 0 && acoeff[1] == 0) {
                // cannot plot equation with all zero coeffs
                if(bcoeff[0] == 0 && bcoeff[1] == 0) {
                    printf("Plotting Error: cannot plot lines with all coefficients equal to 0.\n");
                    return;
                }
                acoeff[0] = bcoeff[0];
                acoeff[1] = bcoeff[1];
                acoeff[2] = bcoeff[2];
            }

        // choosing some arbitrary points on line as result
        if(acoeff[1]) {
            res[0] = 0;
            res[1] = acoeff[2] / acoeff[1];
        }
        else {
            res[1] = 0;
            res[0] = acoeff[2] / acoeff[0];
        }
        printf("1 : %0.4lf x + %0.4lf y = %0.4lf\n", acoeff[0], acoeff[1], acoeff[2]);
    }
    else {
        printf("1 : %0.4lf x + %0.4lf y = %0.4lf\n", acoeff[0], acoeff[1], acoeff[2]);
        printf("2 : %0.4lf x + %0.4lf y = %0.4lf\n\n\n", bcoeff[0], bcoeff[1], bcoeff[2]);
    }
    
    char** ws = getWorkSpace(plt_h, plt_w);
    
    // scaling the variables acording to input scale attrs
    acoeff[0] = scale_x * acoeff[0];
    acoeff[1] = scale_y * acoeff[1];
    bcoeff[0] = scale_x * bcoeff[0];
    bcoeff[1] = scale_y * bcoeff[1];

    // translating the coordinate system, so that
    // result (x. y) is always at the center of workspace
    double x0 = res[0] / scale_x - plt_w / 2;
    double y0 = res[1] / scale_y - plt_h / 2;
    acoeff[2] -= (acoeff[0] * x0 + acoeff[1] * y0);
    bcoeff[2] -= (bcoeff[0] * x0 + bcoeff[1] * y0);

    // drawing the lines  
    switch(resFlag) {
        case SGL_SOL: 
            draw(ws, plt_h, plt_w, acoeff, algo, '1');
            draw(ws, plt_h, plt_w, bcoeff, algo, '2');
            break;
        case INF_SOL:
            draw(ws, plt_h, plt_w, acoeff, algo, '1');
            break;
        case NO_SOL:
            break;
    }

    show(ws, plt_h, plt_w, res, scale_x, scale_y);
}




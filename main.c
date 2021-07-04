/*
    Main file for the application.

    Parses the input args and runs solver and plotter.   
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "solver/solver.h"
#include "plotting/plotter.h"
#include "plotting/drawing/algo.h"

int main(int argc, char* argv[]){
    double acoeff[3];   // coeff for equation 1
    double bcoeff[3];   // coeff for equation 2 
    enum solve_algo salgo = SUBS;   // solver algorithm
    enum draw_algo dalgo = DDA;     // line drawing algorithm
    int plt_h = -1;     // plot height
    int plt_w = -1;     // plot width
    double scale_x = -1;    // plot scale along x-axis 
    double scale_y = -1;    // plot scale along y-axis

    // Parsing the arguments
    if(argc < 7) { // 6 coeff args are mandatory
        printf("Invalid Input : Specifying 2 x 3 coefficients is required\n");
        return 0;
    }

    // coeff args
    for(int i = 0; i < 3; i++)
        acoeff[i] = atof(argv[1 + i]);
    for(int i = 0; i < 3; i++)
        bcoeff[i] = atof(argv[4 + i]);

    // optional args
    int iter = 7;
    while(iter < argc) {
        if(strcmp(argv[iter], "-d") == 0) { // drawing algo selection flag
            iter++;
            if(iter == argc) {
                printf("Invalid Input : please see README for usage\n");
                return 0;
            }
            if(strcmp(argv[iter], "dsc") == 0) dalgo = DSC;
            else if(strcmp(argv[iter], "dda") == 0) dalgo = DDA;
            else if(strcmp(argv[iter], "brs") == 0) dalgo = BRS;
            iter++;
        }
        else if(strcmp(argv[iter], "-s") == 0) { // solver algo selection flag
            iter++;
            if(iter == argc) {
                printf("Invalid Input : please see README for usage\n");
                return 0;
            }
            if(strcmp(argv[iter], "subs") == 0) salgo = SUBS;
            else if(strcmp(argv[iter], "matinv") == 0) salgo = MATINV;
            iter++;
        }
        else if(strcmp(argv[iter], "-c") == 0) { // plot attributes flag
            iter++;
            if((iter + 4) > argc) {
                printf("Invalid Input : please see README for usage\n");
                return 0;
            }
            plt_h = atoi(argv[iter++]);
            plt_w = atoi(argv[iter++]);
            scale_x = atof(argv[iter++]);
            scale_y = atof(argv[iter++]);
        }
        else {
            printf("Invalid Input : please see README for usage\n");
            return 0;
        }
    }

    double res[2];  // holds solver results, res[0] = x, res[1] = y
    enum solve_rflag flag;  // to tell whether system of solutions has 1 solution,
                            // infinite solutions or no solution 

    // Running the solver
    clock_t start, end; // timing 
    switch(salgo){
        case MATINV:
            start = clock();
            flag = solveByMatrixInversion(acoeff, bcoeff, res);
            end = clock();
            break;
        case SUBS:
            start = clock();
            flag = solveBySubstitution(acoeff, bcoeff, res);
            end = clock();
    }
    end = clock();
    printf("Solver exectution time: %lf s\n", (double)(end - start)/CLOCKS_PER_SEC);
    
    // Priting solutions as text
    switch(flag) {
        case SGL_SOL: 
            printf("Single solution exists : (x = %0.4lf, y = %0.4lf)\n\n", res[0], res[1]);
            break;
        case INF_SOL:
            printf("Infinite solutions exist\n\n");
            break;
        case NO_SOL:
            printf("No solution exists\n\n");
    }

    // Running the plotter
    start = clock();
    plot(acoeff, bcoeff, res, flag, dalgo, plt_h, plt_w, scale_x, scale_y);
    end = clock();
    printf("Plotter exectution time: %lf s\n", (double)(end - start)/CLOCKS_PER_SEC);
    
    printf("DONE!\n");
    printf("========================================\n");
    return 0;
}
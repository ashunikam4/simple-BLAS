#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "solver/solver.h"
#include "plotting/plotter.h"
#include "plotting/drawing/algo.h"

int main(int argc, char* argv[]){
    double acoeff[3];
    double bcoeff[3];
    enum solve_algo salgo = MATINV;
    enum draw_algo dalgo = DSC;
    int plt_h = -1;
    int plt_w = -1; 
    int scale_x = -1; 
    int scale_y = -1; 

    if(argc < 7) {
        printf("Invalid Input : Specifying 2 x 3 coefficients is required\n");
        return 0;
    }

    for(int i = 0; i < 3; i++)
        acoeff[i] = atof(argv[1 + i]);
    for(int i = 0; i < 3; i++)
        bcoeff[i] = atof(argv[4 + i]);

    
    int iter = 7;
    while(iter < argc) {
        if(strcmp(argv[iter], "-d") == 0) {
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
        else if(strcmp(argv[iter], "-s") == 0) {
            iter++;
            if(iter == argc) {
                printf("Invalid Input : please see README for usage\n");
                return 0;
            }
            if(strcmp(argv[iter], "subs") == 0) salgo = SUBS;
            else if(strcmp(argv[iter], "matinv") == 0) salgo = MATINV;
            iter++;
        }
        else if(strcmp(argv[iter], "-c") == 0) {
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

    double res[2];
    enum solve_rflag flag;

    clock_t start, end;
    start = clock();
    switch(salgo){
        case MATINV:
            flag = solveByMatrixInversion(acoeff, bcoeff, res);
            break;
        case SUBS:
            flag = solveBySubstitution(acoeff, bcoeff, res);
    }
    end = clock();
    printf("Solver exectution time: %lf s\n", (double)(end - start)/CLOCKS_PER_SEC);
    
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

    start = clock();
    plot(acoeff, bcoeff, res, flag, dalgo, plt_h, plt_w, scale_x, scale_y);
    end = clock();
    printf("Plotter exectution time: %lf s\n", (double)(end - start)/CLOCKS_PER_SEC);
    printf("DONE!\n");
    return 0;
}
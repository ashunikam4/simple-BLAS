#include <stdio.h>
#include "solver.h" 

enum solve_rflag solveByMatrixInversion(double acoeff[], double bcoeff[], double res[]) {
    double det = acoeff[0] * bcoeff[1] - bcoeff[0] * acoeff[1];
    printf("Determinant of the Coefficient Matrix: %0.4lf\n", det);
    if(det == 0) {
        if((acoeff[0] * bcoeff[2]) == (bcoeff[0] * acoeff[2]))
            return INF_SOL;
        else 
            return NO_SOL;
    }
    double inv[4];
    inv[0] =  bcoeff[1] / det;
    inv[1] = -acoeff[1] / det;
    inv[2] = -bcoeff[0] / det;
    inv[3] = acoeff[0] / det;
    printf("Inverted Coefficient Matrix:\n");
    printf("%9.4lf\t%9.4lf\n", inv[0], inv[1]);
    printf("%9.4lf\t%9.4lf\n", inv[2], inv[3]);

    res[0] = inv[0] * acoeff[2] + inv[1] * bcoeff[2];
    res[1] = inv[2] * acoeff[2] + inv[3] * bcoeff[2];
    return SGL_SOL;
}
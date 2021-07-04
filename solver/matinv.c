/*
    Implementation of matrix inversion based solver.
*/

#include <stdio.h>
#include "solver.h" 

/*
    solveByMatrixInversion: Takes system of equation as input, 
    checks if solution exists and solves using matrix inversion method.
    Intermediate determinant value and inverted matrix are also displayed.

    Input:
        acoeff : coefficients of 1st equation a * x + b * y = c
                 acoeff[0] = a, acoeff[1] = b, acoeff[2] = c
        bcoeff : coefficients of 2nd equation p * x + q * y = r
                 bcoeff[0] = p, bcoeff[1] = q, bcoeff[2] = r
        res : placeholder to store result (if single solution exists)
                res[0] = x, res[1] = y

    returns:
        flag : equals SGL_SOL if single solution exists
                equals IN_SOL if infinite solutions exist
                equals NO_SOL if no solution exists
*/
enum solve_rflag solveByMatrixInversion(double acoeff[], double bcoeff[], double res[]) {
    // deteminant = a * q - p * b
    double det = acoeff[0] * bcoeff[1] - bcoeff[0] * acoeff[1];
    printf("Determinant of the Coefficient Matrix: %0.4lf\n", det);
    
    // determinant = 0 => a / b = p / q => infinite or 0 solutions
    if(det == 0) {
        if((acoeff[0] * bcoeff[2]) == (bcoeff[0] * acoeff[2])) // a / b = p / q = c / r
            return INF_SOL;
        else 
            return NO_SOL;
    }

    // inverted matrix
    // Ainv[i][j] = inv[2 * i + j]
    // if A = [x  y]
    //        [z  w],
    // Ainv = 1/det(A) * [w  -y]
    //                   [-z  x]
    double inv[4];
    inv[0] =  bcoeff[1] / det;
    inv[1] = -acoeff[1] / det;
    inv[2] = -bcoeff[0] / det;
    inv[3] = acoeff[0] / det;
    printf("Inverted Coefficient Matrix:\n");
    printf("%9.4lf\t%9.4lf\n", inv[0], inv[1]);
    printf("%9.4lf\t%9.4lf\n", inv[2], inv[3]);

    // A.x = b
    // x = Ainv.b
    res[0] = inv[0] * acoeff[2] + inv[1] * bcoeff[2];
    res[1] = inv[2] * acoeff[2] + inv[3] * bcoeff[2];
    return SGL_SOL;
}
/*
    Implementation of substitution method based solver.
*/

#include "solver.h" 

/*
    solveBySubstitution: Takes system of equation as input, 
    checks if solution exists and solves using substitution method.

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
enum solve_rflag solveBySubstitution(double acoeff[], double bcoeff[], double res[]) {    
    if(acoeff[0]) { // if x is present in equation 1

        // represent x in terms of y
        // x = ta1 * y + ta2
        double ta2 =  acoeff[2] / acoeff[0];
        double ta1 = -acoeff[1] / acoeff[0];

        // solve for y by substituting x
        // tb1 * y = tb2
        double tb1 = bcoeff[1] + bcoeff[0] * ta1;
        double tb2 = bcoeff[2] - bcoeff[0] * ta2;

        if(tb1 == 0) {  
            if(tb2 == 0) // solving 0 = 0
                return INF_SOL;
            else // solving 0 = non_zero
                return NO_SOL;
        }

        // for unique solution
        res[1] = tb2 / tb1;
        res[0] = ta2 + ta1 * res[1];
        return SGL_SOL;

    }
    else {
        // Equation 1 form : b * y = c
        if(acoeff[1] == 0) { // b = 0
            if(acoeff[2] == 0) // c = 0
                return INF_SOL;
            else 
                return NO_SOL;
        }

        // if b is non-zero, y = c / b
        double ta2 = acoeff[2] / acoeff[1];
        // substitute y in equation 2
        double tb2 = bcoeff[2] - bcoeff[1] * ta2;

        // solving for x, p * x = tb2
        if(bcoeff[0] == 0) { // p = 0
            if(tb2 == 0) // tb2 = 0
                return INF_SOL;
            else    
                return NO_SOL;
        }

        // for unique solution
        res[1] = ta2;
        res[0] = tb2 / bcoeff[0];
        return SGL_SOL;
    }
}
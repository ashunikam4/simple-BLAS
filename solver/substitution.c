#include "solver.h" 

enum solve_rflag solveBySubstitution(double acoeff[], double bcoeff[], double res[]) {    
    if(acoeff[0]) {
        double ta2 =  acoeff[2] / acoeff[0];
        double ta1 = -acoeff[1] / acoeff[0];

        double tb1 = bcoeff[1] + bcoeff[0] * ta1;
        double tb2 = bcoeff[2] - bcoeff[0] * ta2;

        if(tb1 == 0) {  
            if(tb2 == 0) 
                return INF_SOL;
            else
                return NO_SOL;
        }

        res[1] = tb2 / tb1;
        res[0] = ta2 + ta1 * res[1];
        return SGL_SOL;

    }
    else {
        if(acoeff[1] == 0) {
            if(acoeff[2] == 0)
                return INF_SOL;
            else 
                return NO_SOL;
        }

        double ta2 = acoeff[2] / acoeff[1];
        double tb2 = bcoeff[2] - bcoeff[1] * ta2;

        if(bcoeff[0] == 0) {
            if(tb2 == 0)
                return INF_SOL;
            else    
                return NO_SOL;
        }

        res[1] = ta2;
        res[0] = tb2 / bcoeff[0];
        return SGL_SOL;
    }
}
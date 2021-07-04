/*
    Implementation of direct scan conversion line-drawing algorithm
*/

#include <stdlib.h>
#include <math.h>

/*
    directScanConversion : runs direct scan conversion to draw the given line

    takes the line coeff and character used to mark the points on plot
*/
void directScanConversion(char** ws, double coeff[3], int plt_h, int plt_w, char sym) {
    // abs(slope) > 1 
    if(fabs(coeff[0]) > fabs(coeff[1])) {
        int x;
        // for each y value, evaluate the x value 
        // and choose the closest point
        for(int y = 0; y < plt_h; y++) {
            x = round((-coeff[1] * y + coeff[2])/coeff[0]);
            if(x >= 0 && x < plt_w) ws[y][x] = sym;
        }
    }
    else { // abs(slope) <= 1, same logic with flipped vars 
        int y;
        for(int x = 0; x < plt_w; x++) {
            y = round((-coeff[0] * x + coeff[2])/coeff[1]);
            if(y >= 0 && y < plt_h) ws[y][x] = sym;
        } 
    }
}
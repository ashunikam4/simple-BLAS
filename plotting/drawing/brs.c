/*
    Implementation of Bresenhams's line-drawing algorithm
*/

#include <stdlib.h>
#include <math.h>

/*
    bresenhamAlgorithm : runs Bresenhams's algo to draw the given line

    takes the line coeff and character used to mark the points on plot
*/

void bresenhamAlgorithm(char** ws, double coeff[3], int plt_h, int plt_w, char sym) {
    // abs(slope) > 1 
    if(fabs(coeff[0]) > fabs(coeff[1])) {
        // initial and final points, approx to integers
        // NOTE : this is actual a approximation, because we should
        //          use points which lie on line. But, using integers is 
        //          the essence of bresenham's algo
        int y0 = 0;
        int y1 = plt_h - 1;
        int x0 = round((-coeff[1] * y0 + coeff[2])/coeff[0]);
        int x1 = round((-coeff[1] * y1 + coeff[2])/coeff[0]);
        
        int dy = y1 - y0;
        int dx = x1 - x0;
        int xi = 1;
        if(dx < 0) { // negative slope
            dx = -dx;
            xi = -1; // x will reduce as y increases
        }

        int D = 2 * dx - dy; // error term 
        int x = x0;
        for(int y = y0; y <= y1; y++) {
            if(x >= 0 && x < plt_w) ws[y][x] = sym;
            // error is too much, increment x
            if(D > 0) {
                x += xi; // uses integer incr instead of floating point
                D -= 2 * dy;
            }
            D += 2 * dx;
        }
    }else {  // same logic with flipped vars
        int x0 = 0;
        int x1 = plt_w - 1;
        int y0 = round((-coeff[0] * x0 + coeff[2])/coeff[1]);
        int y1 = round((-coeff[0] * x1 + coeff[2])/coeff[1]);
        int dy = y1 - y0;
        int dx = x1 - x0;
        int yi = 1;
        if(dy < 0) {
            dy = -dy;
            yi = -1;
        }

        int D = 2 * dy - dx;
        int y = y0;
        for(int x = x0; x <= x1; x++) {
            if(y >= 0 && y < plt_h) ws[y][x] = sym;
            if(D > 0) {
                y += yi;
                D -= 2 * dx;
            }
            D += 2 * dy;
        }
    }
}
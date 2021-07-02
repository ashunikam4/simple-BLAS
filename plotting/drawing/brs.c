#include <stdlib.h>
#include <math.h>

void bresenhamAlgorithm(char** ws, double coeff[3], int plt_h, int plt_w, char sym) {
    if(fabs(coeff[0]) > fabs(coeff[1])) {
        int y0 = 0;
        int y1 = plt_h - 1;
        int x0 = round((-coeff[1] * y0 + coeff[2])/coeff[0]);
        int x1 = round((-coeff[1] * y1 + coeff[2])/coeff[0]);
        int dy = y1 - y0;
        int dx = x1 - x0;
        int xi = 1;
        if(dx < 0) {
            dx = -dx;
            xi = -1;
        }

        int D = 2 * dx - dy;
        int x = x0;
        for(int y = y0; y <= y1; y++) {
            if(x >= 0 && x < plt_w) ws[y][x] = sym;
            if(D > 0) {
                x += xi;
                D -= 2 * dy;
            }
            D += 2 * dx;
        }
    }else {
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
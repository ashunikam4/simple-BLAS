#include <stdlib.h>
#include <math.h>

void digitalDifferentialAnalyzer(char** ws, double coeff[3], int plt_h, int plt_w, char sym) {
    if(fabs(coeff[0]) > fabs(coeff[1])) {
        double dx = -coeff[1]/coeff[0];
        double x = coeff[2]/coeff[0];
        int xr;
        for(int y = 0; y < plt_h; y++) {
            xr = round(x);
            if(xr >= 0 && xr < plt_w) ws[y][xr] = sym;
            x += dx;
        }
    }
    else {
        double dy = -coeff[0]/coeff[1];
        double y = coeff[2]/coeff[1];
        int yr;
        for(int x = 0; x < plt_w; x++) {
            yr = round(y);
            if(yr >= 0 && yr < plt_h) ws[yr][x] = sym;
            y += dy;
        }
    }
}
#include <stdlib.h>
#include <math.h>

void directScanConversion(char** ws, double coeff[3], int plt_h, int plt_w, char sym) {
    if(fabs(coeff[0]) > fabs(coeff[1])) {
        int x;
        for(int y = 0; y < plt_h; y++) {
            x = round((-coeff[1] * y + coeff[2])/coeff[0]);
            if(x >= 0 && x < plt_w) ws[y][x] = sym;
        }
    }
    else {
        int y;
        for(int x = 0; x < plt_w; x++) {
            y = round((-coeff[0] * x + coeff[2])/coeff[1]);
            if(y >= 0 && y < plt_h) ws[y][x] = sym;
        } 
    }
}
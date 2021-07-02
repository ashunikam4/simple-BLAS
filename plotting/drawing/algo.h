#ifndef DRAW_ALGO_H
#define DRAW_ALGO_H

enum draw_algo {DSC, DDA, BRS};
void directScanConversion(char**, double[], int, int, char);
void digitalDifferentialAnalyzer(char**, double[], int, int, char);

#endif
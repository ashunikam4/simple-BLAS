#ifndef SOLVER_H
#define SOLVER_H

// Solver algorithm options : matrix inversion, substitution 
enum solve_algo {MATINV, SUBS};

// Solution type : single, infinite or no solution
enum solve_rflag {SGL_SOL, INF_SOL, NO_SOL};

// prototypes for solver functions
enum solve_rflag solveByMatrixInversion(double [], double [], double []);
enum solve_rflag solveBySubstitution(double [], double [], double []);

#endif
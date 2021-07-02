#ifndef SOLVER_H
#define SOLVER_H

enum solve_algo {MATINV, SUBS};
enum solve_rflag {SGL_SOL, INF_SOL, NO_SOL};
enum solve_rflag solveByMatrixInversion(double [], double [], double []);
enum solve_rflag solveBySubstitution(double [], double [], double []);

#endif
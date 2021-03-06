# simple-BLAS

This is a rudimetary BLAS implementation in C, supporting just 2 operations:
- Solving system of 2 equations in 2 variables
- If solution exists, plotting the equations on console using ascii characters

The work was done as part of final project for a C training course.

## Build

Clone the repository and run make

```bash
~$ git clone https://github.com/ashunikam4/simple-BLAS.git
~$ cd simple-BLAS
~$ make
```

## Usage

### Basic
The equation are represented as:
- a *x* + b *y* = c
- p *x* + q *y* = r

where *x* and *y* are cartesian variables. To run the app with default options:
```bash
# ./app a b c p q r 
~$ ./app 1.0 1.0 2.0 1.0 -1.0 0.0  
```

### Optional 
Few optional flags are provided.

`-s` **: Choose solver Algorithm**

2 options are available
- `subs` for substitution (default)
- `matinv` for matrix inversion
```bash
~$ ./app 1.0 1.0 2.0 1.0 -1.0 0.0 -s matinv
```
`-d` **: Choose drawing Algorithm**

3 options are available
- `dsc` for [direct scan conversion](https://en.wikipedia.org/wiki/Line_drawing_algorithm)
- `dda` for [direct differential analyzer](https://en.wikipedia.org/wiki/Digital_Differential_Analyzer_(graphics_algorithm)) (default)
- `brs` for [Bresenham's algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
```bash
~$ ./app 1.0 1.0 2.0 1.0 -1.0 0.0 -d brs
```

`-c` **: Configure plot**

Arguments are plot height, plot width, scale along x axis, and scale along y axis. Height and width (int) are number of charactars along X and Y axis, and scales (double) are number of units per character. Use `-1` value for using default for certain attributes 
```bash
# e.g.
# height = 100, width = 80, scale_x = 1.0, scale_y = 0.7
~$ ./app 1.0 1.0 2.0 1.0 -1.0 0.0 -c 100 80 1.0 0.7

# height = 75, width = 35, scale is default
~$ ./app 1.0 1.0 2.0 1.0 -1.0 0.0 -c 75 35 -1 -1
```

## Running Tests

1. In `tests.sh`, uncomment the tests you want to run
2. run `tests.sh`
3. check `output.txt` for results

## Output Format

* The solver dumps following things: 
  * Time required to solve
  * The type of solution (single, inifite or no solution)
  * The solution if exists


    For matinv solver, the intermediate results e.g. determinant and inverted matrix values are also shown.

* The plot is created such that **the solution is located at the center of the plot**. For infinite solutions case, an arbitrary point on the lines is chosen to be located at center.

* `1` and `2` are used to show the lines.
*  5 markings are shown on X axis using `a, b, c, d, e` and on Y axis using `p, q, r, s, t` for reference. The values correspoding to these markings are displayed below the plot.

```bash
# Example
~$ ./app 1.0 1.0 2.0 1.0 -1.0 0.0  

Solver execution time: 0.000002 s
Single solution exists : (x = 1.0000, y = 1.0000)

Plotting the lines on cartesian plane ...
1 : 1.0000 x + 1.0000 y = 2.0000
2 : 1.0000 x + -1.0000 y = 0.0000


 |11                                                                       22
 |  11                                                                   22  
 |    11                                                               22    
 |      111                                                         222      
 |         11                                                     22         
 |           11                                                 22           
t|             11                                             22             
 |               11                                         22               
 |                 11                                     22                 
 |                   11                                 22                   
 |                     111                           222                     
 |                        11                       22                        
 |                          11                   22                          
s|                            11               22                            
 |                              11           22                              
 |                                11       22                                
 |                                  11   22                                  
 |                                    222                                    
 |                                  22   11                                  
 |                                22       11                                
r|                              22           11                              
 |                            22               11                            
 |                          22                   11                          
 |                        22                       11                        
 |                     222                           111                     
 |                   22                                 11                   
 |                 22                                     11                 
q|               22                                         11               
 |             22                                             11             
 |           22                                                 11           
 |         22                                                     11         
 |      222                                                         111      
 |    22                                                               11    
 |  22                                                                   11  
p|22                                                                       11
 |___________________________________________________________________________
  a              b              c              d              e              

 p :     -0.3125
 q :      0.2125
 r :      0.7375
 s :      1.2625
 t :      1.7875


 a :     -0.3125
 b :      0.2125
 c :      0.7375
 d :      1.2625
 e :      1.7875


Plotter execution time: 0.000075 s
DONE!
========================================
```

# simple-BLAS (WIP)

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
- p *x* + q *y* = c

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

## Running Test

1. In `test.sh`, uncomment the tests you want to run
2. run `test.sh`
3. check `output.txt` for results
#! /bin/bash
# Uncomment the tests you wish to run

make
rm -f output.txt
touch output.txt

# -------- testing solvers ------------ 
# ./app  1 1.0 2 1 -1 0.0 -s subs >> output.txt
# ./app  5 3 7 6 5 4 -s subs >> output.txt
# ./app  245 -46 66 -876 264 -461 -s subs >> output.txt
# ./app  2 4 6 1 2 3 -s subs >> output.txt
# ./app  0 0 0 1 2 4 -s subs >> output.txt
# ./app  0 0 0 0 0 0 -s subs >> output.txt
# ./app  0 1 2 1 0 4 -s subs >> output.txt
# ./app  0 3 5 0 3 6 -s subs >> output.txt
# ./app  1 2 5 3 6 4 -s subs >> output.txt

# ./app  1 1.0 2 1 -1 0.0 -s matinv >> output.txt
# ./app  5 3 7 6 5 4 -s matinv >> output.txt
# ./app  245 -46 66 -876 264 -461 -s matinv >> output.txt
# ./app  2 4 6 1 2 3 -s matinv >> output.txt
# ./app  0 0 0 1 2 4 -s matinv >> output.txt
# ./app  0 0 0 0 0 0 -s matinv >> output.txt
# ./app  0 1 2 1 0 4 -s matinv >> output.txt
# ./app  0 3 5 0 3 6 -s matinv >> output.txt
# ./app  1 2 5 3 6 4 -s matinv >> output.txt

# -------------- testing plotting --------------
# ./app  1 1.0 2 1 -1 0.0 -d dsc >> output.txt
# ./app  5 3 7 6 5 4 -d dsc >> output.txt
# ./app  245 -46 66 -876 264 -461 -d dsc >> output.txt

# ./app  1 1.0 2 1 -1 0.0 -d dda >> output.txt
# ./app  5 3 7 6 5 4 -d dda >> output.txt
# ./app  245 -46 66 -876 264 -461 -d dda >> output.txt

# ./app  1 1.0 2 1 -1 0.0 -d brs >> output.txt
# ./app  5 3 7 6 5 4 -d brs >> output.txt
# ./app  245 -46 66 -876 264 -461 -d brs >> output.txt

# -------------- testing plot config --------------
# ./app  1 1.0 2 1 -1 0.0 -c 50 100 -1 -1  >> output.txt
# ./app  1 1.0 2 1 -1 0.0 -c -1 -1 2 1  >> output.txt
# ./app  1 1.0 2 1 -1 0.0 -c -1 -1 0.5 2.5  >> output.txt
# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/file2c/regress.sh 146277 2005-05-15 07:35:34Z marcel $

echo 1..9

REGRESSION_START($1)

REGRESSION_TEST(`1', `head -c 13 regress.in | file2c')
REGRESSION_TEST(`2', `head -c 26 regress.in | file2c PREFIX')
REGRESSION_TEST(`3', `head -c 39 regress.in | file2c PREFIX SUFFIX')
REGRESSION_TEST(`4', `head -c 52 regress.in | file2c -x')
REGRESSION_TEST(`5', `head -c 65 regress.in | file2c -n -1')

REGRESSION_TEST(`6', `head -c  7 regress.in | file2c -n 1 P S')
REGRESSION_TEST(`7', `head -c 14 regress.in | file2c -n 2 -x "P S"')
REGRESSION_TEST(`8', `head -c 21 regress.in | file2c -n 16 P -x S')

REGRESSION_TEST(`9', `file2c "const char data[] = {" ", 0};" < regress.in')

REGRESSION_END()

reset
set term epslatex color solid 
set output "2dim_test.tex"

set samples 2000
set linetype 10
f(x)=0.5+0.5*cos(2*x)
set xrange[0:4]
p f(x), "2dim_test.dat" u 1:2  with points lc rgb "red" ps 0.4 
set key invert

set output

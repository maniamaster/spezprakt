reset
set term eps
set output "test.eps"

set samples 2000
set linetype 10
set autoscale

p "test.dat" u 1:2  with points lc rgb "red" ps 0.1 


set output

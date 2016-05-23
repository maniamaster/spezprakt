reset
set term epslatex color solid
set output "kurzzeit.tex"
set samples 200100
set xrange [0:6]
set yrange [-0.5:0.5]
f(x)=-0.5+0.5*x**2
b(x)=-0.5*besj0(2*x)
list=system("ls kurzzeit_*.dat")
load "Spectral.plt"
set size 1,1.5
set key horizontal
set key at 5,-0.65
set bmargin 9
set lmargin 0.5
set rmargin 0.5
set key spacing 1.5
set xlabel "time $t$"
set ylabel 'z-spin exp. value $\braket{S_1^z}_t$ 
p for [i=1:words(list)] word(list,i) w l ls words(list)-i+1 lw 2 title '$N=~$ '.(2*i),f(x) with lines dt 2 lc rgb "blue" lw 2.5 title '$0.5-0.5t^2$', b(x) with lines dt 3 lc rgb "black" lw 2.5 title '$-0.5~J_0(2x)$' 
set output

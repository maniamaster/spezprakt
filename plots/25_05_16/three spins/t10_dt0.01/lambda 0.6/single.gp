reset
set term epslatex color solid size 4in, 4in
#set noborder
set autoscale xfix
set autoscale yfix
set autoscale cbfix
load "RdBu.plt"
set palette negative
list =system("ls Sz_*.dat")
end=".tex"
mu=" 0_4 0_8 0_0 1_2 2_0 "
set xlabel "particle index $i$"
set ylabel "time $t$"
set cblabel '$\braket{S_1^z}_t$'
set cbrange [-0.5:0.5]
set cbtics (-0.5,-0.4,-0.3,-0.2,-0.1,0,0.1,0.2,0.3,0.4,0.5)
do for [i=1:words(list)] {
    name="SzTwo_l06_mu".word(mu,i)
    outname= name.end
    set output outname
    set title "$\\lambda=0,~\\mu=$".word(mu,i)[1:1].".".word(mu,i)[3:3]
    p word(list,i) matrix u 1:($2/100):3 with image notitle 
    set output
}


reset
set term epslatex color solid size 4in, 3in
#set noborder
set autoscale xfix
set autoscale yfix
set autoscale cbfix
set bmargin 2.5
load "RdBu.plt"
set palette negative
list =system("ls Sz_*.dat")
end=".tex"
mu=" 0_1 0_2 0_3 0_4 0_5 0_6 0_7 0_8 0_9 0_0 1_0 "
set xlabel "particle index $i$"
set ylabel "time $Jt$"
set cblabel '$\braket{S_1^z}_t$'
set cbrange [-0.5:0.5]
set cbtics (-0.5,-0.4,-0.3,-0.2,-0.1,0,0.1,0.2,0.3,0.4,0.5)
do for [i=1:words(list)] {
    name="Sz2_l0_mu".word(mu,i)
    outname= name.end
    set output outname
    set title "$\\lambda=0,~\\mu=$".word(mu,i)[1:1].".".word(mu,i)[3:3].",~$N=30$"
    p word(list,i) matrix u 1:($2/50):3 with image notitle 
    set output
}


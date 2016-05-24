reset
set term epslatex color solid size 8in, 8in
set noborder
set autoscale xfix
set autoscale yfix
set autoscale cbfix
load "RdBu.plt"
set palette negative
list =system("ls Sz_*.dat")
end=".tex"
do for [i=1:words(list)] {
    name=word(list,i)
    outname= name[1:8].end
    set output outname
    p word(list,i) matrix with image notitle 
    set output
}


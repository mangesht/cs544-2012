#GNUplot script file for plotting x(t) for different integrations steps
# x0
unset log
unset label
set autoscale

set xlabel "Time (secs)"
set ylabel "Pn(t) - State Probability of n customers"
set terminal gif

set title "State probability Pn(t) as a function of time \nlambda=0.8 mu=1.0 x(t=0)=0 h=0.01"
set output "output-q4-test.gif"
set xrange [0:30]
set yrange [0.0:1.1]
plot "output-4-a.dat" using 1:3 title "P3(t)" with lines, \
    "output-4-a-p2.dat" using 1:3 title "P2(t)" with lines, \
    "output-4-a-p1.dat" using 1:3 title "P1(t)" with lines, \
    "output-4-a-p0.dat" using 1:3 title "P0(t)" with lines, \
    "output-4-a-p4.dat" using 1:3 title "P4(t)" with lines

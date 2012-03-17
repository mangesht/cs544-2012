#GNUplot script file for plotting x(t) for different integrations steps
# x0
unset log
unset label
set autoscale

set xlabel "Time (secs)"
set ylabel "Pn(t) - State Probability of n customers"
set terminal gif

set title "State probability Pn(t) as a function of time \nlambda=0.8 mu=1.0 x(t=0)=0 h=0.01"
set output "output-q4-a.gif"
set xrange [0:30]
set yrange [0.0:0.2]
plot "output-4-a.dat" using 1:3 title "P3(t)" with lines

set title "State probability Pn(t) as a function of time \nlambda=0.6 mu=1.0 x(t=0)=0 h=0.01"
set output "output-q4-b.gif"
set xrange [0:100]
set yrange [0.0:0.35]
plot "output-4-b.dat" using 1:3 title "P1(t)" with lines

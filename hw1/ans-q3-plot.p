#GNUplot script file for plotting x(t) for different integrations steps
# x0
unset log
unset label
set autoscale
set title "Mean pkts in the system as a function of time \nlambda=0.8 mu=1.0 x(t=0)=0"
set xlabel "Time (secs)"
set ylabel "x - mean number of pkts in system"
set xrange [0:200]
set yrange [0.0:5.0]
set terminal gif
set output "output-q3-h.gif"
plot "output-3-h-3.0.dat" using 1:2 title 'h=3.0' with lines, \
     "output-3-h-1.0.dat" using 1:2 title 'h=1.0' with lines, \
     "output-3-h-0.01.dat" using 1:2 title 'h=0.01' with lines, \
     "output-3-h-0.001.dat" using 1:2 title 'h=0.001' with lines, \
     "output-3-h-0.0001.dat" using 1:2 title 'h=0.0001' with lines

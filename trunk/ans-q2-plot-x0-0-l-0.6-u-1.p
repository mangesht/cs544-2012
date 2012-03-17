#GNUplot script file for plotting x(t) for different integrations steps
# x0
unset log
unset label
set autoscale
set title "Mean pkts in the system as a function of time lambda=0.6 mu=1.0 x(t=0)=0"
set xlabel "Time (secs)"
set ylabel "x - mean number of pkts in system"
set yrange [0.0:5.0]
set terminal gif
set output "output-l-0.6-u-1.0-x0-0.gif"
plot "output-x0-0-l-0.6-u-1.0-h-0.1.dat" using 1:2 title 'h=0.1' with lines, \
     "output-x0-0-l-0.6-u-1.0-h-0.1.dat" using 1:2 title 'h=0.2' with lines, \
     "output-x0-0-l-0.6-u-1.0-h-0.1.dat" using 1:2 title 'h=0.3' with lines, \
     "output-x0-0-l-0.6-u-1.0-h-0.1.dat" using 1:2 title 'h=0.4' with lines, \
     "output-x0-0-l-0.6-u-1.0-h-0.1.dat" using 1:2 title 'h=0.5' with lines, \
     "output-x0-0-l-0.6-u-1.0-h-0.1.dat" using 1:2 title 'h=0.6' with lines, \
     "output-x0-0-l-0.6-u-1.0-h-0.1.dat" using 1:2 title 'h=0.7' with lines, \
     "output-x0-0-l-0.6-u-1.0-h-0.1.dat" using 1:2 title 'h=0.8' with lines, \
     "output-x0-0-l-0.6-u-1.0-h-0.1.dat" using 1:2 title 'h=0.9'

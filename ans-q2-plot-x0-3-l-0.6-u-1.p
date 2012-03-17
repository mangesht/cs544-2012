#GNUplot script file for plotting x(t) for different integrations steps
# x0
unset log
unset label
set autoscale
set title "Mean pkts in the system as a function of time x(t=0)=3 lambda=0.6 Mu=1"
set xlabel "Time (secs)"
set ylabel "x - mean number of pkts in system"
set yrange [0.0:5.0]
set terminal gif
set output "output-l-0.6-u-1.0-x0-3.gif"
plot "output-l-0.8-u-1.0-x-0-0-h-1.dat" using 1:2 title 'h=0.1' with lines, \
     "output-l-0.8-u-1.0-x-0-0-h-2.dat" using 1:2 title 'h=0.2' with lines, \
     "output-l-0.8-u-1.0-x-0-0-h-3.dat" using 1:2 title 'h=0.3' with lines, \
     "output-l-0.8-u-1.0-x-0-0-h-4.dat" using 1:2 title 'h=0.4' with lines, \
     "output-l-0.8-u-1.0-x-0-0-h-5.dat" using 1:2 title 'h=0.5' with lines, \
     "output-l-0.8-u-1.0-x-0-0-h-6.dat" using 1:2 title 'h=0.6' with lines, \
     "output-l-0.8-u-1.0-x-0-0-h-7.dat" using 1:2 title 'h=0.7' with lines, \
     "output-l-0.8-u-1.0-x-0-0-h-8.dat" using 1:2 title 'h=0.8' with lines, \
     "output-l-0.8-u-1.0-x-0-0-h-9.dat" using 1:2 title 'h=0.9'


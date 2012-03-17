#GNUplot script file for plotting x(t) for different integrations steps
# x0
unset log
unset label
set autoscale
set title "Mean pkts in the system as a function of time lambda=0.8 mu=1.0 x(t=0)=0"
set xlabel "Time (secs)"
set ylabel "x - mean number of pkts in system"
set yrange [0.0:8.0]
#set terminal gif
#set output "output-l-0.8-u-1.0-small.gif"
plot "out-h-0.001.out" using 1:2 title 'h=0.001' with lines, \
     "out-h-0.0001.out" using 1:2 title 'h=0.0001' with lines, \
     "out-h-0.01.out" using 1:2 title 'h=0.01' with lines, \
     "out-h-0.1.out" using 1:2 title 'h=0.1' with lines

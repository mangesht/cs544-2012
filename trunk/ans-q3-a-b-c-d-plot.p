#GNUplot script file for plotting x(t) for different integrations steps
# x0
unset log
unset label
set autoscale

set xlabel "Time (secs)"
set ylabel "x - mean number of pkts in system"
set terminal gif

set title "Mean pkts in the system as a function of time \nlambda=0.8 mu=1.0 x(t=0)=0 h=0.01"
set output "output-q3-a.gif"
set xrange [0:200]
set yrange [0.0:5.0]
plot "output-3-a.dat" using 1:2 title "" with lines

set title "Mean pkts in the system as a function of time \nlambda=0.8 mu=1.0 x(t=0)=6 h=0.01"
set output "output-q3-b.gif"
set xrange [0:300]
set yrange [0.0:7.0]
plot "output-3-b.dat" using 1:2 title "" with lines

set title "Mean pkts in the system as a function of time \nlambda=0.8 mu=1.0 h=0.01"
set output "output-q3-ab.gif"
set xrange [0:300]
set yrange [0.0:7.0]
plot "output-3-a.dat" using 1:2 title "x(t=0)=0" with lines, \
        "output-3-b.dat" using 1:2 title "x(t=0)=6" with lines


set title "Mean pkts in the system as a function of time \nlambda=0.6 mu=1.0 x(t=0)=0 h=0.01"
set output "output-q3-c.gif"
set xrange [0:85]
set yrange [0.0:2.5]
plot "output-3-c.dat" using 1:2 title "" with lines

set title "Mean pkts in the system as a function of time \nlambda=0.6 mu=1.0 x(t=0)=3 h=0.01"
set output "output-q3-d.gif"
set xrange [0:85]
set yrange [0.0:4.0]
plot "output-3-d.dat" using 1:2 title "" with lines

set title "Mean pkts in the system as a function of time \nlambda=0.6 mu=1.0 h=0.01"
set output "output-q3-cd.gif"
set xrange [0:85]
set yrange [0.0:4.0]
plot "output-3-c.dat" using 1:2 title "x(t=0)=0" with lines, \
        "output-3-d.dat" using 1:2 title "x(t=0)=3" with lines


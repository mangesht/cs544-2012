#GNUplot script file for plotting 
#   Workload#2 throughput as a function of k for the population vector(20, k),k=0,1,2,3,...,15
unset log
unset label
set autoscale
set title "Workload#2 throughput as a function of k for the population vector(20, k),k=0,1,2,3,...,15"
set xlabel "k - Class-2 population"
set ylabel "X - Throughput of Workload#2"
set yrange [0.0:4.0]
set terminal gif
set output "output-Q3.a.500.gif"
plot "output-3.a.500.dat" using 1:2 title 'h=0.1' with lines

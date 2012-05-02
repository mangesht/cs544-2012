#GNUplot script file for plotting 
#   Workload#2 throughput as a function of k for the population vector(20, k),k=0,1,2,3,...,15
unset log
unset label
set autoscale
set title "Workload#2 throughput vs. population vector(20, k),k=0,1,2,3,...,15"
set xlabel "k - Class-2 population (k=0,1,2,...,15)"
set ylabel "X - Throughput of Workload#2"
set yrange [0.0:2.0]
set terminal gif
set output "output-Q3.a.gif"
plot "output-3.a.dat" using 1:2 title 'Workload#1 customers = 20' with lines

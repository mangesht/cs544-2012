#GNUplot script file for plotting 
#  Mean number of Workload#1 customers at CPU as a func. of m for the population vector (m, 15), m=0,1,2,3,..., 20
unset log
unset label
set autoscale
set title "Mean no. of Workload#1 cust. at CPU for the population vector(m,15)"
set xlabel "m - Class-1 population (m=0,1,2,...20)"
set ylabel "X - Mean no. of Workload#1 cust. at CPU"
set yrange [0.0:10.0]
set terminal gif
set output "output-Q3.b.gif"
plot "output-3.b.dat" using 1:2 title 'Workload#2 customers = 15' with lines

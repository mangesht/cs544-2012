#!/bin/sh

# Question 4 : a,b
#
# This script plots Pn(t) as a function of time t
# 

##
#Main body of the script
#
# Generate x(t) for lambda=0.8; mu=1.0; x(t=0)= 0; P3
./runge-kutta -h 0.01 -x 0 -l 0.8 -u 1 -p 3 > output-4-a.dat

# Generate x(t) for lambda=0.6; mu=1.0; x(t=0) = 0; P1
./runge-kutta -h 0.01 -x 0 -l 0.8  -u 1 -p 1 > output-4-b.dat

/usr/bin/gnuplot ans-q4-a-b-plot.p

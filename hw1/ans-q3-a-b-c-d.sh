#!/bin/sh

# Question 3 : a,b,c,d
#
# This script plots x(t) as a function of time t for
# 

##
#Main body of the script
#
# Generate x(t) for lambda=0.8; mu=1.0; x(t=0) = 0
./runge-kutta -h 0.01 -x 0 -l 0.8  -u 1 > output-3-a.dat

# Generate x(t) for lambda=0.8; mu=1.0; x(t=0) = 6
./runge-kutta -h 0.01 -x 6 -l 0.8  -u 1 > output-3-b.dat

# Generate x(t) for lambda=0.6; mu=1.0; x(t=0) = 0
./runge-kutta -h 0.01 -x 0 -l 0.6  -u 1 > output-3-c.dat

# Generate x(t) for lambda=0.6; mu=1.0; x(t=0) = 3
./runge-kutta -h 0.01 -x 3 -l 0.6  -u 1 > output-3-d.dat

/usr/bin/gnuplot ans-q3-a-b-c-d-plot.p

#!/bin/sh

# This script helps us find the best value of h
#
# The script executes the Runge-Kutta method to plot the values of x(t)
# with different values for integration step h = (1.0, 0.1, 0.001, 0.001, 0.0001)
# 
# For this case we chose lamba = 0.8 and mu = 1 and x0 = 0

##
#Main body of the script
#
# Generate x(t) for x0 = 0; lambda=0.8; mu=1.0
./runge-kutta -h 3.0 -x 0 -l 0.8  -u 1 > output-3-h-3.0.dat
./runge-kutta -h 1.0 -x 0 -l 0.8  -u 1 > output-3-h-1.0.dat
./runge-kutta -h 0.01 -x 0 -l 0.8  -u 1 > output-3-h-0.01.dat
./runge-kutta -h 0.001 -x 0 -l 0.8  -u 1 > output-3-h-0.001.dat
./runge-kutta -h 0.0001 -x 0 -l 0.8  -u 1 > output-3-h-0.0001.dat

/usr/bin/gnuplot ans-q3-plot.p

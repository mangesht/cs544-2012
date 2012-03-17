#!/bin/sh

# This script helps us find the best value of h
#
# The script executes the Runge-Kutta method to plot the values of x(t)
# with different values for integration step h = (1.0, 0.1, 0.001, 0.001, 0.0001)
# 
# For this case we chose lamba = 0.8 and mu = 1 and x0 = 0

# Function runit():
# This function executes the runge-kutta method to generate the values of x(t)
# given the values of x(t=0), lambda and Mu
#
# $1 = x --> initial value of x(t) aka x(t=0) 
# $2 = l --> value of lambda 
# $3 = u --> value of Meu 
runit()
{
    h=1
    x=$1
    l="$2"
    u="$3"

    while [ $h -lt 10 ]
    do
        ./runge-kutta-cmd -h '0.'$h -x $x -l $l -u $u > "output-x0-$x-l-$l-u-$u-h-0.$h.dat"
        h=$(($h + 1))
    done
}

##
#Main body of the script
#
# Generate x(t) for x0 = 0; lambda=0.8; mu=1.0
./runge-kutta-cmd -h 1.0 -x 0 -l 0.8  -u 1 > output-3-h-1.0.dat
./runge-kutta-cmd -h 0.1 -x 0 -l 0.8  -u 1 > output-3-h-0.1.dat
./runge-kutta-cmd -h 0.01 -x 0 -l 0.8  -u 1 > output-3-h-0.01.dat
./runge-kutta-cmd -h 0.001 -x 0 -l 0.8  -u 1 > output-3-h-0.001.dat
./runge-kutta-cmd -h 0.0001 -x 0 -l 0.8  -u 1 > output-3-h-0.0001.dat

/usr/bin/gnuplot ans-q3-plot.p

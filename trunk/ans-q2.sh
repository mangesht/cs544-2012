#!/bin/sh


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
        ./runge-kutta-cmd -h '0.'$h -x $x -l $l -u $u > "output-l-$l-u-$u-x-$x-$x-h-$h.dat"
        h=$(($h + 1))
    done
}

##
#Main body of the script
#

# Generate x(t) for x0 = 0; lambda=0.8; mu=1.0
runit 0 "0.8" "1.0" 
# Generate x(t) for x0 = 6; lambda=0.8; mu=1.0
runit 6 "0.8" "1.0" 

# Generate x(t) for x0 = 0; lambda=0.6; mu=1.0
runit 0 "0.6" "1.0" 
# Generate x(t) for x0 = 3; lambda=0.6; mu=1.0
runit 0 "0.6" "1.0" 

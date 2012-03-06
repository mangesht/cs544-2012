#include <stdio.h>

double lamda ;
double mu ; 


double user_def_function(double t0,double x0){
    // lamda    - arriaval rate 
    // mu       - service rate 
    // x0 is initial value for first iteration. This serves as thetai for all the interations 
    double result; 
    // Function specific code goes here

    return result;
}


double calc_next_value(double t0, double x0,double h){
    // This function calculates 
    // thetai + (1 / 6 ) * (k1 + 2*k2 + 2*k3 +k4)*h
    // the value is returned to be used as theta(i+1)
    // lamda    - arriaval rate 
    // mu       - service rate 
    // x0 is initial value for first iteration. This serves as thetai for all the interations 
    //t0    Initial time 
    // h    step size in which time increases
    double result;
    double k1;
    double k2;
    double k3;
    double k4;
    
    // Calcualte k1 , k2 , k3 , k4 
    k1 = user_def_function(t0,x0);
    k2 = user_def_function(t0 + (1/2)*h,x0+(1/2)*k1*h);
    k3 = user_def_function(t0 + (1/2)*h,x0+(1/2)*k2*h);
    k4 = user_def_function(t0+h,x0+k3*h);
    
    result = x0 + (1/6)*(k1+2*k2+2*k3+k4)*h;
    return result;
}
int main(){
     // Local variable declaration 
    double t0 ; 	// Intial time , mostly 0
    double x0 ; 	// Initial mean number of customers at time t0


    return 1;
}

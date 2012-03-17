#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define STABLE_CNT_MAX  50
#define MAX_ITR         10000000

double lambda;
double mu;

/*
 * lamda    - arriaval rate
 * mu       - service rate
 * x_prev   - is the current value. This serves as thetai for all the interations 
 */
double user_def_function(double t0, double x_prev){
    double x_next; 
    
    /*
     * The differential equation for x_next
     */
    x_next = lambda - mu * x_prev / (x_prev + 1);
    //printf("user defined fn returns %f \n",result);
    return x_next;
}

/*
 * This function calculates 
 * thetai + (1 / 6 ) * (k1 + 2*k2 + 2*k3 +k4)*h
 * the value is returned to be used as theta(i+1)
 * lamda    - arriaval rate 
 * mu       - service rate 
 * x_prev is initial value for first iteration. This serves as thetai for all the interations 
 * t0    Initial time 
 * h    step size in which time increases
 */
double calc_next_value(double t0, double x0, double h)
{
    double result;
    double k1;
    double k2;
    double k3;
    double k4;
    
    // Calcualte k1 , k2 , k3 , k4 
    k1 = user_def_function(t0, x0);
    k2 = user_def_function(t0 + (1/2) * h, x0 + (1/2) * k1 * h);
    k3 = user_def_function(t0 + (1/2)* h, x0 + (1/2) * k2 * h);
    k4 = user_def_function(t0 + h, x0 + k3 * h);
    
    result = x0 + ((double)1/6)*(k1+2*k2+2*k3+k4)*h;
    //printf("k1=%f k2=%f k3=%f k4=%f result = %f\n", k1, k2, k3, k4, result);

    return result;
}

/*
 * Round it to the 5th decimal point.
 */
#define MAX_PRECISION 10000000
double roundit(double x)
{
    long tmp = x * MAX_PRECISION;
    double result = ((double) tmp) / MAX_PRECISION;

    return (result);
}

/*
 * find_pn() : This routine returns the probability of n customers in the system
 * given the current mean number of customers in the system.
 *
 * n - Number of customers for which we want to find the probability
 * x - Current mean number of customers in the system.
 *
 * pn = u(t)^n * (1 - u(t)) where u(t) = x(t) / (x(t) + 1)
 */
double find_pn(double x, int n) 
{
    double res, ut;

    ut = x / (x + 1);
    res = (1 - ut) * (pow(ut, n)); 
    return (res);
}

void usage(char *prog)
{
    printf("Usage : %s -h <h_val> -x <x0> -l <lambda_val> -u <mu_val> [-p n]\n", prog);
    printf(" -h <h_val>      : Where h_val is the integration step for Runge-Kutta method\n");
    printf(" -x <x0>         : Where x0 is the initial number of customers in the system at time t=0\n");
    printf(" -l <lambda_val> : Where lambda_val is the Poissonian incoming rate\n");
    printf(" -u <mu_val>     : Where mu_val is the Exponential service rate\n");
    printf(" -p <n>          : Where n is the number of customers for which we need probability P(N=n)\n");
}

int main(int argc, char *argv[])
{
     // Local variable declaration 
    double t0 = 0; 	// Intial time , mostly 0
    double x0 = 0; 	// Initial mean number of customers at time t0
    double h = 1;
    double x1 = 0;
    int i, opt, stable_cnt = 0, n, pflag = 0;

    if (argc != 9 && argc != 11) {
        printf("argc %d\n", argc);
        usage(argv[0]);
        return 1;
    }

    while ((opt = getopt(argc, argv, ":h:x:l:u:p:")) != -1) {
        //printf("opt %c optarg %s\n", opt, optarg);
        switch (opt) {
            case 'h':
                h = strtod(optarg, NULL);
                //printf("optarg %s h = %lf\n", optarg, h);
                break;
            case 'x':
                x0 = strtod(optarg, NULL);
                //printf("optarg %s x0 = %lf\n", optarg, x0);
                //printf("val = %lf\n", strtod(optarg, NULL));
                break;
            case 'l':
                lambda = strtod(optarg, NULL);
                //printf("optarg %s lambda = %f\n", optarg, lambda);
                //printf("val = %lf\n", strtod(optarg, NULL));
                break;
            case 'u':
                mu = strtod(optarg, NULL);
                //printf("optarg %s mu = %f\n", optarg, mu);
                //printf("val = %lf\n", strtod(optarg, NULL));
                break;
            case 'p':
                pflag = 1;
                n = atoi(optarg);
                break;
            default:
                usage(argv[0]);
                return 1;
        }
    }

    //lambda = 0.8; mu = 1.0; x0 = 0; h = 0.1;

    printf("# Average number of pkts in the system as a function of time t\n");
    printf("# Parameters for this plot\n");
    printf("# lambda = %lf mu = %f h = %f x0 = %f\n", lambda, mu, h, x0) ;
    printf("#\n");
    if (pflag) {
        printf("# time \t\tAvg-number-of-pkts\t\t P(n=%d)\n", n);
    } else {
        printf("# time \t\tAvg-number-of-pkts\n");
    }


        if (pflag) {
            printf("%lf\t\t%.7f\t\t%lf\n", t0, x0, find_pn(x0, n));
        } else {
            printf("%lf\t\t%.7f\n", t0, x0);
        }

    /*
     * This loop continues to calculate until the value of x stays stable for
     * STABLE_CNT_MAX iterations or upto MAX_ITR iterations.
     */
    for(i = 0; i < MAX_ITR; i++) {
        x1 = calc_next_value(t0, x0, h);

        if (pflag) {
            printf("%lf\t\t%.7f\t\t%lf\n", t0, x1, find_pn(x1, n));
        } else {
            printf("%lf\t\t%.7f\n", t0, x1);
        }

        //printf("iter %d x0 = %f x1 = %f stable_cnt = %d\n", i, x0, x1, stable_cnt);
        if (roundit(x0) == roundit(x1)) {
            stable_cnt++;
            if (stable_cnt >= STABLE_CNT_MAX) {
                printf("Breaking early...\n");
                break;
            }
        } else {
            /*
             * The value of x has not yet stabilized hence we reset the count.
             */
            stable_cnt = 0;
        }

        x0 = x1; 
        t0 = t0 + h;
    }

    return 0;
}

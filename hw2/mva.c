#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
 * The Service-demand array.
 * Each row describes the service demand of one kind of workload. And each
 * column describes the service demand for a queue.
 *
 * Eg. D[0,1] = 0.75 is the service-demand of disk D1 for Workload-1.
 *     Where as, D[1,1] = 0.135 is the service-demand of disk D1 for Workload-2.
 * 
 * The "thinking-time" has been converted to service-demand 1/Z and added as the
 * last column.
 */
float D[2,5] = {0.50,   0.75,   0.40,   0.40,   0.10,
                0.45,   0.135,  0.16.   0.16,   0.20};

typedef struct node {
    float n[5, 2];
} node_t;

node_t nodes[20, 15];

int main(int argc, char *argv[])
{
    int i, j, k;


    return 0;
}

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

#define Q 0
#define U 1
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
float D[2][3] = {0.105,  0.18,   0.0,
                0.375,  0.48,   0.24}; 


/*
 * n[i,r] :
 * i - Number of queue in the QN
 * r - Types of workloads.
 */
typedef struct node {
    float n[3][2];
} node_t;

/*
 * Population vector.
 */
node_t nodes[1+1][1+3];

/*
 * Compute the sum of the given row 
 */
float sum_of_row (int ref_vec_i, int ref_vec_j, int row, int cols)
{
    int j;
    float sum = 0.0;

    for (j = 0; j < cols; j++) {
        sum += nodes[ref_vec_i][ref_vec_j].n[row][j];
    }
    
    return (sum);
}

int main(int argc, char *argv[])
{
    int i, j, q, w;
    int N[2] = {1, 3};
    int nQ = 3; /* Total number of queues in the system */
    int nW = 2; /* Total number of workloads in the system */
    float R[3][2];

    /*
     * We compute rowise. ie.   (0,0),      (0,1),      (0,2),...       (0,N[1])
     *                          (1,0),      (1,1),      (1,2),...       (1,N[1])
     *                          ....
     *                          ....
     *                          (N[0],0),   (N[0],1),   (N[0],2),...    (N[0],N[1])   
     */
    for (i = 0; i <= N[1]; i++) {
        for (j = 0; j <= N[0]; j++) {
            /*
             * Handle special case of the first node and initialize it to zero.
             */
            if (i == 0 && j == 0) {
                for (q = 0; q < nQ; q++) {
                    for (w = 0; w < nW; w++) {
                        nodes[i][j].n[q][w] = 0.0;
                    }
                }
                continue;
            }

            /*
             * For every type to workload compute the following :
             *  - Response time R' for every queue.
             *  - Throughput X
             *  - Mean number of customers n
             */ 
            for (w = 0; w < nW; w++) {
                int ref_vec_i, ref_vec_j;
                float sigmaR = 0, Xr = 0;
                int Nr = 0;

                switch (w) {
                case 0 : ref_vec_i = i - 1;
                         ref_vec_j = j;
                         Nr = i;
                         break;
                case 1 : ref_vec_i = i;
                         ref_vec_j = j - 1;
                         Nr = j;
                }

                for (q = 0; q < nQ; q++) {
                    R[q][w] = D[w][q] * (1 + sum_of_row(ref_vec_i, ref_vec_j, q, nW));
                    sigmaR += R[q][w];

                    printf("(%d, %d) R'[%d][%d] = %lf\n", i, j, q, w, R[q][w]); 
                }

                Xr = Nr / sigmaR; 
                printf("X%d = %lf\n", w, Xr);

                for (q = 0; q < nQ; q++) {
                    nodes[i][j].n[q][w] = Xr * R[q][w];

                    printf("(%d, %d) n[%d][%d] = %lf\n", i, j, i, j, nodes[i][j].n[q][w]);
                }
            }
        }
    }
    return 0;
}

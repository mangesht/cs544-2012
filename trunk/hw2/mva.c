#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define Q 0
#define U 1
/*
 * Enum to describe the type of queue or resource.
 */
typedef enum res_type {
    DELAY_RESOURCE,
    QUEUEING_RESOURCE 
} res_type_t;

/*
 * n[i,r] :
 * i - Number of queues in the QN
 * r - Types of workloads.
 */
typedef struct node {
    float n[5][2];
} node_t;

/*
 * The following array describes the type of the resources in the QN.
 */
res_type_t res_type[5] = {  QUEUEING_RESOURCE,  /* CPU */
                            QUEUEING_RESOURCE,  /* D1 */
                            QUEUEING_RESOURCE,  /* D2 */
                            QUEUEING_RESOURCE,  /* D3 */
                            DELAY_RESOURCE      /* Thinking terminals pool */
                        };

/*
 * Population vector.
 */
node_t nodes[1 + 20][1 + 15];

char workload_str[2] = {'1', '2'};

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
float D[2][5] = {   0.50,   0.75,   0.40,   0.40,   10.0,   /* Service-demand for Workload-1 */
                    0.45,   0.135,  0.16,   0.16,   5.0};   /* Service-demand for Workload-2 */

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
    int N[2] = {20, 15};
    int nQ = 5; /* Total number of queues in the system */
    int nW = 2; /* Total number of workloads in the system */
    float R[5][2];

    /*
     * We compute rowise. ie.   (0,0),      (0,1),      (0,2),...       (0,N[1])
     *                          (1,0),      (1,1),      (1,2),...       (1,N[1])
     *                          ....
     *                          ....
     *                          (N[0],0),   (N[0],1),   (N[0],2),...    (N[0],N[1])   
     */
    for (i = 0; i <= N[0]; i++) {
        for (j = 0; j <= N[1]; j++) {
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

                /*
                 * If there are no queries or updates then don't compute for
                 * them.
                 */
                if ((w == 0 && i == 0) || (w == 1 && j == 0)) {
                    nodes[i][j].n[q][w] = 0.0;
                    continue;
                }

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
                    if (res_type[q] == QUEUEING_RESOURCE) {
                        R[q][w] = D[w][q] * (1 + sum_of_row(ref_vec_i, ref_vec_j, q, nW));
                    } else {
                        R[q][w] = D[w][q];
                    }

                    sigmaR += R[q][w];

                    /*
                    printf("ref_vec_i = %d ref_vec_j= %d q = %d nW = %d sum = %lf\n",
                            ref_vec_i, ref_vec_j, q, nW, sum_of_row(ref_vec_i, ref_vec_j, q, nW)); 
                    printf("(%d, %d) D[%d][%d] = %lf sum\n", i, j, w, q, D[w][q]); 
                    printf("(%d, %d) R'[%d][%d] = %lf\n", i, j, q, w, R[q][w]); 
                    */
                }

                Xr = Nr / sigmaR; 
                printf("X%c(%d) = %lf\n", workload_str[w], Nr, Xr);

                for (q = 0; q < nQ; q++) {
                    nodes[i][j].n[q][w] = Xr * R[q][w];

                    printf("(%d, %d) n%d,%c = %lf\n", i, j, q+1, workload_str[w], nodes[i][j].n[q][w]);
                }
            }
        }
    }
    return 0;
}

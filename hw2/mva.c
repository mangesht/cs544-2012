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

#define NUM_QUEUES  5
#define NUM_CLASSES 2
/*
 * Every element of the population vector is represented by one node_t
 * structure.
 *
 * n[i,r]   : Mean number of customers at Queue-i, Class-r.
 * X[r]     : Throughput of workload-class r 
 * i - Number of queues in the QN
 * r - Types of workloads (workload class).
 */
typedef struct node {
    float n[NUM_QUEUES][NUM_CLASSES];   /* Mean number of customers at Queue-i, Class-r */ 
    float X[NUM_CLASSES];               /* Throughput of workload-class r */ 
} node_t;

/*
 * The following array describes the type of the resources in the QN.
 */
res_type_t res_type[NUM_QUEUES] = { QUEUEING_RESOURCE,  /* CPU */
                                    QUEUEING_RESOURCE,  /* D1 */
                                    QUEUEING_RESOURCE,  /* D2 */
                                    QUEUEING_RESOURCE,  /* D3 */
                                    DELAY_RESOURCE      /* Thinking terminals pool */
                                };

#define CLASS_1_POPLN   20      /* Population of Class 1 */
#define CLASS_2_POPLN   15      /* Population of Class 2 */

/*
 * Population vector.
 */
node_t nodes[1 + CLASS_1_POPLN][1 + CLASS_2_POPLN];

/*
 * Workload names.
 */
char *workload_str[NUM_CLASSES] = {"w1", "w2"};

/*
 * Resource/Queue names
 */
char *Q_str[NUM_QUEUES] = {"CPU", "D1", "D2", "D3", "TTP"};

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
float D[NUM_CLASSES][NUM_QUEUES] = {
                0.50,   0.075,   0.40,   0.40,   10.0,   /* Service-demand for Workload-1 */
                0.45,   0.135,  0.16,   0.16,   5.0     /* Service-demand for Workload-2 */
        };

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
float sum_of_mean_cust (int ref_vec_i, int ref_vec_j, int row, int ncols)
{
    int j;
    float sum = 0.0;

    for (j = 0; j < ncols; j++) {
        sum += nodes[ref_vec_i][ref_vec_j].n[row][j];
    }
    
    return (sum);
}

int main(int argc, char *argv[])
{
    int i, j, q, r;
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
    for (i = 0; i <= CLASS_1_POPLN; i++) {
        for (j = 0; j <= CLASS_2_POPLN; j++) {
            printf("Iteration(%d, %d)\n", i, j);
            /*
             * Handle special case of the first node and initialize it to zero.
             */
            if (i == 0 && j == 0) {
                for (q = 0; q < NUM_QUEUES; q++) {
                    for (r = 0; r < NUM_CLASSES; r++) {
                        nodes[i][j].n[q][r] = 0.0;
                    }
                }
                printf("\t\tSkipping\n");
                continue;
            }

            /*
             * For every workload-class compute the following :
             *  - Response time R' for every queue.
             *  - Throughput X
             *  - Mean number of customers n
             */ 
            for (r = 0; r < NUM_CLASSES; r++) {
                int ref_vec_i, ref_vec_j;
                float sigmaR = 0, Xr = 0;
                int Nr = 0;

                printf("\tWorkload-class %s\n", workload_str[r]);
                /*
                 * If there are no queries or updates then don't compute for
                 * them.
                 */
                if ((r == 0 && i == 0) || (r == 1 && j == 0)) {
                    nodes[i][j].n[q][r] = 0.0;
                    printf("\t\tSkipping\n");
                    continue;
                }

                /*
                 * Find the reference vector to use for this workload class
                 */
                switch (r) {
                case 0 : ref_vec_i = i - 1;
                         ref_vec_j = j;
                         Nr = i;
                         break;
                case 1 : ref_vec_i = i;
                         ref_vec_j = j - 1;
                         Nr = j;
                }

                /*
                 * Compute the Resdidence times for this workload class for all
                 * the queues.
                 */
                for (q = 0; q < NUM_QUEUES; q++) {
                    if (res_type[q] == QUEUEING_RESOURCE) {
                        R[q][r] = D[r][q] * (1 + sum_of_mean_cust(ref_vec_i, ref_vec_j, q, NUM_CLASSES));
                    } else {
                        R[q][r] = D[r][q];
                    }

                    sigmaR += R[q][r];

                    /*
                    printf("ref_vec_i = %d ref_vec_j= %d q = %d NUM_CLASSES = %d sum = %lf\n",
                            ref_vec_i, ref_vec_j, q, NUM_CLASSES, sum_of_row(ref_vec_i, ref_vec_j, q, NUM_CLASSES)); 
                    printf("(%d, %d) D[%d][%d] = %lf sum\n", i, j, r, q, D[r][q]); 
                    */
                    printf("\t\tR'%s,%s(%d,%d) = %lf\n", Q_str[q], workload_str[r], i, j, R[q][r]); 
                }

                printf("\t\tRo,%s(%d,%d) = %lf\n", workload_str[r], i, j, sigmaR); 

                /*
                 * Compute the throughput X for this workload-class
                 */
                nodes[i][j].X[r] = Nr / sigmaR; 
                printf("\t\tXo,%s(%d,%d) = %lf\n", workload_str[r], i, j, nodes[i][j].X[r]);

                /*
                 * Compute the mean-number-of-customers n for all Queues for
                 * this workload-class.
                 */
                for (q = 0; q < NUM_QUEUES; q++) {
                    nodes[i][j].n[q][r] = nodes[i][j].X[r] * R[q][r];

                    printf("\t\tn%s,%s(%d,%d) = %lf\n", Q_str[q], workload_str[r], i, j, nodes[i][j].n[q][r]);
                }
            }

            /*
             * Compute the Mean-number-of-customers-at-each-device.
             */
            for (q = 0; q < NUM_QUEUES; q++) {
                printf("\tn%s(%d,%d) = %lf\n", Q_str[q], i, j, nodes[i][j].n[q][0] + nodes[i][j].n[q][1]);
            }
        }
    }


    printf("Q.3.a:Workload#2 throughput as a function of k for the population vector(20, k),k=0,1,2,3,...,15\n");
    printf("k\tXo,w2\n");
    for (i = 20, j = 0; j <= CLASS_2_POPLN; j++) {
        printf("%d\t%lf\n", j, nodes[i][j].X[1]);
    }

    printf("Q.3.b:Mean number of Workload#1 customers at CPU as a func. of m for the population vector (m, 15), m=0,1,2,3,..., 20\n");
    printf("m\tnCPU,w1\n");
    for (i = 0, j = 15; i <= CLASS_1_POPLN; i++) {
        printf("%d\t%lf\n", i, nodes[i][j].n[0][0]);
    }


    return 0;
}

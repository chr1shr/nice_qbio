#include "wri-fish.hh"

#ifdef _OPENMP
#include "omp.h"
inline int thread_num() {
    return omp_get_thread_num();
}
#else
inline int thread_num() {
    return 0;
}
#endif

// The total population size
const int N=1000;

// The maximum number of generations
const int Tmax=1000;

// The number of random samples to perform
const int nsims=100000;

int main() {
    int nfix,nlose;

    // Loop over a variety of fitnesses
    for(double s=0;s<2.01;s+=0.02) {
        nfix=nlose=0;

        // Create a number of different threads. Each gets its own
        // Wright-Fisher model with a random number generator with a different
        // initial seed
#pragma omp parallel
        {
            wright_fisher wf(1000,2000,omp_get_thread_num()+1);

            // Perform a number of trials, which are split among the threads
#pragma omp for reduction(+:nfix,nlose)
            for(int i=0;i<nsims;i++) {

                // Count the number of times that the mutation fixes or
                // is removed
                int e=wf.end_population(1,s);
                if(e==0) nlose++;
                else if(e==N) nfix++;
            }
        }

        // Print the probability of fixing
        printf("%g %d %d %g\n",s,nlose,nfix,nfix/double(nfix+nlose));
    }
}

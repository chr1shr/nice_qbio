#include "wri-fish.hh"

#include <gsl/gsl_randist.h>

/** The class constructor sets constants and initializes the GSL random number
 * generator.
 * \param[in] N_ the total population size.
 * \param[in] Tmax_ the maximum number of generations.
 * \param[in] seed a seed for the random number generator. */
wright_fisher::wright_fisher(int N_,int Tmax_,int seed) : N(N_), Ninv(1./N),
    Tmax(Tmax_), rng(gsl_rng_alloc(gsl_rng_taus)) {
    gsl_rng_set(rng,seed);
}

/** The class destructor frees the dynamically allocated random number
 * generator. */
wright_fisher::~wright_fisher() {
    gsl_rng_free(rng);
}

/** Computes the end population of individuals with a fitness of s.
 * \param[in] init_n the initial number of individuals in this population.
 * \param[in] s the fitness.
 * \return The end population. */
int wright_fisher::end_population(int init_n,double s) {
    int n=init_n;
    double p;

    // Perform the generations
    for(int i=0;i<Tmax;i++) {
        p=Ninv*(1+s)*n/(1.+s*Ninv*n);
        n=gsl_ran_binomial(rng,p,N);
        if(n==0||n==N) break;
    }
    return n;
}

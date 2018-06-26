#ifndef WRIGHT_FISHER_HH
#define WRIGHT_FISHER_HH

#include <gsl/gsl_rng.h>

class wright_fisher {
    public:
        /** The total population size. */
        const int N;
        /** The inverse total population size, precomputed for computational
         * efficiency. */
        const double Ninv;
        /** The maximum number of generations. */
        const int Tmax;
        wright_fisher(int N_,int Tmax_,int seed);
        ~wright_fisher();
        int end_population(int init_n,double s);
    private:
        /** A pointer to the GSL random number generator. */
        gsl_rng *rng;
};

#endif

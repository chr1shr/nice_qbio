import numpy as np

# Population size
N=1000

# Maximum number of generations
Tmax=1000

# Number of simulations
nsims=1000

# Function to compute the population that has the mutation after a number of
# generations
def end_population(init_n,s):

    # Initial population that has the mutation
    n=init_n

    # Simulate a number of generations
    for j in xrange(Tmax):
        p=float(n)/N*(1+s)/(1.+s*n/N)
        n=np.random.binomial(N,p,1)[0]

        # Check if we have either zero or N individuals. In either case, we can
        # terminate early
        if n==0 or n==N:
            break
    return n

# Test a range of different fitnesses
for s in np.linspace(0,1,41):

    # Initialize counters
    nfix=0;nlose=0

    # Initialize the number of individuals that have the mutation
    init_n=1
    #init_n=int(round((1.+s)/((1./N)*s+1)))
    
    # Perform a number of trials with this fitness
    for i in xrange(1000):
        e=end_population(init_n,s)
        if e==0:
            nlose+=1
        elif e==N:
            nfix+=1

    # Print the proportion of cases where the mutation fixed 
    print s,init_n,nlose,nfix,float(nfix)/(nfix+nlose)

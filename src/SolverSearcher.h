#ifndef MILESTONE2_SOLVERSEARCHER_H
#define MILESTONE2_SOLVERSEARCHER_H

#include "Solver.h"
#include "Searcher.h"

template<class P, class S> class SolverSearcher : public Solver<P, S> {
private:
    Searcher<P, S>* searcher;

public:
    /****************************************************
    * Function Name:            constructor.
    * The Input:                Searcher<P, S>* s.
    * The Output:
    * The Function Operation:
    ****************************************************/
    SolverSearcher(Searcher<P, S>* s) {
        this->searcher = s;
    }

    /****************************************************
    * Function Name:            solve.
    * The Input:                P problem.
    * The Output:               S solution.
    * The Function Operation:
    ****************************************************/
    S solve(P problem) {
        return this->searcher->search(problem);
    }

    /****************************************************
    * Function Name:            destructor.
    * The Input:
    * The Output:
    * The Function Operation:   delete the searcher.
    ****************************************************/
    ~SolverSearcher() {
        delete(this->searcher);
    }
};

#endif //MILESTONE2_SOLVERSEARCHER_H

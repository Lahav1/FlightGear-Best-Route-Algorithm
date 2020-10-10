#ifndef MILESTONE2_STRINGREVERSER_H
#define MILESTONE2_STRINGREVERSER_H

#include "Solver.h"
#include <string>

using namespace std;

class StringReverser : public Solver<string, string> {
public:
    /****************************************************
    * Function Name:            solve.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    string solve(string problem) {
        string solution;
        for (int i = problem.length() - 1; i >= 0; i--) {
            solution += problem.at(i);
        }
        return solution;
    }
};

#endif //MILESTONE2_STRINGREVERSER_H

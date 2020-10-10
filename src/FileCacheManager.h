#ifndef MILESTONE2_FILECACHEMANAGER_H
#define MILESTONE2_FILECACHEMANAGER_H

#include "CacheManager.h"
#include "Matrix.h"

template <class P, class S>

class FileCacheManager : public CacheManager<P, S> {
private:
    unordered_map<string, string> solutionMap;
    string fileName;

public:
    /****************************************************
    * Function Name:            constructor.
    * The Input:                string problemType : description of problem type.
    * The Output:
    * The Function Operation:
    ****************************************************/
    FileCacheManager(string problemType) {
        this->fileName = problemType + ".txt";
        // load previous information from file.
        loadFromFile();
    }

    /****************************************************
    * Function Name:            loadSolutionToMap.
    * The Input:                P problem, S solution.
    * The Output:
    * The Function Operation:   adds a solution to the map.
    ****************************************************/
    void loadSolutionToMap(P problem, S solution) {
        if (this->fileName == "FindShortestPath.txt") {
            this->solutionMap[problem->toString()] = solution;
        }
    }

    /****************************************************
    * Function Name:            loadFromFile.
    * The Input:
    * The Output:
    * The Function Operation:   loads the information from the file to the map.
    ****************************************************/
    void loadFromFile() {
        vector<string> lines = Lexer::fromTextFileToVectorOfLines(this->fileName);
        for (int i = 0; i < lines.size(); i++) {
            string currentLine = lines[i];
            vector<string> splitted = Lexer::splitStringAfterChar(currentLine, '$');
//            if (this->fileName == "StringReverser.txt") {
//                this->loadSolutionToMap(splitted[0], splitted[1]);
//            }
            if (this->fileName == "FindShortestPath.txt") {
                Matrix* m = new Matrix(splitted[0]);
                this->loadSolutionToMap(m, splitted[1]);
                delete(m);
            }
        }
    }

    /****************************************************
    * Function Name:            loadSolutionToFile.
    * The Input:                P problem, S solution.
    * The Output:
    * The Function Operation:   loads a new solution to the file.
     *                          separate the problem from the solution by "$" sign.
    ****************************************************/
    void loadSolutionToFile(P problem, S solution) {
        ofstream file;
        file.open(this->fileName, ios::app);
        if (file.is_open()) {
            if (this->fileName == "StringReverser.txt") {
                file << problem << "$" << solution << endl;
            }
            if (this->fileName == "FindShortestPath.txt") {
                file << *problem << "$" << solution << endl;
            }
        }
        file.close();
    }

    /****************************************************
    * Function Name:            addNewSolution.
    * The Input:                P problem, S solution.
    * The Output:
    * The Function Operation:   adds a  new solution to the system (to both map and file).
    ****************************************************/
    void addNewSolution(P problem, S solution) {
        if (this->fileName == "FindShortestPath.txt") {
            loadSolutionToMap(problem, solution);
            loadSolutionToFile(problem, solution);
        }
    }

    /****************************************************
    * Function Name:            findSolution.
    * The Input:                P problem.
    * The Output:               string solution.
    * The Function Operation:   returns the solution (.toString()) as it appears in the hash map.
    ****************************************************/
    string findSolution(P problem) {
        return this->solutionMap[problem->toString()];
    }

    /****************************************************
    * Function Name:            getSolverTypes.
    * The Input:
    * The Output:               pair<string, string> : string1 = problem type, string2 = solution type.
    * The Function Operation:
    ****************************************************/
    pair<string, string> getSolverTypes() {
        pair<string, string> p;
        if (this->fileName == "StringReverser.txt") {
            p.first = "string";
            p.second = "string";
        }
        else if (this->fileName == "FindShortestPath.txt") {
            p.first = "matrix";
            p.second = "string";
        }
        return p;
    }

    /****************************************************
    * Function Name:            isSaved.
    * The Input:                P problem.
    * The Output:               true if exists in map, false if not.
    * The Function Operation:
    ****************************************************/
    bool isSaved(P problem) {
        if (this->fileName == "FindShortestPath.txt") {
            if (this->solutionMap.count(problem->toString()) == 1) {
                return true;
            }
        }
//        if (this->fileName == "StringReverser.txt") {
//            if (this->solutionMap.count(problem) == 1) {
//                return true;
//            }
//        }
        return false;
    }
};

#endif //MILESTONE2_FILECACHEMANAGER_H
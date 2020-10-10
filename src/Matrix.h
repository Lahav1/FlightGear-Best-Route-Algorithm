#ifndef MILESTONE2_MATRIX_H
#define MILESTONE2_MATRIX_H

#include "MatrixNode.h"
#include "Lexer.h"
#include "ISearchable.h"
#include <vector>
#include <string>

using namespace std;

class Matrix : public ISearchable<Point*>  {
private:
    vector<vector<State<Point*>*>> nodes;
    Point* start;
    Point* goal;

public:
    /****************************************************
    * Function Name:            constructor.
    * The Input:                string s : a string that represents the matrix.
    * The Output:
    * The Function Operation:   creates a new matrix by a string.
    ****************************************************/
    Matrix(string s) {
        this->nodes = {};
        // separate the line by "|".
        vector<string> v = Lexer::separateStringByChar(s, '|');
        for (int i = 0; i < v.size() - 2; i++) {
            vector<string> temp = Lexer::separateStringByChar(v[i], ',');
            vector<State<Point*>*> current = {};
            for (int j = 0; j < temp.size(); j++) {
                int value = stoi(temp[j]);
                Point* p = new Point(j, i);
                State<Point*>* node = new MatrixNode(p, value);
                current.push_back(node);
            }
            this->nodes.push_back(current);
        }
        // add start point and goal point.
        vector<string> vstart = Lexer::separateStringByChar(v[v.size() - 2], ',');
        this->start = new Point(stoi(vstart[1]), stoi(vstart[0]));
        vector<string> vgoal = Lexer::separateStringByChar(v[v.size() - 1], ',');
        this->goal = new Point(stoi(vgoal[1]), stoi(vgoal[0]));
        //Set aerial distance from every node to goal.
        for(int i = 0; i < nodes.size(); i++) {
            vector<State<Point*>*> currentRow = this->nodes.at(i);
            for(int j = 0; j < currentRow.size(); j++) {
                double heuristicValue =
                        ((MatrixNode*)nodes.at(i).at(j))->calculateManhattanDistance(new MatrixNode(goal, 0));
                nodes.at(i).at(j)->setHeuristicValue(heuristicValue);
            }
        }
    }

    /****************************************************
    * Function Name:            constructor.
    * The Input:                vector<vector<State<Point*>*>> v : nodes vector.
     *                          Point* s : start point.
     *                          Point* g : goal point.
    * The Output:
    * The Function Operation:
    ****************************************************/
    Matrix(vector<vector<State<Point*>*>> v, Point* s, Point* g) {
        this->nodes = v;
        this->start = s;
        this->goal = g;
        for(int i = 0; i < nodes.size(); i++) {
            vector<State<Point*>*> currentRow = this->nodes.at(i);
            for(int j = 0; j < currentRow.size(); j++) {
                double heuristicValue =
                        ((MatrixNode*)nodes.at(i).at(j))->calculateManhattanDistance(new MatrixNode(goal, 0));
                nodes.at(i).at(j)->setHeuristicValue(heuristicValue);
            }
        }
    }

    /****************************************************
    * Function Name:            getNodeAt.
    * The Input:                int col : column num.
     *                          int row : row num.
    * The Output:               State<Point*>* : a pointer to the state of the specified coordinates.
    * The Function Operation:
    ****************************************************/
    State<Point*>* getNodeAt(int col, int row) {
        vector<State<Point*>*> rowv = this->nodes[row];
        State<Point*>* s = rowv[col];
        return s;
    }

    /****************************************************
    * Function Name:            getStart.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    Point* getStart() {
        return this->start;
    }

    /****************************************************
    * Function Name:            getGoal.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    Point* getGoal() {
        return this->goal;
    }

    /****************************************************
    * Function Name:            getMatrixBlock.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    vector<vector<State<Point*>*>> getMatrixBlock() {
        return this->nodes;
    }

    /****************************************************
    * Function Name:            getInitialState.
    * The Input:
    * The Output:               State<Point*>* : initial state.
    * The Function Operation:
    ****************************************************/
    State<Point*>* getInitialState() {
        return getNodeAt(start->getX(), start->getY());
    }

    /****************************************************
    * Function Name:            isGoal.
    * The Input:                State<Point*>* s : a point.
    * The Output:
    * The Function Operation:   returns true if it's the goal state.
    ****************************************************/
    bool isGoal(State<Point*>* s) {
        return (*(s->getState()) == *(this->goal));
    }

    /****************************************************
    * Function Name:            getDimensions.
    * The Input:
    * The Output:               pair<int, int> : first element is width, second is height.
    * The Function Operation:
    ****************************************************/
    pair<int, int> getDimensions() {
        pair<int, int> p;
        // rows
        p.first = this->nodes.size();
        // cols
        p.second = this->nodes.at(0).size();
        return p;
    }

    /****************************************************
    * Function Name:            getPossibleStates.
    * The Input:                State<Point*>* s : state.
    * The Output:               vector<State<Point*>*> : a vector of all possible next-states in path.
    * The Function Operation:   checks if the state is on the frame of the matrix, or if the value is infinite (-1)
     *                          to know the possible directions.
    ****************************************************/
    vector<State<Point*>*> getPossibleStates(State<Point*>* s) {
        vector<State<Point*>*> v = {};
        int sx = s->getState()->getX();
        int sy = s->getState()->getY();
        pair<int, int> dims = this->getDimensions();
        int maxRow = dims.first - 1;
        int maxCol = dims.second - 1;
        // check if the state coordinates are on the matrix'es frame.
        if (sx > 0) {
            double value = ((MatrixNode*) (this->getNodeAt(sx - 1, sy)))->getValue();
            // for each state check if the value is infinite.
            if (value != -1) {
                v.push_back(this->getNodeAt(sx - 1, sy));
            }
        }
        if (sx < maxCol) {
            double value = ((MatrixNode*) (this->getNodeAt(sx + 1, sy)))->getValue();
            if (value != -1) {
                v.push_back(this->getNodeAt(sx + 1, sy));
            }
        }
        if (sy > 0) {
            double value = ((MatrixNode*) (this->getNodeAt(sx, sy - 1)))->getValue();
            if (value != -1) {
                v.push_back(this->getNodeAt(sx, sy - 1));
            }
        }
        if (sy < maxRow) {
            double value = ((MatrixNode*) (this->getNodeAt(sx, sy + 1)))->getValue();
            if (value != -1) {
                v.push_back(this->getNodeAt(sx, sy + 1));
            }
        }
        return v;
    }

    /****************************************************
    * Function Name:            overload operator<<.
    * The Input:                ostream &output, Matrix &m.
    * The Output:
    * The Function Operation:
    ****************************************************/
    friend ostream &operator<< (ostream &output, Matrix &m) {
        output << m.toString();
        return output;
    }

    /****************************************************
    * Function Name:            overload operator==.
    * The Input:                Matrix &other.
    * The Output:
    * The Function Operation:
    ****************************************************/
    bool operator==(Matrix &other) {
        return (this->toString() == other.toString());
    }

    /****************************************************
    * Function Name:            toString.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    string toString() {
        string s = "";
        for (int i = 0; i < this->nodes.size(); i++) {
            vector<State<Point*>*> current = this->nodes[i];
            for (int j = 0; j < current.size(); j++) {
                MatrixNode* node = (MatrixNode*) current[j];
                s += to_string(node->getValue());
                if (j != (current.size() - 1)) {
                    s += ",";
                }
            }
            s += "|";
        }
        s += to_string(this->start->getX()) + "," + to_string(this->start->getY()) + "|" +
                to_string(this->goal->getX()) + "," + to_string(this->goal->getY());
        return s;
    }

    /****************************************************
    * Function Name:            destructor.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    ~Matrix() {
        for (int i = 0; i < this->nodes.size(); i++) {
            vector<State<Point*>*> current = this->nodes[i];
            for (int j = 0; j < current.size(); j++) {
                delete((MatrixNode*) current[j]);
            }
        }
        delete(this->start);
        delete(this->goal);
    }
};

#endif //MILESTONE2_MATRIX_H

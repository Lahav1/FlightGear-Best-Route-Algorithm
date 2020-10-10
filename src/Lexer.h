#ifndef MILESTONE2_LEXER_H
#define MILESTONE2_LEXER_H

#include "vector"
#include "string"
#include "math.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

class Lexer {
public:
    static void reverseString(string* s);
    static double stringToDouble(string s);
    static void fixVarVector(vector<string>* v);
    static bool checkIfContainsEqualSign(string s);
    static vector<string> fromTextFileToVectorOfLines(string path);
    static vector<string> fromLineToVectorOfStrings(string line);
    static vector<string> separateStringByChar(string line, char ch);
    static vector<string> splitBufferToVector(char* buffer);
    static string fromVectorToString(vector<string> v);
    static string fromVectorToStringWithSpaces(vector<string> v);
    static vector<string> expressionStringToFixedVector(string s);
    static void replaceVarNamesByValues(vector<string> *v, map<string, pair<string, double>> varMap);
    static bool keyExist(string key, map <string, pair <string, double>> varMap);
    static char* stringToCharPtr(string s);
    static vector<string> stringToVectorOfChars(string s);
    static void addZerosToVector(vector <string>* originalVector);
    static void separateElements(vector <string>* v);
    static bool checkIfLineContainsChar(string s, char c);
    static vector<string> returnConditionBlock(vector<string> linesVector, int index);
    static void calcMinusSequences(vector<string>* v);
    static vector<string> separateCondition(vector<string> v);
    static vector<string> arrangeOpenServerExpression(vector<string> s);
    static vector<string> removeScopesFromVector(vector<string> v);
    static vector<string> splitStringAfterChar(string s, char ch);
    static string charPtrToString(char* arr);
    static string removeWhiteSpaces(string);
    static bool isNumber(string s);
    static bool isOperator(string s);
    static bool isParenthesis(string s);
    static bool isOperand(string s);
    static bool isVar(string s);
    static bool isWhiteSpace(const char c);
    static string removeLastChar(string s);
    static vector<string> SeaparateBlockByEndline(vector<string> v);
    };

#endif //MILESTONE2_LEXER_H

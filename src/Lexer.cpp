#include "Lexer.h"

/****************************************************
 * Function Name:               fromTextFileToVectorOfLines.
 * The Input:                   string path: the path to the text file that includes the script.
 * The Output:                  vector<string>: each string is a single line in the text file.
 * The Function Operation:      the function separates the line by the end-line char and adds the strings to a vector.
 ****************************************************/
vector<string> Lexer::fromTextFileToVectorOfLines(string path) {
    ifstream file;
    vector<string> v;
    string line;
    file.open(path);
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line != "") {
                v.push_back(line);
            }
        }
    }
    file.close();
    return v;
}

/****************************************************
 * Function Name:               fromLineToVectorOfStrings.
 * The Input:                   string line: a string that represents a single line in the text file.
 * The Output:                  a vector of strings..
 * The Function Operation:      the function separates the line by the spaces, and returns a vector of its' parts.
 ****************************************************/
vector<string> Lexer::fromLineToVectorOfStrings(string line) {
    vector<string> v;
    string word;
    stringstream wordsStreamer (line);
    while (getline(wordsStreamer, word, ' ')) {
        if (word != "") {
            v.push_back(word);
        }
    }
    if (v[0] == "var") {
        fixVarVector(&v);
    }
    return v;
}

/****************************************************
 * Function Name:               removeScopesFromVector
 * The Input:                   vector<string> v : vector of words.
 * The Output:                  vector<string> newv : vector of words after removing all scopes.
 * The Function Operation:      checks if scope appears in each word and if so, remove them and push the word
 *                              into a new vector.
 ****************************************************/
vector<string> Lexer::removeScopesFromVector(vector<string> v) {
    vector<string> newv = {};
    for (int i = 0; i < v.size(); i++) {
        string word = v[i];
        // if word contains open scope, remove it.
        if (checkIfLineContainsChar(word, '{')) {
            string tmp = "";
            for (int i = 1; i < word.length(); i++) {
                tmp += word.at(i);
            }
            word = tmp;
        }
        // if word contains close scope, remove it.
        if (checkIfLineContainsChar(word, '}')) {
            string tmp = "";
            for (int i = 0; i < word.length() - 1; i++) {
                tmp += word.at(i);
            }
            word = tmp;
        }
        if (word != "") {
            newv.push_back(word);
        }
    }
    return newv;
}

/****************************************************
 * Function Name:               reverseString.
 * The Input:                   string.
 * The Output:                  reversed string.
 * The Function Operation:      the function builds a string in reversed order and returns it.
 ****************************************************/
void Lexer::reverseString(string *s) {
    string newString;
    // build a string in reversed order.
    for (int i = s->length() - 1; i >= 0; i--) {
        newString.append(1, s->at(i));
    }
    *s = newString;
}

/****************************************************
 * Function Name:               stringToDouble.
 * The Input:                   string numString.
 * The Output:                  double number.
 * The Function Operation:      the function takes a string that represents a number and returns the
 *                              double number as an integer.
 ****************************************************/
double Lexer::stringToDouble(string numString) {
    // create a vector for the number parts.
    vector<string> v;
    stringstream s (numString);
    string temp;
    while (getline(s, temp, '.')) {
        v.push_back(temp);
    }
    // n1 is the integer part of the number
    string n1 = v.at(0);
    int n1AbsLen = n1.length();
    double tempN1 = 0;
    double num = 0;
    int i = 0;
    bool isPositive = true;
    // if the string starts with '-' it means that the length of the abs number is shorter by one.
    if (n1.at(0) == '-') {
        n1AbsLen --;
        isPositive = false;
    }
    // reverse the string
    reverseString(&n1);
    // multiply each digit by 10 in suitable power.
    for (i = 0; i < n1AbsLen; i++) {
        tempN1 += (n1.at(i) - 48) * pow(10, i);
    }
    if (v.size() == 1) {
        // if the number is not positive we multiply the resuly by (-1).
        if (!isPositive) {
            tempN1 *= -1;
        }
        return tempN1;
    }
    // n2 is the float part of the number
    string n2 = v.at(1);
    double tempN2 = 0;
    reverseString(&n2);
    // calculating the float part of the number.
    for (i = 0; i < n2.length(); i++) {
        tempN2 += (n2.at(i) - 48) * pow(10, i);
    }
    tempN2 /= pow(10, n2.size());
    // adding the integer and the float parts.
    num = tempN1 + tempN2;
    // if the number is not positive we multiply the resuly by (-1).
    if (!isPositive) {
        num *= -1;
    }
    return num;
}

/****************************************************
 * Function Name:           fixVarVector.
 * The Input:               vector<string>* v : a line of var command.
 * The Output:
 * Function Operation:      removes equals sign.
 ****************************************************/
void Lexer::fixVarVector(vector<string>* v) {
    vector<string> newV = {};
    for (int i = 0; i < v->size(); i++) {
        // add each substring which does not contain equals sign to the new vector.
        string temp = v->at(i);
        if (!checkIfContainsEqualSign(temp)) {
            newV.push_back(temp);
        } else {
            stringstream wordsStreamer (temp);
            string sub;
            // remove equals sign from the substring that contains it, then push both parts of it to the vector.
            while (getline(wordsStreamer, sub, '=')) {
                if (sub != "") {
                    newV.push_back(sub);
                }
            }
        }
    }
    *v = newV;
}

/****************************************************
 * Function Name:       splitBufferToVector.
 * The Input:           char* buffer.
 * The Output:          vector of strings.
 * Function Operation:  function getts the buffer of the info received from the server,
 *                      and separates it to a vector of 23 values (in the order they appear in the xml file).
 ****************************************************/
vector<string> Lexer::splitBufferToVector(char *buffer) {
    vector<string> v;
    stringstream s (buffer);
    string temp;
    // split the string by the ',' char.
    while (getline(s, temp, ',')) {
        v.push_back(temp);
    }
    return v;
}

/****************************************************
 * Function Name:       fromVectorToString.
 * The Input:           vector v.
 * The Output:          a string that includes the mathematical expression.
 * Function Operation:  creates an empty string and appends every string in the vector to the new string,
 * from the 3rd element and on (first ones are var, varname).
 ****************************************************/
string Lexer::fromVectorToString(vector<string> v) {
    string s = "";
    // vector is in format of "var varname expression", whe are currently interested in the expression.
    for(int i = 0; i < v.size(); i++) {
        s += v[i];
    }
    return s;
}

/****************************************************
 * Function Name:       fromVectorToStringWithSpaces.
 * The Input:           vector v.
 * The Output:          a string that includes the mathematical expression.
 * Function Operation:  creates an empty string and appends every string in the vector to the new string,
 * from the 3rd element and on (first ones are var, varname).
 ****************************************************/
string Lexer::fromVectorToStringWithSpaces(vector<string> v) {
    string s = "";
    // vector is in format of "var varname expression", whe are currently interested in the expression.
    for(int i = 0; i < v.size(); i++) {
        s += v[i];
        // if it's not the last element, add space after it.
        if (i != v.size() - 1) {
            s += " ";
        }
    }
    return s;
}

/****************************************************
 * Function Name:       expressionStringToFixedVector.
 * The Input:           string s.
 * The Output:          a string that includes the mathematical expression.
 * Function Operation:  creates an empty string and appends every string in the vector to the new string,
 * from the 3rd element and on (first ones are var, varname).
 ****************************************************/
vector<string> Lexer::expressionStringToFixedVector(string s) {
    vector<string> chars = stringToVectorOfChars(s);
    separateElements(&chars);
    addZerosToVector(&chars);
    return chars;
}

/****************************************************
 * Function Name:       separateElements.
 * The Input:           vector <string> v: a vector of strings representing a character.
 * The Output:          null.
 * Function Operation:  The function going character by character in the vector and accumulate all number and variables to one element.
 ****************************************************/
void Lexer::separateElements(vector <string>* v) {
    vector<string> newVector;
    for(int i = 0; i < v->size(); i++) {
        string currentChar = v->at(i);
        if(isParenthesis(currentChar) || (isOperator(currentChar))) {
            newVector.push_back(currentChar);
        }
            //If the element starts with a character - it's a variable.
        else if(((currentChar >= "a") && (currentChar <= "z")) || ((currentChar >= "A") && (currentChar <= "Z"))) {
            string accumulate = "";
            while(((currentChar >= "a") && (currentChar <= "z")) || ((currentChar >= "A") && (currentChar <= "Z")) || isNumber(currentChar)) {
                accumulate += currentChar;
                i++;
                if(i < v->size()) {
                    currentChar = v->at(i);
                } else {
                    break;
                }
            }
            newVector.push_back(accumulate);
            i--;
        }
            //If the element starts with a digit - it's a number
        else if(isNumber(currentChar)) {
            string accmulate = "";
            while(isNumber(currentChar) || currentChar == ".") {
                accmulate += currentChar;
                i++;
                if(i < v->size()) {
                    currentChar = v->at(i);
                } else {
                    break;
                }
            }
            newVector.push_back(accmulate);
            i--;
        }
        else if((currentChar == "!") || (currentChar == "=")) {
            string accumulate = currentChar + v->at(i + 1);
            i++;
            newVector.push_back(accumulate);
        }
        else if ((currentChar == ">") || (currentChar == "<")) {
            string accumulate = currentChar;
            if(v->at(i + 1) == "=") {
                accumulate += v->at(i + 1);
                i++;
            }
            newVector.push_back(accumulate);
        }
    }
    *v = newVector;
}

/****************************************************
 * Function Name:       stringToVectorOfChars.
 * The Input:           string s
 * The Output:          vector<string v> : vector of sepatated chars.
 * Function Operation:  separates s to single chars and return a vector of the chars.
 ****************************************************/
vector<string> Lexer::stringToVectorOfChars(string s) {
    vector<string> v;
    for(int i = 0; i < s.length(); i++) {
        v.push_back(string(1, s.at(i)));
    }
    return v;
}

/****************************************************
 * Function Name:       addZerosToVector.
 * The Input:           vector <string> originalVector: a vector of strings representing a formula.
 * The Output:          null.
 * Function Operation:  The function checks if a number/variable starting with a sign, if it does it adds a zero before it.
 ****************************************************/
void Lexer::addZerosToVector(vector <string>* originalVector) {
    vector <string> v;
    for(int i = 0; i < originalVector->size(); i++) {
        string currentElement = originalVector->at(i);
        //If the formula starts with '-' we add '0' to the beggining of the new vector.
        if((i == 0) && currentElement == "-") {
            v.push_back("0");
            v.push_back("-");
        }
        else if (isParenthesis(currentElement)) {
            v.push_back(currentElement);
        }
            //If the current element is an operator with a preceding parenthesis we add '0'.
        else if (currentElement == "-") {
            if((isParenthesis(originalVector->at(i - 1))) || (isOperator(originalVector->at(i - 1)))) {
                v.push_back("(");
                v.push_back("0");
            }
            //Closing the next number with right parenthesis.
            v.push_back(currentElement);
            v.push_back(originalVector->at(i + 1));
            v.push_back(")");
            i++;
        }
            //If the element is number/variable/operator we push it to the vector.
        else if (isNumber(currentElement) || isVar(currentElement) || isOperator(currentElement)) {
            v.push_back(currentElement);
        }
    }
    *originalVector = v;
}

/****************************************************
 * Function Name:       keyExist.
 * The Input:           string key.
 * The Output:          true if key exists in the variable collection map, false if not.
 * Function Operation:  The function checks if the variable exists in the collection.
 ****************************************************/
bool Lexer::keyExist(string key, map <string, pair <string, double>> varMap) {
    // iterate the map and check if theres a key that matches the given variable name.
    for(auto var : varMap) {
        if(key == var.first) {
            return true;
        }
    }
    return false;
}

/****************************************************
 * Function Name:       replaceVarNamesByValues.
 * The Input:           vector <string> *v, map <string, pair <string, double>>
 * The Output:          Parsed vector.
 * Function Operation:  Function parse all the variables in a vector.
 ****************************************************/
void Lexer::replaceVarNamesByValues(vector<string> *v, map<string, pair<string, double>> varMap) {
    for(int i = 0; i < v->size(); i++) {
        // Checking if the current string in the vector is a variable.
        if(isVar(v->at(i))) {
            // Checking if the key exists
            if(!keyExist(v->at(i), varMap)) {
                string error = "error: '" + v->at(i) + "' was not declared in this scope.";
            } else {
                string value = std::to_string(varMap[v->at(i)].second);
                v->at(i) = value;
            }
        }
    }
    calcMinusSequences(v);
}

/****************************************************
 * Function Name:           stringToCharPtr.
 * The Input:               string s.
 * The Output:              char* array.
 * Function Operation:      function converts a string into an array of chars.
 ****************************************************/
char* Lexer::stringToCharPtr(string s) {
    // allocate a char array with the string's size + 1 for '\0'
    char* arr = new char[s.length() + 1];
    for (int i = 0; i < s.length(); i++) {
        arr[i] = s.at(i);
    }
    // add '\0'
    arr[s.length()] = '\0';
    return arr;
}

/****************************************************
 * Function Name:       calcMinusSequences.
 * The Input:           vector <string> v*: a vector of strings representing a formula with numbers only.
 * The Output:          null.
 * Function Operation:  The function changes all the sequences of two minuses to a plus sign.
 ****************************************************/
void Lexer::calcMinusSequences(vector<string>* v) {
    for (int i = 0; i < v->size() - 1; i++) {
        //Checking if there is a sequence of 2 minuses in the vector (a minus sign followed by a negative number).
        if ((v->at(i) == "-") && (v->at(i + 1).at(0) == '-')) {
            //Change the minus sign to plus sign.
            v->at(i) = "+";
            //Erase the minus from the beginning of the following number.
            v->at(i + 1).erase(0, 1);
        }
    }
}

/****************************************************
 * Function Name:       returnConditionBlock.
 * The Input:           vector<string> linesVector : every string is a line in the text file.
 *                      int index : the index of the first line of the condition block.
 * The Output:          vector<string> v : the whole condition block.
 * Function Operation:  function compares the amounts of open-close scope and returns the whole condition block by it.
 ****************************************************/
vector<string> Lexer::returnConditionBlock(vector<string> linesVector, int index) {
    vector<string> conditionBlock = {};
    int openScopeCount = 0;
    int closeScopeCount = 0;
    conditionBlock.push_back(linesVector[index]);
    // if first line conatains open scope, increase openScopeCount and move to next line.
    if (checkIfLineContainsChar(linesVector[index], '{')) {
        openScopeCount ++;
        index++;
        //  else, next line must be "{", so increase openScopeCount and jump 2 lines ahead.
    } else {
        index ++;
        conditionBlock.push_back(linesVector[index]);
        openScopeCount ++;
        if (checkIfLineContainsChar(linesVector[index], '}')) {
            closeScopeCount++;
        }
        index ++;
    }
    // keep pushing lines to the condition block until openScopeCount is equal to closeScopeCount.
    while (openScopeCount != closeScopeCount) {
        conditionBlock.push_back(linesVector[index]);
        if (checkIfLineContainsChar(linesVector[index], '{')) {
            openScopeCount++;
        }
        if (checkIfLineContainsChar(linesVector[index], '}')) {
            closeScopeCount++;
        }
        index++;
    }
    return conditionBlock;
}

/****************************************************
 * Function Name:       separateCondition.
 * The Input:
 * The Output:
 * Function Operation:
 ****************************************************/
vector<string> Lexer::separateCondition(vector<string> v) {
    vector<string> newVector;
    string accumulate = "";
    int i = 0;
    while(!isOperand(v.at(i))) {
        accumulate += v.at(i);
        i++;
    }
    newVector.push_back(accumulate);
    accumulate = "";
    newVector.push_back(v.at(i));
    i++;
    while(i < v.size()) {
        accumulate += v.at(i);
        i++;
    }
    if (checkIfLineContainsChar(accumulate, '{')) {
        string tmp = "";
        for (int i = 0; i < accumulate.length() - 1; i++) {
            tmp += accumulate.at(i);
        }
        accumulate = tmp;
    }
    newVector.push_back(accumulate);
    return newVector;
}

/****************************************************
 * Function Name:       arrangeOpenServerExpression.
 * The Input:           vector<string> s: vector with no spaces of mathematical expression
 * The Output:          An arranged vector of 2 expressions: port and host.
 * Function Operation:  The function iterates over all the elements in the vector and orgenaize all of the expressions
 *                      by spaces and commas.
 ****************************************************/
vector<string> Lexer::arrangeOpenServerExpression(vector<string> s) {
    vector<string> parameters;
    string temp = "";
    for(int i = 0; i < s.size(); i++) {
        string currentElement = s.at(i);
        //Checking if the current string contains a comma sign. If it does we will seperate the string to it's left and right part.
        if(checkIfLineContainsChar(currentElement, ',')) {
            for(int j = 0; j < currentElement.length(); j++) {
                //We will accumulate all of the characters until the comma.
                if(currentElement.at(j) != ',') {
                    temp += currentElement.at(j);
                } else {
                    //We will push what we got until the comma to the vector if it's not empty.
                    if(temp != "") {
                        parameters.push_back(temp);
                    }
                    temp = "";
                }
            }
            //We will push what we got until the comma to the vector if it's not empty.
            if(temp != "") {
                parameters.push_back(temp);
            }
            temp = "";
        }
            // If the last character on this element and the first character of the next elements are digits they need to be
            // separated.
        else if((i < s.size() - 1) && (isNumber(string(1, currentElement.at(currentElement.length() - 1)))) &&
                (isNumber(string(1, s.at(i + 1).at(0))))) {
            temp += currentElement;
            if(temp != "") {
                parameters.push_back(temp);
            }
            temp = "";
        } else {
            temp += currentElement;
        }
    }
    if(temp != "") {
        parameters.push_back(temp);
    }
    // We will delete all the commas that are in any elements in the vector.
    for(int i = 0; i < parameters.size(); i++) {
        if(checkIfLineContainsChar(parameters.at(i), ',')) {
            temp = "";
            //We will accumulate the part from the left and right of the element and change the element.
            for(int j = 0; j < parameters.at(i).length(); j++) {
                if(parameters.at(i).at(j) != ',') {
                    temp += parameters.at(i).at(j);
                }
            }
            parameters.at(i) = temp;
        }
    }
    return parameters;
}

/****************************************************
 * Function Name:       checkIfContainsEqualSign.
 * The Input:           const string s
 * The Output:          If string contains '=' or not.
 * Function Operation:  Function checks if string contains '=' or not.
 ****************************************************/
bool Lexer::checkIfContainsEqualSign(const string s) {
    return (s.find('=') != string::npos);
}

/****************************************************
 * Function Name:       checkIfLineContainsChar.
 * The Input:           string s, char c
 * The Output:          true if c is in the string s, else false.
 * Function Operation:  The function is going over all the chars in s, and checks if it's in s.
 ****************************************************/
bool Lexer::checkIfLineContainsChar(string s, char c) {
    for (int i = 0; i < s.size(); i++) {
        if (s.at(i) == c) {
            return true;
        }
    }
    return false;
}

/****************************************************
 * Function Name:       isNumber.
 * The Input:           const string s
 * The Output:          if the string represents a number.
 * Function Operation:  Function checks if all the charchters in the string are digits.
 ****************************************************/
bool Lexer::isNumber(const string s) {
    if(s == "-") {
        return false;
    }
    int dec_points = 0;
    for (int i = 0; i < s.length(); i++) {
        if((i > 0) && (s.at(i) == '-')) {
            return false;
        }
        if (((s.at(i) < '0') || (s.at(i) > '9')) && (s.at(i) != '.') && (s.at(i) != '-')) {
            return false;
        }
        if (s.at(i) == '.') {
            dec_points++;
        }
    }
    if(dec_points > 1) {
        return false;
    }
    return true;
}

/****************************************************
 * Function Name:       isVar.
 * The Input:           const string s.
 * The Output:          null.
 * Function Operation:  The function checks if a string is variable.
 ****************************************************/
bool Lexer::isVar(const string s) {
    if(!isNumber(s) && !isOperator(s) && !isParenthesis(s) && !isOperand(s)) {
        return true;
    }
    return false;
}

/****************************************************
 * Function Name:       isOperator.
 * The Input:           const string s
 * The Output:          if the string represents an operator.
 * Function Operation:  Function checks if the char is an operator.
 ****************************************************/
bool Lexer::isOperator(const string s) {
    if((s == "+") || (s == "-") || (s == "*") || (s == "/")) {
        return true;
    }
    return false;
}

/****************************************************
 * Function Name:       isParenthesis.
 * The Input:           string s
 * The Output:          if the string represents a parenthese.
 * Function Operation:  Function checks if the char is a parenthese.
 ****************************************************/
bool Lexer::isParenthesis(const string s) {
    if ((s == ")") || (s == "(")) {
        return true;
    }
    return false;
}

/****************************************************
 * Function Name:       isOperand.
 * The Input:           const string s
 * The Output:          true if s is operands
 * Function Operation:  The function checks if the string equeals to an operand
 ****************************************************/
bool Lexer::isOperand(const string s) {
    if ((s == "<") || (s == ">") || (s == "==") || (s == "!=") || (s == "<=") || (s == ">=")) {
        return true;
    }
    return false;
}

/****************************************************
 * Function Name:           isWhiteSpace.
 * The Input:
 * The Output:
 * Function Operation:
 ****************************************************/
bool Lexer::isWhiteSpace(const char c) {
    bool whiteSpace = false;
    vector<char> whiteSpaces = {' ', '\t', '\n', '\f', '\v', '\r'};
    for(auto w : whiteSpaces) {
        if(c == w) {
            whiteSpace = true;
        }
    }
    return whiteSpace;
}

/****************************************************
* Function Name:
* The Input:
* The Output:
* The Function Operation:
****************************************************/
vector<string> Lexer::splitStringAfterChar(string s, char ch) {
    vector<string> v = {};
    string temp;
    int i = 0;
    while (s.at(i) != ch) {
        temp += s.at(i);
        i++;
    }
    v.push_back(temp);
    temp = "";
    i++;
    while (i != s.length()) {
        temp += s.at(i);
        i++;
    }
    v.push_back(temp);
    return v;
}

/****************************************************
* Function Name:
* The Input:
* The Output:
* The Function Operation:
****************************************************/
string Lexer::charPtrToString(char* arr) {
    string s;
    int i = 0;
    while (arr[i] != '\0') {
        s += arr[i];
        i++;
    }
    return s;
}

/****************************************************
* Function Name:
* The Input:
* The Output:
* The Function Operation:
****************************************************/
string Lexer::removeWhiteSpaces(string s) {
    string news = "";
    for (int i = 0; i < s.size(); i++) {
        if (!isWhiteSpace(s.at(i))) {
            news += s.at(i);
        }
    }
    return news;
}

/****************************************************
 * Function Name:               separateStringByChar.
 * The Input:
 * The Output:
 * The Function Operation:
 ****************************************************/
vector<string> Lexer::separateStringByChar(string line, char ch) {
    vector<string> v;
    string word;
    stringstream wordsStreamer (line);
    while (getline(wordsStreamer, word, ch)) {
        if (word != "") {
            v.push_back(word);
        }
    }
    return v;
}

/****************************************************
 * Function Name:
 * The Input:
 * The Output:
 * The Function Operation:
 ****************************************************/
string Lexer::removeLastChar(string s) {
    string newstring = "";
    for (int i = 0; i < s.size() - 1; i++) {
        newstring += s.at(i);
    }
    return newstring;
}

/****************************************************
 * Function Name:           SeaparateBlockByEndline.
 * The Input:               vector<string> v.
 * The Output:              vector<string>.
 * The Function Operation:
 ****************************************************/
vector<string> Lexer::SeaparateBlockByEndline(vector<string> v) {
    vector<string> newv = {};
    for (int i = 0; i < v.size(); i++) {
        vector<string> temp = Lexer::separateStringByChar(v[i], '\r\n');
        for (int j = 0; j < temp.size(); j++) {
            newv.push_back(temp[j]);
        }
    }
    return newv;
}


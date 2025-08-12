//
//  htmlparser.hpp
//  HTMLParser C++
//
//  Created by Chidume Nnamdi on 10/08/2025.
//

#ifndef htmlparser_hpp
#define htmlparser_hpp

#include <stdio.h>
#include <iostream>
#include "../models/Token.hpp"
#include "Node.h"

using namespace std;

class HTMLParser {
    
public:
    vector<Node> parse(const vector<Token>& tokens);
    
private:
    const vector<Token> getTokenChildren(const vector<Token>& tokens, const string& name, int index);

};

#endif /* htmlparser_hpp */

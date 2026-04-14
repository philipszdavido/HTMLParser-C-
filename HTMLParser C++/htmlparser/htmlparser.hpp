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
    vector<Node*> parse(Node* parent, const vector<Token>& tokens);
    
private:
    const vector<Token> getTokenChildren(const vector<Token>& tokens, const string& name, int index);
    Node* createNode(const string name, const NodeType type, const string textContent);

};

#endif /* htmlparser_hpp */

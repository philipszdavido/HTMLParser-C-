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
    HTMLParser(const string& htmlString): html(htmlString) {};
    vector<Node> parse();
    vector<Token> getTokenChildren(vector<Token> tokens, const string& name, int index);
    
private:
    const string& html;
    
};

#endif /* htmlparser_hpp */

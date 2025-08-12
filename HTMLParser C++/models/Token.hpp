//
//  Token.hpp
//  HTMLParser C++
//
//  Created by Chidume Nnamdi on 10/08/2025.
//

#ifndef Token_hpp
#define Token_hpp

#include <stdio.h>
#include <iostream>
#include "TokenType.h"
#include "../token_attribute_parser/AttributeToken.hpp"

using namespace std;

class Token {
    
public:
    Token(const string& name, const TokenType& token);
    string name;
    TokenType token;
    bool start = false;
    bool end = false;
    bool isVoid = false;
    int index;
    vector<AttributeToken> attributes;
    int endStartTagIndex = -1;
    
};

#endif /* Token_hpp */

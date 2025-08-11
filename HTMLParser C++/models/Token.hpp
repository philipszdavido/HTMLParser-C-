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

using namespace std;

class Token {
    
public:
    Token(const string& name, const TokenType& token);
    string name;
    TokenType token;
    bool start = false;
    bool end = false;
};

#endif /* Token_hpp */

//
//  Tokenizer.hpp
//  HTMLParser C++
//
//  Created by Chidume Nnamdi on 10/08/2025.
//

#ifndef Tokenizer_hpp
#define Tokenizer_hpp

#include <stdio.h>
#include <iostream>
#include "Token.hpp"

using namespace std;

class Tokenizer {

public:
    Tokenizer(const string& htmlString): html(htmlString) {};
    vector<Token> tokenize();
    const char nextChar();
    const char prevChar();
    const string& html;
    int index = -1;
    
};

#endif /* Tokenizer_hpp */

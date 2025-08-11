//
//  main.cpp
//  HTMLParser C++
//
//  Created by Chidume Nnamdi on 10/07/2025.
//

#include <iostream>
#include "tokenizer/Tokenizer.hpp"
#include "overloads/operators.h"
#include "token_attribute_parser/AttributeParser.hpp"

using namespace std;

int main(int argc, const char * argv[]) {

    const string html = "<div class='main header'>Name: <span>Chi</span></div><img />Ha";

    Tokenizer tokenizer(html);

    vector<Token> tokens = tokenizer.tokenize();
    
//    AttributeParser parser;
//    
//    const string attr = "class='main header' style src";
//    
//    vector<AttributeToken> attrTokens = parser.parseAttribute(attr);
//    
//    for(AttributeToken t : attrTokens) {
//        cout << t.value << " : " << t.key << endl;
//    }
    
    for (Token token : tokens) {
        cout << token << endl;
    }
        
    return 0;
    
}

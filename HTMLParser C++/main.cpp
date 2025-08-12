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
#include "htmlparser/htmlparser.hpp"

using namespace std;

int main(int argc, const char * argv[]) {

    const string _html = "<div class='main header'>Name: <span>Chi</span></div><img />Ha";
    std::string html = R"(
            <html>
                <head><title>Hello</title></head>
                <body>
                    <h1 class="title">Welcome!</h1>
                    <p id="intro">This is a test.</p>
                </body>
            </html>
        )";
    
    Tokenizer tokenizer(html);

    vector<Token> tokens = tokenizer.tokenize();
    
    HTMLParser h;
    vector<Node> nodes = h.parse(tokens);
        
    for (Node node : nodes) {
        cout << node << endl;
    }

    
//    AttributeParser parser;
//    
//    const string attr = "class='main header' style src";
//    
//    vector<AttributeToken> attrTokens = parser.parseAttribute(attr);
//    
//    for(AttributeToken t : attrTokens) {
//        cout << t.value << " : " << t.key << endl;
//    }
    
//    for (Token token : tokens) {
//        cout << token << endl;
//    }
        
    return 0;
    
}

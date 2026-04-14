//
//  AttributeParser.cpp
//  HTMLParser C++
//
//  Created by Chidume Nnamdi on 11/08/2025.
//

#include <ostream>
#include <iostream>
#include <string>
#include "AttributeParser.hpp"
#include "AttributeToken.hpp"

using namespace std;
constexpr char DOUBLE_QUOTE = '"';
constexpr char SINGLE_QUOTE = '\'';

vector<AttributeToken> AttributeParser::parseAttribute(const string& attributeString) {
    
    vector<AttributeToken> attributeTokens;
    
    vector<string> tokens;
    
    string el;
    
    bool isValue = false;
    bool start = false;
    
    for (int i = 0; i < attributeString.length(); ++i) {
        
        const char character = attributeString[i];
                
        if(isValue) {

            if (start) {

                if(character == SINGLE_QUOTE || character == DOUBLE_QUOTE ) {

                    string lastToken = tokens.back();
                    tokens.pop_back();
                    
                    AttributeToken attrToken(lastToken, el);
                                        
                    attributeTokens.push_back(attrToken);
                    
                    start = false;
                    isValue = false;
                    el = "";
                    continue;
                    
                }
                
                el += character;
                continue;
                
            }
            
            if (character == SINGLE_QUOTE || character == DOUBLE_QUOTE) {
                start = true;
                continue;
            }
            
            isValue = false;
            start = false;
            
        }
        
        if(character == '=') {
            
            tokens.push_back(el);
            el = "";
            isValue = true;
            continue;
            
        }
        
        if (character == ' ') {
            
            AttributeToken attrToken(el, "");
            attributeTokens.push_back(attrToken);

            el = "";
            continue;
            
        }
        
        el += character;
        
    }

    AttributeToken attrToken(el, "");
    attributeTokens.push_back(attrToken);
    
    el = "";
    
    return attributeTokens;
    
}

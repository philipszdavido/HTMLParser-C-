//
//  Tokenizer.cpp
//  HTMLParser C++
//
//  Created by Chidume Nnamdi on 10/08/2025.
//

#include "Tokenizer.hpp"

vector<Token> Tokenizer::tokenize() {
    
    vector<Token> data;
    
    bool isTag = false;
    bool endTag = false;
    bool isVoid = false;
    
    string el;
    
    cout << html << endl;
    
    for(unsigned char character : html) {
        
        index++;
        
        if (character == '<') {
            
            isTag = true;
                
            Token token(el, TokenType::Text);
            token.index = index;
            data.push_back(token);
            el.clear();

            continue;
            
        }
        
        if (isTag) {
            
            if (character == '/' && nextChar() == '>') {
                isVoid = true;
                continue;
            }
            
            if(character == '>') {
                
                Token token(el, TokenType::Element);
                token.index = index;

                if(isVoid) {

                    token.isVoid = true;
                    token.start = true;
                    token.end = true;
                    
                } else {
                                        
                    if (endTag) {
                        token.end = true;
                    } else {
                        token.start = true;
                    }
                    
                }

                data.push_back(token);
                el.clear();
                
                isTag = false;
                endTag = false;
                isVoid = false;
                
                continue;
                
            }
            
            if (character == '/' && prevChar() == '<') {
                
                endTag = true;
                
            } else {
                
                el += character;
            }
            
            continue;
            
        }
        
        el += character;
        
    }
    
    Token token(el, TokenType::Text);
    token.index = index;

    data.push_back(token);
    el.clear();

    return data;
    
};

const char Tokenizer::nextChar() {
    return html[index + 1];
}

const char Tokenizer::prevChar() {
    return html[index - 1];
}

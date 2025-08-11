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
                
            Token t(el, TokenType::Text);
            t.index = index;
            data.push_back(t);
            el.clear();

            continue;
        }
        
        if (isTag) {
            
            if (character == '/' && nextChar() == '>') {
                isVoid = true;
                continue;
            }
            
            if(character == '>') {
                
                Token t(el, TokenType::Element);
                t.index = index;

                if(isVoid) {

                    t.start = true;
                    t.end = true;
                    
                } else {
                    
                    if (endTag) {
                        t.end = true;
                    } else {
                        t.start = true;
                    }
                    
                }

                data.push_back(t);
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
    
    Token t(el, TokenType::Text);
    t.index = index;

    data.push_back(t);
    el.clear();

    return data;
    
};

const char Tokenizer::nextChar() {
    return html[index + 1];
}

const char Tokenizer::prevChar() {
    return html[index - 1];
}

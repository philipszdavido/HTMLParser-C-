//
//  Tokenizer.cpp
//  HTMLParser C++
//
//  Created by Chidume Nnamdi on 10/08/2025.
//

#include "Tokenizer.hpp"
#include "../token_attribute_parser/AttributeParser.hpp"

vector<Token> Tokenizer::tokenize() {
    
    vector<Token> data;
    
    bool isTag = false;
    bool endTag = false;
    bool isVoid = false;
    bool collectAttribute = false;
    string attribute;
    
    string el;
    
    cout << html << endl;
    
    for(const char& character : html) {
        
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
            
            if (!collectAttribute) {
                if(character == ' ') {
                    // we collect attributes
                    collectAttribute = true;
                    continue;
                }
            }
                        
            if (character == '/' && nextChar() == '>') {
                isVoid = true;
                collectAttribute = false;

                continue;
            }
            
            if (collectAttribute) {
                
                attribute += character;
                
                if(nextChar() == '>') {
                    collectAttribute = false;
                }
                
                continue;
                
            }

            
            if(character == '>') {
                
                
                Token token(el, TokenType::Element);
                token.index = index;

                
                AttributeParser attributeParser;
                const string& attr = attribute;
                vector<AttributeToken> attributes = attributeParser.parseAttribute(attr);

                attribute = "";

                token.attributes = attributes;

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

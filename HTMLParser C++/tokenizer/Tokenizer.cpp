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
    bool isComment = false;
    bool isDocType = false;
    
    int endStartTagIndex = -1;
    
    string attribute;
    string el;
        
    for (index = 0; index <= (size() - 1); index++) {
        
        const char& character = currentChar();
        
        if (isComment) {
                        
            if (character == '-' &&
                index + 2 < size() &&
                peekChar(1) == '-' &&
                peekChar(2) == '>') {
                                
                index += 2;
                Token token(el, TokenType::Comment);
                token.index = index;

                data.push_back(token);

                el.clear();

                isComment = false;
            } else el += character;
            
            continue;
            
        }
        
        if (character == '<') {
            
            // test for DOCTYPE
            if (isDOCTYPE()) {
                isDocType = true;
                continue;
            }
            
            if (index + 3 < html.size() &&
                peekChar(1) == '!' &&
                peekChar(2) == '-' &&
                peekChar(3) == '-') {
                
                isComment = true;
                index += 3;
                continue;
            }
            
            isTag = true;
            
            if (!el.empty()) {
                Token token(el, TokenType::Text);
                token.index = index;
                data.push_back(token);
                el.clear();
            }
            
            if (index + 1 < size() && peekChar(1) == '/') {
                endTag = true;
                index++;
            }
            
            continue;
        }
        
        if (isDocType) {
            if (character == '>') {
                isDocType = false;
                
                Token token(el, TokenType::DocType);
                token.index = index;
                data.push_back(token);

                el.clear();
                continue;
            }
            el += character;
            continue;
        }
        
        if (isTag) {
            
            if (!collectAttribute && character == ' ') {
                collectAttribute = true;
                continue;
            }
            
            if (character == '/' &&
                index + 1 < size() &&
                peekChar(1) == '>') {
                
                isVoid = true;
                collectAttribute = false;
                index++;
                continue;
            }
            
            if (collectAttribute) {
                attribute += character;
                
                if (index + 1 < size() && peekChar(1) == '>') {
                    collectAttribute = false;
                }
                
                continue;
            }
            
            if (character == '>') {
                
                Token token(el, TokenType::Element);
                token.index = index;
                
                AttributeParser attributeParser;
                vector<AttributeToken> attributes =
                    attributeParser.parseAttribute(attribute);
                
                token.attributes = attributes;
                attribute.clear();
                
                if (isVoid) {
                    token.isVoid = true;
                    token.start = true;
                    token.end = true;
                } else {
                    if (endTag) {
                        token.end = true;
                        token.endStartTagIndex = endStartTagIndex;
                        endStartTagIndex = -1;
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
            
            el += character;
            continue;
        }
        
        el += character;
    }
    
    if (!el.empty()) {
        Token token(el, TokenType::Text);
        token.index = (int)size();
        data.push_back(token);
    }

    return data;
}

const char Tokenizer::nextChar() {
    return html[index + 1];
}

const char Tokenizer::prevChar() {
    return html[index - 1];
}

const char Tokenizer::peekChar(int value) {
    return html[index + value];
}

const char Tokenizer::currentChar() {
    return html[index];
}

const int Tokenizer::size() {
    return (int)html.size();
}

bool Tokenizer::isDOCTYPE() {
    string DOCTYPE = "!DOCTYPE";
    string temp = "";

    int i = index + 1;
    char c = currentChar();
    
    while(c != ' ') {
                
        if (temp == DOCTYPE) {
            index += DOCTYPE.size();
            return true;
        }
        
        c = html[i];
        temp += c;
        
        i++;
    }
    
    return false;
    
}

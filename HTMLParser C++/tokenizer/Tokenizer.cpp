//
//  Tokenizer.cpp
//  HTMLParser C++
//
//  Created by Chidume Nnamdi on 10/08/2025.
//

#include "Tokenizer.hpp"
#include "../token_attribute_parser/AttributeParser/AttributeParser.hpp"

enum State {
    IsTagOpen,
    IsComment,
    IsDocType
};

const char GT = '>';
const char LT = '<';
const char HYPHEN = '-';
const char FORWARD_SLASH = '/';
const char EMPTY = ' ';

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
                        
            if (character == HYPHEN &&
                index + 2 < size() &&
                peekChar(1) == HYPHEN &&
                peekChar(2) == GT) {
                                
                index += 2;
                Token token(el, TokenType::Comment);
                token.index = index;

                data.push_back(token);

                el.clear();

                isComment = false;
            } else el += character;
            
            continue;
            
        }
        
        if (character == LT && !isTag && !isComment && !isDocType) {
            
            // test for DOCTYPE
            if (isDOCTYPE()) {
                isDocType = true;
                continue;
            }
            
            if (index + 3 < html.size() &&
                peekChar(1) == '!' &&
                peekChar(2) == HYPHEN &&
                peekChar(3) == HYPHEN) {
                
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
            
            if (index + 1 < size() && peekChar(1) == FORWARD_SLASH) {
                endTag = true;
                index++;
            }
            
            continue;
        }
        
        if (isDocType) {
            if (character == GT) {
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
            
            if (!collectAttribute && character == EMPTY) {
                collectAttribute = true;
                continue;
            }
            
            if (character == FORWARD_SLASH &&
                index + 1 < size() &&
                peekChar(1) == GT) {
                
                isVoid = true;
                collectAttribute = false;
                index++;
                continue;
            }
            
            if (collectAttribute) {
                attribute += character;
                
                if (index + 1 < size() && peekChar(1) == GT) {
                    collectAttribute = false;
                }
                
                continue;
            }
            
            if (character == GT) {
                
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
    
    int count = 0;
    
    while(count != DOCTYPE.size()) {
                        
        if (i >= size()) {
            break;
        }
        
        c = html[i];
        temp += c;
        
        count++;
    }
    
    if (temp == DOCTYPE) {
        return true;
    }
    
    return false;
    
}

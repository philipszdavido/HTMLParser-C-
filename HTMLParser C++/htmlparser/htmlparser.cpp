//
//  htmlparser.cpp
//  HTMLParser C++
//
//  Created by Chidume Nnamdi on 10/08/2025.
//

#include "htmlparser.hpp"
#include "../tokenizer/Tokenizer.hpp"
#include "../overloads/operators.h"
#include <iostream>

using namespace std;

vector<Node> HTMLParser::parse() {
    
    Tokenizer tokenizer(html);
    vector<Token> tokens = tokenizer.tokenize();
    
    vector<Node> nodes;
    
    for (int i = 0; i < tokens.size(); ++i) {
        
        const Token token = tokens[i];
        
        if(token.token == TokenType::Text) {
            
            nodes.push_back(Node("", NodeType::Text, token.name));
            
        } else if (token.token == TokenType::Element) {
            
            if(token.isVoid) {
                
                nodes.push_back(Node(token.name, NodeType::Element, ""));
                
            }
            
            // search if element has children
            vector<Token> children = getTokenChildren(tokens, token.name, i + 1);

            for (Token t : children) {
                cout << t << endl;
            }
            
            
        }
        
    }
    
    return nodes;
    
}

vector<Token> HTMLParser::getTokenChildren(vector<Token> tokens, const string& name, int index) {

    int seen = 0;
    vector<Token> children;
    
    for (int i = index; i < tokens.size(); ++i) {

        const Token token = tokens[i];
        
        if(token.name == name) {
            
            if(token.start) {
                seen++;
            }
            
            if (token.end) {
                seen--;
            }
            
            if(seen == 0) {
                break;
            }
            
        }
        
        children.push_back(token);
        
        
    }
    
    return children;
    
}

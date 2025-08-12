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

vector<Node> HTMLParser::parse(const vector<Token>& tokens) {
        
    vector<Node> nodes;
    
    for (int i = 0; i < tokens.size(); ++i) {
        
        const Token token = tokens[i];
        
        if(token.token == TokenType::Text) {
            
            nodes.push_back(Node("", NodeType::Text, token.name));
            
        } else if (token.token == TokenType::Element) {
            
            if(token.isVoid) {
                
                nodes.push_back(Node(token.name, NodeType::Element, ""));
                continue;
                
            }
            
            // search if element has children
            const vector<Token>& children = getTokenChildren(tokens, token.name, i + 1);
            Node node = Node(token.name, NodeType::Element, "");
            
            node.children = parse(children);
            
            nodes.push_back(node);
            
            i = (i + static_cast<int>(children.size()) + 1);

        }
        
    }

    return nodes;
    
}

const vector<Token> HTMLParser::getTokenChildren(const vector<Token>& tokens, const string& name, int index) {

    int seen = 0;
    vector<Token> children;
    
    for (int i = index; i < tokens.size(); ++i) {

        const Token token = tokens[i];
        
        if(token.name == name) {
            
            if(seen == 0 && token.end) {
                break;
            }

            if(token.start) {
                seen++;
            }
            
            if (token.end) {
                seen--;
            }
                        
        }
        
        children.push_back(token);
                
    }

    return children;
    
}

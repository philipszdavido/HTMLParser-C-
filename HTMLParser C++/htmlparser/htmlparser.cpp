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

vector<Node*> HTMLParser::parse(Node* parent, const vector<Token>& tokens) {
        
    vector<Node*> nodes;
    Node* prevNode = nullptr;
    
    for (int i = 0; i < tokens.size(); ++i) {
        
        const Token token = tokens[i];
        
        if(token.token == TokenType::Text) {
            
            Node* node = createNode("", NodeType::Text, token.name);
            node->parent = parent;
            
            node->prev = prevNode;
            
            if (prevNode != nullptr) {
                
                prevNode->next = node;
                
                prevNode = node;
                
            }
            
            nodes.push_back(node);
            
        } else if (token.token == TokenType::Element) {
            
            if(token.isVoid) {
                
                Node* voidElement = createNode(token.name, NodeType::Element, "");
                voidElement->attributes = token.attributes;
                voidElement->parent = parent;

                voidElement->prev = prevNode;
                
                if (prevNode != nullptr) {
                    prevNode->next = voidElement;
                    prevNode = voidElement;
                }
                
                nodes.push_back(voidElement);
                continue;
                
            }
            
            // search if element has children
            const vector<Token>& children = getTokenChildren(tokens, token.name, i + 1);
            Node* node = createNode(token.name, NodeType::Element, "");
            node->attributes = token.attributes;
            node->parent = parent;

            node->prev = prevNode;

            if (prevNode != nullptr) {
                
                prevNode->next = node;
                prevNode = node;
                
            }

            node->children = parse(node, children);
            
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


Node* HTMLParser::createNode(const string name, const NodeType type, const string textContent) {
    return new Node(name, type, textContent);
}

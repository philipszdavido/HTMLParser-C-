//
//  operators.cpp
//  HTMLParser C++
//
//  Created by Chidume Nnamdi on 12/08/2025.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Token.hpp"
#include "../htmlparser/Node.h"

using namespace std;

string tokenTypeToString(const Token& token) {
    
    if(token.token == TokenType::Text) {
        return "Text";
    }

    if(token.token == TokenType::Element) {
        return "Element";
    }
    
    if (token.token == TokenType::Comment) {
        return "Comment";
    }
    
    return "Unknown";
    
}

ostream& operator<<(ostream& os, const vector<AttributeToken>& attrs) {
    
    for(AttributeToken t : attrs) {
        cout << "'" << t.key << "' : '" << t.value << "'" << endl;
    }
    
    return os;
}

string nodeType(NodeType nodeType) {
    if (nodeType == NodeType::Element) {
        return "Element";
    }
    
    if (nodeType == NodeType::Text) {
        return "Text";
    }
    
    if (nodeType == NodeType::Comment) {
        return "Comment";
    }
    
    return "Unknown";

}

std::ostream& operator<<(std::ostream& os, const Node& node) {
    
    os << "Node: " << node.name
    << " | Type: " << nodeType(node.nodeType)
    << " | Text: \"" << node.textContent << "\""
    << " | Attributes: \"" << node.attributes << "\""
    << endl;
    
    for (const auto& child : node.children) {
        os << child << endl;
    }
    
    return os;
}

ostream& operator<<(ostream& os, const Token& token) {
    os << "Token(name=\"" << token.name
    << "\", token=" << tokenTypeToString(token)
    << ", start=" << std::boolalpha << token.start
    << ", end=" << std::boolalpha << token.end
    << ", index=" << token.index
    << ", void=" << std::boolalpha << token.isVoid
    << ", endStartTagIndex=" << token.endStartTagIndex
    << ", attributes=[\n" << token.attributes << "])";
    return os;
}

void printNode(const Node& node, int depth = 0) {
    // Indent based on depth
    for (int i = 0; i < depth; i++) {
        cout << "  ";
    }

    // Print node info
    cout << "Node: " << node.name
         << " | Type: " << (node.nodeType == NodeType::Element ? "Element" : "Text")
         << " | Text: \"" << node.textContent << "\""
         << endl;

    // Print children
    for (const auto& child : node.children) {
        printNode(child, depth + 1);
    }
}

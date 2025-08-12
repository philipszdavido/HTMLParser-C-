//
//  Node.h
//  HTMLParser C++
//
//  Created by Chidume Nnamdi on 11/08/2025.
//

#ifndef Node_h
#define Node_h

using namespace std;

enum class NodeType {
    Text,
    Element
};

class Node {
    
public:
    Node(string name, NodeType type, const string textContent) : name(name), nodeType(type), textContent(textContent) {};
    const string name;
    NodeType nodeType;
    const string textContent;
    vector<Node> children;
    vector<AttributeToken> attributes;
};

#endif /* Node_h */

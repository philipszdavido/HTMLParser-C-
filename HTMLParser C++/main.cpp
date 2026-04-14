//
//  main.cpp
//  HTMLParser C++
//
//  Created by Chidume Nnamdi on 10/07/2025.
//

#include <iostream>
#include "tokenizer/Tokenizer.hpp"
#include "overloads/operators.h"
#include "token_attribute_parser/AttributeParser/AttributeParser.hpp"
#include "htmlparser/htmlparser.hpp"

using namespace std;

int main(int argc, const char * argv[]) {

    const string _html = "<div class='main header'>Name: <span>Chi</span></div><img />Ha";
    std::string html = R"(
        <!--    <ng-for item="user" of="users" trackBy="id">-->
        <!--        <div>{{ user.name }}</div>-->
        <!--        <ng-for item="op" of="[9,90]">-->
        <!--            {{op}} {{user.name}}-->
        <!--        </ng-for>-->
        <!--    </ng-for>-->
        <!DOCTYPE html>
            <html>
                <head><title>Hello</title></head>
                <body>
                    <h1 class="title">Welcome!</h1>
                    <p id="intro">This is a test.</p>
                </body>
            </html>
        )";
    
    Tokenizer tokenizer(html);

    vector<Token> tokens = tokenizer.tokenize();
    
    HTMLParser h;
    Node* root = new Node("", NodeType::Element, "");
    vector<Node*> nodes = h.parse(root, tokens);
    root->children = nodes;
            
    printNode(root);

    return 0;
    
}

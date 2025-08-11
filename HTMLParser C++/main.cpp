//
//  main.cpp
//  HTMLParser C++
//
//  Created by Chidume Nnamdi on 10/07/2025.
//

#include <iostream>
#include "tokenizer/Tokenizer.hpp"
#include "overloads/operators.h"

using namespace std;

int main(int argc, const char * argv[]) {

    const string html = "<div>Name: <span>Chi</span></div><img />Ha";

    Tokenizer tokenizer(html);

    vector<Token> tokens = tokenizer.tokenize();
    
    for (Token token : tokens) {
        cout << token << endl;
    }
        
    return 0;
    
}

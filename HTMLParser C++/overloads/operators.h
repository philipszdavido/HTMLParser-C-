//
//  operators.h
//  HTMLParser C++
//
//  Created by Chidume Nnamdi on 11/08/2025.
//

#ifndef operators_h
#define operators_h

#include <ostream>

using namespace std;

string tokenTypeToString(const Token& token) {
    return (token.token == TokenType::Text ? "Text" : "Element");
}

ostream& operator<<(ostream& os, const Token& token) {
    os << "Token(name=\"" << token.name
    << "\", token=" << tokenTypeToString(token)
    << ", start=" << std::boolalpha << token.start
    << ", end=" << std::boolalpha << token.end
    << ", index=" << token.index
    << ", void=" << boolalpha << token.isVoid
    << ")";
    return os;
}

#endif /* operators_h */

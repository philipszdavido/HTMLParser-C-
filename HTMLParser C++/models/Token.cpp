//
//  Token.cpp
//  HTMLParser C++
//
//  Created by Chidume Nnamdi on 10/08/2025.
//

#include "Token.hpp"
#include <iostream>
#include "TokenType.h"

Token::Token(const string& name, const TokenType& token): name(name), token(token) {};

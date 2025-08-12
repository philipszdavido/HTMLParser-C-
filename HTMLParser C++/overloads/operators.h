//
//  operators.h
//  HTMLParser C++
//
//  Created by Chidume Nnamdi on 11/08/2025.
//

#ifndef operators_h
#define operators_h

#pragma once
#include <iostream>
#include <vector>
#include "Token.hpp"
#include "../htmlparser/Node.h"

using namespace std;

std::string tokenTypeToString(const Token& token);
std::ostream& operator<<(std::ostream& os, const std::vector<AttributeToken>& attrs);
std::ostream& operator<<(std::ostream& os, const Token& token);
std::ostream& operator<<(std::ostream& os, const Node& node);

#endif /* operators_h */

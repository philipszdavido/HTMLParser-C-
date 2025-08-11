//
//  AttributeParser.hpp
//  HTMLParser C++
//
//  Created by Chidume Nnamdi on 11/08/2025.
//

#ifndef AttributeParser_hpp
#define AttributeParser_hpp

#include <stdio.h>
#include "AttributeToken.hpp"

using namespace std;

class AttributeParser {
public:
    vector<AttributeToken> parseAttribute(const string& attributeString);
};

#endif /* AttributeParser_hpp */

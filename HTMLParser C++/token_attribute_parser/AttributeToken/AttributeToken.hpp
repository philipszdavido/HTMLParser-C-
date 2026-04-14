//
//  AttributeToken.hpp
//  HTMLParser C++
//
//  Created by Chidume Nnamdi on 11/08/2025.
//

#ifndef AttributeToken_hpp
#define AttributeToken_hpp

#include <stdio.h>
#include <ostream>

using namespace std;

class AttributeToken {

public:
    AttributeToken(const string key, const string value): key(key), value(value) {};
     string key;
     string value;
    
};
#endif /* AttributeToken_hpp */

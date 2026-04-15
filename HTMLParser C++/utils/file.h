//
//  file.h
//  HTMLParser C++
//
//  Created by Chidume Nnamdi on 15/04/2026.
//

#ifndef file_h
#define file_h

#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;
namespace fs = std::filesystem;

string read_file(const string& filename) {
    
    ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        exit(1);
    }
    
    ostringstream buffer;
    buffer << file.rdbuf();
    string source = buffer.str();
        
    file.close();
    
    return source;
    
}

fs::path findFileRecursive(const fs::path& root, const std::string& fileName) {
    for (auto& p : fs::recursive_directory_iterator(root)) {
        if (p.is_regular_file() && p.path().filename() == fileName) {
            return p.path();
        }
    }
    return {};
}

#endif /* file_h */

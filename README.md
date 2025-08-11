# 🛠️ HTML Parser in C++

A lightweight **HTML parser** written entirely in **C++** — no external dependencies.  
Designed for speed, clarity, and flexibility, this parser can tokenize and extract HTML elements, attributes, and text content for further processing.

---

## ✨ Features

- 🔍 **Tokenization** — Splits HTML into tags, attributes, and text nodes  
- 🏷 **Element parsing** — Identifies start tags, end tags, and self-closing tags  
- 📜 **Attribute handling** — Reads attributes and values, supports quoted/unquoted values  
- 🪶 **Lightweight** — Zero third-party dependencies, pure standard C++  
- 🚀 **Fast** — Minimal allocations, stream-based parsing

---

## 📦 Installation

Clone the repository:

```bash
git clone https://github.com/philipszdavido/HTMLParser-C-.git
cd HTMLParser-C-
```

```cpp
#include "HtmlParser.hpp"
#include <iostream>

int main() {
    std::string html = R"(
        <html>
            <head><title>Hello</title></head>
            <body>
                <h1 class="title">Welcome!</h1>
                <p id="intro">This is a test.</p>
            </body>
        </html>
    )";

    HtmlParser parser(html);
    auto tokens = parser.parse();

    for (const auto& token : tokens) {
        std::cout << token << "\n";
    }

    return 0;
}
```

```
Token(name="html", start=true, end=false, attributes=[])
Token(name="head", start=true, end=false, attributes=[])
Token(name="title", start=true, end=false, attributes=[])
...

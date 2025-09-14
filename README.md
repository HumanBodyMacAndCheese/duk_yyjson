# duk_yyjson
Override the default JSON.parse method with yyjson's blazingly fast capabilities. JSON.stringify will come in the next update, although I have profiled Duktape's default JSON.stringify to be pretty snappy, even for large datasets. 

Simply drop the two files in with your build system and call the required method to initialize the library. No code changes needed, it's that simple! 

```cpp
#include "duktape.h"

#include "duk_fastjson.h"    // Was originally going to have a simdjson backend as well, but I scrapped that for yyjson only

// A minimal template for a program with this library
int main(void) {
  duk_context* ctx = duk_create_heap_default();

  if (!ctx) {
    return 1;

  }
  duk_fastjson_init(ctx);
  
  /*

  Do whatever you'd like here

  */
  
  duk_destroy_heap(ctx);

  return 0;

}

```
Call JSON.parse from your code without changing a single line. 
```javascript
// Trivial example with a trivial replacement. 
const RESULT = JSON.parse("{\"answer\" : 42}");
console.log(RESULT["answer"]);    // -> 42

```

# Blazingly-fast performance... almost.

Even though the backend uses the fastest JSON library written in C, it still deals with the significant overhead when pushing all values to Duktape.

GCC (15.2.0, Windows x86_64 using MSYS2)  
Average out of 500 runs with `-O3` for `JSON.parse()`:

| canada.json | citm_catalog.json | twitter.json |
|-------------|-------------------|--------------|
| 75.8 MB/s   | 203.0 MB/s        | 175.2 MB/s   |

Ditto, but with mimalloc* integrated into Duktape's default memory allocation functions:

| canada.json | citm_catalog.json | twitter.json |
|-------------|-------------------|--------------|
| 101.2 MB/s  | 259.0 MB/s        | 229.3 MB/s   |

\* https://github.com/microsoft/mimalloc

# Why Duktape?
It's incredibly easy to integrate and JavaScript is a popular language. As what one guy said, I'm not trying to script my toaster, although you are free to modify the files at will to make them suitable for your toaster. They're less than 200 lines of code, get your hands dirty! 

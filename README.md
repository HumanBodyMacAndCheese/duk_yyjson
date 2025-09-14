# duk_yyjson
Override the default JSON.parse method with yyjson's blazingly fast capabilities. 

Simply drop the two files in with your build system and call the required method to initialize the library. No code changes needed, it's that simple! 

```cpp
#include "duktape.h"

#include "duk_fastjson.h"    // Was originally going to have an simdjson backend as well, but I scrapped that for yyjson only

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

# Blazingly-fast performance... almost.
Even though the backend uses the fastest

Best out of 500 runs with -O3 for JSON.parse(): 

| canada.json | citm_catalog.json | twitter.json |
| :------- | :------: | -------: |

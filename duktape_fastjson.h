#ifndef DUKTAPE_FASTJSON_H
#define DUKTAPE_FASTJSON_H

#include "duktape.h" 

#define DUKFASTJSON_VERSION 0000001		// 0.0.1 Indev 

#ifdef _cplusplus 
extern "C" {
#endif

// Replace JSON.parse with the fast backend. You must define it by either compiling the corresponding C/C++ file in with your project 
duk_ret_t duk_fastjson_parse(duk_context* ctx);

// Ditto, but with JSON.stringify (This does not exist yet, but Duktape's default JSON.stringify seems to be pretty snappy already 
// duk_ret_t duk_fastjson_stringify(duk_context* ctx);

// Initialize the library 
void duk_fastjson_init(duk_context* ctx);

#ifdef _cplusplus
}
#endif 

#endif		// DUKTAPE_FASTJSON_H

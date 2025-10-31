#ifndef DUK_YYJSON_H
#define DUK_YYJSON_H

#include "duktape.h" 

#define DUK_YYJSON_VERSION 000001		// 0.0.1: Pre-release 

#ifdef _cplusplus 
extern "C" {
#endif

// Replace JSON.parse with the fast backend. You must define it by either compiling the corresponding C/C++ file in with your project 
duk_ret_t duk_yyjson_parse(duk_context* ctx);

// Ditto, but with JSON.stringify (This does not exist yet, but Duktape's default JSON.stringify seems to be pretty snappy already 
// duk_ret_t duk_fastjson_stringify(duk_context* ctx);

// Initialize the library 
void duk_yyjson_init(duk_context* ctx);

#ifdef _cplusplus
}
#endif 

#endif		// DUKTAPE_FASTJSON_H

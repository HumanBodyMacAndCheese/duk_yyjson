#ifndef DUK_YYJSON_H
#define DUK_YYJSON_H

#include "duktape.h" 

#define DUK_YYJSON_VERSION 100000		// 1.0.0: Initial release 

#ifdef _cplusplus 
extern "C" {
#endif

// Replace JSON.parse with the fast backend. You must define it by either compiling the corresponding C/C++ file in with your project 
duk_ret_t duk_yyjson_parse(duk_context* ctx);

// Initialize the library 
void duk_yyjson_init(duk_context* ctx);

#ifdef _cplusplus
}
#endif 

#endif		// DUKTAPE_YYJSON_H

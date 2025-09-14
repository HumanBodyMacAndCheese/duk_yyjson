#include "duktape_fastjson.h"

#include "yyjson.h"

#include <stddef.h>		// Required for size_t 

void duk_fastjson_init(duk_context* ctx);

/*

WARNING: This is a recursive function and may cause a stack overflow if your JSON objects are too deep. Anyways, it translates the JSON object from C to Duktape 

*/
static void translate(duk_context* ctx, yyjson_val* obj) {
	duk_idx_t o;
	
	size_t idx, max;
	yyjson_val *key, *val;
	
	/*
	
	Fast paths: Numbers and strings are most commonly used in JSON so we're prioritizing them first 
	
	*/
	if (yyjson_is_num(obj)) { 
		duk_push_number(ctx, (double)yyjson_get_num(obj)); 
		return; 
		
	}
	
	if (yyjson_is_str(obj)) { 
		duk_push_lstring(ctx, yyjson_get_str(obj), yyjson_get_len(obj)); 
		return; 
		
	}
	
	switch (yyjson_get_type(obj)) { 
		case YYJSON_TYPE_OBJ:
			{
			o = duk_push_object(ctx); 
			
			yyjson_obj_foreach(obj, idx, max, key, val) {
				translate(ctx, val);
				duk_put_prop_lstring(ctx, o, yyjson_get_str(key), yyjson_get_len(key));
				
			}
				
			}
			return;
			
		case YYJSON_TYPE_ARR:
			{
			o = duk_push_array(ctx);
			
			yyjson_arr_foreach(obj, idx, max, val) {
				translate(ctx, val);
				duk_put_prop_index(ctx, o, idx);
				
			}
			
			}
			return; 
			
		case YYJSON_TYPE_NULL:
			duk_push_null(ctx);
			return;
			
		case YYJSON_TYPE_BOOL:
			duk_push_boolean(ctx, yyjson_get_bool(obj));
			return;
		
		/*
		
		case YYJSON_TYPE_NUM:
			duk_push_number(ctx, yyjson_get_num(obj));
			return;
			
		case YYJSON_TYPE_STR:
			duk_push_lstring(ctx, yyjson_get_str(obj), yyjson_get_len(obj));
			return;
			
		*/
		
	};
	
}

duk_ret_t duk_fastjson_parse(duk_context* ctx) {
	size_t sizeOfJSON = 0;
	char* json = (char*)duk_to_lstring(ctx, 0, &sizeOfJSON);		// Cast required for proper error handling; No modifications will be made, don't worry  
	
	yyjson_read_err err;
	
	yyjson_doc* doc = yyjson_read_opts(json, sizeOfJSON, 0, NULL, &err);		// YYJSON_READ_BIGNUM_AS_RAW 
	yyjson_val* root = yyjson_doc_get_root(doc);
	
	if (!doc) {
		return duk_error(ctx, DUK_ERR_SYNTAX_ERROR, "JSON.parse: %s at position %zu", err.msg, err.pos); 
	
	}
	
	translate(ctx, root); 

	yyjson_doc_free(doc); 
	
	return 1;
	
}

duk_ret_t duk_fastjson_stringify(duk_context* ctx) {
	/*
	
	TO-DO: Work on this function after you thoroughly test and debug the JSON.parse replacement if needed 
	
	*/
	return 1; 
	
}

void duk_fastjson_init(duk_context* ctx) {
	// Replace method JSON.parse and JSON.stringify with our shiny, new methods
	duk_get_global_string(ctx, "JSON");
	
	duk_push_c_function(ctx, duk_fastjson_parse, 1);
	duk_put_prop_string(ctx, -2, "parse");
	
	/*
	
	duk_push_c_function(ctx, duk_fastjson_stringify, 1);
	duk_put_prop_string(ctx, -2, "stringify"); 
	
	*/
	
}
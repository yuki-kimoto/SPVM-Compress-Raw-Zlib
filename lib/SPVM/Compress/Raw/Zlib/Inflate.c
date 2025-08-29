// Copyright (c) 2025 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include "zlib.h"

#include <stdlib.h>

static const char* FILE_NAME = "Compress/Raw/Zlib/Inflate.c";

int32_t SPVM__Compress__Raw__Zlib__Inflate___inflateInit(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  int32_t windowBits = env->get_field_int_by_name(env, stack, obj_self, "WindowBits", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { goto END_OF_FUNC; }
  
  void* obj_dictionary = env->get_field_string_by_name(env, stack, obj_self, "Dictionary", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { goto END_OF_FUNC; }
  const char* dictionary = NULL;
  int32_t dictonary_length = 0;
  if (obj_dictionary) {
    dictionary = env->get_chars(env, stack, obj_dictionary);
    dictonary_length = env->length(env, stack, obj_dictionary);
  }
  
  z_stream* st_z_stream = NULL;
  int32_t err = inflateInit2(st_z_stream, windowBits);
  
  if (!(err == Z_OK)) {
    error_id = env->die(env, stack, "[zlib Error]inflateInit2() failed(error:%d).", err, __func__, FILE_NAME, __LINE__);
    goto END_OF_FUNC;
  }
  
  if (dictionary && dictonary_length) {
    err = inflateSetDictionary(st_z_stream, (const Bytef*) dictionary, dictonary_length);
  }
  
  if (!(err == Z_OK)) {
    error_id = env->die(env, stack, "[zlib Error]inflateSetDictionary() failed(error:%d).", err, __func__, FILE_NAME, __LINE__);
    goto END_OF_FUNC;
  }
  
  void* obj_z_stream = env->new_pointer_object_by_name(env, stack, "Compress::Raw::Zlib::Z_stream", st_z_stream, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { goto END_OF_FUNC; }
  
  env->set_field_object_by_name(env, stack, obj_self, "z_stream", obj_z_stream, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { goto END_OF_FUNC; }
  
  END_OF_FUNC:
  
  if (error_id) {
    if (st_z_stream) {
      free(st_z_stream);
      st_z_stream = NULL;
    }
  }
  
  return error_id;
}

int32_t SPVM__Compress__Raw__Zlib__Inflate__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_z_stream = env->get_field_object_by_name(env, stack, obj_self, "z_stream", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { goto END_OF_FUNC; }
  
  z_stream* st_z_stream = env->get_pointer(env, stack, obj_z_stream);
  
  inflateEnd(st_z_stream);
  
  END_OF_FUNC:
  
  return error_id;
}


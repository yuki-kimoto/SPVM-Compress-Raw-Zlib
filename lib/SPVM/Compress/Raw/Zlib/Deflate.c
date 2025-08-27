// Copyright (c) 2025 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include "zlib.h"

#include <stdlib.h>

static const char* FILE_NAME = "Compress/Raw/Zlib/Deflate.c";

int32_t SPVM__Compress__Raw__Zlib__Deflate___deflateInit(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  int32_t level = env->get_field_int_by_name(env, stack, obj_self, "Level", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { goto END_OF_FUNC; }
  
  int32_t method = env->get_field_int_by_name(env, stack, obj_self, "Method", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { goto END_OF_FUNC; }
  
  int32_t windowBits = env->get_field_int_by_name(env, stack, obj_self, "WindowBits", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { goto END_OF_FUNC; }
  
  int32_t memLevel = env->get_field_int_by_name(env, stack, obj_self, "MemLevel", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { goto END_OF_FUNC; }
  
  int32_t strategy = env->get_field_int_by_name(env, stack, obj_self, "Strategy", &error_id, __func__, FILE_NAME, __LINE__);
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
  int32_t err = deflateInit2(st_z_stream, level, method, windowBits, memLevel, strategy);
  
  if (!(err == Z_OK)) {
    error_id = env->die(env, stack, "[zlib Error]deflateInit2() failed(error:%d).", err, __func__, FILE_NAME, __LINE__);
    goto END_OF_FUNC;
  }
  
  if (dictionary && dictonary_length) {
    err = deflateSetDictionary(st_z_stream, (const Bytef*) dictionary, dictonary_length);
  }
  
  if (!(err == Z_OK)) {
    error_id = env->die(env, stack, "[zlib Error]deflateSetDictionary() failed(error:%d).", err, __func__, FILE_NAME, __LINE__);
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

int32_t SPVM__Compress__Raw__Zlib__Deflate__deflateReset(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_z_stream = env->get_field_object_by_name(env, stack, obj_self, "z_stream", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { goto END_OF_FUNC; }
  
  z_stream* st_z_stream = env->get_pointer(env, stack, obj_z_stream);
  
  int32_t status = deflateReset(st_z_stream);
  
  if (!(status == Z_OK)) {
    error_id = env->die(env, stack, "[zlib Error]deflateReset() failed(error:%d).", status, __func__, FILE_NAME, __LINE__);
    goto END_OF_FUNC;
  }
  
  END_OF_FUNC:
  
  return error_id;
}

int32_t SPVM__Compress__Raw__Zlib__Deflate__deflateTune(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  int good_length = stack[0].ival;
  int max_lazy = stack[1].ival;
  int nice_length = stack[2].ival;
  int max_chain = stack[3].ival;
  
  void* obj_self = stack[0].oval;
  
  void* obj_z_stream = env->get_field_object_by_name(env, stack, obj_self, "z_stream", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { goto END_OF_FUNC; }
  
  z_stream* st_z_stream = env->get_pointer(env, stack, obj_z_stream);
  
  int32_t status = deflateTune(st_z_stream, good_length, max_lazy, nice_length, max_chain);
  
  if (!(status == Z_OK)) {
    error_id = env->die(env, stack, "[zlib Error]deflateTune() failed(error:%d).", status, __func__, FILE_NAME, __LINE__);
    goto END_OF_FUNC;
  }
  
  END_OF_FUNC:
  
  return error_id;
}

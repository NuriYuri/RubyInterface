#pragma once
//===
//Header d'aliasing des fonctions et constantes du Ruby
//Il est à inclure dans les scripts générant des extensions
//Il est interdit de l'inclure dans stdafx.h : Cela pourrait causer des paradoxes que le compilateur aurait du mal à traiter
//---
//Ecrit par Nuri Yuri (18/04/2014)
//===
#include "RubyDef.h"
#define cast_m VALUE(*)( ...)

#define ruby_init RI::ruby_init
#define ruby_script RI::ruby_script
#define ruby_init_loadpath RI::ruby_init_loadpath
#define rb_eval_string RI::rb_eval_string
#define ruby_finalize RI::ruby_finalize
#define rb_define_class RI::rb_define_class
#define rb_check_type RI::rb_check_type
#define rb_define_module RI::rb_define_module
#define rb_define_class_under RI::rb_define_class_under
#define rb_define_module_under RI::rb_define_module_under
#define rb_include_module RI::rb_include_module
#define rb_extend_object RI::rb_extend_object
#define rb_define_variable RI::rb_define_variable
#define rb_define_virtual_variable RI::rb_define_virtual_variable
#define rb_define_hooked_variable RI::rb_define_hooked_variable
#define rb_define_readonly_variable RI::rb_define_readonly_variable
#define rb_define_const RI::rb_define_const
#define rb_define_global_const RI::rb_define_global_const
#define rb_define_method RI::rb_define_method
#define rb_define_module_function RI::rb_define_module_function
#define rb_define_singleton_method RI::rb_define_singleton_method
#define rb_define_global_function RI::rb_define_global_function
#define rb_undef_method RI::rb_undef_method
#define rb_define_alias RI::rb_define_alias
#define rb_define_attr RI::rb_define_attr
#define rb_intern RI::rb_intern
#define rb_intern2 RI::rb_intern2
#define rb_id2name RI::rb_id2name
#define rb_class2name RI::rb_class2name
#define rb_obj_classname RI::rb_obj_classname
#define rb_funcall RI::rb_funcall
#define rb_funcall2 RI::rb_funcall2
#define rb_funcall_passing_block RI::rb_funcall_passing_block
#define rb_scan_args RI::rb_scan_args
#define rb_gv_set RI::rb_gv_set
#define rb_gv_get RI::rb_gv_get
#define rb_iv_get RI::rb_iv_get
#define rb_iv_set RI::rb_iv_set
#define rb_equal RI::rb_equal
#define rb_raise RI::rb_raise
#define rb_warning RI::rb_warning
#define rb_warn RI::rb_warn
#define rb_fatal RI::rb_fatal
#define rb_each RI::rb_each
#define rb_yield RI::rb_yield
#define rb_yield_values RI::rb_yield_values
#define rb_yield_values2 RI::rb_yield_values2
#define rb_block_given_p RI::rb_block_given_p
#define rb_need_block RI::rb_need_block
#define rb_iterate RI::rb_iterate
#define rb_block_call RI::rb_block_call
#define rb_rescue RI::rb_rescue
#define rb_ensure RI::rb_ensure
#define rb_catch RI::rb_catch
#define rb_throw RI::rb_throw
#define rb_data_object_alloc RI::rb_data_object_alloc
#define ruby_run RI::ruby_run
#define ruby_init_stack RI::ruby_init_stack
#define ruby_sysinit RI::ruby_sysinit
#define rb_cObject *RI::rb_cObject
#define rb_mKernel *RI::rb_mKernel


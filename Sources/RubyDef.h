#pragma once
//===
//Header de définition des fonctions ou constantes à importer
//---
//Ecrit par Nuri Yuri (18/04/2014)
//===

//---
//Constantes utile au fonctionnement des definitions
//---
#define Text_DLL_load_Fail TEXT("Impossible de charger le ruby.")
#define Text_RI_error TEXT("RubyInterface Error")

#define ReturnCode_DLL_Fail -2

//Methode de d'initalisation de tous les pointeurs de fonction ou constante
void initialize_all_functions();
//Macro de chargement d'une fonction du Ruby
#define load_rbf(name) RI::##name=(p_##name)GetProcAddress(RubyDLL,#name)
//Macro de chargement d'une constante du Ruby
#define load_rbc(name) RI::##name=(VALUE*)GetProcAddress(RubyDLL,#name)
//Macro de definition d'une fonction du Ruby
#define ri_rbf(name) static p_##name name
//Macro de definition d'une constante du Ruby
#define ri_rbc(name) static VALUE* name
//Macro d'initialisation du pointeur de fonction vers une fonction du Ruby
#define ri_rbi(name) p_##name RI::##name = NULL
//Macro d'initialisation du pointeur d'object vers une constante du Ruby
#define ri_rbci(name) VALUE* RI::##name = NULL
//Définition du type VALUE utile pour la suite
typedef unsigned long VALUE;
typedef VALUE ID;

//---
//Definition des methodes du ruby CF:ruby.h
//Les type de pointeur de fonction sont définit de la sorte :
//typedef return_type (*p_function_name)(args);
//---
typedef void (*p_ruby_init)(void);
typedef void (*p_ruby_run)(void);
typedef void (*p_ruby_script)(const char* name);
typedef void (*p_ruby_init_loadpath)(void);
typedef VALUE (*p_rb_eval_string)(const char* script);
typedef void (*p_ruby_finalize)(void);
typedef VALUE (*p_rb_define_class)(const char* name,VALUE parent);
typedef void (*p_rb_check_type)(VALUE object,int type);
typedef VALUE (*p_rb_define_module)(const char* name);
typedef VALUE (*p_rb_define_class_under)(VALUE under,const char* name,VALUE parent);
typedef VALUE (*p_rb_define_module_under)(VALUE under,const char* name);
typedef void (*p_rb_include_module)(VALUE in_class,VALUE module_to_include);
typedef void (*p_rb_extend_object)(VALUE in_object,VALUE module_to_include);
typedef void (*p_rb_define_variable)(const char* name,VALUE* ptr);
typedef void (*p_rb_define_virtual_variable)(const char* name, VALUE(*getter)(), void(*setter)());
typedef void (*p_rb_define_hooked_variable)(const char* name, VALUE* ptr, VALUE(*getter)(), void(*setter)());
typedef void (*p_rb_define_readonly_variable)(const char* name,VALUE* ptr);
typedef void (*p_rb_define_const)(VALUE in_class,const char* name, VALUE value);
typedef void (*p_rb_define_global_const)(const char* name, VALUE value);
typedef void (*p_rb_define_method)(VALUE in_class, const char* name, VALUE(*func)(...), int argc);
typedef void (*p_rb_define_module_function)(VALUE in_module, const char* name, VALUE(*func)(...), int argc);
typedef void (*p_rb_define_singleton_method)(VALUE in_object, const char* name, VALUE(*func)(...), int argc);
typedef void (*p_rb_define_global_function)(const char* name, VALUE(*func)(...), int argc);
typedef void (*p_rb_undef_method)(VALUE from_object, const char* name);
typedef void (*p_rb_define_alias)(VALUE in_object, const char* new_name, const char* old_name);
typedef void (*p_rb_define_attr)(VALUE in_class, const char* name, int readable, int writtable);
typedef ID (*p_rb_intern)(const char* name);
typedef ID (*p_rb_intern2)(const char* name, int length);
typedef const char* (*p_rb_id2name)(ID identifier);
typedef const char* (*p_rb_class2name)(VALUE class_object);
typedef const char* (*p_rb_obj_classname)(VALUE object);
typedef VALUE (*p_rb_funcall)(VALUE object, ID meth_id, int argc, ...);
typedef VALUE (*p_rb_funcall2)(VALUE object, ID meth_id, int argc, VALUE* args);
typedef VALUE (*p_rb_funcall_passing_block)(VALUE object, ID meth_id, int argc, VALUE* args);
typedef int (*p_rb_scan_args)(int argc,VALUE* argv, const char* format, ...);
typedef VALUE (*p_rb_gv_set)(const char* name, VALUE value);
typedef VALUE (*p_rb_gv_get)(const char* name);
typedef VALUE (*p_rb_iv_get)(VALUE object, const char* name);
typedef VALUE (*p_rb_iv_set)(VALUE object, const char* name, VALUE value);
typedef VALUE (*p_rb_equal)(VALUE object1, VALUE object2);
typedef void (*p_rb_raise)(VALUE errorClass, const char* message, ...);
typedef void (*p_rb_warning)(const char* message, ...);
typedef void (*p_rb_warn)(const char* message, ...);
typedef void (*p_rb_fatal)(const char* message, ...);
typedef VALUE (*p_rb_each)(VALUE object);
typedef VALUE (*p_rb_yield)(VALUE value);
typedef VALUE (*p_rb_yield_values)(int argc, ...);
typedef VALUE (*p_rb_yield_values2)(int argc, VALUE* argv);
typedef int (*p_rb_block_given_p)(void);
typedef void (*p_rb_need_block)(void);
typedef VALUE (*p_rb_iterate)(VALUE(*func1)(...), void* arg1, VALUE(*func2)(...), void* arg2);
typedef VALUE (*p_rb_block_call)(VALUE object, ID meth_id, int argc, VALUE* args, VALUE(*block_func)(...), VALUE context);
typedef VALUE (*p_rb_rescue)(VALUE(*func1)(...), void* arg1, VALUE(*func2)(...), void* arg2);
typedef VALUE (*p_rb_ensure)(VALUE(*func1)(...), void* arg1, VALUE(*func2)(...), void* arg2);
typedef VALUE (*p_rb_catch)(const char* tag, VALUE(*func)(...), VALUE data);
typedef VALUE (*p_rb_throw)(const char* tag, VALUE data);
typedef VALUE (*p_rb_data_object_alloc)(VALUE object, void* data, void* dmark, void(*dfree)(...));
typedef void (*p_ruby_init_stack)(VALUE* stack);
typedef void (*p_ruby_sysinit)(int* argc, char ***argv);

//---
//Conteneur à Globale, c'est un petit trick nécessaire au fonctionnement de l'interface
//---
class RI
{
public:
	RI(void);
	~RI(void);
	ri_rbf(ruby_init);
	ri_rbf(ruby_script);
	ri_rbf(ruby_init_loadpath);
	ri_rbf(rb_eval_string);
	ri_rbf(ruby_finalize);
	ri_rbf(rb_define_class);
	ri_rbf(rb_check_type);
	ri_rbf(rb_define_module);
	ri_rbf(rb_define_class_under);
	ri_rbf(rb_define_module_under);
	ri_rbf(rb_include_module);
	ri_rbf(rb_extend_object);
	ri_rbf(rb_define_variable);
	ri_rbf(rb_define_virtual_variable);
	ri_rbf(rb_define_hooked_variable);
	ri_rbf(rb_define_readonly_variable);
	ri_rbf(rb_define_const);
	ri_rbf(rb_define_global_const);
	ri_rbf(rb_define_method);
	ri_rbf(rb_define_module_function);
	ri_rbf(rb_define_singleton_method);
	ri_rbf(rb_define_global_function);
	ri_rbf(rb_undef_method);
	ri_rbf(rb_define_alias);
	ri_rbf(rb_define_attr);
	ri_rbf(rb_intern);
	ri_rbf(rb_intern2);
	ri_rbf(rb_id2name);
	ri_rbf(rb_class2name);
	ri_rbf(rb_obj_classname);
	ri_rbf(rb_funcall);
	ri_rbf(rb_funcall2);
	ri_rbf(rb_funcall_passing_block);
	ri_rbf(rb_scan_args);
	ri_rbf(rb_gv_set);
	ri_rbf(rb_gv_get);
	ri_rbf(rb_iv_get);
	ri_rbf(rb_iv_set);
	ri_rbf(rb_equal);
	ri_rbf(rb_raise);
	ri_rbf(rb_warning);
	ri_rbf(rb_warn);
	ri_rbf(rb_fatal);
	ri_rbf(rb_each);
	ri_rbf(rb_yield);
	ri_rbf(rb_yield_values);
	ri_rbf(rb_yield_values2);
	ri_rbf(rb_block_given_p);
	ri_rbf(rb_need_block);
	ri_rbf(rb_iterate);
	ri_rbf(rb_block_call);
	ri_rbf(rb_rescue);
	ri_rbf(rb_ensure);
	ri_rbf(rb_catch);
	ri_rbf(rb_throw);
	ri_rbf(rb_data_object_alloc);
	ri_rbf(ruby_run);
	ri_rbf(ruby_init_stack);
	ri_rbf(ruby_sysinit);

	ri_rbc(rb_cObject);
	ri_rbc(rb_mKernel);

};
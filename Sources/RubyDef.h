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

//---
//Definition des methodes du ruby CF:ruby.h
//Les type de pointeur de fonction sont définit de la sorte :
//typedef return_type (*p_function_name)(args);
//---
typedef void (*p_ruby_init)(void);
typedef void (*p_ruby_script)(const char* name);
typedef void (*p_ruby_init_loadpath)(void);
typedef VALUE (*p_rb_eval_string)(const char* script);
typedef void (*p_ruby_finalize)(void);
typedef VALUE (*p_rb_define_class)(const char* name,VALUE parent);

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

	ri_rbc(rb_cObject);
};
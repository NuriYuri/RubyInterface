//===
//Code de chargement des fonctions et constantes depuis msvcrt-ruby
//---
//Ecrit par Nuri Yuri (18/04/2014)
//===
#include "stdafx.h"

//---
//Initialisation des variable utilisé par l'interface
//---
HMODULE RubyDLL=NULL;
ri_rbi(ruby_init);
ri_rbi(ruby_script);
ri_rbi(ruby_init_loadpath);
ri_rbi(rb_eval_string);
ri_rbi(ruby_finalize);
ri_rbi(rb_define_class);

ri_rbci(rb_cObject);

//Initialisation des pointeurs de fonction et constante.
void initialize_all_functions()
{
	RubyDLL=LoadLibrary(TEXT("msvcrt-ruby200.dll"));
	if(!RubyDLL)
	{
		MessageBox(0,Text_DLL_load_Fail,Text_RI_error,MB_ICONERROR);
		ExitProcess(ReturnCode_DLL_Fail);
	}
	load_rbf(ruby_init);
	load_rbf(ruby_script);
	load_rbf(ruby_init_loadpath);
	load_rbf(rb_eval_string);
	load_rbf(ruby_finalize);
	load_rbf(rb_define_class);

	load_rbc(rb_cObject);
}
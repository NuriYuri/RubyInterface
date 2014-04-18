//===
//Code de lancement de RubyInterface
//---
//Ecrit par Nuri Yuri (18/04/2014)
//===
#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleTitle(TEXT("Initialisation de RubyInterface..."));
	initialize_all_functions();
	RI::ruby_init();
	SetConsoleTitle(TEXT("RubyInterface by Nuri Yuri"));
	RI::ruby_script("test");
	RI::ruby_init_loadpath();
	Init_RubyExtension1();
	RI::rb_eval_string("p rand(999),Extension1;system(\"pause\");");
	RI::ruby_finalize();
	return 0;
}


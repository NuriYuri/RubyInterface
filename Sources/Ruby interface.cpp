//===
//Code de lancement de RubyInterface
//---
//Ecrit par Nuri Yuri (18/04/2014)
//===
#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleTitle(TEXT("Initialisation de RubyInterface..."));
	//On charge toutes les fonctions utile au fonctionnement du programme
	initialize_all_functions();
	//On initialise le système de gestion du ruby (sans ça, la moindre erreur provoque un EAccessViolation)
	RI::ruby_sysinit(&argc,(char***)&argv);
	//On initialise le stack du Ruby
	VALUE ruby_stack;
	RI::ruby_init_stack(&ruby_stack);
	//On initialise l'interpreteur du Ruby
	RI::ruby_init();
	SetConsoleTitle(TEXT("RubyInterface by Nuri Yuri"));
	RI::ruby_script("RubyInterface");
	//On initialise les dossiers de chargement des scripts
	RI::ruby_init_loadpath();
	//On charge notre petite extension
	Init_RubyExtension1();
	//On execute un script défini dans la mémoire programme
	RI::rb_eval_string("p Extension1.new,Extension1.test;system(\"pause\");");
	//On termine le fonctionnement du ruby
	RI::ruby_finalize();
	return 0;
}


//===
//Code de l'Extension 1
//---
//Ecrit par Nuri Yuri (18/04/2014)
//===
#include "stdafx.h"
#include "RubyAlias.h"

//Initialisation de l'Extension 1
void Init_RubyExtension1()
{
	//D�finition de la classe Extension1 avec pour parent Object
	rb_define_class("Extension1",rb_cObject);
}

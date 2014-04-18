//===
//Code de l'Extension 1
//---
//Ecrit par Nuri Yuri (18/04/2014)
//===
#include "stdafx.h"
#include "RubyAlias.h"
VALUE cExtension1=NULL;
//Initialisation de l'Extension 1
void Init_RubyExtension1()
{
	//Définition de la classe Extension1 avec pour parent Object
	cExtension1=rb_define_class("Extension1",rb_cObject);
	rb_define_method(cExtension1,"initialize",(cast_m)Extension1_initialize,0);
	rb_define_singleton_method(cExtension1,"test",(cast_m)Extension1_test,-1);
}

VALUE Extension1_test(int argc,VALUE* argv,VALUE self)
{
	if(argc>0)
		return argv[0];
	else
		return self;
}
VALUE Extension1_initialize(VALUE self)
{
	rb_iv_set(self,"@test",1);
	rb_iv_set(self,"@test2",2);
	return self;
}
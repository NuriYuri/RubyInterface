#pragma once
//===
//Header d'aliasing des fonctions et constantes du Ruby
//Il est � inclure dans les scripts g�n�rant des extensions
//Il est interdit de l'inclure dans stdafx.h : Cela pourrait causer des paradoxes que le compilateur aurait du mal � traiter
//---
//Ecrit par Nuri Yuri (18/04/2014)
//===
#include "RubyDef.h"

#define rb_eval_string RI::rb_eval_string
#define rb_define_class RI::rb_define_class
#define rb_cObject *RI::rb_cObject
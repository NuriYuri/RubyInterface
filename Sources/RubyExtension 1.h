#pragma once
//===
//Header de définition de l'Extension 1
//L'extension 1 sert juste de test.
//---
//Ecrit par Nuri Yuri (18/04/2014)
//===

//Définition de la fonction d'initialisation de l'Extension 1
void Init_RubyExtension1();
VALUE Extension1_test(int argc,VALUE* argv,VALUE self);
VALUE Extension1_initialize(VALUE self);
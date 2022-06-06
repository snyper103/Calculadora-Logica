#ifndef CALCULADOLOGICA_H_INCLUDED
#define CALCULADOLOGICA_H_INCLUDED
#include "pilha.h"
#include <locale.h>

char CalculaSentenca(pilha* pi);
short int InsereSenteca(const char* StrSenteca, pilha* pi);
void Display();

#endif

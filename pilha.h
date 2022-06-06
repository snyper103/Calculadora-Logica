#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct Elementos
{
    char dado;
    struct Elementos* prox;
}*pilha;

typedef struct Elementos Elem;

pilha* CriaPilha();
void LiberaPilha(pilha* pi);

char ConsultaTopo(pilha* pi);

short int InserePilha(pilha* pi, char dado);
short int RemovePilha(pilha* pi);

int TamanhoPilha(pilha* pi);
void ImprimePilha(pilha* pi);
short int PilhaVazia(pilha* pi);

#endif

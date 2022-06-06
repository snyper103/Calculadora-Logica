#include "pilha.h"

pilha* CriaPilha()
{
    pilha* pi = (pilha *)malloc(sizeof(pilha));

    if(pi != NULL)
        (*pi) = NULL;

    return pi;
}
void LiberaPilha(pilha* pi)
{
    if(PilhaVazia(pi))
        return;

    Elem* no = (*pi);

    while((*pi) != NULL)
    {
        (*pi) = no->prox;
        free(no);
        no = (*pi);
    }

    free(pi);
}
char ConsultaTopo(pilha* pi)
{
    if(PilhaVazia(pi))
        return NULL;

    return (*pi)->dado;
}

short int InserePilha(pilha* pi, char dado)
{
    Elem* no = (Elem*)malloc(sizeof(Elem));

    if((!pi) || (!no))
        return 0;

    no->dado = dado;
    no->prox = NULL;

    if(PilhaVazia(pi))
        (*pi) = no;

    else
    {
        no->prox = (*pi);
        (*pi) = no;
    }

    return 1;
}
short int RemovePilha(pilha* pi)
{
    if(PilhaVazia(pi))
        return 0;

    else
    {
        Elem* no = (*pi);
        (*pi) = no->prox;

        free(no);
    }

    return 1;
}
int TamanhoPilha(pilha* pi)
{
    register int i;

    if(PilhaVazia(pi))
        return 0;

    else
    {
        Elem* no = (*pi);

        for(i = 1; no->prox != NULL; no = no->prox, ++i);
    }

    return i;
}

void ImprimePilha(pilha* pi)
{
    Elem* no = (*pi);

    if(PilhaVazia(pi))
        return;

    for(; no != NULL; no = no->prox)
    {
        printf("\nPilha: %c\n", no->dado);
        printf("---------------------\n");
    }
}
short int PilhaVazia(pilha* pi)
{
    return ((!pi) || ((*pi) == NULL));
}

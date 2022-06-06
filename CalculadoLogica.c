#include "CalculadoLogica.h"

void EncontraVariavel(const char* Svar, char* var1, char* var2)
{
    register int i;
    *var1 = -1;
    *var2 = -1;

    for(i = 0; Svar[i] != '\0'; ++i)
    {
        if(((Svar[i] == '1') || (Svar[i] == '0')) && (*var1 == -1))
            *var1 = Svar[i];

        else
            if(((Svar[i] == '1') || (Svar[i] == '0')) && (*var2 == -1))
                *var2 = Svar[i];

        if((*var1 != -1) && (*var2 != -1))
            break;
    }
}
void EncontraCondicao(const char* Svar, char* var)
{
    register int i;

    for(i = 0; Svar[i] != '\0'; ++i)
        if((Svar[i] != '1') && (Svar[i] != '0'))
        {
            *var = Svar[i];

            break;
        }
}

char CalculaConjuncao(const char* Svar)
{
    short int R = 0;
    char p, q;

    EncontraVariavel(Svar, &p, &q);

    R = ((p - '0') && (q - '0'));

    return (R == 1) ? ('1') : ('0');
}
char CalculaDisjuncaoInclusiva(const char* Svar)
{
    short int R = 0;
    char p, q;

    EncontraVariavel(Svar, &p, &q);

    R = ((p - '0') || (q - '0'));

    return (R == 1) ? ('1') : ('0');
}
char CalculaNegacao(const char* Svar)
{
    short int R = !(Svar[1] - '0');

    return (R == 1) ? ('1') : ('0');
}
char CalculaDisjuncaoExclusiva(const char* Svar)
{
    short int R = 0;
    char p, q;

    EncontraVariavel(Svar, &p, &q);

    if(((p - '0' == 1) && (q - '0' == 0))  || ((p - '0' == 0) && (q - '0' == 1)))
        R = 1;

    return (R == 1) ? ('1') : ('0');
}
char CalculaCondicional(const char* Svar, const char condicao)
{
    short int R = 0;
    char p, q;

    EncontraVariavel(Svar, &p, &q);

    if(condicao == '>')
    {
        if((p == '1') && (q == '0'));

        else
            R = 1;
    }

    else
    {
        if((p == '0') && (q == '1'));

        else
            R = 1;
    }

    return (R == 1) ? ('1') : ('0');
}
char CalculacBiCondicional(const char* Svar)
{
    short int R = 0;
    char p, q;

    EncontraVariavel(Svar, &p, &q);

    if(((p == '1') && (q == '1')) || ((p == '0') && (q == '0')))
        R = 1;

    return (R == 1) ? ('1') : ('0');
}

char EscolheOperacao(const char* Svar)
{
    char c;

    EncontraCondicao(Svar, &c);

    switch(c)
    {
        case '¬':
            return CalculaNegacao(Svar);

        case '^':
            return CalculaConjuncao(Svar);

        case 'v':
            return CalculaDisjuncaoInclusiva(Svar);

        case 'w':
            return CalculaDisjuncaoExclusiva(Svar);

        case '-':
            return CalculacBiCondicional(Svar);

        default :
            return CalculaCondicional(Svar, c);
    }
}

char CalculaSentenca(pilha* pi)
{
    char Svar[4], R, aux[3];
    register int i;
    Elem* no = (*pi);
    int size = TamanhoPilha(pi);

    if(size >= 3)
    {
        while(no->prox != NULL)
        {
            for(i = 0; i < 3; ++i)
            {
                if(!(PilhaVazia(pi)))
                {
                    if((no->dado == '(') || (no->dado == '['))
                    {
                        if(no != NULL)
                        {
                            RemovePilha(pi);
                            no = (*pi);
                        }

                        Svar[i] = CalculaSentenca(pi);
                        no = (*pi);
                    }

                    else
                    {
                        if(no->dado == '¬')
                        {
                            while((!(PilhaVazia(pi))) && (no->dado == '¬'))
                            {
                                    if(no != NULL)
                                    {
                                        RemovePilha(pi);
                                        no = (*pi);
                                    }

                                    aux[0] = '¬';
                                    aux[1] = Svar[i - 1];
                                    aux[2] = '\0';

                                    Svar[i - 1] = EscolheOperacao(aux);
                            }
                        }

                        if(!(PilhaVazia(pi)))
                        {
                            Svar[i] = no->dado;

                            if(no != NULL)
                            {
                                RemovePilha(pi);
                                no = (*pi);
                            }
                        }
                    }
                }

                else
                    break;
            }

            Svar[i] = '\0';

            if(!(PilhaVazia(pi)))
            {
                if((no->dado == ')') || (no->dado == ']'))
                {
                    if(no != NULL)
                    {
                        RemovePilha(pi);
                        no = (*pi);
                    }

                    R = EscolheOperacao(Svar);
                    return R;
                }

                if(no->dado == '¬')
                {
                    while((!(PilhaVazia(pi))) && (no->dado == '¬'))
                    {
                        if(no != NULL)
                        {
                            RemovePilha(pi);
                            no = (*pi);
                        }

                        aux[0] = '¬';
                        aux[1] = Svar[2];
                        aux[2] = '\0';

                        Svar[2] = EscolheOperacao(aux);
                    }
                }
            }

            R = EscolheOperacao(Svar);
            InserePilha(pi, R);
            no = (*pi);
        }
    }

    else
        if(size == 2)
        {

            aux[0] = '¬';
            aux[1] = no->dado;
            aux[2] = '\0';

            RemovePilha(pi);
            RemovePilha(pi);

            R = EscolheOperacao(aux);
            InserePilha(pi, R);
            no = (*pi);
        }

    R = no->dado;
    RemovePilha(pi);

    return R;
}

short int VerificaSentenca(const char* StrSenteca)
{
    register int i;
    int Pini = 0, Pfim = 0, Cini = 0, Cfim = 0;

    /*Verifica se as letras e numeros digitados estão dentro das permitadas pelo programa*/
    for(i = 0; StrSenteca[i] != '\0'; ++i)
    {
        if((StrSenteca[i] == '1') || (StrSenteca[i] == '0'));

        else
        {
            if((StrSenteca[i] == '<') || (StrSenteca[i] == '-') || (StrSenteca[i] == '>'));

            else
            {
                if((StrSenteca[i] == '^') || (StrSenteca[i] == 'v') || (StrSenteca[i] == 'V') || (StrSenteca[i] == 'w') || (StrSenteca[i] == 'W'));

                else
                {
                    if((StrSenteca[i] ==  -86) || (StrSenteca[i] == 170)  || (StrSenteca[i] == '~'));

                    else
                    {
                        if((StrSenteca[i] == '(') || (StrSenteca[i] == ')') || (StrSenteca[i] == '[') || (StrSenteca[i] == ']'));

                        else
                            return 0;
                    }
                }
            }
        }
    }

    /*verifica se o final da string esta certa*/
    if((StrSenteca[i - 1] != '1') && (StrSenteca[i - 1] != '0') && (StrSenteca[i - 1] != ')') && (StrSenteca[i - 1] != ']'))
        return 0;

    /*Verifica se a sintaxe da sentença lógica esta certa*/
    for(i = 1; StrSenteca[i] != '\0'; i += 2)
    {
        if((StrSenteca[i] == '1') || (StrSenteca[i] == '0'))
        {
            if((StrSenteca[i - 1] == '1') || (StrSenteca[i - 1] == '<') || (StrSenteca[i - 1] == '0') || (StrSenteca[i - 1] == ')') || (StrSenteca[i - 1] == ']'))
                return 0;

            if((StrSenteca[i + 1] == '1') || (StrSenteca[i + 1] == '>') || (StrSenteca[i + 1] == '0') || (StrSenteca[i + 1] == '(') || (StrSenteca[i + 1] == '[') || (StrSenteca[i + 1] == '~') || (StrSenteca[i + 1] ==  -86) ||(StrSenteca[i + 1] == 170))
                return 0;
        }

        else
        {
            if(StrSenteca[i] == '<')
            {
                if((StrSenteca[i - 1]  != '1') && (StrSenteca[i - 1] != '0') && (StrSenteca[i - 1] != ')') && (StrSenteca[i - 1] != ']'))
                    return 0;

                if(StrSenteca[i + 1] != '-')
                    return 0;
            }

            else
            {
                if(StrSenteca[i] == '>')
                {
                    if((StrSenteca[i + 1]  != '1') && (StrSenteca[i + 1] != '0') && (StrSenteca[i + 1] != '(') && (StrSenteca[i + 1] != '[') && (StrSenteca[i + 1] != '~') && (StrSenteca[i + 1] !=  -86) && (StrSenteca[i + 1] != 170))
                        return 0;

                    if(StrSenteca[i - 1] != '-')
                        return 0;
                }

                else
                {
                    if(StrSenteca[i] == '-')
                    {
                        if((StrSenteca[i + 1]  != '1') && (StrSenteca[i + 1] != '0') && (StrSenteca[i + 1] != '>') && (StrSenteca[i + 1] != '[') && (StrSenteca[i + 1] != '(') && (StrSenteca[i + 1] != '~') && (StrSenteca[i + 1] !=  -86) && (StrSenteca[i + 1] != 170))
                            return 0;

                        if((StrSenteca[i - 1]  != '1') && (StrSenteca[i - 1] != '0') && (StrSenteca[i - 1] != '<') && (StrSenteca[i - 1] != ']') && (StrSenteca[i - 1] != ')'))
                            return 0;

                        if(((StrSenteca[i - 1]  == '1') || (StrSenteca[i - 1] == '0') || (StrSenteca[i - 1] == ']') || (StrSenteca[i - 1] == ')')) && (StrSenteca[i + 1] != '>'))
                            return 0;

                        if(((StrSenteca[i + 1]  == '1') || (StrSenteca[i + 1] == '0') || (StrSenteca[i + 1] == '[') || (StrSenteca[i + 1] == '(') || (StrSenteca[i + 1] == '~') || (StrSenteca[i + 1] ==  -86) || (StrSenteca[i + 1] == 170)) && (StrSenteca[i - 1] != '<'))
                            return 0;
                    }

                    else
                    {
                        if((StrSenteca[i] == '^') || (StrSenteca[i] == 'v') || (StrSenteca[i] == 'V') || (StrSenteca[i] == 'w') || (StrSenteca[i] == 'W'))
                        {
                            if((StrSenteca[i + 1]  != '1') && (StrSenteca[i + 1] != '0') && (StrSenteca[i + 1] != '(') && (StrSenteca[i + 1] != '[') && (StrSenteca[i + 1] != '~') && (StrSenteca[i + 1] !=  -86) && (StrSenteca[i + 1] != 170))
                                return 0;

                            if((StrSenteca[i - 1]  != '1') && (StrSenteca[i - 1] != '0') && (StrSenteca[i - 1] != ')') && (StrSenteca[i - 1] != ']'))
                                return 0;
                        }

                        else
                        {
                            if((StrSenteca[i] == '~') || (StrSenteca[i] ==  -86) || (StrSenteca[i] == 170))
                            {
                                if((StrSenteca[i + 1]  != '1') && (StrSenteca[i + 1] != '0') && (StrSenteca[i + 1] != '(') && (StrSenteca[i + 1] != '[') && (StrSenteca[i + 1] != '~') && (StrSenteca[i + 1] !=  -86) && (StrSenteca[i + 1] != 170))
                                    return 0;

                                if((StrSenteca[i - 1]  == '1') || (StrSenteca[i - 1] == '0') || (StrSenteca[i - 1] == ')') || (StrSenteca[i - 1] == ']') || (StrSenteca[i - 1] == '<'))
                                    return 0;
                            }

                            else
                            {
                                if((StrSenteca[i] == ')') || (StrSenteca[i] == ']'))
                                {
                                    if((StrSenteca[i + 1]  == '1') || (StrSenteca[i + 1] == '0') || (StrSenteca[i + 1] == '(') || (StrSenteca[i + 1] == '[') || (StrSenteca[i + 1] == '~') || (StrSenteca[i + 1] ==  -86) || (StrSenteca[i + 1] == 170) || (StrSenteca[i + 1] == '>'))
                                        return 0;

                                    if((StrSenteca[i - 1]  != '1') && (StrSenteca[i - 1] != '0') && (StrSenteca[i - 1] != ')') && (StrSenteca[i - 1] != ']'))
                                        return 0;

                                    if(((StrSenteca[i] == ')') && (StrSenteca[i - 1] == ']')) || ((StrSenteca[i] == ']') && (StrSenteca[i + 1] == ')')))
                                        return 0;
                                }

                                else
                                    if((StrSenteca[i] == '(') || (StrSenteca[i] == '['))
                                    {
                                        if((StrSenteca[i + 1]  != '1') && (StrSenteca[i + 1] != '0') && (StrSenteca[i + 1] != '~') && (StrSenteca[i + 1] !=  -86) && (StrSenteca[i + 1] != 170) && (StrSenteca[i + 1] != '(') && (StrSenteca[i + 1] != '['))
                                            return 0;

                                        if((StrSenteca[i - 1]  == '1') || (StrSenteca[i - 1] == '0') || (StrSenteca[i - 1] == ')') || (StrSenteca[i - 1] == ']') || (StrSenteca[i - 1] == '<'))
                                            return 0;

                                        if(((StrSenteca[i] == '(') && (StrSenteca[i + 1] == '[')) || ((StrSenteca[i] == '[') && (StrSenteca[i - 1] == '(')))
                                            return 0;
                                    }
                            }
                        }
                    }
                }
            }
        }

        if((StrSenteca[i + 1] == '\0') || (StrSenteca[i + 2] == '\0'))
            break;
    }

    /*verifica se todos os coxetes e paranteses estão certos*/
    for(i = 0; StrSenteca[i] != '\0'; ++i)
    {
        if(StrSenteca[i] == '(')
            ++Pini;

        else
        {
            if(StrSenteca[i] == '[')
                ++Cini;

            else
            {
                if(StrSenteca[i] == ')')
                {
                    ++Pfim;

                    if(Pfim > Pini)
                        return 0;
                }

                else
                    if(StrSenteca[i] == ']')
                    {
                        ++Cfim;

                        if(Cfim > Cini)
                            return 0;
                    }
            }
        }

    }

    if((Cini != Cfim) || (Pini != Pfim))
        return 0;

    return 1;
}
short int InsereSenteca(const char* StrSenteca, pilha* pi)
{
    register int i;
    short int boleano = VerificaSentenca(StrSenteca);

    if(!pi)
        return 0;

    if(boleano == 0)
        return 0;

    for(i = 0; StrSenteca[i] != '\0'; ++i)
    {
        if((StrSenteca[i] == '~') || (StrSenteca[i] == 170) || (StrSenteca[i] == -86))
            boleano = InserePilha(pi, '¬');

        else
        {
            if((StrSenteca[i] == 'v') || (StrSenteca[i] == 'V'))
                boleano = InserePilha(pi, 'v');

            else
            {
                if((StrSenteca[i] == 'w') || (StrSenteca[i] == 'W'))
                    boleano = InserePilha(pi, 'w');

                else
                {
                    if(StrSenteca[i] == '-')
                    {
                        boleano = InserePilha(pi, '<');
                        ++i;
                    }

                    else
                    {
                        if(StrSenteca[i] == '<')
                        {
                            if(StrSenteca[i + 2] == '>')
                            {
                                boleano = InserePilha(pi, '-');
                                i += 2;
                            }
                            else
                            {
                                boleano = InserePilha(pi, '>');
                                ++i;
                            }
                        }

                        else
                        {
                            if((StrSenteca[i] == ']') || (StrSenteca[i] == ')'))
                            {
                                if(StrSenteca[i] == ']')
                                    boleano = InserePilha(pi, '[');
                                else
                                    boleano = InserePilha(pi, '(');
                            }

                            else
                            {
                                if((StrSenteca[i] == '[') || (StrSenteca[i] == '('))
                                {
                                    if(StrSenteca[i] == '[')
                                        boleano = InserePilha(pi, ']');
                                    else
                                        boleano = InserePilha(pi, ')');
                                }

                                else
                                    boleano = InserePilha(pi, StrSenteca[i]);
                            }
                        }
                    }
                }
            }
        }

        if(boleano == 0)
            return 0;
    }

    return 1;
}

short int VerificaControle(const char* ChaveControle)
{
    if(ChaveControle[1] != '\0')
        return 0;

    if((ChaveControle[0] != '0') && (ChaveControle[0] != '1') && (ChaveControle[0] != '2'))
        return 0;

    return 1;
}
void Display()
{
    setlocale(LC_ALL, "Portuguese");

    short int boleano = 0;
    pilha* pi = CriaPilha();
    char StrVar[256], R, controle[256];
    controle[0] = '1';
    controle[1] = '\0';

    while(controle[0] != '0')
    {
        switch(controle[0])
        {
            case '1':
                printf(" ____________________________________________________________________________________\n"
                       "| Operação    | Conectivo que o  |    Estrutura   |            Exemplos              |\n"
                       "|             | Programa aceita  |     Lógica     |                                  |\n"
                       "| ----------- | ---------------- | -------------- | -------------------------------- |\n"
                       "| Negação     |       ¬  ~       |     Não p      | A bicicleta NÃO é azul           |\n"
                       "| ----------- | ---------------- | -------------- | -------------------------------- |\n"
                       "| Conjunção   |         ^        |     p e q      | Thiago é médico E João           |\n"
                       "|             |                  |                | é Engenheiro                     |\n"
                       "| ----------- | ---------------- | -------------- | -------------------------------- |\n"
                       "| Disjunção   |         v        |     p ou q     | Thiago é médico OU               |\n"
                       "| Inclusiva   |         V        |                | João é Engenheiro                |\n"
                       "| ----------- | ---------------- | -------------- | -------------------------------- |\n"
                       "| Disjunção   |         w        |    Ou p ou q   | OU Thiago é Médico               |\n"
                       "| exclusiva   |         W        |                | OU João é Engenheiro             |\n"
                       "| ----------- | ---------------- | -------------- | -------------------------------- |\n"
                       "| Condicional |         ->       |  Se p então q  | SE Thiago é Médico               |\n"
                       "|             |        <-        |                | ENTÃO João é Engenheiro          |\n"
                       "| ----------- | ---------------- | -------------- | -------------------------------- |\n"
                       "|             |                  |     P se e     | Thiago é médico SE E SOMENTE     |\n"
                       "|Bicondicional|        <->       |  somente se q  | SE João é Médico                 |\n"
                       "|_____________|__________________|________________|__________________________________|\n\n");
                break;

            case '2':
                printf("\nDigite a senteça que você deseja calcular: ");
                scanf(" %[^\n]s", StrVar);

                boleano = InsereSenteca(StrVar, pi);

                if(boleano == 0)
                {
                    printf("\n\n\t##### ... ENTRADA INVÁLIDA! ... #####\n\n");
                    break;
                }

                R = CalculaSentenca(pi);

                printf("\n\n\tA resposta é: %c\n"
                       "\t---------------\n", R);

                break;

            default :
                printf("\n\t##### ... Por favor digite uma opção válida ... #####\n\n");
        }

        printf("\n[1]. Mostrar operações que podem ser feitas e como digitá-las."
               "\n[2]. Calcular senteça lógica."
               "\n[0]. Sair do programa.");
        printf("\n\nDigite o numero da opção desejada: ");
        scanf(" %[^\n]s", controle);

        boleano = VerificaControle(controle);

        if(boleano == 0)
        {
            controle[0] = '3';
            controle[1] = '\0';
        }
    }

    LiberaPilha(pi);
}

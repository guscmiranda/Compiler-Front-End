// Construir a árvore sintática concreta (árvore de derivação):
// - Utilizar uma estrutura encadeada para a árvore

// Talvez algo tipo :

#include <stdlib.h>

typedef struct No
{
    char nome[30];
    struct No *filho; // esse eh o primeiro filho do nó
    struct No *irmao; // vai linkando os filhos do mesmo nó
} No;

No *cria_no(char nome[])
{
    No *n = malloc(sizeof(No));

    strcpy(n->nome, nome);

    n->filho = NULL;
    n->irmao = NULL;

    return n;
}

void adiciona_filho(No *pai, No *filho)
{

    filho->irmao = NULL; // último da lista

    if (pai->filho == NULL)
    {
        pai->filho = filho;
    }
    else
    {
        No *atual = pai->filho;

        while (atual->irmao != NULL)
        {
            atual = atual->irmao;
        }

        atual->irmao = filho;
    }
}
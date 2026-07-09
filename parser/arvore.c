// Construir a árvore sintática concreta (árvore de derivação):
// - Utilizar uma estrutura encadeada para a árvore

// Talvez algo tipo :

#include "arvore.h"

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

void libera_arvore(No *raiz)
{
    if (raiz == NULL)
        return;

    libera_arvore(raiz->filho);

    libera_arvore(raiz->irmao);

    free(raiz);
}

void printa_arvore(No *raiz, int nivel)
{
    if (raiz == NULL)
        return;

    for (int i = 0; i < nivel; i++)
        printf("  ");

    // Imprime o nome do nó atual
    printf("- %s\n", raiz->nome);

    // Imprime os filhos (descendo na árvore -> aumenta o nível)
    printa_arvore(raiz->filho, nivel + 1);

    // Imprime os irmãos (mesma altura na árvore -> mantém o nível)
    printa_arvore(raiz->irmao, nivel);
}
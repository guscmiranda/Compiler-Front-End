#ifndef ARVORE_H
#define ARVORE_H

#include <stdlib.h>
#include <string.h>

typedef struct No
{
    char nome[30];
    struct No *filho;
    struct No *irmao;
} No;

No *cria_no(char nome[]);
void adiciona_filho(No *pai, No *filho);

// TODO: Implementar função para liberar a memória da árvore sintática
void libera_arvore(No *raiz);

#endif // ARVORE_H
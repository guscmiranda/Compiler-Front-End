// Implementação manual de um analisador sintático preditivo:
// - Utilizar a abordagem baseada em descida recursiva

// A parte da descida recursiva vai ser resolvida por causa da implementação da árvore sintática

// O QUE FAZER AQUI:
// - Implementar as funções correspondentes às produções da gramática
// - Função que recebe o token atual e chama a função correspondente à produção da gramática  -->
// - Função que verifique o casamento do token atual com o token esperado e avance para o próximo token --> match(token_esperado)
// - Função que verifica se o token atual é um token de erro e trata o erro de forma adequada  --> existe error.c para isso né

#include "parser.h"
#include "arvore.h"

No *expressao3()
/*<expressao3> ::= <termo> <expressao3’>*/
{
    No *n = cria_no("expressao3");

    adiciona_filho(n, termo());
    adiciona_filho(n, expressao3_linha());

    return n;
}

// No *expressao3_linha()
// /*<expressao3’> ::= OP_POT <expressao3> | ϵ*/
// {
//     No *n = cria_no("expressao3_linha");

//     if (tk_atual.tipo == OP_POT)
//     {
//         adiciona_filho(n, cria_no("OP_POT"));
//         match(OP_POT);
//         adiciona_filho(n, expressao3());
//     }

//     return n;
// }

// Enfim, essa é a ideia geral de como devemos implementar.
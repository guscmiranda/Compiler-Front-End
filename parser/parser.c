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
#include <stdio.h>
#include <stdlib.h>

Token tk_atual;

// FIRST(<call>) = {tipo}
No *call() {
    No *n = cria_no("call");
    
    if (tk_atual.tipo == TK_TIPO) {
        adiciona_filho(n, cria_no("tipo"));
        match(TK_TIPO);
        
        adiciona_filho(n, cria_no("programa"));
        match(TK_PROGRAMA);
        
        adiciona_filho(n, cria_no("("));
        match(TK_PARENTESE_ABRE);
        
        adiciona_filho(n, cria_no(")"));
        match(TK_PARENTESE_FECHA);
        
        adiciona_filho(n, bloco());
    } else {
        erro_sintatico("Esperado inicio do programa (tipo)");
    }
    return n;
}


No *bloco() {
// <bloco> ::= inicio <declaracao_das_variaveis> <sequencia_de_comandos> fim
// FIRST(<bloco>) = {inicio}    
    No *n = cria_no("bloco");
    
    if (tk_atual.tipo == TK_INICIO) {
        adiciona_filho(n, cria_no("inicio"));
        match(TK_INICIO);
        
        adiciona_filho(n, declaracao_das_variaveis());
        adiciona_filho(n, sequencia_de_comandos());
        
        adiciona_filho(n, cria_no("fim"));
        match(TK_FIM);
    } else {
        erro_sintatico("Esperado 'inicio' para abrir o bloco");
    }
    return n;
}

No *termo() {
    // <termo> ::= ID | NUM | OP_SUB <num_ou_id> | CONTEUDO_CHAR | (<expressao>)
    No *n = cria_no("termo");
    
    if (tk_atual.tipo == TK_ID) {
        adiciona_filho(n, cria_no("ID"));
        match(TK_ID);
    } 
    else if (tk_atual.tipo == TK_NUM) {
        adiciona_filho(n, cria_no("NUM"));
        match(TK_NUM);
    } 
    else if (tk_atual.tipo == TK_OP_SUB) {
        adiciona_filho(n, cria_no("OP_SUB"));
        match(TK_OP_SUB);
        // adiciona_filho(n, num_ou_id()); 
    } 
    else if (tk_atual.tipo == TK_CHAR_CONTEUDO) {
        adiciona_filho(n, cria_no("CONTEUDO_CHAR"));
        match(TK_CHAR_CONTEUDO);
    } 
    else if (tk_atual.tipo == TK_PARENTESE_ABRE) {
        adiciona_filho(n, cria_no("("));
        match(TK_PARENTESE_ABRE);
        // adiciona_filho(n, expressao()); 
        adiciona_filho(n, cria_no(")"));
        match(TK_PARENTESE_FECHA);
    } 
    else {
        erro_sintatico("Esperado um termo válido (ID, NUM, -, CHAR ou Expressão)");
    }
    
    return n;
}

No *expressao3()
/*<expressao3> ::= <termo> <expressao3’>*/
//FIRST(<expressao3>) = {ID, NUM, OP_SUB, CONTEUDO_CHAR, ( }
{
    No *n = cria_no("expressao3");

    adiciona_filho(n, termo());
    adiciona_filho(n, expressao3_linha());

    return n;
}


No *expressao3_linha() {
    // <expressao3'> ::= OP_POT <expressao3> | ϵ
    // FIRST(<expressao3'>) = {OP_POT, ε}
    No *n = cria_no("expressao3_linha");

    if (tk_atual.tipo == TK_OP_POT) {
        adiciona_filho(n, cria_no("OP_POT"));
        match(TK_OP_POT);
        adiciona_filho(n, expressao3());
    }
    
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
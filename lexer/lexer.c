#include "lexer.h"
#include "tabela_transicao.h"
#include <stdio.h>
#include <string.h>

#include "../symbols/symbol_table.h"
#include "tabela_transicao.h"
#include "../utils/error.h"
#include "lexer.h"
// #include "token.h"

int linha_atual = 1;
int coluna_atual = 1;
FILE *arquivo = NULL;

extern Estado tabela_transicao[N_ESTADOS][NUM_CLASSES];
extern TokenType estado_final[N_ESTADOS];
extern int estado_lookahead[N_ESTADOS];

void inicializa_lexer(FILE *codigo_fonte) {
    arquivo = codigo_fonte;
    inicializa_tabela_transicao();
    linha_atual = 1;
    coluna_atual = 1;
}

// falta get next token no lexer.c, tem que ler o arquivo e usar a tabela de transicao pra gerar os 
// tokens e usar a funcao verifica_palavra_reservada pra diferenciar id de palavra reservada

static TokenType verifica_palavra_reservada(const char* lexema) {
    //tipo
    if (strcmp(lexema, "void") == 0) return TK_TIPO;
    if (strcmp(lexema, "int") == 0) return TK_TIPO;
    if (strcmp(lexema, "char") == 0) return TK_TIPO;
    if (strcmp(lexema, "float") == 0) return TK_TIPO;
    
    //estrutura
    if (strcmp(lexema, "programa") == 0) return TK_PROGRAMA;
    if (strcmp(lexema, "inicio") == 0) return TK_INICIO;
    if (strcmp(lexema, "fim") == 0) return TK_FIM;

    //selecao
    if (strcmp(lexema, "se") == 0) return TK_SE;
    if (strcmp(lexema, "entao") == 0) return TK_ENTAO;
    if (strcmp(lexema, "e_se") == 0) return TK_E_SE;
    if (strcmp(lexema, "senao") == 0) return TK_SENAO;

    //repeticao
    if (strcmp(lexema, "enquanto") == 0) return TK_ENQUANTO;
    if (strcmp(lexema, "faca") == 0) return TK_FACA;
    if (strcmp(lexema, "repita") == 0) return TK_REPITA;
    if (strcmp(lexema, "ate") == 0) return TK_ATE;
    if (strcmp(lexema, "para") == 0) return TK_PARA;
    if (strcmp(lexema, "passo") == 0) return TK_PASSO;

    //se passa eh id
    return TK_ID;
}

void conta_linha_e_coluna(char c){
    const int is_eof = (c == EOF);

    if (c == '\n'){
        linha_atual++;
        coluna_atual = 1;
    } else if (!is_eof){
        coluna_atual++;
    }
}

void trata_lookahead(Estado s, char *lexema, int *tamanho_lexema){
    
    // Se alcançou s sem lookahead não precisa tratar
    if(estado_lookahead[s] != 1) return;

    (*tamanho_lexema)--;
    char lookahead_char = lexema[*tamanho_lexema];

    // Devolve caractere e volta o ponteiro (conferir!)
    ungetc(lookahead_char, arquivo);

    if (lookahead_char == '\n') linha_atual--;
    else coluna_atual--;

}

int get_next_token(){
    Estado s = estado_inicial();
    char lexema[100]; 
    int i = 0;

    // Para reportar erro, informar onde o token está exatamente
    int token_linha = linha_atual;
    int token_coluna = coluna_atual;

    while (!is_estado_final(s))
    {
        char c = fgetc(arquivo); // fazer get_next_char() ?
        int is_eof = (c == EOF);

        conta_linha_e_coluna(c); // Atualizar linha e coluna
        if(!is_eof && c != '\r') lexema[i++] = c;

        if(is_eof && s == estado_inicial()){
            // EOF REAL
            // CRIAR TOKEN NULO ?
            // SAIR DAQUI E IR PRA AÇÕES E TRATAR LÁ?
        } 
        // se o eof é lookahead temos q tratar num else ??
        

        ClasseEntrada classe = classifica_caractere(c);
        s = move(s, classe);
        
    
    }

    // duas linhas abaixo apenas para testes
    trata_lookahead(s, lexema, &i);
    lexema[i] = '\0';


    printf("lexema lido: %s | Token: %d\n", lexema, token_final(s));
    int token = token_final(s);
    // acoes(lexema, token);
}

// Considera que EOF é tratado no while
// Acho que não trata RELOP de acordo...
// Deveria retornar lexema nos q não são id ?
Token acoes(Estado s, char *lexema, int *tamanho_lexema, 
int token_linha, int token_coluna){

    Token token;

    if (s == ST_ERRO){ // Conferir
        lexema[*tamanho_lexema] = '\0';
        // chama função de erro
        token.tipo = TK_NULO;
        return token;
    }

    trata_lookahead(s, lexema, tamanho_lexema);
    lexema[*tamanho_lexema] = '\0';

    TokenType tipo = estado_final[s];

    if(tipo == TK_ID)
        tipo = verifica_palavra_reservada(lexema);

    token.tipo = tipo;
    strcpy(token.lexema, lexema);
    token.linha = token_linha;
    token.coluna = token_coluna;

    if(tipo == TK_ID || tipo == TK_NUM){
        // adiciona na tabela de simbolos
        // indice = insere_simbolo(token.lexema, tipo) ??
        token.tipo = -1; // só pra não reclamar
    } else {
        token.indice = -1;
    }

    return token;
}

// int acoes(lexema, id_token) {
//     switch (id_token) {
//         case TK_ID:
//         // tabela de simbolos
//         // lookahead
//             verifica_palavra_reservada(lexema);
//         default:
//             return id_token;
//     }
//     TK_NULO, // 0
//     TK_TIPO,
//     TK_PROGRAMA,
//     TK_ID,
//     TK_PARENTESE_ABRE,
//     TK_PARENTESE_FECHA, // 5
//     TK_INICIO,
//     TK_FIM,
//     TK_DOIS_PONTOS,
//     TK_PONTO_VIRGULA,
//     TK_VIRGULA, // 10
//     TK_ATRIBUICAO,
//     TK_OP_ADI,
//     TK_OP_SUB,
//     TK_OP_MUL,
//     TK_OP_DIV, // 15
//     TK_OP_POT,
//     TK_CHAR_CONTEUDO,
//     TK_NUM,
//     TK_SE,
//     TK_ENTAO, // 20
//     TK_E_SE,
//     TK_SENAO,
//     TK_ENQUANTO,
//     TK_FACA,
//     TK_REPITA, // 25
//     TK_ATE,
//     TK_RELOP,
//     TK_PARA,
//     TK_PASSO,
//     TK_COMENTARIO, // 30
//     TK_SEPARADOR,  // comentário e separador são ignorados
//     TK_EOF,
//     NUM_TOKENS
// }

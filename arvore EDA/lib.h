#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct produto{
    char nomeProduto[50];
    float preco;
    int quantidade,codigo;
} Produto;

typedef struct No {
    Produto compras;
    struct No* esquerda;
    struct No* direita;
    int altura;
} No;

int getAltura(No* no);
int max(int a, int b);
No* novoNo(Produto P);
No* rotacaoDireita(No* y);
No* rotacaoEsquerda(No* x);
int getBalanceamento(No* no);
No* inserir(No* no, Produto P);
No* busca(No* raiz, Produto P);
void imprimir(No* no);
void imprimirUnicaCompra(No* no);

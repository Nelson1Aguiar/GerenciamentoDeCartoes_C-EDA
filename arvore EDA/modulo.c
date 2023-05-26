#include "lib.h"

// Função para obter a altura de um nó
int getAltura(No* no) {
    if (no == NULL)
        return 0;
    return no->altura;
}

// Função para obter o máximo entre dois números
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para criar um novo nó com uma chave dada
No* novoNo(Produto P) {
    No* no = (No*)malloc(sizeof(No));
    no->compras = P;
    no->esquerda = NULL;
    no->direita= NULL;
    no->altura = 1;
    return no;
}

// Função para fazer uma rotação simples à direita
No* rotacaoDireita(No* y) {
    No* x = y->esquerda;
    No* T2 = x->direita;

    // Realiza a rotação
    x->direita = y;
    y->esquerda = T2;

    // Atualiza as alturas
    y->altura = max(getAltura(y->esquerda), getAltura(y->direita)) + 1;
    x->altura = max(getAltura(x->esquerda), getAltura(x->direita)) + 1;

    return x;
}

// Função para fazer uma rotação simples à esquerda
No* rotacaoEsquerda(No* x) {
    No* y = x->direita;
    No* T2 = y->esquerda;

    // Realiza a rotação
    y->esquerda = x;
    x->direita = T2;

    // Atualiza as alturas
    x->altura = max(getAltura(x->esquerda), getAltura(x->direita)) + 1;
    y->altura = max(getAltura(y->esquerda), getAltura(y->direita)) + 1;

    return y;
}

// Função para obter o fator de balanceamento de um nó
int getBalanceamento(No* no) {
    if (no == NULL)
        return 0;
    return getAltura(no->esquerda) - getAltura(no->direita);
}

// Função para inserir uma chave em uma árvore AVL
No* inserir(No* no, Produto P) {
    // Realiza a inserção normal de uma árvore binária de pesquisa
    if (no == NULL)
        return novoNo(P);

    if (P.codigo < no->compras.codigo)
        no->esquerda = inserir(no->esquerda, P);

    else if (P.codigo > no->compras.codigo)
        no->direita = inserir(no->direita, P);

    else // Chaves iguais não são permitidas
        printf("Codigo ja cadastrado em outra compra!");
        return no;
    // Atualiza a altura do nó pai
    no->altura = 1 + max(getAltura(no->esquerda), getAltura(no->direita));

    // Obtém o fator de balanceamento do nó pai
    int balanceamento = getBalanceamento(no);

    // Caso de desbalanceamento, existem 4 casos possíveis

    // Caso esquerda-esquerda
    if (balanceamento > 1 && P.codigo < no->esquerda->compras.codigo)
        return rotacaoDireita(no);

    // Caso direita-direita
    if (balanceamento < -1 && P.codigo > no->direita->compras.codigo)
        return rotacaoEsquerda(no);

    // Caso esquerda-direita
    if (balanceamento > 1 && P.codigo > no->esquerda->compras.codigo) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Caso direita-esquerda
    if (balanceamento < -1 && P.codigo < no->direita->compras.codigo) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }
    // Árvore balanceada, retorna o nó sem alterações
    return no;
}

// Função para buscar uma chave em uma árvore AVL
No* busca(No* raiz, Produto P) {
    // Caso a árvore esteja vazia ou a chave seja encontrada
    if (raiz == NULL || raiz->compras.codigo == P.codigo)
        return raiz;

    // Se a chave for menor que a chave do nó atual, busca na subárvore esquerda
    if (P.codigo < raiz->compras.codigo)
        return busca(raiz->esquerda, P);

    // Se a chave for maior que a chave do nó atual, busca na subárvore direita
    return busca(raiz->direita, P);
}

// Função para imprimir a árvore em ordem (in-order traversal)
void imprimir(No* no) {
    if (no == NULL)
        return;

    imprimir(no->esquerda);
    printf("COMPRA DE CODIGO %d -----Produto: %s || Preco: %.2f || Quantidade: %d || Valor total: %.2f reais \n\n",
           no->compras.codigo,no->compras.nomeProduto,no->compras.preco,no->compras.quantidade,no->compras.preco * no->compras.quantidade);
    imprimir(no->direita);
}

void imprimirUnicaCompra(No* no){
    printf("COMPRA DE CODIGO %d -----Produto: %s || Preco: %.2f || Quantidade: %d || Valor total: %.2f reais \n\n",
           no->compras.codigo,no->compras.nomeProduto,no->compras.preco,no->compras.quantidade,no->compras.preco * no->compras.quantidade);
}

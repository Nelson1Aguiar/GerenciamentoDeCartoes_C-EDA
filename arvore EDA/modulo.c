#include "lib.h"

// Fun��o para obter a altura de um n�
int getAltura(No* no) {
    if (no == NULL)
        return 0;
    return no->altura;
}

// Fun��o para obter o m�ximo entre dois n�meros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Fun��o para criar um novo n� com uma chave dada
No* novoNo(Produto P) {
    No* no = (No*)malloc(sizeof(No));
    no->compras = P;
    no->esquerda = NULL;
    no->direita= NULL;
    no->altura = 1;
    return no;
}

// Fun��o para fazer uma rota��o simples � direita
No* rotacaoDireita(No* y) {
    No* x = y->esquerda;
    No* T2 = x->direita;

    // Realiza a rota��o
    x->direita = y;
    y->esquerda = T2;

    // Atualiza as alturas
    y->altura = max(getAltura(y->esquerda), getAltura(y->direita)) + 1;
    x->altura = max(getAltura(x->esquerda), getAltura(x->direita)) + 1;

    return x;
}

// Fun��o para fazer uma rota��o simples � esquerda
No* rotacaoEsquerda(No* x) {
    No* y = x->direita;
    No* T2 = y->esquerda;

    // Realiza a rota��o
    y->esquerda = x;
    x->direita = T2;

    // Atualiza as alturas
    x->altura = max(getAltura(x->esquerda), getAltura(x->direita)) + 1;
    y->altura = max(getAltura(y->esquerda), getAltura(y->direita)) + 1;

    return y;
}

// Fun��o para obter o fator de balanceamento de um n�
int getBalanceamento(No* no) {
    if (no == NULL)
        return 0;
    return getAltura(no->esquerda) - getAltura(no->direita);
}

// Fun��o para inserir uma chave em uma �rvore AVL
No* inserir(No* no, Produto P) {
    // Realiza a inser��o normal de uma �rvore bin�ria de pesquisa
    if (no == NULL)
        return novoNo(P);

    if (P.codigo < no->compras.codigo)
        no->esquerda = inserir(no->esquerda, P);

    else if (P.codigo > no->compras.codigo)
        no->direita = inserir(no->direita, P);

    else // Chaves iguais n�o s�o permitidas
        printf("Codigo ja cadastrado em outra compra!");
        return no;
    // Atualiza a altura do n� pai
    no->altura = 1 + max(getAltura(no->esquerda), getAltura(no->direita));

    // Obt�m o fator de balanceamento do n� pai
    int balanceamento = getBalanceamento(no);

    // Caso de desbalanceamento, existem 4 casos poss�veis

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
    // �rvore balanceada, retorna o n� sem altera��es
    return no;
}

// Fun��o para buscar uma chave em uma �rvore AVL
No* busca(No* raiz, Produto P) {
    // Caso a �rvore esteja vazia ou a chave seja encontrada
    if (raiz == NULL || raiz->compras.codigo == P.codigo)
        return raiz;

    // Se a chave for menor que a chave do n� atual, busca na sub�rvore esquerda
    if (P.codigo < raiz->compras.codigo)
        return busca(raiz->esquerda, P);

    // Se a chave for maior que a chave do n� atual, busca na sub�rvore direita
    return busca(raiz->direita, P);
}

// Fun��o para imprimir a �rvore em ordem (in-order traversal)
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

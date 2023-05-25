#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int chave;
    struct No* esquerda;
    struct No* direita;
    int altura;
} No;

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
No* novoNo(int chave) {
    No* no = (No*)malloc(sizeof(No));
    no-> chave = chave;
    no-> esquerda = NULL;
    no-> direita= NULL;
    no-> altura = 1;
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
No* inserir(No* no, int chave) {
    // Realiza a inser��o normal de uma �rvore bin�ria de pesquisa
    if (no == NULL)
        return novoNo(chave);

    if (chave < no->chave)
        no->esquerda = inserir(no->esquerda, chave);

    else if (chave > no->chave)
        no->direita = inserir(no->direita, chave);

    else // Chaves iguais n�o s�o permitidas
        return no;
    // Atualiza a altura do n� pai
    no->altura = 1 + max(getAltura(no->esquerda), getAltura(no->direita));

    // Obt�m o fator de balanceamento do n� pai
    int balanceamento = getBalanceamento(no);

    // Caso de desbalanceamento, existem 4 casos poss�veis

    // Caso esquerda-esquerda
    if (balanceamento > 1 && chave < no->esquerda->chave)
        return rotacaoDireita(no);

    // Caso direita-direita
    if (balanceamento < -1 && chave > no->direita->chave)
        return rotacaoEsquerda(no);

    // Caso esquerda-direita
    if (balanceamento > 1 && chave > no->esquerda->chave) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Caso direita-esquerda
    if (balanceamento < -1 && chave < no->direita->chave) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    // �rvore balanceada, retorna o n� sem altera��es
    return no;
}

// Fun��o para buscar uma chave em uma �rvore AVL
No* busca(No* raiz, int chave) {
    // Caso a �rvore esteja vazia ou a chave seja encontrada
    if (raiz == NULL || raiz->chave == chave)
        return raiz;

    // Se a chave for menor que a chave do n� atual, busca na sub�rvore esquerda
    if (chave < raiz->chave)
        return busca(raiz->esquerda, chave);

    // Se a chave for maior que a chave do n� atual, busca na sub�rvore direita
    return busca(raiz->direita, chave);
}

// Fun��o para imprimir a �rvore em ordem (in-order traversal)
void imprimir(No* no) {
    if (no == NULL)
        return;

    imprimir(no->esquerda);
    printf("%d ", no->chave);
    imprimir(no->direita);
}

int main() {
    No* raiz = NULL; // Raiz da �rvore AVL

    int op, chave;

    do {
        system("cls");
        puts("\n\t\t\t\tARVORE AVL \n");
        puts("\t1  - INSERIR ELEMENTO\n \t2  - IMPRIMIR ARVORE\n\t3  - BUSCAR ELEMENTO\n\t0 - SAIR\n\n");
        printf("\nINFORME SUA OPCAO:\n");
        scanf("%d", &op); // Escolha da Op��o

        switch (op) {
            case 1: {
                printf("Informe um elemento: ");
                scanf("%d", &chave);
                raiz = inserir(raiz, chave);
                printf("Elemento inserido com sucesso!\n");
                break;
            }

            case 2: {
                printf("�rvore em ordem: ");
                imprimir(raiz);
                printf("\n");
                break;
            }

            case 3: {
                printf("Elemento escolhido para busca: ");
                scanf("%d", &chave);
                No* resultado = busca(raiz, chave);

                if (resultado != NULL)
                    printf("Elemento encontrado!\n");

                else
                    printf("Elemento n�o encontrado!\n");
                break;
            }

            case 0: {
                printf("Encerrando o programa...\n");
                break;
            }

            default:
                puts("OPCAO INCORRETA,TENTAR NOVAMENTE.");
                break;
        }
        getchar();
        getchar();
    } while (op != 0);

    return 0;
}

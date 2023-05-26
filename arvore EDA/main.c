#include "lib.h"

int main(){
    No* raiz = NULL; // Raiz da árvore AVL

    int op;
    Produto P;

    do {
        system("cls");
        puts("\n\t\t\t\tARVORE AVL \n");
        puts("\t1  - INSERIR ELEMENTO\n \t2  - IMPRIMIR ARVORE\n\t3  - BUSCAR ELEMENTO\n\t0 - SAIR\n\n");
        printf("\nINFORME SUA OPCAO:\n");
        scanf("%d", &op); // Escolha da Opção

        switch (op) {
            case 1: {
                printf("Informe o nome do produto: ");
                scanf(" %[^\n]", P.nomeProduto);
                printf("Informe o preco do produto: ");
                scanf("%f", &P.preco);
                printf("Informe a quantidade comprada: ");
                scanf("%d", &P.quantidade);
                printf("Informe o codigo da compra: ");
                scanf("%d", &P.codigo);

                raiz=inserir(raiz, P);
                break;
            }

            case 2: {
                imprimir(raiz);
                printf("\n");
                break;
            }

            case 3: {
                printf("Informe o codigo da compra: ");
                scanf("%d", &P.codigo);
                No* resultado = busca(raiz, P);

                if (resultado != NULL)
                    imprimirUnicaCompra(resultado);

                else
                    printf("Compra não encontrado!\n");
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

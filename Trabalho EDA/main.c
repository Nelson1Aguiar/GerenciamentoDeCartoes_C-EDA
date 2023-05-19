#include "lib.h"


//Programa principal
int main()
{
    int op, hash, pos;
    TlistaUsuario L;
    TlistaCardCompra C;
	Telemento dado, aux;

    criar(&L,&C);

    do{
    //Exibir menu
        system("cls");
        puts("\n\t\t\t\tEDITOR DE LISTAS\n");
        puts("\t1  - EXIBIR LISTA DE USUARIOS\n\t2  - INSERIR USUARIO\n\t3  - EXIBIR CARTOES\n\t4  - CADASTRAR NOVO CARTAO\n\t0  - SAIR");
        printf("\nINFORME SUA OPCAO:\n");
        scanf("%d", &op);//Escolha da Op��o

        switch(op)
        {
        //Op��o de exibir lista
    		case 1:
            {
    			 exibirUsuario(L);
    		}break;
    	//inserir
    		case 2:
            {
                printf("Informe seu nome completo: ");
                scanf(" %s", dado.usuario.nome);

                printf("Informe seu CPF: ");
                scanf("%d", &dado.usuario.cpf);

                printf("Informe seu endereco: ");
                scanf(" %s", dado.usuario.endereco);

                printf("Agora precisamos cadastrar um cartao, informe o numero: ");
                scanf("%d",&dado.cartao.numero);

                printf("Informe o dia de vencimento: ");
                scanf("%d",&dado.cartao.dia);

                printf("Informe o mes de vencimento: ");
                scanf("%d",&dado.cartao.mes);

                printf("Informe o ano de vencimento: ");
                scanf("%d",&dado.cartao.ano);

                if(inserirUsuario(&L,&C, dado)){
                    printf("Inserido!");
                    printf(" Ola %s",dado.usuario.nome);
                }


            }break;

            case 3:
            {
                exibirCartoes(C);

            }break;

           case 4:
            {
                int indice;
                printf("Digite o CPF: ");
                scanf(" %d",&dado.usuario.cpf);

                indice=buscarUsuario(L,dado.usuario.cpf);

                printf("Informe o numero do cartao: ");
                scanf("%d",&dado.cartao.numero);

                printf("Informe o dia de vencimento: ");
                scanf("%d",&dado.cartao.dia);

                printf("Informe o mes de vencimento: ");
                scanf("%d",&dado.cartao.mes);

                printf("Informe o ano de vencimento: ");
                scanf("%d",&dado.cartao.ano);

                inserirCartao(&L,&C,dado);



    		}break;

    		case 0:
            {
    		     printf("ENCERRANDO PROGRAMA");
    		     return 0;
    		}break;

    		// Outra op��o nao oferecida
    		default:
    			puts("OPCAO INCORRETA,TENTAR NOVAMENTE.");break;

        }
	getch();
    }while(op!=0);

  system("PAUSE");
  return 0;
}

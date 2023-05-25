#include "lib.h"


//Programa principal
int main()
{
    int op;
    TlistaUsuario L;
    TlistaCardCompra C;
	Telemento dadoUser,dadoCard;

    L=criarUsuario();
    C=criarCartao();

    do{
    //Exibir menu
        system("cls");
        puts("\n\t\t\t\tEDITOR DE LISTAS\n");
        puts("\t1 - EXIBIR LISTA DE USUARIOS\n\t2 - INSERIR USUARIO\n\t3 - EXIBIR CARTOES\n\t4 - CADASTRAR NOVO CARTAO\n\t5 - BUSCAR USUARIO\n\t0 - SAIR");
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
                scanf(" %[^\n]", dadoUser.usuario.nome);

                printf("Informe seu CPF: ");
                scanf("%d", &dadoUser.usuario.cpf);

                printf("Informe seu endereco: ");
                scanf(" %[^\n]", dadoUser.usuario.endereco);

                printf("Agora precisamos cadastrar um cartao, informe o numero: ");
                scanf("%d",&dadoCard.cartao.numero);

                printf("Informe o dia de vencimento: ");
                scanf("%d",&dadoCard.cartao.dia);

                printf("Informe o mes de vencimento: ");
                scanf("%d",&dadoCard.cartao.mes);

                printf("Informe o ano de vencimento: ");
                scanf("%d",&dadoCard.cartao.ano);

                if(inserirUsuario(&L,&C, dadoUser,dadoCard)){
                    printf("Inserido!");
                    printf(" Ola %s",dadoUser.usuario.nome);
                }


            }break;

            case 3:
            {
                exibirCartoes(C);

            }break;

           case 4:
            {
                printf("Digite o CPF: ");
                scanf(" %d",&dadoUser.usuario.cpf);

                if(buscarUsuario(L,dadoUser.usuario.cpf)){
                    int pos=buscarUsuario(L,dadoUser.usuario.cpf);

                    if(L.elemento[pos].usuario.qtdCartoes>=10){
                        printf("Maximo de cartoes atingido!");
                        break;
                    }
                    else{
                        printf("Informe o numero do cartao: ");
                        scanf("%d",&dadoCard.cartao.numero);

                        printf("Informe o dia de vencimento: ");
                        scanf("%d",&dadoCard.cartao.dia);

                        printf("Informe o mes de vencimento: ");
                        scanf("%d",&dadoCard.cartao.mes);

                        printf("Informe o ano de vencimento: ");
                        scanf("%d",&dadoCard.cartao.ano);

                        inserirCartao(&L,&C,dadoCard,dadoUser);
                        printf("Cartao cadastrado!");
                    }
                }
                else{
                    printf("Usuario nao cadastrado!");
                }


    		}break;

           case 5:
            {
                printf("Digite o CPF do usuario que deseja: ");
                scanf(" %d",&dadoUser.usuario.cpf);
                int pos=buscarUsuario(L,dadoUser.usuario.cpf);
                exibirUsuarioUnico(L,pos);
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

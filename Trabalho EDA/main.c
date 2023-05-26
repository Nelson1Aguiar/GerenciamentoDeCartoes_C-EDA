#include "lib.h"


//Programa principal
int main()
{
    int op;
    TlistaUsuario L;
    TlistaCardCompra C;
	Telemento dadoUser,dadoCard;
	Produto P;
	No* raiz=NULL;

    L=criarUsuario();
    C=criarCartao();

    do{
    //Exibir menu
        system("cls");
        puts("\n\t\t\t\tEDITOR DE LISTAS\n");
        puts("\t1 - EXIBIR LISTA DE USUARIOS\n\t2 - INSERIR USUARIO\n\t3 - EXIBIR CARTOES E COMPRAS\n\t4 - CADASTRAR NOVO CARTAO\n\t5 - BUSCAR USUARIO");
        puts("\t6 - CADASTRAR COMPRA\n\t7 - BUSCAR UM CARTAO\n\t0 - SAIR");
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
                scanf(" %lli", &dadoUser.usuario.cpf);

                printf("Informe seu endereco: ");
                scanf(" %[^\n]", dadoUser.usuario.endereco);

                printf("Agora precisamos cadastrar um cartao, informe o numero: ");
                scanf("%lli",&dadoCard.cartao.numero);

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
                scanf(" %lli",&dadoUser.usuario.cpf);

                if(buscarUsuario(L,dadoUser.usuario.cpf)){
                    int pos=buscarUsuario(L,dadoUser.usuario.cpf);
                    dadoUser=L.elemento[pos];

                    if(L.elemento[pos].usuario.qtdCartoes>=10){
                        printf("Maximo de cartoes atingido!");
                        break;
                    }
                    else{
                        printf("Informe o numero do cartao: ");
                        scanf("%lli",&dadoCard.cartao.numero);

                        printf("Informe o dia de vencimento: ");
                        scanf("%d",&dadoCard.cartao.dia);

                        printf("Informe o mes de vencimento: ");
                        scanf("%d",&dadoCard.cartao.mes);

                        printf("Informe o ano de vencimento: ");
                        scanf("%d",&dadoCard.cartao.ano);

                        if(inserirCartao(&L,&C,dadoCard,dadoUser)){
                            printf("Cartao cadastrado!");
                        }
                    }
                }
                else{
                    printf("Usuario nao cadastrado!");
                }


    		}break;

           case 5:
            {
                printf("Digite o CPF do usuario que deseja: ");
                scanf(" %lli",&dadoUser.usuario.cpf);
                int pos=buscarUsuario(L,dadoUser.usuario.cpf);
                exibirUsuarioUnico(L,pos);
            }break;

           case 6:
            {
                printf("Digite o numero do cartao da compra: ");
                scanf(" %lli",&dadoCard.cartao.numero);
                int endereco=buscarCartao(C,dadoCard.cartao.numero);
                if(C.elemento[endereco].cartao.numero==0){
                    printf("Cartao nao cadastrado!");
                    break;
                }

                printf("Informe o nome do produto: ");
                scanf(" %[^\n]", P.nomeProduto);
                printf("Informe o preco do produto: ");
                scanf("%f", &P.preco);
                printf("Informe a quantidade comprada: ");
                scanf("%d", &P.quantidade);
                printf("Informe o codigo da compra: ");
                scanf("%d", &P.codigo);

                C.elemento[endereco].cartao.produto=inserir(C.elemento[endereco].cartao.produto, P);

            }break;

           case 7:
            {
                printf("Digite o numero do cartao: ");
                scanf(" %lli",&dadoCard.cartao.numero);
                int endereco=buscarCartao(C,dadoCard.cartao.numero);
                ExibirCartaoUnico(C,endereco);

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

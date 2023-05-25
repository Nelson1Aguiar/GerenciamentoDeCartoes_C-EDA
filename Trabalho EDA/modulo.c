#include "lib.h"

TlistaUsuario criarUsuario(){
    TlistaUsuario *L=malloc(sizeof(TlistaUsuario));
    L->elemento=malloc(sizeof(Telemento)*MAX);
    memset(L->elemento, 0, (sizeof(elemento)));
	L->n = 0;
    L->m=MAX;
    return *L;
}

TlistaCardCompra criarCartao(){
    TlistaCardCompra *C=malloc(sizeof(TlistaCardCompra));
    C->elemento=malloc(sizeof(Telemento)*MAX);
    memset(C->elemento, 0, (sizeof(elemento)));
    for(int i=0;i<MAX;i++){
        C->elemento[i].cartao.numero=0;
    }
	C->n = 0;
    C->m=MAX;
    for(int i=0;i<C->m;i++){
        C->elemento[i].cartao.numero=0;
    }
    return *C;
}

void redimensionarUsuario(TlistaCardCompra *C,TlistaUsuario *L,int tam_novo){
    Telemento *nova,*antigaUser,*antigaCard;
    int tam_antigo;
    nova=malloc(sizeof(Telemento)*tam_novo);
    memset(nova, 0, (sizeof(nova)));

    antigaUser=L->elemento;
    antigaCard=C->elemento;

    tam_antigo=L->m;
    L->elemento=nova;
    L->m=tam_novo;
    L->n=0;

    for(int i=0;i<tam_antigo;i++){
        if(antigaUser[i].usuario.cpf!=0){
            for(int j=0;j<tam_antigo;j++){
                for(int k=0;k<10;k++){
                    if(antigaCard[i].cartao.numero==antigaUser[j].usuario.numeroCartao[k]){
                        inserirUsuario(L,C,antigaUser[j],antigaCard[i]);
                    }
                }
            }
        }
    }
    free(antigaUser);
    free(antigaCard);
}

void redimensionarCartao(TlistaUsuario *L,TlistaCardCompra *C,int tam_novo){
    Telemento *nova,*antigaCartao,*antigaUser;
    int tam_antigo;
    nova=malloc(sizeof(Telemento)*tam_novo);
    memset(nova, 0, (sizeof(nova)));

    antigaCartao=C->elemento;
    antigaUser=L->elemento;

    tam_antigo=C->m;
    C->elemento=nova;
    C->m=tam_novo;
    C->n=0;

    for(int i=0;i<tam_antigo;i++){
        if(antigaCartao[i].cartao.numero!=0){
            for(int j=0;j<tam_antigo;j++){
                for(int k=0;k<10;k++){
                    if(antigaCartao[i].cartao.numero==antigaUser[j].usuario.numeroCartao[k]){
                    inserirCartao(L,C,antigaCartao[i],antigaUser[j]);
                    }
                }
            }
        }
    }
    free(antigaUser);
    free(antigaCartao);
}

int tamanhoUsuario(TlistaUsuario L){
	return L.n;
}

int tamanhoCartao(TlistaCardCompra C){
	return C.n;
}

//int elemento(TlistaUsuario L, int pos, Telemento *dado){
//	if(pos<0 || pos >MAX) return 0;
	//*dado = L.elemento[pos];
	//return 1;
//}

void exibirUsuario(TlistaUsuario L){
	int i;
    if(tamanhoUsuario(L)!=0)
        for (i=0; i<L.m; i++){
            if(L.elemento[i].usuario.cpf!=NULL){
                printf("indice: %d\n", i);
                printf("Nome: %s\n", L.elemento[i].usuario.nome);
                printf("Endereco: %s\n", L.elemento[i].usuario.endereco);
                printf("CPF: %d\n",L.elemento[i].usuario.cpf);
                printf("Numero cartao ou cartoes: ");
                for(int j=0;j<10;j++){
                    if(L.elemento[i].usuario.numeroCartao[j]!=0){
                        printf(" %d || ",L.elemento[i].usuario.numeroCartao[j]);
                    }
                }
                printf("\n\n");
            }
        }
    else
        puts("NAO EXISTE NENHUM USUÁRIO NO MOMENTO");
}

void exibirCartoes(TlistaCardCompra C){
    int i;
    if(tamanhoCartao(C)!=0)
        for(i=0;i<C.m;i++){
        if(C.elemento[i].cartao.numero!=0){
            printf("Indice: %d\n",i);
            printf("Numero: %d\n",C.elemento[i].cartao.numero);
            printf("Nome do titular: %s\n",C.elemento[i].cartao.nome);
            printf("Validade: %d/%d/%d\n\n",C.elemento[i].cartao.dia,C.elemento[i].cartao.mes,C.elemento[i].cartao.ano);
        }
    }
    else
        printf("Nenhum cartao cadastrado! Faca o cadastro de usuario primeiro");
}

int hashing(int chave,int tam){
	return chave % tam;
}

int inserirUsuario(TlistaUsuario *L,TlistaCardCompra *C,Telemento dado,Telemento dadoCard){
    float carg=L->n/L->m;
    if(carg>=fator_carga){
        redimensionarUsuario(C,L,L->m * 2);
    }
    for(int i=0;i<L->m;i++){
        if(dado.usuario.cpf==L->elemento[i].usuario.cpf){
            printf("User ja cadastrado!");
            return 0;
        }
    }
    int endereco = hashing(dado.usuario.cpf,L->m);
    while(L->elemento[endereco].usuario.cpf!=0){
        endereco=hashing(endereco+1,L->m);
    }
    strcpy(L->elemento[endereco].usuario.nome,dado.usuario.nome);
    L->elemento[endereco].usuario.cpf = dado.usuario.cpf;
    strcpy(L->elemento[endereco].usuario.endereco,dado.usuario.endereco);
    L->n=L->n+1;
    inserirCartao(L,C,dadoCard,dado);
	return 1;
}

int inserirCartao(TlistaUsuario *L,TlistaCardCompra *C, Telemento dado,Telemento dadoUser){
    float carg=C->n/C->m;
    if(carg>=0.60){
        printf("Tabela cheia, redimensionando");
        redimensionarCartao(L,C,C->m * 2);
    }
    for(int i=0;i<C->m;i++){
        if(dado.cartao.numero==C->elemento[i].cartao.numero){
            printf("Cartao ja cadastrado!");
            return 0;
        }
    }
    int endereco = hashing(dado.cartao.numero,C->m);

    while(C->elemento[endereco].cartao.numero!=0){
        endereco=hashing(endereco+1,C->m);
    }

    C->elemento[endereco].cartao.numero = dado.cartao.numero;
    strcpy(C->elemento[endereco].cartao.nome,dadoUser.usuario.nome);
    C->elemento[endereco].cartao.dia=dado.cartao.dia;
    C->elemento[endereco].cartao.mes=dado.cartao.mes;
    C->elemento[endereco].cartao.ano=dado.cartao.ano;
    C->n=C->n+1;
    int pos=buscarUsuario(*L,dadoUser.usuario.cpf);
    atrelarCartaoUsuario(L,pos,dado);
	return C->elemento[endereco].cartao.numero;
}

int buscarUsuario(TlistaUsuario L,int chave){
    int endereco=hashing(chave,L.m);
     while(L.elemento[endereco].usuario.cpf!=0){
        if(L.elemento[endereco].usuario.cpf == chave){
            return endereco;
        }
        else{
            endereco=hashing(endereco+1,L.m);
        }
    }
}
void atrelarCartaoUsuario(TlistaUsuario *L,int pos,Telemento dado){
    for(int i=0;i<10;i++){
       if(L->elemento[pos].usuario.numeroCartao[i]==dado.cartao.numero){
            return 0;
       }
    }
    L->elemento[pos].usuario.numeroCartao[L->elemento[pos].usuario.qtdCartoes]=dado.cartao.numero;
    L->elemento[pos].usuario.qtdCartoes+=1;
}
void exibirUsuarioUnico(TlistaUsuario L,int pos){
    printf("indice: %d\n", pos);
    printf("Nome: %s\n", L.elemento[pos].usuario.nome);
    printf("Endereco: %s\n", L.elemento[pos].usuario.endereco);
    printf("CPF: %d\n",L.elemento[pos].usuario.cpf);
    printf("Numero cartao ou cartoes: ");
    for(int j=0;j<10;j++){
        if(L.elemento[pos].usuario.numeroCartao[j]!=0){
            printf(" %d || ",L.elemento[pos].usuario.numeroCartao[j]);
        }
    }
}

int buscarCartao(TlistaCardCompra C,int chave){
    int endereco=hashing(chave,C.m);
     while(C.elemento[endereco].cartao.numero!=0){
        if(C.elemento[endereco].cartao.numero == chave){
            return endereco;
        }
        else{
            endereco=hashing(endereco+1,C.m);
        }
    }
}






#include "lib.h"

void criar(TlistaUsuario *L, TlistaCardCompra *C){
	memset(L->elemento, 0, (sizeof(L->elemento)));
	C->n = 0;
	memset(C->elemento, 0, (sizeof(C->elemento)));
	C->n = 0;
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
        for (i=0; i<MAX; i++){
            if(L.elemento[i].usuario.cpf!=NULL){
                printf("indice: %d\n", i);
                printf("Nome: %s\n", L.elemento[i].usuario.nome);
                printf("Endereco: %s\n", L.elemento[i].usuario.endereco);
                printf("CPF: %d\n",L.elemento[i].usuario.cpf);
                printf("Numero cartao ou cartoes: ");
                for(int j=0;j<10;j++){
                    if(L.elemento[i].usuario.numeroCartao[j]!=0){
                        printf(" %d ",L.elemento[i].usuario.numeroCartao[j]);
                    }
                }
                printf("\n\n");
            }
        }
    else
        puts("nao ha elementos");
}

void exibirCartoes(TlistaCardCompra C){
    int i;
    if(tamanhoCartao(C)!=0)
        for(i=0;i<MAX;i++){
        if(C.elemento[i].cartao.numero!=NULL){
            printf("Indice: %d\n",i);
            printf("Numero: %d\n",C.elemento[i].cartao.numero);
            printf("Nome do titular: %s\n",C.elemento[i].cartao.nome);
            printf("Validade: %d/%d/%d\n\n",C.elemento[i].cartao.dia,C.elemento[i].cartao.mes,C.elemento[i].cartao.ano);
        }
    }
    else
        printf("Nenhum cartao cadastrado! Faca o cadastro de usuario primeiro");
}

int hashing(int chave){
	return chave % MAX;
}

int inserirUsuario(TlistaUsuario *L,TlistaCardCompra *C,Telemento dado){
    for(int i=0;i<MAX;i++){
        if(dado.usuario.cpf==L->elemento[i].usuario.cpf){
            printf("User ja cadastrado!");
            return 0;
        }
    }
    int endereco = hashing(dado.usuario.cpf);
    while(L->elemento[endereco].usuario.cpf!=0){
        endereco=hashing(endereco+1);
    }
    strcpy(L->elemento[endereco].usuario.nome,dado.usuario.nome);
    L->elemento[endereco].usuario.cpf = dado.usuario.cpf;
    strcpy(L->elemento[endereco].usuario.endereco,dado.usuario.endereco);
    L->elemento[endereco].usuario.numeroCartao[L->elemento[endereco].usuario.qtdCartoes]=dado.cartao.numero;
    L->n+=1;
    int pos=buscarUsuario(*L,L->elemento[endereco].usuario.cpf);
    inserirCartao(L,C,dado);
	return 1;
}

int inserirCartao(TlistaUsuario *L,TlistaCardCompra *C, Telemento dado){
    int contadorDeCartao=0;
    for(int i=0;i<MAX;i++){
        if(dado.cartao.numero==C->elemento[i].cartao.numero){
            printf("Cartao ja cadastrado!");
            return 0;
        }
    }
    int endereco = hashing(dado.cartao.numero);

    while(C->elemento[endereco].cartao.numero!=0){
        endereco=hashing(endereco+1);
    }

    C->elemento[endereco].cartao.numero = dado.cartao.numero;
    strcpy(C->elemento[endereco].cartao.nome,dado.usuario.nome);
    C->elemento[endereco].cartao.dia=dado.cartao.dia;
    C->elemento[endereco].cartao.mes=dado.cartao.mes;
    C->elemento[endereco].cartao.ano=dado.cartao.ano;
    C->n+=1;
    if(dado.usuario.cpf==L->elemento[endereco].usuario.cpf){
        L->elemento[endereco].usuario.qtdCartoes+=1;
    }
    L->elemento[endereco].usuario.numeroCartao[L->elemento[endereco].usuario.qtdCartoes+1]=dado.cartao.numero;
	return C->elemento[endereco].cartao.numero;
}

int buscarUsuario(TlistaUsuario L,int chave){
    int endereco=hashing(chave);
     while(L.elemento[endereco].usuario.cpf!=0){
        if(L.elemento[endereco].usuario.cpf == chave){
            return endereco;
        }
        else{
            endereco=hashing(endereco+1);
        }
    }
}

int buscarCartao(TlistaCardCompra C,int chave){

}












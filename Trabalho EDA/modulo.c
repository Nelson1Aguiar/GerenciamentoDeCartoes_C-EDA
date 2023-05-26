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
	C->n = 0;
    C->m=MAX;
    return *C;
}

void redimensionarUsuario(TlistaCardCompra *C,TlistaUsuario* L,int tam_novo){
    Telemento *antigaCard,*antigaUser;
    int tam_antigo;

    TlistaUsuario *nova=malloc(sizeof(TlistaUsuario));
    nova->elemento=malloc(sizeof(Telemento)*tam_novo);
    memset(nova->elemento, 0, (sizeof(elemento)));

    antigaUser=L->elemento;
    antigaCard=C->elemento;

    tam_antigo=L->m;
    L->elemento=nova->elemento;
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

void redimensionarCartao(TlistaUsuario *L,TlistaCardCompra*C,int tam_novo){
    Telemento *antigaCartao,*antigaUser;
    int tam_antigo;

    TlistaCardCompra *nova=malloc(sizeof(TlistaCardCompra));
    nova->elemento=malloc(sizeof(Telemento)*tam_novo);
    memset(nova->elemento, 0, (sizeof(elemento)));

    antigaCartao=C->elemento;
    antigaUser=L->elemento;

    tam_antigo=C->m;
    C->elemento=nova->elemento;

    C->m=tam_novo;
    C->n=0;

    for(int i=0;i<tam_antigo;i++){
        if(antigaCartao[i].cartao.numero!=0){
            for(int j=0;j<tam_antigo;j++){
                for(int k=0;k<10;k++){
                    if(antigaCartao[i].cartao.numero==antigaUser[j].usuario.numeroCartao[k]){
                    inserirCartao(L,C,antigaCartao[i],antigaUser[j]);
                    inserirCompras(C,antigaCartao[i]);
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

void exibirUsuario(TlistaUsuario L){
	int i;
    if(tamanhoUsuario(L)!=0)
        for (i=0; i<L.m; i++){
            if(L.elemento[i].usuario.cpf!=0){
                printf("indice: %d\n", i);
                printf("Nome: %s\n", L.elemento[i].usuario.nome);
                printf("Endereco: %s\n", L.elemento[i].usuario.endereco);
                printf("CPF: %lli \n",L.elemento[i].usuario.cpf);
                printf("Numero cartao ou cartoes: ");
                for(int j=0;j<10;j++){
                    if(L.elemento[i].usuario.numeroCartao[j]!=0){
                        printf(" %lli || ",L.elemento[i].usuario.numeroCartao[j]);
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
        if(C.elemento[i].cartao.numero!=0 && C.elemento[i].cartao.ano!=0){
            printf("Indice: %d\n",i);
            printf("Numero: %lli\n",C.elemento[i].cartao.numero);
            printf("Nome do titular: %s\n",C.elemento[i].cartao.nome);
            printf("Validade: %d/%d/%d\n\n",C.elemento[i].cartao.dia,C.elemento[i].cartao.mes,C.elemento[i].cartao.ano);
            if(C.elemento[i].cartao.produto==NULL){
                printf("Nenhuma compra realizada!\n");
                printf("_________________________________________________________________________\n");
            }
            else{
                printf("-------COMPRAS DO CARTAO-------\n");
                imprimir(C.elemento[i].cartao.produto);
                printf("_________________________________________________________________________\n");
            }
        }
    }
    else
        printf("Nenhum cartao cadastrado! Faca o cadastro de usuario primeiro");
}

int hashing(long long chave, int tam){
	return chave % tam;
}

int inserirUsuario(TlistaUsuario *L,TlistaCardCompra *C,Telemento dado,Telemento dadoCard){
    float carg=L->n/L->m;
    if(carg>=0.80){
        redimensionarUsuario(C,L,L->m * 2);
    }

    int endereco = hashing(dado.usuario.cpf,L->m);
    while(L->elemento[endereco].usuario.cpf!=0){
        if(dado.usuario.cpf==L->elemento[endereco].usuario.cpf){
            return 0;
        }
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
        redimensionarCartao(L,C,C->m * 2);
    }
    int endereco = hashing(dado.cartao.numero,C->m);

    while(C->elemento[endereco].cartao.numero!=0){
        if(dado.cartao.numero==C->elemento[endereco].cartao.numero){
            int pos=buscarUsuario(*L,dadoUser.usuario.cpf);
            atrelarCartaoUsuario(L,pos,dado);
            return 0;
        }
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

int buscarUsuario(TlistaUsuario L,long long chave){
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
int atrelarCartaoUsuario(TlistaUsuario *L,int pos,Telemento dado){
    for(int i=0;i<10;i++){
       if(L->elemento[pos].usuario.numeroCartao[i]==dado.cartao.numero){
            return 0;
       }
    }
    L->elemento[pos].usuario.numeroCartao[L->elemento[pos].usuario.qtdCartoes]=dado.cartao.numero;
    L->elemento[pos].usuario.qtdCartoes+=1;
    return 1;
}
int exibirUsuarioUnico(TlistaUsuario L,int pos){
     if(L.elemento[pos].usuario.cpf==0){
        printf("Usuario nao cadastrado!");
        return 0;
    }
    printf("indice: %d\n", pos);
    printf("Nome: %s\n", L.elemento[pos].usuario.nome);
    printf("Endereco: %s\n", L.elemento[pos].usuario.endereco);
    printf("CPF: %lli\n",L.elemento[pos].usuario.cpf);
    printf("Numero cartao ou cartoes: ");
    for(int j=0;j<10;j++){
        if(L.elemento[pos].usuario.numeroCartao[j]!=0){
            printf(" %lli || ",L.elemento[pos].usuario.numeroCartao[j]);
        }
    }
    return 1;
}

int buscarCartao(TlistaCardCompra C,long long chave){
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

int ExibirCartaoUnico(TlistaCardCompra C,int endereco){
    if(C.elemento[endereco].cartao.numero==0){
        printf("Cartao nao cadastrado!");
        return 0;
    }
    printf("Indice: %d\n",endereco);
    printf("Numero: %lli\n",C.elemento[endereco].cartao.numero);
    printf("Nome do titular: %s\n",C.elemento[endereco].cartao.nome);
    printf("Validade: %d/%d/%d\n\n",C.elemento[endereco].cartao.dia,C.elemento[endereco].cartao.mes,C.elemento[endereco].cartao.ano);
    if(C.elemento[endereco].cartao.produto==NULL){
        printf("Nenhuma compra realizada!\n");
        printf("_________________________________________________________________________\n");
    }
    else{
        printf("-------COMPRAS DO CARTAO-------\n");
        imprimir(C.elemento[endereco].cartao.produto);
        printf("_________________________________________________________________________\n");
        }
        return 1;
}

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

void inserirCompras(TlistaCardCompra *C,Telemento dado){
    int pos=buscarCartao(*C,dado.cartao.numero);
    C->elemento[pos].cartao.produto=dado.cartao.produto;
}

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 11

typedef struct produto{
    char nomeProduto[50];
    float preco;
    int quantidade,codigo;
} Produto;

typedef struct No {
    Produto compras;
    struct No* esquerda;
    struct No* direita;
    int altura;
} No;

struct cartao{
    long long numero;//numero unico do cartao
    char nome[60];//nome do titular do cartao
    int dia,mes,ano;//data de validade do cartao
    No* produto;
};
typedef struct cartao Card;

struct usuario{
    long long cpf;
    char endereco[60];
    long long numeroCartao[10];//cartoes cadastrados com limite de 10 cartoes
    char nome[60]; //nome do usuario
    int qtdCartoes;//quantos cartoes o usuario tem cadastrado;
};
typedef struct usuario User;

typedef struct{
	Card cartao;//A chave usada será feita com o número do cartao ou com o cpf, dependendo da tabela
	User usuario;
} Telemento;

typedef struct{
        Telemento* elemento;
        float n; // qtd de elementos inseridos na estrutura
        float m; //capacidade da tabela
} TlistaUsuario; // tabela hash de usuarios

typedef struct{
        Telemento* elemento;
        float n; // qtd de elementos inseridos na estrutura
        float m; //capacidade da tabela
} TlistaCardCompra; //Tabela hash de cartao e compras


int hashing(long long chave,int tam);
TlistaUsuario criarUsuario();
TlistaCardCompra criarCartao();
void redimensionarUsuario(TlistaCardCompra *C,TlistaUsuario *L,int tam_novo);
void redimensionarCartao(TlistaUsuario *L,TlistaCardCompra *C,int tam_novo);
int tamanho(TlistaUsuario L);
int elemento(TlistaUsuario L, int pos, Telemento *dado);
void exibirUsuario(TlistaUsuario L);
int inserirUsuario(TlistaUsuario *L,TlistaCardCompra *C,Telemento dado,Telemento dadoCard);
int inserirCartao(TlistaUsuario *L,TlistaCardCompra *C, Telemento dado,Telemento dadoUser);
int buscarUsuario(TlistaUsuario L,long long chave);
int atrelarCartaoUsuario(TlistaUsuario *L,int pos,Telemento dado);
void exibirCartoes(TlistaCardCompra C);
int exibirUsuarioUnico(TlistaUsuario L,int pos);
int ExibirCartaoUnico(TlistaCardCompra C,int endereco);
int buscarCartao(TlistaCardCompra C,long long chave);
int getAltura(No* no);
int max(int a, int b);
No* novoNo(Produto P);
No* rotacaoDireita(No* y);
No* rotacaoEsquerda(No* x);
int getBalanceamento(No* no);
No* inserir(No* no, Produto P);
void imprimir(No* no);
void inserirCompras(TlistaCardCompra *C,Telemento dado);


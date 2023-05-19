#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 23

struct cartao{
    int numero;//numero unico do cartao
    char nome[60];//nome do titular do cartao
    int dia,mes,ano;//data de validade do cartao
};
typedef struct cartao Card;

struct usuario{
    int cpf;
    char endereco[60];
    int numeroCartao[10];//cartoes cadastrados com limite de 10 cartoes
    char nome[60]; //nome do usuario
    int qtdCartoes;//vetor que diz quantos cartoes o usuario tem cadastrado;
};
typedef struct usuario User;

typedef struct{
	Card cartao;//A chave usada será feita com o número do cartao ou com o cpf, dependendo da tabela
	User usuario;
} Telemento;

typedef struct{
        Telemento elemento[MAX];
        int n; // qtd de elementos inseridos na estrutura
} TlistaUsuario; // tabela hash de usuarios

typedef struct{
        Telemento elemento[MAX];
        int n; // qtd de elementos inseridos na estrutura
} TlistaCardCompra; //Tabela hash de cartao e compras


int hashing(int chave);
void criar(TlistaUsuario *L, TlistaCardCompra *C);
int tamanho(TlistaUsuario L);
int elemento(TlistaUsuario L, int pos, Telemento *dado);
void exibirUsuario(TlistaUsuario L);
int inserirUsuario(TlistaUsuario *L,TlistaCardCompra *C, Telemento dado);
int inserirCartao(TlistaUsuario *L,TlistaCardCompra *C, Telemento dado);
int buscarUsuario(TlistaUsuario L,int chave);
int buscarCartao(TlistaCardCompra C,int chave);

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 11
#define fator_carga 0.8

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


int hashing(int chave,int tam);
TlistaUsuario criarUsuario();
TlistaCardCompra criarCartao();
void redimensionarUsuario(TlistaCardCompra *C,TlistaUsuario *L,int tam_novo);
void redimensionarCartao(TlistaUsuario *L,TlistaCardCompra *C,int tam_novo);
int tamanho(TlistaUsuario L);
int elemento(TlistaUsuario L, int pos, Telemento *dado);
void exibirUsuario(TlistaUsuario L);
int inserirUsuario(TlistaUsuario *L,TlistaCardCompra *C,Telemento dado,Telemento dadoCard);
int inserirCartao(TlistaUsuario *L,TlistaCardCompra *C, Telemento dado,Telemento dadoUser);
int buscarUsuario(TlistaUsuario L,int chave);
void atrelarCartaoUsuario(TlistaUsuario *L,int pos,Telemento dado);
void exibirCartoes(TlistaCardCompra C);
void exibirUsuarioUnico(TlistaUsuario L,int pos);
int buscarCartao(TlistaCardCompra C,int chave);

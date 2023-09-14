#ifndef TYPESPROJECT_H
#define TYPESPROJECT_H
using namespace std;

typedef struct nave{ 
    int prioridade;
	string nome;
    string classe;
    string recursosSuporteVidas;
    string numeroPassageiros;

    // sobrescrevendo as seguinte operação 
    bool operator == (nave p) const {return prioridade == p.prioridade;}
    bool operator < (nave p) const {return prioridade < p.prioridade;}
    bool operator > (nave p) const {return prioridade > p.prioridade;}
}Nave; 

typedef struct passgeiro{
    char nome[50];
    char planeta_de_origem[50];
    int idade;
    char identificador[30];
}Passageiro;

typedef struct  recursor {
    char nomeRecursor[50];
    int quantideda;
    // 0 para não contem recusor de suporte a vida, e 1 contem 
    int suporteVida; 
}Recursor;



#endif
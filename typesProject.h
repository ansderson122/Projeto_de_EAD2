#ifndef TYPESPROJECT_H
#define TYPESPROJECT_H
using namespace std;

typedef struct nave{ 
    int prioridade;
	string nome;
    string classe;
    string recursosSuporteVidas;
    string numeroPassageiros;
    int nivelDeDoenca;

    // sobrescrevendo as seguinte operação 
    bool operator == (nave p) const {return prioridade == p.prioridade;}
    bool operator < (nave p) const {return prioridade < p.prioridade;}
    bool operator > (nave p) const {return prioridade > p.prioridade;}
}Nave; 

typedef struct passageiro{
    string nome;
    string planeta_de_origem;
    unsigned int idade;
    string identificador;
}Passageiro;

typedef struct  recursor {
    string nomeRecursor;
    unsigned int quantideda;
    // 0 para não contem recusor de suporte a vida, e 1 contem 
    int suporteVida; 
}Recursor;



#endif
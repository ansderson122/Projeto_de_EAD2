#ifndef TYPESPROJECT_H
#define TYPESPROJECT_H
using namespace std;



typedef struct passageiro{
    string nome;
    string planeta_de_origem;
    unsigned int idade;
    string identificador;
}Passageiro;

typedef struct  recurso {
    string nomerecurso;
    unsigned int quantideda;
    // 0 para não contem recusor de suporte a vida, e 1 contem 
    string suporteVida; 
}Recurso;

typedef struct nave{ 
    int prioridade;
	string nome;
    string classe;
    string recursosSuporteVidas;
    int numeroPassageiros;
    int nivelDeDoenca;

    vector<Recurso> rescursos;
    vector<Passageiro> passageiros;

    // sobrescrevendo as seguinte operação 
    bool operator == (nave p) const {return prioridade == p.prioridade;}
    bool operator < (nave p) const {return prioridade < p.prioridade;}
    bool operator > (nave p) const {return prioridade > p.prioridade;}
}Nave; 



#endif
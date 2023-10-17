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
    float prioridade;
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

inline string geraSigla(vector<Recurso> rescursos){
    string sigla = "";
    for(unsigned int i = 0; i < rescursos.size();i++){
        sigla += rescursos[i].nomerecurso[0];
    }
    return sigla;
}

typedef struct grupo{
    Nave naves[6];
    Grupo *prox;
}Grupo;


#endif
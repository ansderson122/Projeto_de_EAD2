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

    string suporteVida; 

    bool operator<(const recurso& other) const {
        return nomerecurso < other.nomerecurso;
    }
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
}Nave; 

inline string geraSigla(vector<Recurso> rescursos){
    sort(rescursos.begin(), rescursos.end());
    string sigla = "";
    for(unsigned int i = 0; i < rescursos.size();i++){
        sigla += rescursos[i].nomerecurso;
    }
    return sigla;
}

typedef struct grupo{
    Nave naves[6];
    grupo *prox = nullptr;
    int pos = 0;
}Grupo;


#endif
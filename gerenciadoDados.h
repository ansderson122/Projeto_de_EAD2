#ifndef GERENCIADODADOS_H
#define GERENCIADODADOS_H
using namespace std;
#include <string>
#include <vector>
#include "typesProject.h"

class gerenciadoDados
{
private:
    string pathPrincipal;
    string pathSegundaria;
    bool criarDiretorio(string path);
    bool criaArquivo(string path,string nome);
public:
    gerenciadoDados(/* args */);
    ~gerenciadoDados();
    bool carregaDados(vector<Nave>& out_dados);
    bool adicionarNave(Nave* dados); 
    bool salvarArquivo(vector<Nave> naves);
    bool registraPassageiro(string nomeNave, Passageiro * passageiro);
    bool registraRecurso(string nomeNave, Recurso* recurso);
    bool criaBancoDadosNave(string nomeNave);
    bool carregaRecursos(string nomeNave ,vector<Recurso>& out_recursos);
    bool carregaPassageiros(string nomeNave ,vector<Passageiro>& out_passageiros);
};




#endif

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
    bool editarPrioridade(string nome, int prioridade);
    bool registraPassageiro(string nomeNave, Passageiro * passageiro);
    bool registraRecurso(string nomeNave, Recurso* recurso);
};




#endif

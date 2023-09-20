#ifndef GERENCIADODADOS_H
#define GERENCIADODADOS_H
using namespace std;
#include <string>
#include <vector>
#include "typesProject.h"

class gerenciadoDados
{
private:
    bool criarDiretorio(string path);
    bool criaArquivo(string path,string nome);
public:
    gerenciadoDados(/* args */);
    ~gerenciadoDados();
    bool carregaDados(string path , vector<Nave>& out_dados);
    bool adicionarNave(Nave* dados); 
};




#endif

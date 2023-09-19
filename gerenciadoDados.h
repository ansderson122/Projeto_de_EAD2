#ifndef GERENCIADODADOS_H
#define GERENCIADODADOS_H
using namespace std;
#include <string>
#include <vector>
#include "typesProject.h"

class gerenciadoDados
{
private:
    /* data */
public:
    gerenciadoDados(/* args */);
    ~gerenciadoDados();
    bool carregaDados(string path , vector<Nave>& out_dados);
    bool adicionarDados(string path, Nave* dados); 
};




#endif

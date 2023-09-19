#include <iostream>
#include <fstream>
using namespace std;

#include "gerenciadoDados.h"
#include <sstream>


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

gerenciadoDados::gerenciadoDados(/* args */)
{
}

gerenciadoDados::~gerenciadoDados()
{
}

bool gerenciadoDados::carregaDados(string path, vector<Nave>& out_dados) {
    ifstream arquivo(path);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return false;
    }

    int campoNum;
    string linha;
    while (std::getline(arquivo, linha)) {
        stringstream ss(linha);
        string campo;

        Nave novaNave; // Crie uma nova instância de Nave para cada linha

        campoNum = 0;

        while (std::getline(ss, campo, ';')) {
            switch (campoNum) {
                case 0: novaNave.nome = linha; break;
                case 1: novaNave.classe = linha; break;
                case 2: novaNave.recursosSuporteVidas = linha; break;
                case 3: novaNave.numeroPassageiros = linha; break;
        }
        campoNum++;
    }
        // Adicione a novaNave ao vetor de dados
        out_dados.push_back(novaNave);
    }

    arquivo.close();
    return true;
}



bool gerenciadoDados::adicionarDados(string path ,Nave* dados){

     // Abrir o arquivo para escrita e leitura no final
    ofstream arquivo(path, ios::app | ios::in);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return false;
    }
    // Posicionar o ponteiro no final do arquivo
    arquivo.seekp(0, ios::end);

    arquivo <<  dados->nome + ";" + dados->classe + ";" + dados->recursosSuporteVidas + ";" + dados->numeroPassageiros + ";0" <<  endl ;

    arquivo.close(); 
    return true;
}


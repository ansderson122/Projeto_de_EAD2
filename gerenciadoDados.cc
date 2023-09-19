#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "typesProject.h"

class gerenciadoDados
{
private:
    /* data */
public:
    gerenciadoDados(/* args */);
    ~gerenciadoDados();
    Nave* carregaNave(std::string nomeNave);
    bool adicionarDados(string path, Nave* dados); 
};

gerenciadoDados::gerenciadoDados(/* args */)
{
}

gerenciadoDados::~gerenciadoDados()
{
}


Nave* gerenciadoDados::carregaNave(std::string nomeNave) {
    string path = "C:/Users//ansde/Documents/Projeto_de_EAD2/dados/naves/" +  nomeNave + "/"+ nomeNave + ".txt";
 
    //cout << path << endl;

    ifstream arquivo(path);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return nullptr;
    }

    Nave* newNave = new Nave;

    string linha;
    int campo = 0;
    while (std::getline(arquivo, linha, ';')) {
        switch (campo) {
            case 0: newNave->nome = linha; break;
            case 1: newNave->classe = linha; break;
            case 2: newNave->recursosSuporteVidas = linha; break;
            case 3: newNave->numeroPassageiros = linha; break;
        }
        campo++;
    }

    arquivo.close();
    return newNave;
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



int main() {
    gerenciadoDados g;
    Nave* nave = g.carregaNave("Rocinante");
    if (nave) {
        cout << "Nome: " << nave->nome << endl;
        cout << "Classe: " << nave->classe << endl;
        cout << "Recursos de Suporte a Vida: " << nave->recursosSuporteVidas << endl;
        cout << "Numero de Passageiros: " << nave->numeroPassageiros << endl;
      

        string path = "C:/Users//ansde/Documents/Projeto_de_EAD2/dados/naves.txt";
        g.adicionarDados(path,nave);
        delete nave; // Lembre-se de liberar a memória alocada.
    }
    return 0;
}



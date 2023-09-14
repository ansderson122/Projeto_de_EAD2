#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "typesProject.h"

Nave* listaNave(const std::string& nomeNave) {
    string path = "C:/Users/ansde/Documents/Projeto_de_EAD2/dados/naves/Rocinante/" + nomeNave + ".txt";
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

int main() {
    Nave* nave = listaNave("Rocinante");
    if (nave) {
        cout << "Nome: " << nave->nome << endl;
        cout << "Classe: " << nave->classe << endl;
        cout << "Recursos de Suporte a Vida: " << nave->recursosSuporteVidas << endl;
        cout << "Numero de Passageiros: " << nave->numeroPassageiros << endl;
        delete nave; // Lembre-se de liberar a memória alocada.
    }
    return 0;
}



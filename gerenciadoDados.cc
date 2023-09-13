#include <iostream>
#include <fstream>
#include <string>

#include "typesProject.h"

Nave* listaNave(const std::string& nomeNave) {
    std::string path = "C:/Users/ansde/Documents/Projeto_de_EAD2/dados/naves/Rocinante/" + nomeNave + ".txt";
    std::cout << path << std::endl;

    std::ifstream arquivo(path);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return nullptr;
    }

    Nave* newNave = new Nave;

    std::string linha;
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
        std::cout << "Nome: " << nave->nome << std::endl;
        std::cout << "Classe: " << nave->classe << std::endl;
        std::cout << "Recursos de Suporte à Vida: " << nave->recursosSuporteVidas << std::endl;
        std::cout << "Número de Passageiros: " << nave->numeroPassageiros << std::endl;
        delete nave; // Lembre-se de liberar a memória alocada.
    }
    return 0;
}



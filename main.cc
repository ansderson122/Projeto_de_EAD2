#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "gerenciadoDados.h"


int main(void) {
    string path = "C:/Users//ansde/Documents/Projeto_de_EAD2/dados/naves.txt";
    Nave nave;
    gerenciadoDados gb;

    cout << "adicionar nave" << endl;
    cout << "nome da nave: ";
    cin >> nave.nome;
    cout << "Classe da nave: ";
    cin >> nave.classe;
    cout << "recurso de suporte a vida: ";
    cin >> nave.recursosSuporteVidas;
    nave.numeroPassageiros = "0";
    gb.adicionarDados(path,&nave);

    
    
    return 0;
}

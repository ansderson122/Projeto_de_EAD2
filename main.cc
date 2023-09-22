#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "gerenciadoDados.h"
#include "gerenciadoDados.cc"

void cadastraNave(gerenciadoDados gb){
    Nave nave;
    

    cout << "adicionar nave" << endl;
    cout << "nome da nave: ";
    cin >> nave.nome;
    cout << "Classe da nave: ";
    cin >> nave.classe;
    cout << "recurso de suporte a vida(sim/nao): ";
    cin >> nave.recursosSuporteVidas;
    while (nave.recursosSuporteVidas != "sim" || nave.recursosSuporteVidas != "nao")
    {
        cout << "digite novamente recurso de suporte a vida(sim/nao): ";
        cin >> nave.recursosSuporteVidas;
    }
    cout << "Existe alguma doença na nave, de 0 a 10 para a gravidade, sendo 0 nenhuma doença e 10 uma doença extremamente mortal.";
    cin >> nave.nivelDeDoenca; 
    while ( !(nave.nivelDeDoenca >= 0 || nave.nivelDeDoenca <=10) )
    {
        cout << "e de 0 a 10";
        cin >> nave.nivelDeDoenca; 
    }
    
    
    nave.numeroPassageiros = 0;
    gb.adicionarNave(&nave);


}


int main(void) {
    gerenciadoDados gb;
    //cadastraNave(gb);
    gb.editarPrioridade("Rocinante",6);
    
    
    return 0;
}

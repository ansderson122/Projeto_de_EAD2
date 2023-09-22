#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "gerenciadoDados.h"
#include "gerenciadoDados.cc"

void cadastraNave(gerenciadoDados gb){
    Nave nave;
    nave.recursosSuporteVidas = "nao";
    

    cout << "adicionar nave" << endl;
    cout << "nome da nave: ";
    cin >> nave.nome;
    while(!gb.criaBancoDadosNave(nave.nome)){
        cout << "Ja existe uma nave com esse nome, digite outro nome :";
        cin >> nave.nome;
    }
    cout << "Classe da nave: ";
    cin >> nave.classe;
    
    
    cout << "Existe alguma doença na nave, de 0 a 10 para a gravidade, sendo 0 nenhuma doença e 10 uma doença extremamente mortal.";
    cin >> nave.nivelDeDoenca; 
    while ( !(nave.nivelDeDoenca >= 0 || nave.nivelDeDoenca <=10) )
    {
        cout << "e de 0 a 10";
        cin >> nave.nivelDeDoenca; 
    }
    cout << "digite o numero de passageiros:";
    cin >> nave.numeroPassageiros;

    //--------------------- cadastro de passageiro -------------------------------- 
    Passageiro passageiro;
    for (int i = 0; i < nave.numeroPassageiros; i++){
        cout << endl << "Registre o passageiro " + to_string(i) << endl; 
        cout << "Nome :";
        cin >> passageiro.nome;
        cout << "Planeta de origem: ";
        cin >> passageiro.planeta_de_origem;
        cout << "Idade :";
        cin >> passageiro.idade;
        gb.registraPassageiro(nave.nome, &passageiro);
    }

    
    //--------------------- cadastro de recursos -------------------------------- 
    int numRecurso;

    cout << "Quanto recurso diferente existem na nave: ";
    cin >> numRecurso;
    Recurso recurso;

    for(int i = 0; i < numRecurso;i++){
        cout << endl << "registre o recurso " + to_string(i) << endl ;
        cout << "Nome :" ;
        cin >> recurso.nomerecurso;
        cout << "Quantidade :";
        cin >> recurso.quantideda;
        cout << "recurso de suporte a vida(sim/nao):";
        cin >> recurso.suporteVida;
        while (recurso.suporteVida != "sim" || recurso.suporteVida != "nao"){
            cout << "digite novamente recurso de suporte a vida(sim/nao): ";
            cin >> recurso.suporteVida;
        }
        if (recurso.suporteVida == "sim"){
            nave.recursosSuporteVidas = "sim";
        }

        gb.registraRecurso(nave.nome,&recurso);
    }

    // cadastra Nave
    gb.adicionarNave(&nave);
}


int main(void) {
    gerenciadoDados gb;
    cadastraNave(gb);
    //gb.editarPrioridade("Rocinante",6);
    
    
    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;
#include "gerenciadoDados.h"
#include "gerenciadoDados.cc"

void cadastraPassageiro(string nomeNave,int numeroPassageiro, gerenciadoDados gd){
    Passageiro passageiro;
    for (int i = 0; i < numeroPassageiro; i++){
        cout << "Registre o passageiro " << i << endl; 
        cout << "Nome: ";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer
        getline(cin, passageiro.nome);

        cout << "Planeta de origem: ";
        getline(cin, passageiro.planeta_de_origem);

        cout << "Idade :";
        cin >> passageiro.idade;
        gd.registraPassageiro(nomeNave, &passageiro);
    }


}

void cadastraRecursos(Nave *nave,gerenciadoDados gd){
    int numRecurso=6;

    cout << "Quanto recurso diferente existem na nave: ";
    cin >> numRecurso;

    Recurso recurso;

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer
    for(int i = 0; i < numRecurso;i++){
        cout << "registre o recurso " << i << endl ;
        cout << "Nome: " ;
        getline(cin, recurso.nomerecurso);

        cout << "Quantidade :";
        cin >> recurso.quantideda;

        cout << "recurso de suporte a vida(sim/nao):";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer
        getline(cin, recurso.suporteVida);

        while ((recurso.suporteVida != "sim" && recurso.suporteVida != "nao")){
            cout << "digite novamente recurso de suporte a vida(sim/nao): ";
            getline(cin, recurso.suporteVida);            
        }
        if (recurso.suporteVida == "sim"){
            nave->recursosSuporteVidas = "sim";
        }

        gd.registraRecurso(nave->nome,&recurso);

    }

}

void cadastraNave(gerenciadoDados gd){
    Nave nave;
    nave.recursosSuporteVidas = "nao";
    nave.numeroPassageiros = 2;


    cout << "adicionar nave" << endl;
    cout << "nome da nave: ";
    getline(cin, nave.nome);
    replace(nave.nome.begin(), nave.nome.end(), ' ', '_');

    while(!(gd.criaBancoDadosNave(nave.nome))){
        cout << "Ja existe uma nave com esse nome, digite outro nome :";
        getline(cin, nave.nome);
        replace(nave.nome.begin(), nave.nome.end(), ' ', '_');

    }
    cout << "Classe da nave: ";
    getline(cin, nave.classe);

    
    
    cout << "Existe alguma doenca na nave, de 0 a 10 para a gravidade, sendo 0 nenhuma doenca e 10 uma doenca extremamente mortal. ";
    cin >> nave.nivelDeDoenca; 
    while ( !(nave.nivelDeDoenca >= 0 && nave.nivelDeDoenca <=10) )
    {
        cout << "Deve ser de 0 a 10. Digite novamente: ";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer
        cin >> nave.nivelDeDoenca; 
    }
    cout << "digite o numero de passageiros:";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer
    cin >> nave.numeroPassageiros;

    //--------------------- cadastro de passageiro -------------------------------- 
    cadastraPassageiro( nave.nome,nave.numeroPassageiros,gd);
    
    //--------------------- cadastro de recursos -------------------------------- 
    cadastraRecursos(&nave,gd);

    // cadastra Nave
    gd.adicionarNave(&nave);
}

void vetorPrint(vector<Nave> naves){
    for(int i = 0 ; i< 2;i++){
        cout << naves[i].nome << endl;
    }
}

void calcularPrioridade(vector<Nave> naves,vector<float> pesos,gerenciadoDados gd){

}



int main(void) {
    gerenciadoDados gd;

    // os pesos são usados para o calculo da prioridade
    // e corresponde passageiros, recursos e doenças
    vector<float> pesos = {0.2f, 0.5f, -0.8f};

    vector<Nave> naves;
    gd.carregaDados(naves);

    cout << naves[0].passageiros[0].nome;
    

    //cadastraNave(gd);
    //gd.editarPrioridade("Rocinante",6);
    
    
    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>
#include <map>

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

        cout << "O identificado: ";
        cin >> passageiro.identificador;

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

void cadastraNave(gerenciadoDados gd,vector<Nave>& naves){
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
    naves.push_back(nave);
}

void vetorPrint(vector<Nave> naves){
    for(unsigned int i = 1 ; i< naves.size();i++){
        cout << naves[i].nome <<  " com a prioridade de " << naves[i].prioridade << endl;
    }
}

void calcularPrioridade(Nave &nave){
    float prioridade = 0;

    //passageiros
    prioridade += 10 * nave.passageiros.size();

        // rcursos
    for(unsigned int j = 0; j < nave.rescursos.size();j++){
        if (nave.rescursos[j].suporteVida == "sim"){
            prioridade += nave.rescursos[j].quantideda;
        }else{
            prioridade += 0.02 * nave.rescursos[j].quantideda;
        }
    }

    // doenças
    prioridade -= 10 * nave.nivelDeDoenca;

    //cout << "prioridade " << prioridade << endl;
    nave.prioridade = prioridade;

}

void calcularPrioridade(vector<Nave>& naves){
    // para cada passageiro seram considerado 10 pontos
    // para cada quilo de recurso seram adicionados 0,02 pontos
    // para recursos de suporte a vidas seram 1 pontos
    // para cada nivel de gravidade de doença seram menos 100 pontos por nivel

    float prioridade;

    for (unsigned int i = 0; i < naves.size(); i++){
        prioridade = 0;

        //passageiros
        prioridade += 10 * naves[i].passageiros.size();

        // rcursos
        for(unsigned int j = 0; j < naves[i].rescursos.size();j++){
            if (naves[i].rescursos[j].suporteVida == "sim"){
                prioridade += naves[i].rescursos[j].quantideda;
            }else{
                prioridade += 0.02 * naves[i].rescursos[j].quantideda;
            }
        }

        // doenças
        prioridade -= 10 * naves[i].nivelDeDoenca;

        //cout << "prioridade " << prioridade << endl;
        naves[i].prioridade = prioridade;
    }
}

void alteraNivelDoenca(vector<Nave>& naves){
    cout << "Altera Nivel de doenca" << endl;
    string nomeNave;
    int nivel;
    cout << "Qual o nome da Nave: ";
    cin >> nomeNave;
    cout << "Qual o novo nivel de doença";
    cin >> nivel;

    for(unsigned int i = 1; i < naves.size();i++ ){
        if(nomeNave == naves[i].nome){
            //salvando a prioridade atuar
            int pri = naves[i].prioridade;

            naves[i].nivelDeDoenca = nivel;
            calcularPrioridade(naves[i]); // recalculando o prioridade 
           
            cout << "A alteracao foi um sucesso" << endl;
            break;
        }
    }
}

void adicionarClandestinos(vector<Nave> naves, gerenciadoDados gd){
    cout << "Cadastra clandestinos" << endl;
    string nomeNave;
    int num;
    cout << "Qual o nome da Nave: ";
    cin >> nomeNave;
    cout << "Qual e a quantidade de clandestinos: ";
    cin >> num;

    for(unsigned int i = 1; i < naves.size();i++ ){
        if(nomeNave == naves[i].nome){
            naves[i].numeroPassageiros += num;
            
            cadastraPassageiro(naves[i].nome,num,gd);
            gd.carregaDados(naves);
            calcularPrioridade(naves[i]); // recalculando o prioridade 
            
            
            cout << "A alteracao foi um sucesso" << endl;
            break;
        }
    }

}



int main(void) {
    gerenciadoDados gd;
    

    vector<Nave> naves;
    gd.carregaDados(naves);

    map<string, Grupo> tabelaGrupos;
    



    


    cout << geraSigla(naves[2].rescursos);
    return 1;

}
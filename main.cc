#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>
#include <map>
#include <queue>

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

Nave cadastraNave(gerenciadoDados gd){
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
    return nave;

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
            //int pri = naves[i].prioridade;

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

bool existeSiglaNoGrupo(Grupo grupo, string sigla){
    for(int i = 0; i < grupo.pos; i++){
        if(grupo.naves[i].siglaRecursos == sigla){
            return true;
        }
    }
    return false;
}

bool adicionaNaveGrupo(Grupo& grupo, Nave nave,queue<string>& filaSaida){
    // posição para se colocada a nave
    int pos = grupo.pos;

    if(pos < 6 && !(existeSiglaNoGrupo(grupo,nave.siglaRecursos))){
            grupo.naves[pos] = nave;
            grupo.pos++;

            if(grupo.pos == 6){
                filaSaida.push(geraSigla(nave.rescursos));
            }
            return true;
    }else if (grupo.prox != nullptr){
        Grupo proximoGrupo = *(grupo.prox);
        adicionaNaveGrupo(proximoGrupo,nave,filaSaida);
        return true;
    }else{
        Grupo* novaGrupo = new Grupo;
        grupo.prox = novaGrupo;
        novaGrupo->naves[0] = nave;
        novaGrupo->prox = nullptr;
        novaGrupo->pos++;
        return true; 
    }
    return false;         

}


bool geraTabela(vector<Nave> naves,map<string, Grupo>& tabelaGrupos,queue<string>& filaSaida){
    string sigla;
    for(unsigned int i = 0; i < naves.size();i++){
        sigla = geraSigla(naves[i].rescursos);

        // Verifica se a chave "sigla" existe no mapa
        auto it = tabelaGrupos.find(sigla);
        if (it != tabelaGrupos.end()) {
            // se existe no mapa
            adicionaNaveGrupo(tabelaGrupos[sigla], naves[i],filaSaida);
        }else{
            // nao existe no map 
            
            // criar nova chave, e adiciona a nave
            tabelaGrupos[sigla].naves[0] = naves[i];
            tabelaGrupos[sigla].pos++;
            tabelaGrupos[sigla].prox = nullptr;
        }
        
    }
    return true;
}

bool adicionaNaveTabela(Nave nave,map<string, Grupo>& tabelaGrupos,queue<string>& filaSaida){
    string chave = geraSigla(nave.rescursos);

    adicionaNaveGrupo(tabelaGrupos[chave],nave,filaSaida);
    return true;
}

void printGrupo(Grupo grupo){
    cout << "Nome das naves: ";
    for(Nave nave : grupo.naves){
        cout << nave.nome << " ";
    }
    cout << endl;
    if(grupo.prox != nullptr){
        cout << "Proximo grupo com a mesma chave" << endl;
        printGrupo(*grupo.prox);
    }
    
}

void printTabela( map<string, Grupo> tabelaGrupos){
    
    for (const auto& par : tabelaGrupos) {
        cout << "Chave: " << par.first << std::endl;
        printGrupo(par.second);
        cout << endl;
    }
}

void removerGrupo(string chave,map<string, Grupo>& tabelaGrupos){
    Grupo grupo = tabelaGrupos[chave];

    if(grupo.prox == nullptr){
        tabelaGrupos.erase(chave);
    }else{
        tabelaGrupos[chave] = *grupo.prox;
    }
}





int main(void) {
    gerenciadoDados gd;
    queue<string> filaSaida;
    Nave nave;
    

    vector<Nave> naves;
    gd.carregaDados(naves);

    map<string, Grupo> tabelaGrupos;
    geraTabela(naves,tabelaGrupos,filaSaida);
    //printTabela(tabelaGrupos);
    //cout << filaSaida.front() ;
    //cout << geraSigla(naves[2].rescursos);
    //removerGrupo(filaSaida.front(),tabelaGrupos);
    //printTabela(tabelaGrupos);
    int op = -1;
    while(op != 0){
        cout << "Digite 0 para sair" << endl;
        cout << "Digite 1 para cadastrar uma nova nave" << endl;
        cout << "Digite 2 para passa uma grupo de naves pelo a abetura" << endl;
        cout << "Digite 3 para lista os grupos de naves" << endl;
        cout << "Digite uma das opcoes: ";

        // caso o usuario digete uma string
        if(!(cin >> op)){
            system("cls"); // limpa a tela
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Entrada invalida. Tente novamente." << endl;
            op = -1;
            continue;
        }
        if(op == 0){
            cout << "Desligando o sistema" << endl;
            break;
        }
        
    
        system("cls"); // limpa a tela
        switch (op){
            case 1:
                nave = cadastraNave(gd);
                

                break;
            case 2:
                cout << "A nave " << naves[1].nome << " passo pela o abetura"<<endl<<endl;
                
                //gd.salvarArquivo(naves)
                
            case 3:
                vetorPrint(naves);
                break; 

            default:
                cout << "O numero digitado nao e uma opcao valida" << endl;
                break;
        }

       cout<<endl<<endl;
    } 




    return 1;

}
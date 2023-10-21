#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <vector>
#include <unistd.h>
using namespace std;

#include "gerenciadoDados.h"
#include <sstream>

gerenciadoDados::gerenciadoDados(/* args */){
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::string currentDirectory(cwd);
        currentDirectory = currentDirectory.substr(0, currentDirectory.find_last_of("\\/"));
        this->pathPrincipal = currentDirectory + "/dados/naves.txt";
        this->pathSegundaria = currentDirectory + "/dados/naves/";
    } else {
        std::cerr << "Erro ao obter o diretório atual." << std::endl;
    }
   
}

gerenciadoDados::~gerenciadoDados()
{
}

bool gerenciadoDados::carregaDados(vector<Nave>& out_dados) {
    ifstream arquivo(this->pathPrincipal);

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
                case 0: novaNave.nome = campo; break;
                case 1: novaNave.classe = campo; break;
                case 2: novaNave.recursosSuporteVidas = campo; break;
                case 3: novaNave.numeroPassageiros = stoi(campo); break;
                case 4: novaNave.nivelDeDoenca = stoi(campo); break;
            }
            campoNum++;
        }
        this->carregaPassageiros(novaNave.nome,novaNave.passageiros); 
        this->carregaRecursos(novaNave.nome,novaNave.rescursos);      

        // Adicione a novaNave ao vetor de dados
        out_dados.push_back(novaNave);
    }

    arquivo.close();
    return true;
}

bool gerenciadoDados::criarDiretorio(string path){
    wstring minhaWString(path.begin(), path.end());
    LPCWSTR newPath = minhaWString.c_str();

    if (CreateDirectoryW(newPath, NULL) != 0) {
        return true;
    } else {
        DWORD erro = GetLastError();
        if (erro == ERROR_ALREADY_EXISTS) {
            std::wcerr << L"O diretorio já existe." << std::endl;
        } else {
            std::wcerr << L"Erro ao criar o diretorio. Codigo de erro: " << erro << std::endl;
        }
        return false;
    }
}

bool gerenciadoDados::criaArquivo(string path,string nome){
    string pathArquivo = path + "/" + nome;
    ofstream arquivo(pathArquivo);

    if(arquivo.is_open()){
        arquivo.close();
        return true;
    }
    arquivo.close();
    return false;
}



bool gerenciadoDados::adicionarNave(Nave* dados){
     // Abrir o arquivo para escrita e leitura no final
    ofstream arquivo(this->pathPrincipal, ios::app | ios::in);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return false;
    }
    // Posicionar o ponteiro no final do arquivo
    arquivo.seekp(0, ios::end);

    // salvando dados 
    arquivo <<  dados->nome + ";" + dados->classe + ";" + dados->recursosSuporteVidas + ";" +to_string(dados->numeroPassageiros) + ";" + to_string(dados->nivelDeDoenca) + ";0" <<  endl ;
    arquivo.close();


    return true;
}

bool gerenciadoDados::salvarArquivo(vector<Nave> naves) {
    ofstream arquivoTemp("temp.txt"); // Arquivo temporário para armazenar as edições
    string linha;

    if (!arquivoTemp.is_open()) {
        return false;
    }

    for(unsigned int i = 1; i < naves.size();i++){
        arquivoTemp << 
        naves[i].nome + ";" + 
        naves[i].classe + ";" + 
        naves[i].recursosSuporteVidas + ";" +
        to_string(naves[i].numeroPassageiros) + ";" + 
        to_string(naves[i].nivelDeDoenca) + ";0" <<  endl ;
    }

    arquivoTemp << endl;
    arquivoTemp.close();

    // Substitui o arquivo original pelo arquivo temporário
    if (remove(this->pathPrincipal.c_str()) != 0) {
        return false;
    }
    if (rename("temp.txt", this->pathPrincipal.c_str()) != 0) {
        return false;
    }

    return true;
}

bool gerenciadoDados::registraPassageiro(string nomeNave, Passageiro * passageiro){
    string path = this->pathSegundaria + nomeNave + "/passageiros.txt" ;

    ofstream arquivo(path, ios::app | ios::in);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        arquivo.close();
        return false;
    }
    // Posicionar o ponteiro no final do arquivo
    arquivo.seekp(0, ios::end);
    arquivo << passageiro->nome + ";" + passageiro->planeta_de_origem +";"+ to_string(passageiro->idade) +";"+ passageiro->identificador << endl;
    arquivo.close();
    return true;
}

bool gerenciadoDados::registraRecurso(string nomeNave, Recurso * recurso){
    string path = this->pathSegundaria + nomeNave + "/recursos.txt" ;

    ofstream arquivo(path, ios::app | ios::in);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        arquivo.close();
        return false;
    }
    // Posicionar o ponteiro no final do arquivo
    arquivo.seekp(0, ios::end);
    arquivo << recurso->nomerecurso + ";" + to_string(recurso->quantideda) +";" + recurso->suporteVida << endl;
    arquivo.close();
    return true;
}

bool gerenciadoDados::criaBancoDadosNave(string nomeNave){
    string path1 = this->pathSegundaria + nomeNave ;
    if (this->criarDiretorio(path1)){
        this->criaArquivo(path1,"passageiros.txt");
        this->criaArquivo(path1,"recursos.txt");
        return true;
    }else{
        return false;
    }
}

bool gerenciadoDados::carregaRecursos(string nomeNave ,vector<Recurso>& out_recursos){
    string path = this->pathSegundaria + nomeNave + "/recursos.txt" ;

    ifstream arquivo(path);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        arquivo.close();
        return false;
    }
   
    string linha;
    int campoNum;

    while (getline(arquivo,linha)){
        stringstream ss(linha);
        string campo;

        Recurso recurso;
        campoNum = 0;

        while (std::getline(ss, campo, ';')) {
            switch (campoNum) {
                case 0: recurso.nomerecurso = campo; break;
                case 1: recurso.quantideda = stoi(campo); break;
                case 2: recurso.suporteVida = campo; break;
            }
            campoNum++;
        }
        // Adicione a novaNave ao vetor de dados
        out_recursos.push_back(recurso);
    }

    arquivo.close();
    return true;
}

bool gerenciadoDados::carregaPassageiros(string nomeNave ,vector<Passageiro>& out_passageiros){
    string path = this->pathSegundaria + nomeNave + "/passageiros.txt" ;

    ifstream arquivo(path);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        arquivo.close();
        return false;
    }
   
    string linha;
    int campoNum;

    while (getline(arquivo,linha)){
        stringstream ss(linha);
        string campo;

        Passageiro passageiro;
        campoNum = 0;

        while (std::getline(ss, campo, ';')) {
            switch (campoNum) {
                case 0: passageiro.nome = campo; break;
                case 1: passageiro.planeta_de_origem = campo; break;
                case 2: passageiro.idade = stoi(campo); break;
                case 3: passageiro.identificador = campo; break;
            }
            campoNum++;
        }
        // Adicione a novaNave ao vetor de dados
        out_passageiros.push_back(passageiro);
    }

    arquivo.close();
    return true;
}
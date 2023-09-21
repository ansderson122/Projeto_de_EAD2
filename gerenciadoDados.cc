#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

#include "gerenciadoDados.h"
#include <sstream>

gerenciadoDados::gerenciadoDados(/* args */){
    this->pathPrincipal = "C:/Users/ansde/Documents/Projeto_de_EAD2/dados/naves.txt";
    this->pathSegundaria = "C:/Users/ansde/Documents/Projeto_de_EAD2/dados/naves/";
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
                case 0: novaNave.nome = linha; break;
                case 1: novaNave.classe = linha; break;
                case 2: novaNave.recursosSuporteVidas = linha; break;
                case 3: novaNave.numeroPassageiros = linha; break;
        }
        campoNum++;
    }
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
        arquivo << endl;
        arquivo.close();
        return true;
    }
    arquivo.close();
    return false;
}



bool gerenciadoDados::adicionarNave(Nave* dados){

    string path1 = this->pathSegundaria + dados->nome ;
    if (this->criarDiretorio(path1)){
        this->criaArquivo(path1,"passageiros.txt");
        this->criaArquivo(path1,"recursos.txt");
    }else{
        return false;
    }

     // Abrir o arquivo para escrita e leitura no final
    ofstream arquivo(this->pathPrincipal, ios::app | ios::in);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return false;
    }
    // Posicionar o ponteiro no final do arquivo
    arquivo.seekp(0, ios::end);

    // salvando dados 
    arquivo <<  dados->nome + ";" + dados->classe + ";" + dados->recursosSuporteVidas + ";" + dados->numeroPassageiros + ";" + to_string(dados->nivelDeDoenca) + ";0" <<  endl ;
    
    return true;
}

bool gerenciadoDados::editarPrioridade(string nome, int prioridade) {
    ifstream arquivoLeitura(this->pathPrincipal);
    ofstream arquivoTemp("temp.txt"); // Arquivo temporário para armazenar as edições
    string linha;

    if (!arquivoLeitura.is_open() || !arquivoTemp.is_open()) {
        return false;
    }

    while (getline(arquivoLeitura, linha)) {
        stringstream ss(linha);
        string campus;
        getline(ss, campus, ';');

        if (campus == nome) {
            int i = 0;
            string linhaEditada;

            while (i <= 4) {
                linhaEditada += campus + ";";
                getline(ss, campus, ';');
                i++;
            }

            linhaEditada += to_string(prioridade);
            arquivoTemp << linhaEditada << endl; // Escreve a linha editada no arquivo temporário
        } else {
            arquivoTemp << linha << endl; // Mantém as outras linhas inalteradas
        }
    }

    arquivoLeitura.close();
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

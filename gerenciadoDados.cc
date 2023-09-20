#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

#include "gerenciadoDados.h"
#include <sstream>

gerenciadoDados::gerenciadoDados(/* args */)
{
}

gerenciadoDados::~gerenciadoDados()
{
}

bool gerenciadoDados::carregaDados(string path, vector<Nave>& out_dados) {
    ifstream arquivo(path);

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
        return true;
    }
    return false;
}



bool gerenciadoDados::adicionarNave(Nave* dados){

    string path1 = "C:/Users/ansde/Documents/Projeto_de_EAD2/dados/naves/" + dados->nome ;
    if (this->criarDiretorio(path1)){
        this->criaArquivo(path1,"passageiros.txt");
        this->criaArquivo(path1,"recursos.txt");
    }else{
        return false;
    }

     // Abrir o arquivo para escrita e leitura no final
    ofstream arquivo("C:/Users/ansde/Documents/Projeto_de_EAD2/dados/naves.txt", ios::app | ios::in);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return false;
    }
    // Posicionar o ponteiro no final do arquivo
    arquivo.seekp(0, ios::end);

    arquivo <<  dados->nome + ";" + dados->classe + ";" + dados->recursosSuporteVidas + ";" + dados->numeroPassageiros + ";0" <<  endl ;
    
    return true;
}


int main(void) {
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
    gb.adicionarNave(&nave);

    
    
    return 0;
}

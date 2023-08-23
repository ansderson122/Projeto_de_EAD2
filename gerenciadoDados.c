#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nave.h"


Nave* listaNave(char*);

int main() {
	char* nome = "Rocinante";
	Nave *nave = NULL;
	nave = listaNave(nome);
	
    printf("O nome da nave e %s\n", nave->nome);
    printf("A classe da nave e %s\n", nave->classe);
    printf("%s esta transportando recursos de suporte a vida\n", nave->recursosParaVidas);
    printf("E contém %s passageiros a bordo\n", nave->numeroPassageiros);
   	return 1;
   
}

Nave* listaNave(char* nomeNave){
	char path[100];
	strcpy(path, "./dados/naves/"); // Copia o prefixo do caminho
    strcat(path, nomeNave);   // Concatena o nome da nave
    strcat(path, "/");         // Concatena uma barra
    strcat(path, nomeNave);   // Concatena o nome da nave novamente
    strcat(path, ".txt");     // Concatena a extensão do arquivo
    
    FILE *arquivo = fopen(path, "r");  
    
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        fclose(arquivo);
        return NULL;
    }
    
    Nave* newNave = malloc(sizeof(Nave));

    char linha[100]; // Buffer para armazenar cada linha lida
	int campo = 0;
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char* termo = strtok(linha, ";");
        
        while (termo != NULL) {
            if (campo == 0) strcpy(newNave->nome, termo);
            else if (campo == 1) strcpy(newNave->classe, termo);
            else if (campo == 2) strcpy(newNave->recursosParaVidas, termo);
            else if (campo == 3) strcpy(newNave->numeroPassageiros, termo);
            
            campo++;
            termo = strtok(NULL, ";");
        }
    }

    fclose(arquivo);
    
    return newNave;
}




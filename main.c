#include <stdio.h>
#include <string.h>
#include "passageiro.h"


int main(void) {
	Passageiro pessoa1;
    strcpy(pessoa1.nome, "Ruan");
    strcpy(pessoa1.planeta_de_origem, "Terra");
	pessoa1.idade = 27;
	


    printf("Nome: %s\n", pessoa1.nome);
    printf("Planeta de Origem: %s\n", pessoa1.planeta_de_origem);
    printf("Idade: %d\n", pessoa1.idade);
    
    return 0;
}

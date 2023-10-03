#include <iostream>
#include<vector>
#include "heap.h"
#include "typesProject.h"

using namespace std;


heap::heap(){
}

heap::~heap()
{
}

void heap::subir(vector<Nave>& naves,int i){
    int j = i / 2;
    if (j >=1){
        if(naves[i] > naves[j]){
            Nave temp;
            temp = naves[i];
            naves[i] = naves[j];
            naves[j] = temp;

            this->subir(naves,j);
        }
    }
}

void heap::descer(vector<Nave>& naves,int i, int n){
    int j = 2 * i;

    if (j <= n){
        if(j < n) {
            if (naves[j+1] > naves[j]){
                j++;
            }
        }
        if(naves[j].prioridade > naves[i].prioridade){
            Nave temp;
            temp = naves[i];
            naves[i] = naves[j];
            naves[j] = temp;

            this->descer(naves,j,n);
        }
    }
}

void heap::construiHeap(vector<Nave>& naves){
    for(int i = naves.size() /2 ; i >=1;i--){
        this->descer(naves,i,naves.size());
    }
}

void heap::remover(vector<Nave>& naves){
    naves[1] = naves[naves.size()-1];
    naves.pop_back();

    this->descer(naves,1,naves.size());
}

void heap::adicionar(vector<Nave>& naves){
    int i = naves.size()-1;
    this->subir(naves,i);
}
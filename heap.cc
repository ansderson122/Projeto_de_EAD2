#include <iostream>
#include<vector>
#include "heap.h"
#include "typesProject.h"

heap::heap(/* args */){
    vector<Nave> naves;
}

heap::~heap()
{
}

void heap::subir(int i){
    int j = i / 2;
    if (j >=1){
        if(naves[i] > naves[j]){
            Nave temp;
            temp = naves[i];
            naves[i] = naves[j];
            naves[j] = temp;

            this->subir(i);
        }
    }
}

void heap::descer(int i, int n){
    int j = 2 * i;
    if (j <= n){
        if(j < n) {
            if (naves[j+1] > naves[j]){
                j++;
            }
        }
        if(naves[j] > naves[i]){
            Nave temp;
            temp = naves[i];
            naves[i] = naves[j];
            naves[j] = temp;

            this->descer(j,n);
        }
    }
}
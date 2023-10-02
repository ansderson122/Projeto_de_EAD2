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
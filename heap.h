#ifndef HEAP_H
#define HEAP_H

class heap
{
private:
    /* data */
public:
    vector<Nave> naves;
    heap(/* args */);
    ~heap();
    void subir(int i);
    void descer(int i, int n);
    void construiHeap(vector<Nave> naves);
};




#endif
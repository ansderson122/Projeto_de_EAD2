#ifndef HEAP_H
#define HEAP_H

class heap
{
private:
    /* data */
public:
    heap();
    ~heap();
    void subir(vector<Nave>& naves,int i);
    void descer(vector<Nave>& naves,int i, int n);
    void construiHeap(vector<Nave>& naves);
};




#endif
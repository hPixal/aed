#include <iostream>
#include <tuple>
using namespace std;

class Fantasma
{
protected:
    int posicionx; //vector de dos enteros (x,y)
    int posiciony;
public:
    Fantasma(/* args */);
    virtual void mover(int x, int y){
        posicionx = posicionx + x;
        posiciony = posiciony + y;
    }
    tuple<int,int> conseguirPosicion(){ return tie(posicionx,posiciony); };
    ~Fantasma();
};

Fantasma::Fantasma(/* args */)
{
}

Fantasma::~Fantasma()
{
}

class Amarillo : public Fantasma
{
private:
    /* data */
public:
    Amarillo(/* args */);
    void mover(int x, int y) override {
        posicionx = posicionx - x;
        posiciony = posiciony - y;
    }
    ~Amarillo();
};

Amarillo::Amarillo(/* args */)
{
}

Amarillo::~Amarillo()
{
}




int main(){
    return 0;
}


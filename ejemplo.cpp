#include <iostream>
#include <tuple>
#include <vector>
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
    void actualizar( ... ) { };
    void dibujar( ... ) { };
    tuple<int,int> conseguirPosicion(){ return tie(posicionx,posiciony); };
    ~Fantasma();
};

Fantasma::Fantasma(/* args */)
{
    posiciony = 0;
    posicionx = 0;
}

Fantasma::~Fantasma()
{
}

class Amarillo : public Fantasma
{
private:
    /* data */
public:
    Amarillo(/* args */) { }
    void mover(int x, int y) override {
        posicionx = posicionx - x;
        posiciony = posiciony - y;
    }
    ~Amarillo(){ }
};

class Verde : public Fantasma
{
private:
    /* data */
public:
    Verde(/* args */);
    ~Verde();
};

Verde::Verde(/* args */)
{
}

Verde::~Verde()
{
}

int main(){
    vector<Fantasma> ejemplo;
    Verde ver; Amarillo amar;
    ejemplo.push_back(ver);
    ejemplo.push_back(amar);

    ejemplo[0].mover(3,3);
    ejemplo[1].mover(3,3);


    while (juego.detenerse())
    {
        for (size_t i = 0; i < ejemplo.size(); i++)
        {
            ejemplo[i].actualizar();
            ejemplo[i].dibujar();
        }
        
    }
    
    return 0;
}


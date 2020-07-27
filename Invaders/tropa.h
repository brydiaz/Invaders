
#ifndef TROPA_H
#define TROPA_H
#import <QPushButton>
#include <QKeyEvent>
#include <QLabel>

class Tropa
{
public:
    QPushButton *representacion;
    Tropa *balaEnemigo=nullptr;
    bool isOn;
    bool isJugador=false;
    int posx;
    int posy;
    int control=0;
    int tipoM=0;
    Tropa(QPushButton *representacion, bool isOn);
    void moverJugador(int key, Tropa *matriz[13][18], Tropa *vacia, Tropa *jugador);
    void moverEnemigo(Tropa *matriz[13][18], Tropa *vacia);
    void moverEnemigoIz(Tropa *matriz[13][18], Tropa *vacia);
    void moverEnemigoDer(Tropa *matriz[13][18], Tropa *vacia);
    void moverEnemigo4(Tropa *matriz[13][18], Tropa *vacia);
    int enemigoAtacar(Tropa *matriz[13][18], Tropa *vacia, int vida, int puntaje);

    void setJugador(Tropa *f);
};

#endif // TROPA_H


#ifndef TROPA_H
#define TROPA_H
#import <QPushButton>
#include <QKeyEvent>
#include <QLabel>

class Tropa
{
public:
    QPushButton *representacion;
    bool isOn;
    int posx;
    int posy;
    Tropa(QPushButton *representacion, bool isOn);
    void moverJugador(int key, Tropa *matriz[13][18], Tropa *vacia, Tropa *jugador);
    void moverEnemigoIz(Tropa *matriz[13][18], Tropa *vacia);
    void moverEnemigoDer(Tropa *matriz[13][18], Tropa *vacia);
};

#endif // TROPA_H

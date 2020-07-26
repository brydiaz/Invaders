#include "tropa.h"
#include <iostream>
#include <QKeyEvent>
#include <juegoprincipal.h>

Tropa::Tropa(QPushButton *repre, bool isOn1){
    representacion= repre;
    isOn=isOn1;
}


void Tropa::moverJugador(int key,Tropa *matriz[13][18], Tropa *vacia, Tropa *jugador){

    switch(key){
        case 1:

            if(jugador->posy<=0){
                break;
            }else{
                               matriz[this->posx][this->posy]->isOn=vacia->isOn;
                               matriz[this->posx][this->posy]->representacion->setIcon(vacia->representacion->icon());
                               this->posy-=1;
                               matriz[this->posx][this->posy]->isOn=true;
                               matriz[this->posx][this->posy]->representacion->setIcon(QIcon("://jugador.png"));
                               this->representacion= matriz[this->posx][this->posy]->representacion;
                               jugador=matriz[this->posx][this->posy];

            }
        break;

        case 0:
            if(this->posy>=17){

                break;
            }else{
                               matriz[this->posx][this->posy]->isOn=vacia->isOn;
                               matriz[this->posx][this->posy]->representacion->setIcon(vacia->representacion->icon());
                               this->posy+=1;
                               matriz[this->posx][this->posy]->isOn=true;
                               matriz[this->posx][this->posy]->representacion->setIcon(QIcon("://jugador.png"));
                               this->representacion= matriz[this->posx][this->posy]->representacion;
                               jugador=matriz[this->posx][this->posy];
            }

        break;

    }
}


void Tropa::moverEnemigoIz(Tropa *(*matriz)[18], Tropa *vacia){
        matriz[this->posx][this->posy]->isOn=vacia->isOn;
        matriz[this->posx][this->posy]->representacion->setIcon(vacia->representacion->icon());
        this->posy-=1;
        matriz[this->posx][this->posy]->isOn=true;
        matriz[this->posx][this->posy]->representacion->setIcon(QIcon("://enemigo.png"));
        this->representacion= matriz[this->posx][this->posy]->representacion;
}


void Tropa::moverEnemigoDer(Tropa *(*matriz)[18], Tropa *vacia){
        matriz[this->posx][this->posy]->isOn=vacia->isOn;
        matriz[this->posx][this->posy]->representacion->setIcon(vacia->representacion->icon());
        this->posy+=1;
        matriz[this->posx][this->posy]->isOn=true;
        matriz[this->posx][this->posy]->representacion->setIcon(QIcon("://enemigo.png"));
        this->representacion= matriz[this->posx][this->posy]->representacion;
}

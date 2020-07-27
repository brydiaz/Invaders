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
                               matriz[this->posx][this->posy]->isJugador=false;
                               this->posy-=1;
                               matriz[this->posx][this->posy]->isOn=true;
                               matriz[this->posx][this->posy]->representacion->setIcon(QIcon("://jugador.png"));
                               this->representacion= matriz[this->posx][this->posy]->representacion;
                               jugador=matriz[this->posx][this->posy];
                               matriz[this->posx][this->posy]->isJugador=true;
                               break;

            }

        case 0:
            if(this->posy>=17){
                break;
            }else{
                               matriz[this->posx][this->posy]->isOn=vacia->isOn;
                               matriz[this->posx][this->posy]->representacion->setIcon(vacia->representacion->icon());
                               matriz[this->posx][this->posy]->isJugador=false;
                               this->posy+=1;
                               matriz[this->posx][this->posy]->isOn=true;
                               matriz[this->posx][this->posy]->representacion->setIcon(QIcon("://jugador.png"));
                               this->representacion= matriz[this->posx][this->posy]->representacion;
                               jugador=matriz[this->posx][this->posy];
                               matriz[this->posx][this->posy]->isJugador=true;
                               break;
            }

    }
}


void Tropa::moverEnemigo(Tropa *matriz[13][18], Tropa *vacia){
        if(tipoM==0){
            if(this->posy!=16){
                moverEnemigoDer(matriz,vacia);
            }else{
                tipoM=1;
            }
        }else{
            if(this->posy!=0){
                moverEnemigoIz(matriz,vacia);
            }else{
                tipoM=0;
            }
        }
}

void Tropa::moverEnemigoDer(Tropa *matriz[13][18], Tropa *vacia){

        if(this!=vacia){
        matriz[this->posx][this->posy]->isOn=vacia->isOn;
        matriz[this->posx][this->posy]->representacion->setIcon(vacia->representacion->icon());
        this->posy+=1;
        matriz[this->posx][this->posy]->isOn=true;
        matriz[this->posx][this->posy]->representacion->setIcon(QIcon("://enemigo.png"));
        this->representacion= matriz[this->posx][this->posy]->representacion;
        }
}

void Tropa::moverEnemigoIz(Tropa *matriz[13][18], Tropa *vacia){

        if(this!=vacia){
            matriz[this->posx][this->posy]->isOn=false;
            matriz[this->posx][this->posy]->representacion->setIcon(vacia->representacion->icon());
            this->posy-=1;
            matriz[this->posx][this->posy]->isOn=true;
            matriz[this->posx][this->posy]->representacion->setIcon(QIcon("://enemigo.png"));
            this->representacion= matriz[this->posx][this->posy]->representacion;
        }
}


int Tropa::enemigoAtacar(Tropa *matriz[13][18], Tropa *vacia, int vidas, int puntaje){

    if(this!=vacia){

    if(control==0){
        Tropa *bala= new Tropa (matriz[this->posx+1][this->posy]->representacion, false);
        bala->posx=this->posx+1;
        bala->posy=this->posy;
        bala->representacion->setIcon(QIcon("://blast.png"));
        matriz[bala->posx][bala->posy]->representacion->setIcon(bala->representacion->icon());
        this->balaEnemigo=bala;
        control=1;
    }
    if(this->balaEnemigo==nullptr){
    }else{

        if(this->balaEnemigo->posx==12){
            matriz[this->balaEnemigo->posx][this->balaEnemigo->posy]->representacion->setIcon(QIcon("://fondoNegroPoVacias.jpg"));
            this->balaEnemigo=nullptr;
            control=0;
        }else{
            if(matriz[this->balaEnemigo->posx+1][this->balaEnemigo->posy]->isJugador){
               vidas-=1;
               matriz[this->balaEnemigo->posx+1][this->balaEnemigo->posy]->representacion->setIcon(QIcon("://fondoNegroPoVacias.jpg"));
               this->balaEnemigo=nullptr;
               control=0;
            }else{

               matriz[this->balaEnemigo->posx][this->balaEnemigo->posy]->representacion->setIcon(QIcon("://fondoNegroPoVacias.jpg"));
               this->balaEnemigo->posx+=1;
               matriz[this->balaEnemigo->posx][this->balaEnemigo->posy]->representacion->setIcon(QIcon("://blast.png"));
               this->balaEnemigo->representacion= matriz[this->balaEnemigo->posx][this->balaEnemigo->posy]->representacion;
                }

        }

    }
    }
    return vidas;
}



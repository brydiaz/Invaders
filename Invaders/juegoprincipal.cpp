#include "juegoprincipal.h"
#include "ui_juegoprincipal.h"
#include <tropa.h>
#include <QIcon>
#include<iostream>
#include <QObject>
#include <QKeyEvent>
#include <string>

JuegoPrincipal::JuegoPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::JuegoPrincipal)
{
    ui->setupUi(this);

    generarTableroGrafico();
    generarJugador();
    generarEnemigos();
    //connect(timer, SIGNAL(timeout()), this, SLOT(actualizarJuego()));
    //actualizarJuego();
    //timer->start(1000);

}

JuegoPrincipal::~JuegoPrincipal()
{
    delete ui;
}

void JuegoPrincipal::generarTableroGrafico(){
    int nombre=0;
    int x=0;
    int y=0;
    for(int i=0;i<13;i++){

        for(int j=0;j<18;j++){
            bool isOn=false;
            QPushButton *newButton= new  QPushButton(ui->frame);
            QString SNombre=QString::number(nombre);
            newButton->setGeometry(x,y,41,41);
            newButton->setObjectName(SNombre);
            Tropa *tropaVacia= new Tropa (newButton, isOn);
            tropaVacia->representacion->setIcon(QIcon("://fondoNegroPoVacias.jpg"));
            tropaVacia->representacion->setIconSize(QSize(41,41));
            tropaVacia->posx=i;
            tropaVacia->posy=j;
            matrizGrafica[i][j]=tropaVacia;
            matrizLogica[i][j]=0;
            tropaNula= tropaVacia;
            nombre=nombre+1;
            x=x+41;
        }
        nombre=nombre+1;
        y=y+41;
        x=0;
    }


}



void JuegoPrincipal::generarJugador(){

    jugador=matrizGrafica[11][8];
    jugador->isOn=true;
    jugador->representacion->setIcon(QIcon("://jugador.png"));

}

void JuegoPrincipal::keyPressEvent(QKeyEvent *e){
    switch (e->key()) {
        case Qt::Key_D:
            jugador->moverJugador(0, matrizGrafica, tropaNula, jugador);
        break;
        case Qt::Key_A:
            jugador->moverJugador(1,matrizGrafica, tropaNula, jugador);
        break;
    }
}

void JuegoPrincipal::generarEnemigos(){
        int k=0;
        for(int i=1; i!=6;i++){
            for(int j=1; j!=16;j++){
                if(j%2==0){
                    matrizGrafica[i][j]->isOn=true;
                    matrizGrafica[i][j]->representacion->setIcon(QIcon("://enemigo.png"));
                    enemigos[k]=matrizGrafica[i][j];
                    k+=1;
                }
            }
        }
}



void JuegoPrincipal::actualizarJuego(){


    if(enemigos[0]->posy!=1){
        for(int i=0; i!=35;i++){
            enemigos[i]->moverEnemigoIz(matrizGrafica, tropaNula);
            }
    }else{
         if(enemigos[6]->posy!=16){
            for(int i=0; i!=35;i++){
                enemigos[i]->moverEnemigoDer(matrizGrafica, tropaNula);
             }
         }
    }

}

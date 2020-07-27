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
    connect(timer, SIGNAL(timeout()), this, SLOT(actualizarJuego()));
    timer->start(300);
    connect(timerTiempo, SIGNAL(timeout()), this, SLOT(tiempo()));
    timerTiempo->start(1000);

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
    jugador->isJugador=true;
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
        case Qt::Key_W:
           if(controlDisparo==0){
           Tropa *bala= new Tropa (matrizGrafica[jugador->posx-1][jugador->posy]->representacion, false);
           bala->posx=jugador->posx-1;
           bala->posy=jugador->posy;
           bala->representacion->setIcon(QIcon("://blast.png"));
           matrizGrafica[bala->posx][bala->posy]->representacion->setIcon(bala->representacion->icon());
           this->bala=bala;
           }

        break;
    }
}

void JuegoPrincipal::generarEnemigos(){
        int k=0;
        for(int i=1; i!=8;i++){
            for(int j=1; j!=2;j++){
                int aleatorio= rand()%(16-1+1)+1;
                    matrizGrafica[i][aleatorio]->isOn=true;
                    matrizGrafica[i][aleatorio]->representacion->setIcon(QIcon("://enemigo.png"));
                    enemigos[k]=matrizGrafica[i][aleatorio];
                    k+=1;
                }
            }
 }




void JuegoPrincipal::actualizarJuego(){
        moverEnemigos();

        if(bala==nullptr){
        }else{
            hiloBala();
        }
        enemigosRestantes();
}


void JuegoPrincipal::hiloBala(){




        if(bala->posx==0){
            matrizGrafica[bala->posx][bala->posy]->representacion->setIcon(QIcon("://fondoNegroPoVacias.jpg"));
            bala=nullptr;
            controlDisparo=0;
        }else{
            if(matrizGrafica[bala->posx-1][bala->posy]->isOn){
               int posx= bala->posx-1;
               int posy= bala->posy;
               largoEnemigos-=1;
               puntaje+=1000;

               enemigos[posx-1]=tropaNula;
               enemigos[posx-1]->isOn=false;
               matrizGrafica[posx][posy]->isOn=false;
               controlDisparo=0;
               matrizGrafica[posx][posy]->representacion->setIcon(QIcon("://fondoNegroPoVacias.jpg"));

               bala->representacion->setIcon(QIcon("://fondoNegroPoVacias.jpg"));
               bala=nullptr;

            }else{
                controlDisparo=1;
                matrizGrafica[bala->posx][bala->posy]->representacion->setIcon(QIcon("://fondoNegroPoVacias.jpg"));
                bala->posx-=1;
                matrizGrafica[bala->posx][bala->posy]->representacion->setIcon(QIcon("://blast.png"));
                bala->representacion= matrizGrafica[bala->posx][bala->posy]->representacion;

        }
    }
}
void JuegoPrincipal::moverEnemigos(){
    for(int i=0; i!=7;i++){
        enemigos[i]->moverEnemigo(matrizGrafica, tropaNula);
        vidas=enemigos[i]->enemigoAtacar(matrizGrafica,tropaNula, vidas, puntaje);
    }
}

void JuegoPrincipal::enemigosRestantes(){
    if(largoEnemigos==0){
        timer->stop();
        timerTiempo->stop();
       msgBox.setWindowTitle("Juego Terminado!!!");
       msgBox.setIcon(QMessageBox::Information);
       msgBox.setStandardButtons(QMessageBox::Yes);
       msgBox.addButton(QMessageBox::No);
       msgBox.setDefaultButton(QMessageBox::Yes);
       msgBox.setEscapeButton(QMessageBox::No);
       QString p=QString::number(puntaje+tiempoEnSegundos);
       msgBox.setText("Ganaste, Jugar de nuevo? Tu puntaje "+p);
       if(QMessageBox::Yes==msgBox.exec()){
       }else{
          this->~JuegoPrincipal();
       }
    }else if(vidas==0){
        timer->stop();
        timerTiempo->stop();
       msgBox.setWindowTitle("Juego Terminado!!!");
       msgBox.setIcon(QMessageBox::Information);
       msgBox.setStandardButtons(QMessageBox::Yes);
       msgBox.addButton(QMessageBox::No);
       msgBox.setDefaultButton(QMessageBox::Yes);
       msgBox.setEscapeButton(QMessageBox::No);
       QString p=QString::number(puntaje);
       msgBox.setText("Perdiste, Jugar de nuevo? Tu puntaje "+p);
       if(QMessageBox::Yes==msgBox.exec()){
       }else{
          this->~JuegoPrincipal();
       }
    }

    ui->eRestantes->setNum(largoEnemigos);
    ui->ePuntaje->setNum(puntaje);
    ui->eVidas->setNum(vidas);
}

void JuegoPrincipal::tiempo(){
    if(tiempoEnSegundos==0){
        timer->stop();
        timerTiempo->stop();
       msgBox.setWindowTitle("Juego Terminado!!!");
       msgBox.setIcon(QMessageBox::Information);
       msgBox.setStandardButtons(QMessageBox::Yes);
       msgBox.addButton(QMessageBox::No);
       msgBox.setDefaultButton(QMessageBox::Yes);
       msgBox.setEscapeButton(QMessageBox::No);
       QString p=QString::number(puntaje);
       msgBox.setText("Se acabo el tiempo, Jugar de nuevo? Tu puntaje "+p);
       if(QMessageBox::Yes==msgBox.exec()){

       }else{
          this->~JuegoPrincipal();
       }
    }
    tiempoEnSegundos-=1;
    QString s= QString::number(tiempoEnSegundos);
    QString m="0:"+s;
    ui->eTiempo->setText(m);
}

#ifndef JUEGOPRINCIPAL_H
#define JUEGOPRINCIPAL_H
#include <QLabel>
#include<QPushButton>
#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <tropa.h>
#include <QKeyEvent>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class JuegoPrincipal; }
QT_END_NAMESPACE

class JuegoPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    int control=0;
    int mov=0;
    int controlDisparo=0;
    int largoEnemigos=7;
    int puntaje=0;
    int vidas=3;
    int tiempoEnSegundos=60;
    Tropa *jugador;
    Tropa *tropaNula;
    Tropa *bala=nullptr;
    Tropa *enemigos[10];

    QMessageBox msgBox;

    QKeyEvent *event;
    Tropa *matrizGrafica[13][18];
    int *matrizLogica[13][18];
    JuegoPrincipal(QWidget *parent = nullptr);
    ~JuegoPrincipal();
    QTimer *timer= new QTimer();
    QTimer *timerTiempo= new QTimer();
    QTime time;
    void generarTableroGrafico();
    void generarJugador();
    void generarEnemigos();
    void moverEnemigos();
    void hiloBala();
    void enemigosRestantes();

protected:
    void keyPressEvent(QKeyEvent *e);

private slots:
    void tiempo();
    void actualizarJuego();


private:
    Ui::JuegoPrincipal *ui;
};
#endif // JUEGOPRINCIPAL_H

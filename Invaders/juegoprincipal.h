#ifndef JUEGOPRINCIPAL_H
#define JUEGOPRINCIPAL_H
#include <QLabel>
#include<QPushButton>
#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <tropa.h>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class JuegoPrincipal; }
QT_END_NAMESPACE

class JuegoPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    Tropa *jugador;
    Tropa *tropaNula;
    Tropa *enemigos[48];
    QKeyEvent *event;
    Tropa *matrizGrafica[13][18];
    int *matrizLogica[13][18];
    JuegoPrincipal(QWidget *parent = nullptr);
    ~JuegoPrincipal();
    QTimer *timer= new QTimer();
    QTime time;
    void generarTableroGrafico();
    void generarJugador();
    void generarEnemigos();
    void moverEnemigos();
protected:
    void keyPressEvent(QKeyEvent *e);

private slots:
    void actualizarJuego();
private:
    Ui::JuegoPrincipal *ui;
};
#endif // JUEGOPRINCIPAL_H

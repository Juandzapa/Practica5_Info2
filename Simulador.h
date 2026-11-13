#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <fstream>
#include <string>
#include <vector>
#include "Obstaculo.h"
#include "Particula.h"

using namespace std;

class Simulador {
private:
    double ancho;
    double alto;
    double dt;
    double tiempo;
    int siguienteId;
    int totalColisiones;
    vector<Particula> particulas;
    vector<Obstaculo> obstaculos;
    ofstream archivo;

    void paso();
    void colisionesEntreParticulas();
    void colisionesConObstaculos();
    void colisionesConParedes();
    void guardarPosiciones();

public:
    Simulador(double ancho_, double alto_, double dt_);

    void agregarObstaculo(double x, double y, double lado, double e);
    bool agregarParticula(double x, double y, double vx, double vy, double masa, double radio);

    void ejecutar(double tiempoTotal, const string& nombreArchivo);
    void mostrarParticulas() const;
};

#endif


#include <iostream>
#include <cstdlib>
#include <ctime>
#include "simulador.h"

using namespace std;

double aleatorio(double minimo, double maximo) {
    return minimo + (maximo - minimo) * rand() / RAND_MAX;
}

int main() {
    const double ANCHO = 100.0;
    const double ALTO = 60.0;
    const double DT = 0.01;
    const double TIEMPO_TOTAL = 20.0;
    const double E = 0.7;
    const int NUM_PARTICULAS = 20;

    srand(time(NULL));

    Simulador sim(ANCHO, ALTO, DT);

    sim.agregarObstaculo(18, 12, 10, E);
    sim.agregarObstaculo(68, 12, 10, E);
    sim.agregarObstaculo(18, 38, 10, E);
    sim.agregarObstaculo(68, 38, 10, E);

    int creadas = 0;
    while (creadas < NUM_PARTICULAS) {
        double masa = aleatorio(1.0, 4.0);
        double radio = 0.6 + 0.4 * masa;
        double x = aleatorio(0, ANCHO);
        double y = aleatorio(0, ALTO);
        double vx = aleatorio(-15, 15);
        double vy = aleatorio(-15, 15);

        if (sim.agregarParticula(x, y, vx, vy, masa, radio)) creadas++;
    }

    cout << "SIMULACION DE COLISIONES MULTIPLES -\n\nParticulas iniciales:\n";
    sim.mostrarParticulas();

    cout << "\n";
    sim.ejecutar(TIEMPO_TOTAL, "simulacion.txt");

    cout << "\nParticulas al final:\n";
    sim.mostrarParticulas();
    return 0;
}

#ifndef PARTICULA_H
#define PARTICULA_H

#include "Cuerpo.h"

using namespace std;

class Particula : public Cuerpo {
private:
    double vx;
    double vy;
    double masa;
    double radio;
    bool activa;

public:
    Particula(int id_, double x_, double y_, double vx_, double vy_, double masa_, double radio_);

    void mover(double dt);

    double getVx() const;
    double getVy() const;
    void setVelocidad(double vx_, double vy_);
    double getMasa() const;
    double getRadio() const;
    bool estaActiva() const;
    void desactivar();

    bool colisionaCon(const Particula& otra) const;

    void mostrar(ostream& os) const override;
};

#endif

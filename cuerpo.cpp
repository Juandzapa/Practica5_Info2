#include "cuerpo.h"

Cuerpo::Cuerpo(int id_, double x_, double y_) : id(id_), x(x_), y(y_) {}

int Cuerpo::getId() const { return id; }
double Cuerpo::getX() const { return x; }
double Cuerpo::getY() const { return y; }

void Cuerpo::setPosicion(double x_, double y_) {
    x = x_;
    y = y_;
}

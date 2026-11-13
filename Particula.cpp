#include "Particula.h"
#include <cmath>

using namespace std;

Particula::Particula(int id_, double x_, double y_, double vx_, double vy_, double masa_, double radio_) : Cuerpo(id_, x_, y_), vx(vx_), vy(vy_), masa(masa_), radio(radio_), activa(true) {}

void Particula::mover(double dt) {
    x = x + vx * dt;
    y = y + vy * dt;
}

double Particula::getVx() const { return vx; }
double Particula::getVy() const { return vy; }

void Particula::setVelocidad(double vx_, double vy_) {
    vx = vx_;
    vy = vy_;
}

double Particula::getMasa() const { return masa; }
double Particula::getRadio() const { return radio; }
bool Particula::estaActiva() const { return activa; }
void Particula::desactivar() { activa = false; }

bool Particula::colisionaCon(const Particula& otra) const {
    double dx = x - otra.x;
    double dy = y - otra.y;
    return sqrt(dx * dx + dy * dy) < radio + otra.radio;
}

void Particula::mostrar(ostream& os) const {
    os << "P" << id << " pos=(" << x << ", " << y << ")"
       << " v=(" << vx << ", " << vy << ")"
       << " m=" << masa << " r=" << radio;
}

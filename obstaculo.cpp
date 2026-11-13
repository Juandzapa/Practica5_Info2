#include "obstaculo.h"
#include <algorithm>
#include <cmath>

using namespace std;

Obstaculo::Obstaculo(int id_, double x_, double y_, double lado_, double e_)
    : Cuerpo(id_, x_, y_), lado(lado_), e(e_) {}

bool Obstaculo::seSolapa(double px, double py, double r) const {
    double dx = px - max(x, min(px, x + lado));
    double dy = py - max(y, min(py, y + lado));
    return sqrt(dx * dx + dy * dy) < r;
}

bool Obstaculo::resolverColision(Particula& p, string& ladoImpacto) const {
    double r = p.getRadio();
    double qx = max(x, min(p.getX(), x + lado));
    double qy = max(y, min(p.getY(), y + lado));
    double dx = p.getX() - qx;
    double dy = p.getY() - qy;
    double distancia = sqrt(dx * dx + dy * dy);

    if (distancia >= r || distancia == 0) return false;

    double nx = dx / distancia;
    double ny = dy / distancia;
    p.setPosicion(qx + nx * r, qy + ny * r);

    double vn = p.getVx() * nx + p.getVy() * ny;
    if (vn >= 0) return false;

    double vPerpX = nx * vn;
    double vPerpY = ny * vn;
    double vParX = p.getVx() - vPerpX;
    double vParY = p.getVy() - vPerpY;
    p.setVelocidad(vParX - e * vPerpX, vParY - e * vPerpY);

    bool izq = qx == x, der = qx == x + lado;
    bool inf = qy == y, sup = qy == y + lado;
    if ((izq || der) && (inf || sup)) ladoImpacto = "esquina";
    else if (izq) ladoImpacto = "izquierdo";
    else if (der) ladoImpacto = "derecho";
    else if (inf) ladoImpacto = "inferior";
    else          ladoImpacto = "superior";
    return true;
}

void Obstaculo::mostrar(ostream& os) const {
    os << "O" << id << " esquina=(" << x << ", " << y << ")"
       << " lado=" << lado << " e=" << e;
}

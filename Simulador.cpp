#include "Simulador.h"
#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

Simulador::Simulador(double ancho_, double alto_, double dt_)
    : ancho(ancho_), alto(alto_), dt(dt_), tiempo(0.0), siguienteId(1), totalColisiones(0) {}

void Simulador::agregarObstaculo(double x, double y, double lado, double e) {
    obstaculos.push_back(Obstaculo((int)obstaculos.size() + 1, x, y, lado, e));
}

bool Simulador::agregarParticula(double x, double y, double vx, double vy, double masa, double radio) {
    if (x - radio < 0 || x + radio > ancho || y - radio < 0 || y + radio > alto) return false;

    for (const Obstaculo& o : obstaculos)
        if (o.seSolapa(x, y, radio)) return false;

    for (const Particula& p : particulas) {
        double dx = x - p.getX();
        double dy = y - p.getY();
        if (sqrt(dx * dx + dy * dy) < radio + p.getRadio()) return false;
    }

    particulas.push_back(Particula(siguienteId++, x, y, vx, vy, masa, radio));
    return true;
}

void Simulador::paso() {
    tiempo += dt;
    for (Particula& p : particulas)
        if (p.estaActiva()) p.mover(dt);

    colisionesEntreParticulas();
    colisionesConObstaculos();
    colisionesConParedes();
}

void Simulador::colisionesEntreParticulas() {
    const size_t n = particulas.size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            Particula& a = particulas[i];
            Particula& b = particulas[j];
            if (!a.estaActiva() || !b.estaActiva() || !a.colisionaCon(b)) continue;

            double m1 = a.getMasa(), m2 = b.getMasa();
            double M = m1 + m2;
            double x = (m1 * a.getX() + m2 * b.getX()) / M;
            double y = (m1 * a.getY() + m2 * b.getY()) / M;
            double vx = (m1 * a.getVx() + m2 * b.getVx()) / M;
            double vy = (m1 * a.getVy() + m2 * b.getVy()) / M;
            double r = sqrt(a.getRadio() * a.getRadio() + b.getRadio() * b.getRadio());

            archivo << "COLISION t=" << tiempo << "  PARTICULA-PARTICULA  P" << a.getId()
                    << " + P" << b.getId() << " -> P" << siguienteId
                    << "  M=" << M << "  v'=(" << vx << ", " << vy << ")\n";
            totalColisiones++;

            a.desactivar();
            b.desactivar();
            particulas.push_back(Particula(siguienteId++, x, y, vx, vy, M, r));
            break;
        }
    }
}

void Simulador::colisionesConObstaculos() {
    for (Particula& p : particulas) {
        if (!p.estaActiva()) continue;
        for (const Obstaculo& o : obstaculos) {
            string lado;
            if (o.resolverColision(p, lado)) {
                archivo << "COLISION t=" << tiempo << "  PARTICULA-OBSTACULO  P" << p.getId()
                        << " con O" << o.getId() << "  lado=" << lado
                        << "  v'=(" << p.getVx() << ", " << p.getVy() << ")\n";
                totalColisiones++;
            }
        }
    }
}

void Simulador::colisionesConParedes() {
    for (Particula& p : particulas) {
        if (!p.estaActiva()) continue;
        double x = p.getX(), y = p.getY();
        double vx = p.getVx(), vy = p.getVy();
        double r = p.getRadio();
        string pared = "";

        if (x - r < 0 && vx < 0)
        { vx = -vx; x = r;         pared = "izquierda"; }

        if (x + r > ancho && vx > 0)
        { vx = -vx; x = ancho - r; pared = "derecha"; }

        if (y - r < 0 && vy < 0)
        { vy = -vy; y = r;         pared = "inferior"; }

        if (y + r > alto && vy > 0)
        { vy = -vy; y = alto - r;  pared = "superior"; }

        if (pared != "") {
            p.setPosicion(x, y);
            p.setVelocidad(vx, vy);
            archivo << "COLISION t=" << tiempo << "  PARTICULA-PARED  P" << p.getId()
                    << " pared " << pared << "  v'=(" << vx << ", " << vy << ")\n";
            totalColisiones++;
        }
    }
}

void Simulador::guardarPosiciones() {
    archivo << "t=" << tiempo;
    for (const Particula& p : particulas)
        if (p.estaActiva())
            archivo << " | P" << p.getId() << " (" << p.getX() << ", " << p.getY() << ")";
    archivo << "\n";
}

void Simulador::ejecutar(double tiempoTotal, const string& nombreArchivo) {
    archivo.open(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error: no se pudo crear '" << nombreArchivo << "'\n";
        return;
    }
    archivo << fixed << setprecision(3);

    archivo << "=== SIMULACION DE COLISIONES MULTIPLES ===\n";
    archivo << "Caja: " << ancho << " x " << alto << "   dt = " << dt << " s\n";
    for (const Obstaculo& o : obstaculos) { o.mostrar(archivo); archivo << "\n"; }
    for (const Particula& p : particulas) { p.mostrar(archivo); archivo << "\n"; }
    archivo << "\n--- POSICIONES Y COLISIONES ---\n";

    guardarPosiciones();
    int pasos = (int)round(tiempoTotal / dt);
    for (int k = 0; k < pasos; k++) {
        paso();
        guardarPosiciones();
    }

    archivo << "\nTotal de colisiones: " << totalColisiones << "\n";
    archivo.close();
    cout << "Total de colisiones: " << totalColisiones << "\n";
    cout << "Datos guardados en '" << nombreArchivo << "'\n";
}

void Simulador::mostrarParticulas() const {
    cout << fixed << setprecision(2);
    for (const Particula& p : particulas)
        if (p.estaActiva()) { p.mostrar(cout); cout << "\n"; }
}

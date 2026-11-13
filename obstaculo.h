#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <string>
#include "cuerpo.h"
#include "particula.h"

using namespace std;

class Obstaculo : public Cuerpo {
private:
    double lado;
    double e;

public:
    Obstaculo(int id_, double x_, double y_, double lado_, double e_);

    bool seSolapa(double px, double py, double r) const;
    bool resolverColision(Particula& p, string& ladoImpacto) const;

    void mostrar(ostream& os) const override;
};

#endif

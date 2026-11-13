#ifndef CUERPO_H
#define CUERPO_H

#include <ostream>

using namespace std;

class Cuerpo {
protected:
    int id;
    double x;
    double y;

public:
    Cuerpo(int id_, double x_, double y_);
    virtual ~Cuerpo() = default;

    int getId() const;
    double getX() const;
    double getY() const;
    void setPosicion(double x_, double y_);

    virtual void mostrar(ostream& os) const = 0;
};

#endif

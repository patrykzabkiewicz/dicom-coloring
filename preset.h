#ifndef PRESET_H
#define PRESET_H

#include <points.h>

class preset
{
public:
    preset();
    void addPoint(Points *point);
    Points getPoint(int i);
    int getIloscPunktow();
private:
    Points tab[255];
    int iloscPunktow;
};

#endif // PRESET_H

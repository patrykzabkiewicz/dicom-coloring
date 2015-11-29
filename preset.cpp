#include "preset.h"

preset::preset()
{
    this->iloscPunktow = 0;
}

void preset::addPoint(Points *point) {
    this->tab[this->iloscPunktow] = *point;
    this->iloscPunktow++;
}

Points preset::getPoint(int i) {
    return this->tab[i];
}

int preset::getIloscPunktow() {
    return this->iloscPunktow;
}

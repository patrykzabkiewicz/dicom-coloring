#include "points.h"

Points::Points() {}

Points::Points(QPoint *point, QColor *color)
{
    this->cords = *point;
    this->color = *color;
}

Points::Points(QPoint point, QColor color)
{
    this->cords = point;
    this->color = color;
}

void Points::operator =(Points point) {
    this->color = point.color;
    this->cords = point.cords;
}

#ifndef POINTS_H
#define POINTS_H

#include <QPoint>
#include <QColor>

class Points
{
public:
    Points();
    Points(QPoint point, QColor color);
    Points(QPoint *point, QColor *color);
    void operator=(Points point);
    QPoint cords;
    QColor color;
};

#endif // POINTS_H

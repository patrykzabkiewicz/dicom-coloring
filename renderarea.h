
#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QWidget>
#include <QPainter>
#include <QPalette>
#include <QPoint>
#include <QList>
#include <iostream>
#include <points.h>

using namespace std;

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    RenderArea(QWidget *parent = 0);
    void addHPoint(int x, int y);
    void addHPoint(QPoint point, QColor color);
    void addHPoint(int x, int y, QColor color);
    void delHPoint();
    void delHPoint(int i);
    void delHPoint(int x, int y);
    void changeHPoint(int x, int y);
    void changeHPoint(int x, int y, QColor *al);
    void changeHPoint(int i, int x, int y);
    void setHistogram(int *accumulate);
    int getIloscPunktow();
    Points* getPoint(int i);
    QPoint getMax();
    Points getActual();
    void mousePress(QPoint event);
    void clearPoints();

private:
    static const int sizex = 400;
    static const int sizey = 100;
    Points *pointsTab[400];
    int iloscpunktow;
    int original[400];
    int imageloaded;
    int aktualniewybrany;
    void SortPoints();
    QPainter *path;

protected:
    void paintEvent(QPaintEvent *event);


};


#endif

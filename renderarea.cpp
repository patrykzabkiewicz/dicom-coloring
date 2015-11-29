
#include <QtGui>

#include "renderarea.h"


RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    this->resize(this->sizex+1,this->sizey+1);
    this->setMinimumSize(this->sizex+1,this->sizey+1);
    this->setMaximumSize(this->sizex+1,this->sizey+1);

    this->imageloaded = 0;
    this->aktualniewybrany = 0;

    //this->pointsTab = new Points[this->sizex];

    this->pointsTab[0] = new Points(QPoint(0,50),QColor(0,0,0,255));
    this->pointsTab[1] = new Points(QPoint(this->sizex,50),QColor(0,0,0,255));

    this->iloscpunktow =2;
    this->aktualniewybrany = 1;

}

void RenderArea::clearPoints() {
    for(int i=this->iloscpunktow; i>0; i--) {
        this->delHPoint(i);
    }
}


int RenderArea::getIloscPunktow() {
    return this->iloscpunktow;
}


Points* RenderArea::getPoint(int i) {
    return this->pointsTab[i];
}

void RenderArea::setHistogram(int *accumulate) {

    for(int i=0; i<this->sizex; i++, accumulate++) {
        this->original[i] = *accumulate;
    }

    this->imageloaded=1;
    this->update();
}

void RenderArea::addHPoint(int x, int y) {
    this->pointsTab[this->iloscpunktow] = new Points(QPoint(x,this->sizey-y),QColor(0,0,0,255));
    this->iloscpunktow++;
    this->SortPoints();
    for(int i=0; i<this->iloscpunktow; i++) {
     if(this->pointsTab[i]->cords.x()==x && this->pointsTab[i]->cords.y()==this->sizey-y) this->aktualniewybrany = i;
        }
    this->update();
}


void RenderArea::addHPoint(QPoint point, QColor color) {
    this->pointsTab[this->iloscpunktow] = new Points(point,color);
    this->iloscpunktow++;
    this->SortPoints();
    for(int i=0; i<this->iloscpunktow; i++) {
     if(this->pointsTab[i]->cords.x()==point.x() && this->pointsTab[i]->cords.y()==this->sizey-point.y()) this->aktualniewybrany = i;
        }
    this->update();
}


void RenderArea::addHPoint(int x, int y, QColor color) {
    this->pointsTab[this->iloscpunktow] = new Points(QPoint(x,this->sizey-y),color);
    this->iloscpunktow++;
    this->SortPoints();
    for(int i=0; i<this->iloscpunktow; i++) {
     if(this->pointsTab[i]->cords.x()==x && this->pointsTab[i]->cords.y()==this->sizey-y) this->aktualniewybrany = i;
        }
    this->update();
}

void RenderArea::changeHPoint(int i, int x, int y) {
    this->pointsTab[i]->cords.setX(x);
    this->pointsTab[i]->cords.setY(this->sizey-y);
    this->SortPoints();
    this->update();
}

void RenderArea::changeHPoint(int x, int y) {
    this->pointsTab[this->aktualniewybrany]->cords.setX(x);
    this->pointsTab[this->aktualniewybrany]->cords.setY(this->sizey-y);
    this->SortPoints();
    this->update();
}

void RenderArea::changeHPoint(int x, int y, QColor *color) {
    this->pointsTab[this->aktualniewybrany]->cords.setX(x);
    this->pointsTab[this->aktualniewybrany]->cords.setY(this->sizey-y);
    this->pointsTab[this->aktualniewybrany]->color = *color;

    this->SortPoints();
    this->update();
}

void RenderArea::SortPoints() {
    for(int i=0; i < this->iloscpunktow; i++) {
        for(int j=0; j < this->iloscpunktow; j++) {
            if(this->pointsTab[i]->cords.x() < this->pointsTab[j]->cords.x()) {
            Points *c = this->pointsTab[i];
            this->pointsTab[i]=this->pointsTab[j];
            this->pointsTab[j]=c;
            }
        }
    }
}

void RenderArea::delHPoint() {
    for(int j=this->aktualniewybrany; j< this->iloscpunktow; j++) {
        this->pointsTab[j]=this->pointsTab[j+1];
    }
    this->iloscpunktow--;
    this->aktualniewybrany--;
    this->update();
}

void RenderArea::delHPoint(int i) {
    for(int j=i; j< this->iloscpunktow; j++) {
        this->pointsTab[j]=this->pointsTab[j+1];
    }
    this->iloscpunktow--;
    this->aktualniewybrany--;
    this->update();
}

void RenderArea::delHPoint(int x, int y) {

    int z =0;
for(int i=0; i< this->iloscpunktow; i++) {

        if(this->pointsTab[i]->cords.x()==x && this->pointsTab[i]->cords.y()==this->sizey-y) {
            for(int j=i; j< this->iloscpunktow; j++) {
                this->pointsTab[j]=this->pointsTab[j+1];
            }
            this->iloscpunktow--;
            this->aktualniewybrany--;
            z=1;
        }
    }

    if(z==0) this->delHPoint();
    this->update();
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);

    painter.setPen(QPen(QColor(160, 160, 160, 255), 1));

    if(this->imageloaded==1)
    for(int x=0; x < this->sizex ; x++) {
            painter.drawLine(x,this->sizey,x,this->sizey-(this->original[x]/15));
    }


    painter.setRenderHint(QPainter::Antialiasing, true);
    QPainterPath path;
    painter.setPen(QPen(QColor(50, 50, 50, 255), 2));
     path.moveTo(this->pointsTab[0]->cords);

     for(int i=0; i < this->iloscpunktow; i++) {
        path.lineTo(this->pointsTab[i]->cords);
     }

     painter.drawPath(path);

     painter.setPen(QPen(QColor(0, 0, 0, 255), 1));

     for(int i=0; i < this->iloscpunktow; i++) {
         if(i==this->aktualniewybrany) {
         painter.setBrush(QBrush(QColor(255,255,255,255),Qt::SolidPattern));
         } else {
         painter.setBrush(QBrush(this->pointsTab[i]->color,Qt::SolidPattern));
         }
         painter.drawEllipse(this->pointsTab[i]->cords,4,4);
     }

     painter.setBrush(Qt::NoBrush);

     painter.setRenderHint(QPainter::Antialiasing, false);
     painter.drawRect(0,0,this->sizex,this->sizey);


}

void RenderArea::mousePress(QPoint event) {

    int z=0;

    for(int i=0; i<this->iloscpunktow; i++) {
        if(
                (this->pointsTab[i]->cords.x() >= event.x()-3 && this->pointsTab[i]->cords.x() <= event.x()+3 ) &&
                (this->pointsTab[i]->cords.y() >= event.y()-3 && this->pointsTab[i]->cords.y() <= event.y()+3)
                ) {
            this->aktualniewybrany = i;
            z=1;
        }
    }

    if(z==0) {
        this->addHPoint(event.x(),this->sizey-event.y());
    }

    this->update();

}

QPoint RenderArea::getMax() {
    return QPoint(this->sizex,this->sizey);
}

Points RenderArea::getActual() {
    Points *z = new Points(this->pointsTab[this->aktualniewybrany]->cords,this->pointsTab[this->aktualniewybrany]->color);

    return *z;
}

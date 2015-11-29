
#include <QtGui>

#include "renderarea.h"
#include "window.h"

const int IdRole = Qt::UserRole;

Window::Window()
{
    renderArea = new RenderArea;

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(renderArea, 0, 0, 1, 4);
    mainLayout->setRowMinimumHeight(1, 6);

    setLayout(mainLayout);

    setWindowTitle(tr("Histogram Widget"));
}


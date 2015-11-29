
#include <QtGui>

#include "renderarea.h"
#include "window.h"

Window::Window()
{
    createMenu();
    renderArea = new RenderArea;


    QLabel *lbl1 = new QLabel(QString(tr("X:")));
    QLabel *lbl2 = new QLabel(QString(tr("Y:")));

    QLabel *lbl3 = new QLabel(QString(tr("R:")));
    QLabel *lbl4 = new QLabel(QString(tr("G:")));
    QLabel *lbl5 = new QLabel(QString(tr("B:")));
    QLabel *lbl6 = new QLabel(QString(tr("Alpha:")));

    zakR = new QLineEdit();
    zakG = new QLineEdit();
    zakB = new QLineEdit();
    zakA = new QLineEdit();

    zakx = new QLineEdit();
    zaky = new QLineEdit();

    QPushButton *addButton = new QPushButton(tr("&Dodaj"));
    QPushButton *changeButton = new QPushButton(tr("&Zmien"));
    QPushButton *delButton = new QPushButton(tr("&Usun"));

    saveName = new QLineEdit();
    QPushButton *loadButton = new QPushButton(tr("Wczytaj"));
    QPushButton *saveButton = new QPushButton(tr("Zapisz"));

    QHBoxLayout *savePanel = new QHBoxLayout();
    savePanel->addWidget(saveName);
    savePanel->addWidget(loadButton);
    savePanel->addWidget(saveButton);

    //
    //definiowanie listy presetow

    presetList = new QListWidget();
    presetList->addItem("preset #1");


    Points *point = new Points(QPoint(0,100),QColor(0,0,0,255));
    Points *point2 = new Points(QPoint(renderArea->getMax().x(),0),QColor(255,255,255,255));

    this->pList[0] = new preset();
    this->pList[0]->addPoint(point);
    this->pList[0]->addPoint(point2);

    this->aktualnyPreset = 0;
    this->iloscPresetow = 1;

    this->presetList->setCurrentRow(0);

    //
    //end

    QVBoxLayout *sPanel = new QVBoxLayout();
    sPanel->addLayout(savePanel);
    sPanel->addWidget(presetList);

    QHBoxLayout *bottomPanel  = new QHBoxLayout();

    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadPreset()));
    connect(saveButton, SIGNAL(clicked()),this, SLOT(savePreset()));
    connect(presetList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(changePreset()));

    connect(addButton, SIGNAL(clicked()), this, SLOT(addHPoint()));
    connect(changeButton, SIGNAL(clicked()), this, SLOT(changeHPoint()));
    connect(delButton, SIGNAL(clicked()), this, SLOT(delHPoint()));

    QHBoxLayout *panel = new QHBoxLayout;

    QHBoxLayout *panelRGB = new QHBoxLayout;

    okno = new QVTKWidget();
    okno->resize(640,480);
    okno->setMinimumSize(640,480);
    okno->setMaximumSize(640,480);

    QGridLayout *mainLayout = new QGridLayout;

    panelRGB->addWidget(lbl3);
    panelRGB->addWidget(zakR);
    panelRGB->addWidget(lbl4);
    panelRGB->addWidget(zakG);
    panelRGB->addWidget(lbl5);
    panelRGB->addWidget(zakB);
    panelRGB->addWidget(lbl6);
    panelRGB->addWidget(zakA);

    panel->addWidget(lbl1);
    panel->addWidget(zakx);

    panel->addWidget(lbl2);
    panel->addWidget(zaky);

    panel->addWidget(addButton);
    panel->addWidget(changeButton);
    panel->addWidget(delButton);

    bottomPanel->addWidget(renderArea);
    bottomPanel->addLayout(sPanel);

    mainLayout->addWidget(okno,0,0);
    mainLayout->addLayout(panel,2,0);
    mainLayout->addLayout(panelRGB,1,0);
    mainLayout->addLayout(bottomPanel,3,0);

    mainLayout->setMenuBar(menuBar);

    setLayout(mainLayout);

    setWindowTitle(tr("Histogram"));

}

void Window::createMenu()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&Plik"), this);
    openAction = fileMenu->addAction(tr("&Otworz Alt+O"));
    loadAction = fileMenu->addAction(tr("W&czytaj Preset Alt+C"));
    saveAction = fileMenu->addAction(tr("&Zapisz Preset Alt+Z"));
    exitAction = fileMenu->addAction(tr("&Wyjscie Alt+W"));
    menuBar->addMenu(fileMenu);

    connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(loadAction, SIGNAL(triggered()), this, SLOT(loadPresetFile()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(savePresetFile()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
}

void Window::changePreset() {
    this->saveName->setText(this->presetList->currentItem()->text());
}

void Window::savePreset(QString name) {

    if(this->presetList->currentItem()->text()!=this->saveName->text()) {

        if(name == QString("")) {
            this->presetList->addItem(this->saveName->text());
        }
        else {
            this->presetList->addItem(name);
        }

    this->pList[this->iloscPresetow] = new preset();

    for(int i=0; i< renderArea->getIloscPunktow(); i++)
    this->pList[this->iloscPresetow]->addPoint(renderArea->getPoint(i));

    this->iloscPresetow++;
    this->aktualnyPreset = this->iloscPresetow-1;
    this->presetList->setCurrentRow(this->aktualnyPreset);

} else {

    this->pList[this->presetList->currentIndex().row()] = new preset();

    for(int i=0; i< renderArea->getIloscPunktow(); i++)
    this->pList[this->presetList->currentIndex().row()]->addPoint(renderArea->getPoint(i));

}
this->saveName->setText(QString(""));
}

void Window::loadPreset() {
    renderArea->clearPoints();
    this->aktualnyPreset = this->presetList->currentIndex().row();

    Points a;

    for(int i=0; i<this->pList[this->aktualnyPreset]->getIloscPunktow(); i++) {
        a = this->pList[this->aktualnyPreset]->getPoint(i);
        renderArea->addHPoint(a.cords,a.color);

    }

    this->makeMapToColors();
}

void Window::loadPresetFile() {
    QString fileName;

    fileName = QFileDialog::getOpenFileName(this, tr("Otworz Plik"), m_currentPath, "Wszystkie (*.pre)");

    if (!fileName.isEmpty()) {

        renderArea->clearPoints();

    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream lo(&file);

    while(!lo.atEnd()) {
    QString line = lo.readLine();
    QStringList list = line.split(",");

    renderArea->addHPoint(QPoint(list.at(0).toInt(),list.at(1).toInt()),QColor(list.at(2).toInt(),list.at(3).toInt(),list.at(4).toInt(),255));
    }
    this->savePreset(fileName);
    this->makeMapToColors();
    }
}

void Window::savePresetFile() {
    QString fileName;

    fileName = QFileDialog::getSaveFileName(this, tr("Zapisz Plik"), m_currentPath, "Wszystkie (*.*)");
    //QFileDialog::getOpenFileName();

    QFile file(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);

        for(int i=0; i< renderArea->getIloscPunktow(); i++)
        {
            Points p = *(renderArea->getPoint(i));
            out << p.cords.x() << ",";
            out << p.cords.y() << ",";
            out << p.color.red() << ",";
            out << p.color.green() << ",";
            out << p.color.blue() << ",";
            out << p.color.alpha();
            out << "\n";
            //out << QString("dupa blada\n");
        }
         //out << "bla\n";

        file.close();
}

QString Window::serializePoint(Points p) {
    QString tmp;

    tmp += p.cords.x();
    tmp += p.cords.y();
    tmp += "\n";

    cout << tmp.toStdString() << endl;

    return tmp;
}

void Window::setZakX(int x) {

    string tmp; // brzydkie rozwiązanie
    sprintf((char*)tmp.c_str(), "%d", x);
    string str = tmp.c_str();

    this->zakx->setText(QString(str.c_str()));
}

void Window::setZakY(int y) {

    string tmp; // brzydkie rozwiązanie
    sprintf((char*)tmp.c_str(), "%d", y);
    string str = tmp.c_str();

    this->zaky->setText(QString(str.c_str()));
}

void Window::setZakR(int r) {
    string tmp; // brzydkie rozwiązanie
    sprintf((char*)tmp.c_str(), "%d", r);
    string str = tmp.c_str();

    this->zakR->setText(QString(str.c_str()));
}

void Window::setZakG(int g) {
    string tmp; // brzydkie rozwiązanie
    sprintf((char*)tmp.c_str(), "%d", g);
    string str = tmp.c_str();

    this->zakG->setText(QString(str.c_str()));
}

void Window::setZakB(int b) {
    string tmp; // brzydkie rozwiązanie
    sprintf((char*)tmp.c_str(), "%d", b);
    string str = tmp.c_str();

    this->zakB->setText(QString(str.c_str()));
}

void Window::setZakA(int a) {
    string tmp; // brzydkie rozwiązanie
    sprintf((char*)tmp.c_str(), "%d", a);
    string str = tmp.c_str();

    this->zakA->setText(QString(str.c_str()));
}


void Window::makeMapToColors() {

    vtkSmartPointer<vtkLookupTable> tab1 =
      vtkSmartPointer<vtkLookupTable>::New();

    tab1->SetNumberOfColors(2000);
    tab1->SetNumberOfTableValues(2000);
    tab1->SetTableRange(-1000,1000);


    vtkColorTransferFunction *color = vtkColorTransferFunction::New();
    color->SetColorSpaceToDiverging();


    for(int i=0;i<renderArea->getIloscPunktow();i++) {

        Points *p = renderArea->getPoint(i);

        color->AddRGBPoint((double)p->cords.x()*5.0,
                           (double)p->color.red()/255.0,
                           (double)p->color.green()/255.0,
                           (double)p->color.blue()/255.0
                );
    }

    for(int i=0;i<2000;i++) {
        double *cc = color->GetColor(i);

        tab1->SetTableValue(i,cc[0],cc[1],cc[2],0.9);
    }

    vtkSmartPointer<vtkImageMapToColors> mapper =
      vtkSmartPointer<vtkImageMapToColors>::New();

    mapper->SetLookupTable(tab1);
    mapper->SetInput(this->reader->GetOutput());
    mapper->Update();

    this->image_view->SetInput(mapper->GetOutput());
    this->image_view->Render();

}


void Window::openFile(const QString &path) {

    QString fileName;

    if (path.isNull())
        fileName = QFileDialog::getOpenFileName(this, tr("Otworz Plik"), m_currentPath, "Wszystkie (*.dcm)");
    else
        fileName = path;



    if (!fileName.isEmpty()) {
        this->reader = vtkDICOMImageReader::New();
        if( !reader->CanReadFile( fileName.toAscii() ) )
          {
            QMessageBox::information(this, tr("Puste Pole"),tr("Nie mozna odczytac obrazka"));
        } else {

             reader->SetFileName( fileName.toAscii() );
             reader->Update();

             vtkSmartPointer<vtkLookupTable> tab1 =
               vtkSmartPointer<vtkLookupTable>::New();

             tab1->SetTableRange(-1000,1000);
             tab1->SetNumberOfColors(2000);
             tab1->SetHueRange(0.0,0.0);
             tab1->SetValueRange(0.0,1.0);
             tab1->SetSaturationRange(0.0,0.0);
             tab1->SetRampToLinear();
             tab1->Build();


             vtkSmartPointer<vtkImageMapToColors> mapper =
               vtkSmartPointer<vtkImageMapToColors>::New();

             mapper->SetLookupTable(tab1);
             mapper->SetInput(reader->GetOutput());
             mapper->Update();

             this->image_view = vtkImageViewer::New();
             image_view->SetInput(mapper->GetOutput());


             int middley=0;
             int middlex=0;
             int sizex=reader->GetWidth();
             int sizey=reader->GetHeight();

             if((okno->size().width() - reader->GetWidth())<0) {
                sizex = reader->GetWidth()+(okno->size().width() - reader->GetWidth());
             }

             if((okno->size().height() - reader->GetHeight())<0) {
                sizey = reader->GetHeight()+(okno->size().height() - reader->GetHeight());
             }

             middlex = okno->size().width()/2 - sizex/2;
             middley = okno->size().height()/2 - sizey/2;

             okno->SetRenderWindow(image_view->GetRenderWindow());

             image_view->SetColorLevel(128);
             image_view->SetColorWindow(255);
             image_view->SetPosition(okno->pos().x()+middlex,okno->pos().y()+middley);
             image_view->SetSize(sizex,sizey);

             image_view->SetupInteractor(okno->GetRenderWindow()->GetInteractor());
             image_view->Render();

             vtkSmartPointer<vtkImageAccumulate> histogram = vtkSmartPointer<vtkImageAccumulate>::New();
             histogram->SetInputConnection(reader->GetOutputPort());
             histogram->SetComponentExtent(-200,200,0,0,0,0);
             histogram->SetComponentOrigin(1,0,0);
             histogram->SetComponentSpacing(1,0,0);
             histogram->IgnoreZeroOn();
             histogram->Update();

             int* output = static_cast<int*>(histogram->GetOutput()->GetScalarPointer());

             renderArea->setHistogram(output);

         }
    }
}

void Window::changeHPoint() {
    if (zakx->text().isEmpty() || zaky->text().isEmpty()) {
        QMessageBox::information(this, tr("Puste Pole"),tr("Wpisz Numer w Pole"));
    } else {
        int x = zakx->text().toInt();
        int y = zaky->text().toInt();

        QColor *al = new QColor(zakR->text().toInt(),zakG->text().toInt(),zakB->text().toInt(),zakA->text().toInt());

        renderArea->changeHPoint(x,y,al);
            this->makeMapToColors();
    }
}

void Window::delHPoint() {
    if (zakx->text().isEmpty() || zaky->text().isEmpty()) {
        //QMessageBox::information(this, tr("Puste Pole"),tr("Wpisz Numer w Pole"));
        renderArea->delHPoint();
        Points z = renderArea->getActual();
        this->setZakX(z.cords.x());
        this->setZakY(z.cords.y());
    } else {
        int x = zakx->text().toInt();
        int y = zaky->text().toInt();
        renderArea->delHPoint(x,y);

        Points z = renderArea->getActual();
        this->setZakX(z.cords.x());
        this->setZakY(z.cords.y());
    }
        this->makeMapToColors();
}

void Window::addHPoint()
{
    if (zakx->text().isEmpty() || zaky->text().isEmpty()) {
        QMessageBox::information(this, tr("Puste Pole"),tr("Wpisz Numer w Pole"));
    } else {
        int x = zakx->text().toInt();
        int y = zaky->text().toInt();
        renderArea->addHPoint(x,y);
            this->makeMapToColors();
    }
}

void Window::mousePressEvent(QMouseEvent *event) {
QPoint w = event->pos() - renderArea->pos();
QPoint z = renderArea->getMax();

if( (w.x() >= 0 && w.y() >= 0) && (w.x() <= z.x() && w.y() <= z.y()) ) {
    renderArea->mousePress(event->pos() - renderArea->pos());
    Points z = renderArea->getActual();
    this->setZakX(z.cords.x());
    this->setZakY(renderArea->getMax().y()-z.cords.y());
    this->setZakR(z.color.red());
    this->setZakG(z.color.green());
    this->setZakB(z.color.blue());
    this->setZakA(z.color.alpha());
        this->makeMapToColors();
}

}

void Window::mouseMoveEvent(QMouseEvent *event)
{
    QPoint w = event->pos() - renderArea->pos();
    QPoint z = renderArea->getMax();

if( (w.x() >= 0 && w.y() >= 0) && (w.x() <= z.x() && w.y() <= z.y()) ) {
    renderArea->changeHPoint(event->pos().x() - renderArea->pos().x(),renderArea->getMax().y() - (event->pos().y() - renderArea->pos().y()));
    this->setZakX(event->pos().x() - renderArea->pos().x());
    this->setZakY(renderArea->getMax().y() - (event->pos().y() - renderArea->pos().y()));
    this->makeMapToColors();
}
}

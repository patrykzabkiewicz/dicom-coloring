
#ifndef WINDOW_H
#define WINDOW_H

#include <cstdio>
#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <QMenuBar>
#include <QMenu>
#include <QPoint>
#include <QAction>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>

#include <QVTKWidget.h>
#include <vtkImageAccumulate.h>
#include <vtkImageData.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkDICOMImageReader.h>
#include <vtkImageViewer.h>
#include <vtkLookupTable.h>
#include <vtkImageMapToColors.h>
#include <vtkColorTransferFunction.h>

#include <points.h>
#include <preset.h>


class RenderArea;

QT_BEGIN_NAMESPACE
class QMenuBar;
class QMenu;
class QAction;
class QLabel;
class QLineEdit;
class QPushButton;
class QString;
class QPoint;
class QVTKWidget;
class QListWidget;
QT_END_NAMESPACE


class Window : public QDialog
{
    Q_OBJECT

public:
    Window();

public slots:
    void addHPoint();
    void delHPoint();
    void changeHPoint();
    void openFile(const QString &path = QString());
    void loadPresetFile();
    void savePresetFile();
    void changePreset();
    void loadPreset();
    void savePreset(QString name = QString());

private:
    RenderArea *renderArea;
    void createMenu();
    void makeMapToColors();
    void setZakX(int x);
    void setZakY(int y);
    void setZakR(int r);
    void setZakG(int g);
    void setZakB(int b);
    void setZakA(int a);
    QString serializePoint(Points p);

    vtkDICOMImageReader *reader;
    vtkImageViewer *image_view;

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QAction *exitAction;
    QAction *openAction;
    QAction *loadAction;
    QAction *saveAction;

    QLabel *lbl1;
    QLabel *lbl2;

    QLabel *lbl3;
    QLabel *lbl4;
    QLabel *lbl5;
    QLabel *lbl6;

    QLineEdit *zakx;
    QLineEdit *zaky;

    QLineEdit *zakR;
    QLineEdit *zakG;
    QLineEdit *zakB;
    QLineEdit *zakA;

    QPushButton *addButton;
    QPushButton *delButton;
    QPushButton *changeButton;
    QVTKWidget *okno;
    QString *path;
    QString m_currentPath;

    QLineEdit *saveName;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QListWidget *presetList;

    int dl,zak, iloscPresetow, aktualnyPreset;
    preset *pList[25];

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

};


#endif

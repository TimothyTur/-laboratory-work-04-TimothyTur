#include "mainwindow.h"
#include "figures.h"

#include <QMenuBar>
#include <QCoreApplication>
#include <QContextMenuEvent>

//public:
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(800, 623);

    _MainMenu = menuBar()->addMenu(tr("&File"));
    _ActionQuit = _MainMenu->addAction(tr("&Quit"),
                                       QCoreApplication::instance(),
                                       SLOT(quit()));



    Figure1* f1 = new Figure1(this);
    f1->move(25, 25); // +225, +180
    Figure1* f2 = new Figure1(this);
    f2->move(250, 25);
    Figure1* f3 = new Figure1(this);
    f3->move(475, 25);
    Figure1* f4 = new Figure1(this);
    f4->move(25, 205);
    //Figure2* f5 = new Figure2(this);
    //f5->move(250, 205);
    Figure2* f6 = new Figure2(this);
    f6->move(475, 205);
    Figure2* f7 = new Figure2(this);
    f7->move(25, 385);
    Figure2* f8 = new Figure2(this);
    f8->move(250, 385);
    Figure2* f9 = new Figure2(this);
    f9->move(475, 385);

    figures.push_back(f1);
    figures.push_back(f2);
    figures.push_back(f3);
    figures.push_back(f4);
    //figures.push_back(f5);
    figures.push_back(f6);
    figures.push_back(f7);
    figures.push_back(f8);
    figures.push_back(f9);
    for(size_t i=0; i<figures.size(); ++i)
        connect(figures[i], SIGNAL(selectedSgn(Figure*)),
                this, SLOT(deselect(Figure*)));
}

MainWindow::~MainWindow() {}

//protected:
void MainWindow::contextMenuEvent(QContextMenuEvent* event) {
    //additional:
    //else
    //    show BackgroundMenu
    _MainMenu->exec(event->globalPos());
}

void MainWindow::mousePressEvent(QMouseEvent* event) {                         //!!!
    deselect(nullptr);
}

//void MainWindow::mouseReleaseEvent(QMouseEvent* e) {                     //!!!
//}

//private slots:
void MainWindow::deselect(Figure* figure) {                                          //!!!
    for(size_t i=0; i<figures.size(); ++i) {
        if(figures[i]!=figure)
            figures[i]->deselect();
    }
    update();
}

void MainWindow::deleteFigure() {                                          //!!!
    //delete selected
}

void MainWindow::showFigureChange() {                                      //!!!
    //on selected figure
}

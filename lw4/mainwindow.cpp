#include "mainwindow.h"
#include "figures.h"

#include <QMenuBar>
#include <QCoreApplication>
#include <QContextMenuEvent>
#include <QRandomGenerator>

#include <iostream>

//public:
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , selected(0)
{
    setFixedSize(800, 623);

    _ActionFigure1 = menuBar()->addAction(tr("&Figure 1"),
                                          this, SLOT(select1()));
    _ActionFigure2 = menuBar()->addAction(tr("&Figure 2"),
                                          this, SLOT(select2()));
    _ActionCreate = menuBar()->addAction(tr("&Create"),
                                          this, SLOT(create()));
    _ActionDelete = menuBar()->addAction(tr("&Delete"),
                                          this, SLOT(delSelected()));


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
    for(size_t i=0; i<figures.size(); ++i) {
        connect(figures[i], SIGNAL(selectedSgn(Figure*)),
                this, SLOT(deselect(Figure*)));
        connect(figures[i], SIGNAL(moveSgn(Figure*,int,int)),
                this, SLOT(moveFigure(Figure*,int,int)));
        connect(figures[i], SIGNAL(delSgn(Figure*)),
                this, SLOT(delSingle(Figure*)));
    }
}

MainWindow::~MainWindow() {}

//protected:
void MainWindow::contextMenuEvent(QContextMenuEvent* event) {
    //additional:
    //    show BackgroundMenu
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
    deselect(nullptr);
}

//private slots:
void MainWindow::deselect(Figure* figure) {
    for(size_t i=0; i<figures.size(); ++i) {
        if(figures[i]!=figure)
            figures[i]->deselect();
    }
    update();
}
void MainWindow::moveFigure(Figure* figure, int dx, int dy) {
    if(figure->isSelected()) {
        int x = figure->geometry().left(),
            y = figure->geometry().top(),
            w = figure->geometry().right() - x,
            h = figure->geometry().bottom() - y;
        x += dx; y += dy;
        if(x<0)
            x = 0;
        else if(x+w>800)
            x = 800-w;
        if(y<20)
            y = 20;
        else if(y+h>623)
            y = 623-h;
        figure->move(x, y);
    }
}
void MainWindow::select1() {
    _ActionFigure1->setEnabled(false);
    _ActionFigure2->setEnabled(true);
    selected = 1;
}
void MainWindow::select2() {
    _ActionFigure1->setEnabled(true);
    _ActionFigure2->setEnabled(false);
    selected = 2;
}
void MainWindow::create() {
    //Figure* f;
    if(selected==1) {
        Figure1* f = new Figure1(this);
        int w = QRandomGenerator::global()->bounded(600),
            h = QRandomGenerator::global()->bounded(400);
        std::cout << (selected+10) << ' ' << f << ' ' << w << ' ' << h << '\n';
        f->move(w, h);
        connect(f, SIGNAL(selectedSgn(Figure*)),
                this, SLOT(deselect(Figure*)));
        figures.push_back(f);
    }
    else if(selected==2) {
        Figure2* f = new Figure2(this);
        int w = QRandomGenerator::global()->bounded(600),
            h = QRandomGenerator::global()->bounded(400);
        std::cout << (selected+10) << ' ' << f << ' ' << w << ' ' << h << '\n';
        f->move(w, h);
        connect(f, SIGNAL(selectedSgn(Figure*)),
                this, SLOT(deselect(Figure*)));
        figures.push_back(f);
    }
    update();
}
void MainWindow::delSingle(Figure* figure) {
    int i = figures.indexOf(figure);
    delete figures[i];
    figures[i] = nullptr;
    figures.remove(i);
}
void MainWindow::delSelected() {
    for(int i=0; i<figures.size(); ++i) {
        if(figures[i]->isSelected()) {
            delete figures[i];
            figures[i] = nullptr;
            figures.remove(i);
        }
    }
    update();
}

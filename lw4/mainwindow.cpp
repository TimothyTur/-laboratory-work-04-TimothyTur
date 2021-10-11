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
    _ActionFigure1 = menuBar()->addAction(tr("&Figure 1"),
                                          this, SLOT(select1()));
    _ActionFigure2 = menuBar()->addAction(tr("&Figure 2"),
                                          this, SLOT(select2()));
    _ActionCreate = menuBar()->addAction(tr("&Create"),
                                          this, SLOT(create()));
    _ActionDelete = menuBar()->addAction(tr("&Delete"),
                                          this, SLOT(delSelected()));
    _ActionCreate->setEnabled(false);
    _ActionDelete->setEnabled(false);

    _BackgroundMenu = new QMenu(this);
    _ActionDeleteAll =
            _BackgroundMenu->addAction(tr("&Delete All"),
                                       this, SLOT(delAll()));
    _ActionDeleteColliding =
            _BackgroundMenu->addAction(tr("&Delete Colliding"),
                                       this, SLOT(delColliding()));

    toolbarH = menuBar()->height();
    setFixedSize(800, 622);

    /*
    Figure1* f1 = new Figure1(this);
    f1->move(25, 23); // +225, +180
    Figure1* f2 = new Figure1(this);
    f2->move(250, 23);
    Figure1* f3 = new Figure1(this);
    f3->move(475, 23);
    Figure1* f4 = new Figure1(this);
    f4->move(25, 205);
    //f5
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
    */
}

MainWindow::~MainWindow() {}

//protected:
void MainWindow::contextMenuEvent(QContextMenuEvent* event) {
    //additional:
    //    show BackgroundMenu
    _BackgroundMenu->exec(event->globalPos());
}
void MainWindow::mousePressEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        deselect(nullptr);
        _ActionDelete->setEnabled(false);
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent* e) {
    /*
    for(size_t i=0; i<figures.size(); ++i) {
        if(figures[i]->hasMouseTracking())
            moveFigure(figures[i],
                       e->pos().x()-figures[i]->geometry().left(),
                       e->pos().y()-figures[i]->geometry().top());
    }
    */
}

//private slots:
void MainWindow::deselect(Figure* figure) {
    for(size_t i=0; i<figures.size(); ++i) {
        if(figures[i]!=figure)
            figures[i]->deselect();
    }
    if(figure != nullptr)
        _ActionDelete->setEnabled(true);
    update();
}
void MainWindow::moveFigure(Figure* figure, int dx, int dy) {
    if(not figure->isBlocked()) {
        int x = figure->geometry().left(),
            y = figure->geometry().top(),
            w = figure->geometry().right() - x,
            h = figure->geometry().bottom() - y;
        x += dx; y += dy;
        if(x<0)
            x = 0;
        else if(x+w>800)
            x = 800-w;
        if(y<23)
            y = 23;
        else if(y+h>623)
            y = 623-h;
        bool toCheck;
        for(int i=0; i<figures.size(); ++i) {
            toCheck = false;
            if(figures[i] != figure) {
                int xf = figures[i]->geometry().left(),
                    yf = figures[i]->geometry().top(),
                    wf = figures[i]->geometry().right() - xf,
                    hf = figures[i]->geometry().bottom() - yf;
                if(x>xf and x<xf+wf) {
                    if(y>yf and y<yf+hf) {
                        toCheck = true;
                    }
                    else if(y+h>yf and y+h<yf+hf) {
                        toCheck = true;
                    }
                }
                else if(x+w>xf and x+w<xf+wf) {
                    if(y>yf and y<yf+hf) {
                        toCheck = true;
                    }
                    else if(y+h>yf and y+h<yf+hf) {
                        toCheck = true;
                    }
                }
                if(toCheck) {
                    if(figuresColliding(figure, figures[i],
                                        x-xf, y-yf)) {
                        figure->block();
                        figures[i]->block();
                    }
                }
            }
        }
        if(not figure->isBlocked())
            figure->move(x, y);
    }
}
void MainWindow::select1() {
    _ActionFigure1->setEnabled(false);
    _ActionFigure2->setEnabled(true);
    _ActionCreate->setEnabled(true);
    selected = 1;
}
void MainWindow::select2() {
    _ActionFigure1->setEnabled(true);
    _ActionFigure2->setEnabled(false);
    _ActionCreate->setEnabled(true);
    selected = 2;
}
void MainWindow::create() {
    Figure* f;
    if(selected==1)
        f = new Figure1(this);
    else if(selected==2)
        f = new Figure2(this);
    else
        return;
    f->move(QRandomGenerator::global()->bounded(600),
            QRandomGenerator::global()->bounded(23, 423));
    f->show();
    connect(f, SIGNAL(selectedSgn(Figure*)),
            this, SLOT(deselect(Figure*)));
    connect(f, SIGNAL(moveSgn(Figure*,int,int)),
            this, SLOT(moveFigure(Figure*,int,int)));
    connect(f, SIGNAL(delSgn(Figure*)),
            this, SLOT(delSingle(Figure*)));
    connect(f, SIGNAL(mousePressSgn(QMouseEvent*)),
            this, SLOT(callMousePress(QMouseEvent*)));
    connect(f, SIGNAL(contextMenuSgn(QContextMenuEvent*)),
            this, SLOT(callContextMenu(QContextMenuEvent*)));
    figures.push_back(f);

    int x = f->geometry().left(),
        y = f->geometry().top(),
        w = f->geometry().right() - x,
        h = f->geometry().bottom() - y;
    bool toCheck;
    for(int i=0; i<figures.size(); ++i) {
        toCheck = false;
        if(figures[i] != f) {
            int xf = figures[i]->geometry().left(),
                yf = figures[i]->geometry().top(),
                wf = figures[i]->geometry().right() - xf,
                hf = figures[i]->geometry().bottom() - yf;
            if(x>xf and x<xf+wf) {
                if(y>yf and y<yf+hf) {
                    toCheck = true;
                }
                else if(y+h>yf and y+h<yf+hf) {
                    toCheck = true;
                }
            }
            else if(x+w>xf and x+w<xf+wf) {
                if(y>yf and y<yf+hf) {
                    toCheck = true;
                }
                else if(y+h>yf and y+h<yf+hf) {
                    toCheck = true;
                }
            }
            if(toCheck) {
                if(figuresColliding(f, figures[i],
                                    x-xf, y-yf)) {
                    f->block();
                    figures[i]->block();
                }
            }
        }
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
    _ActionDelete->setEnabled(false);
    update();
}
void MainWindow::callMousePress(QMouseEvent* e) {
    mousePressEvent(e);
}
void MainWindow::callContextMenu(QContextMenuEvent* e) {
    contextMenuEvent(e);
}
void MainWindow::delAll() {
    int sz = figures.size();
    while(sz) {
        delete figures[sz-1];
        figures[sz-1] = nullptr;
        figures.pop_back();
        sz--;
    }
}
void MainWindow::delColliding() {
    int i=0;
    while(i!=figures.size()) {
        if(figures[i]->isBlocked()) {
            delete figures[i];
            figures[i] = nullptr;
            figures.remove(i);
        }
        else
            ++i;
    }
    update();
}

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
    _ActionFitAll =
            _BackgroundMenu->addAction(tr("&Fit All Figures"),
                                       this, SLOT(fit()));

    toolbarH = menuBar()->height();
    setFixedSize(800, 622);
}

MainWindow::~MainWindow() {}

//protected:
void MainWindow::contextMenuEvent(QContextMenuEvent* event) {
    _BackgroundMenu->exec(event->globalPos());
}
void MainWindow::mousePressEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        deselect(nullptr);
        _ActionDelete->setEnabled(false);
    }
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
        int x = figure->geometry().left()+figure->left(),
            y = figure->geometry().top()+figure->top(),
            w = figure->right() - figure->left(),
            h = figure->bottom() - figure->top();
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
        // hadooken.begin();
        for(int i=0; i<figures.size(); ++i) {
          toCheck = false;
          if(figures[i] != figure) {
            if(figure->geometry().left()>figures[i]->geometry().left() and
               figure->geometry().left()<figures[i]->geometry().right()) {
              if(figure->geometry().top()>figures[i]->geometry().top() and
                 figure->geometry().top()<figures[i]->geometry().bottom())
                toCheck = true;
              else if(
                 figure->geometry().bottom()>figures[i]->geometry().top() and
                 figure->geometry().bottom()<figures[i]->geometry().bottom())
                toCheck = true;
            }
            else if(
               figure->geometry().right()>figures[i]->geometry().left() and
               figure->geometry().right()<figures[i]->geometry().right()) {
              if(figure->geometry().top()>figures[i]->geometry().top() and
                 figure->geometry().top()<figures[i]->geometry().bottom())
                toCheck = true;
              else if(
                 figure->geometry().bottom()>figures[i]->geometry().top() and
                 figure->geometry().bottom()<figures[i]->geometry().bottom())
                toCheck = true;
            }
            if(toCheck) {
              if(figuresColliding(figure, figures[i],
                    figure->geometry().left()-figures[i]->geometry().left(),
                    figure->geometry().top()-figures[i]->geometry().top()) or
                 figuresColliding(figures[i], figure,
                    figures[i]->geometry().left()-figure->geometry().left(),
                    figures[i]->geometry().top()-figure->geometry().top())) {
                figure->block();
                figures[i]->block();
              }
            }
          }
        }
        //hadooken.end();
        if(not figure->isBlocked())
            figure->move(x-figure->left(), y-figure->top());
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
    f->move(QRandomGenerator::global()->bounded(500),
            QRandomGenerator::global()->bounded(23, 323));
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

    bool toCheck;
    // hadooken.begin();
    for(int i=0; i<figures.size(); ++i) {
      toCheck = false;
      if(figures[i] != f) {
        if(f->geometry().left()>figures[i]->geometry().left() and
           f->geometry().left()<figures[i]->geometry().right()) {
          if(f->geometry().top()>figures[i]->geometry().top() and
             f->geometry().top()<figures[i]->geometry().bottom())
            toCheck = true;
          else if(
             f->geometry().bottom()>figures[i]->geometry().top() and
             f->geometry().bottom()<figures[i]->geometry().bottom())
            toCheck = true;
        }
        else if(
           f->geometry().right()>figures[i]->geometry().left() and
           f->geometry().right()<figures[i]->geometry().right()) {
          if(f->geometry().top()>figures[i]->geometry().top() and
             f->geometry().top()<figures[i]->geometry().bottom())
            toCheck = true;
          else if(
             f->geometry().bottom()>figures[i]->geometry().top() and
             f->geometry().bottom()<figures[i]->geometry().bottom())
            toCheck = true;
        }
        if(toCheck) {
          if(figuresColliding(f, figures[i],
                f->geometry().left()-figures[i]->geometry().left(),
                f->geometry().top()-figures[i]->geometry().top()) or
             figuresColliding(figures[i], f,
                figures[i]->geometry().left()-f->geometry().left(),
                figures[i]->geometry().top()-f->geometry().top())) {
            f->block();
            figures[i]->block();
          }
        }
      }
    }
    // hadooken.end();
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
void MainWindow::fit() {
    int dx = 0, dy = 0;
    for(int i=0; i<figures.size(); ++i) {
        figures[i]->unblock();
        figures[i]->minimize();
        figures[i]->move(dx+1, dy+24);
        dx = figures[i]->geometry().right();
        if(dx > 800) {
            dx = 0;
            dy = figures[i]->geometry().bottom();
        }
    }
    update();
}

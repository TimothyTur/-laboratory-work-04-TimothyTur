/*
 * СКБ201 Тур лр4 17.10.21
 * Вариант 105 (позиция в рейтинге по алфавиту -1)
 * фигуры 55 и 60
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QVector>

#include "figures.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void contextMenuEvent(QContextMenuEvent* e);
    void mousePressEvent(QMouseEvent* e);
    //void mouseReleaseEvent(QMouseEvent* e);

private slots:
    void deselect(Figure* figure);
    void deleteFigure();
    void showFigureChange();

private:
    QMenu* _MainMenu; // figure 1 ; figure 2 ; create ;
    //f1 and f2 are holding, none at start, only one can be holded
    //create - create figure of choosen form (none of not selected)
    //random place and rotation
    QAction* _ActionQuit;
    //QMenu* _BackgroundMenu; //additional

    //QMenu* _FigureMenu; // хрень реализации, но так заметно проще

    QVector<Figure*> figures;



};
#endif // MAINWINDOW_H

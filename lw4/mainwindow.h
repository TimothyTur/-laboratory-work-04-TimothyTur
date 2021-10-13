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

private slots:
    void deselect(Figure* figure);
    void moveFigure(Figure* figure, int dx, int dy);
    void select1();
    void select2();
    void create();
    void delSingle(Figure*);
    void delSelected();
    void callMousePress(QMouseEvent* e);
    void callContextMenu(QContextMenuEvent* e);
    void delAll();
    void delColliding();
    void fit();

private:
    QAction* _ActionFigure1;
    QAction* _ActionFigure2;
    QAction* _ActionCreate;
    QAction* _ActionDelete;

    QMenu* _BackgroundMenu;
    QAction* _ActionDeleteAll;
    QAction* _ActionDeleteColliding;
    QAction* _ActionFitAll;
    QVector<Figure*> figures;
    char selected;
    int toolbarH;
};
#endif // MAINWINDOW_H

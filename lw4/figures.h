#ifndef FIGURES_H
#define FIGURES_H

#include <QWidget>
#include <QMenu>
#include <QDialog>
#include <QLabel>
#include <QSpinBox>

class EditDialog : public QDialog
{
    Q_OBJECT
public:
    EditDialog(int, int, int, int, int, int, int, int,
               QWidget *parent = nullptr);

    int getw(), geth(), geta(), getb(), getc(), getd(), gete(), getf();

private slots:
    void wValueChanged(int val);
    void hValueChanged(int val);
    void aValueChanged(int val);
    void bValueChanged(int val);
    void cValueChanged(int val);
    void dValueChanged(int val);
    void eValueChanged(int val);
    void fValueChanged(int val);

private: // ыы
    int w, h,
        a, b, c, d, e, f;
    QLabel* wLabel;
    QLabel* hLabel;
    QLabel* aLabel;
    QLabel* bLabel;
    QLabel* cLabel;
    QLabel* dLabel;
    QLabel* eLabel;
    QLabel* fLabel;
    QSpinBox* wSpinBox;
    QSpinBox* hSpinBox;
    QSpinBox* aSpinBox;
    QSpinBox* bSpinBox;
    QSpinBox* cSpinBox;
    QSpinBox* dSpinBox;
    QSpinBox* eSpinBox;
    QSpinBox* fSpinBox;
    QPushButton* acceptButton;
};


class Figure : public QWidget
{
    Q_OBJECT
public:
    explicit Figure(QWidget *parent = nullptr);

    void deselect();

protected:
    //void paintEvent(QPaintEvent* e); // на перегрузки
    void contextMenuEvent(QContextMenuEvent* e);
    void mousePressEvent(QMouseEvent* e);

    int w, h,
        a, b, c, d, e, f;
    bool selected;

private slots:
    void deleteFigure();
    void showFigureEdit();
    void figureChanged();

private:
    QMenu* _FigureMenu;
    QAction* _ActionFigureDelete;
    QAction* _ActionFigureEdit;
    EditDialog* _EditDialog;

signals:
    void selectedSgn(Figure*);
};

// фигура 55: A3B3C2D3EF6
class Figure1 : public Figure
{
    Q_OBJECT
public:
    explicit Figure1(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event);
};

// фигура 60: AB1C3D4E5F5
class Figure2 : public Figure
{
    Q_OBJECT
public:
    explicit Figure2(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event);
};

#endif // FIGURES_H

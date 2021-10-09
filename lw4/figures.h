#ifndef FIGURES_H
#define FIGURES_H

#include <QWidget>
#include <QMenu>
#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include <QDial>

class EditDialog : public QDialog
{
    Q_OBJECT
public:
    EditDialog(int, int, int, int, int, int, int, int, int, bool,
               QWidget *parent = nullptr);

    int getw(), geth(), geta(), getb(), getc(), getd(),
        gete(), getf(), getfi();
    void setw(int), seth(int), seta(int), setb(int), setc(int), setd(int),
         sete(int), setf(int), setfi(int);

private slots:
    void wValueChanged(int val);
    void hValueChanged(int val);
    void aValueChanged(int val);
    void bValueChanged(int val);
    void cValueChanged(int val);
    void dValueChanged(int val);
    void eValueChanged(int val);
    void fValueChanged(int val);
    void fiValueChanged(int val);

private: // ыы
    int w, h,
        a, b, c, d, e, f,
        fi;
    double S, P;
    bool figureType; // 0 -> 1, 1 -> 2.
    QLabel* wLabel;
    QLabel* hLabel;
    QLabel* aLabel;
    QLabel* bLabel;
    QLabel* cLabel;
    QLabel* dLabel;
    QLabel* eLabel;
    QLabel* fLabel;
    QLabel* fiLabel;
    QLabel* SLabel;
    QLabel* PLabel;
    QSpinBox* wSpinBox;
    QSpinBox* hSpinBox;
    QSpinBox* aSpinBox;
    QSpinBox* bSpinBox;
    QSpinBox* cSpinBox;
    QSpinBox* dSpinBox;
    QSpinBox* eSpinBox;
    QSpinBox* fSpinBox;
    QSpinBox* fiSpinBox;
    QPushButton* acceptButton;
};

class RotateDialog : public QDialog
{
    Q_OBJECT
public:
    RotateDialog(int& fi, QWidget* parent = nullptr);

    int getFi();

private slots:
    void fiChanged(int);

private:
    QLabel* fiLabel;
    QDial* fiDial;
    QPushButton* acceptButton;

signals:
    void fiChangedSgn(int fi);
};

class Figure : public QWidget
{
    Q_OBJECT
public:
    explicit Figure(QWidget *parent = nullptr);

    void deselect();
    bool isSelected();
    //int getFi();
    bool getForm();
    bool isBlocked();
    void block();

    friend bool figuresColliding(Figure*, Figure*, int, int);

protected:
    //void paintEvent(QPaintEvent* e); // на перегрузки
    //void contextMenuEvent(QContextMenuEvent* e); // на перегрузки
    //void mousePressEvent(QMouseEvent* e); // на перегрузки
    void mouseReleaseEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);

    int w, h,
        a, b, c, d, e, f,
        fi;
    bool selected;
    bool lmHolds;
    bool form; // false = 1, true = 2;
    QMenu* _FigureMenu;
    EditDialog* _EditDialog;
    RotateDialog* _RotateDialog;
    bool blocked;

    //int dx, dy;

private slots:
    void deleteFigure();
    void showFigureEdit();
    void figureChanged();
    void fiChanged(int val);
    void startMoving();
    void showFigureRotate();

private:
    QAction* _ActionFigureDelete;
    QAction* _ActionFigureEdit;
    QAction* _ActionFigureMove;
    QAction* _ActionFigureRotate;

signals:
    void selectedSgn(Figure*);
    void moveSgn(Figure*, int, int);
    void delSgn(Figure*);
    void contextMenuSgn(QContextMenuEvent*);
    void mousePressSgn(QMouseEvent*);
};

class Figure2;

// фигура 55: A3B3C2D3EF6
class Figure1 : public Figure
{
    Q_OBJECT
public:
    explicit Figure1(QWidget *parent = nullptr);

    friend bool figuresColliding(Figure1*, Figure1*, int, int);
    friend bool figuresColliding(Figure1*, Figure2*, int, int);
    friend bool figuresColliding(Figure2*, Figure1*, int, int);

protected:
    void paintEvent(QPaintEvent* event);
    void contextMenuEvent(QContextMenuEvent* e);
    void mousePressEvent(QMouseEvent* e);

    bool collidingWithBox(QPoint p);
    bool collidingWithBox(int x, int y);
    bool collidingWith(QPoint p);
    bool collidingWith(int x, int y);
};

// фигура 60: AB1C3D4E5F5
class Figure2 : public Figure
{
    Q_OBJECT
public:
    explicit Figure2(QWidget *parent = nullptr);

    friend bool figuresColliding(Figure2*, Figure2*, int, int);
    friend bool figuresColliding(Figure1*, Figure2*, int, int);
    friend bool figuresColliding(Figure2*, Figure1*, int, int);

protected:
    void paintEvent(QPaintEvent* event);
    void contextMenuEvent(QContextMenuEvent* e);
    void mousePressEvent(QMouseEvent* e);

    bool collidingWithBox(QPoint p);
    bool collidingWithBox(int x, int y);
    bool collidingWith(QPoint p);
    bool collidingWith(int x, int y);
};


//bool figuresColliding(Figure1*, Figure1*);
//bool figuresColliding(Figure2*, Figure2*);
//bool figuresColliding(Figure1*, Figure2*);
//bool figuresColliding(Figure2*, Figure1*);

#endif // FIGURES_H

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
    RotateDialog(int fi, QWidget* parent = nullptr);

    int getFi();
    void setFi(int);

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
    virtual bool getForm() = 0;
    bool isBlocked();
    void block();
    void unblock();
    virtual int top() = 0;
    virtual int bottom() = 0;
    virtual int left() = 0;
    virtual int right() = 0;
    void minimize();

    friend bool figuresColliding(Figure*, Figure*, int, int);

protected:
    void contextMenuEvent(QContextMenuEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);

    virtual bool collidingWithDot(QPoint p) = 0;
    virtual bool collidingWithDot(int x, int y) = 0;

    int w, h, s,
        a, b, c, d, e, f,
        fi;
    bool selected;
    bool lmHolds;
    QMenu* _FigureMenu;
    EditDialog* _EditDialog;
    RotateDialog* _RotateDialog;
    bool blocked;

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

// фигура 55: A3B3C2D3EF6
class Figure1 : public Figure
{
    Q_OBJECT
public:
    explicit Figure1(QWidget *parent = nullptr);
    bool getForm();

    int top();
    int bottom();
    int left();
    int right();

protected:
    void paintEvent(QPaintEvent* event);

    bool collidingWithDot(QPoint p);
    bool collidingWithDot(int x, int y);
};

// фигура 60: AB1C3D4E5F5
class Figure2 : public Figure
{
    Q_OBJECT
public:
    explicit Figure2(QWidget *parent = nullptr);
    bool getForm();

    int top();
    int bottom();
    int left();
    int right();

protected:
    void paintEvent(QPaintEvent* event);

    bool collidingWithDot(QPoint p);
    bool collidingWithDot(int x, int y);
};

#endif // FIGURES_H

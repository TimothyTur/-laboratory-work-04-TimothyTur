#include "figures.h"

#include <QPainter>
#include <QContextMenuEvent>
#include <QRandomGenerator>
#include <QGridLayout>
#include <QPushButton>
#include <QtMath>

#include <iostream>

template<typename T>
T abs(T val) {
    if(val<0)
        return -val;
    return val;
}

// EditDialog
//public:
EditDialog::EditDialog(int w, int h, int a, int b, int c, int d, int e, int f,
                       int fi, bool type, QWidget *parent)
    : QDialog(parent)
    , w(w), h(h), a(a), b(b), c(c), d(d), e(e), f(f), figureType(type)
{
    setModal(true);

    wSpinBox = new QSpinBox;
    wSpinBox->setRange(20, 200);
    wSpinBox->setValue(w);
    wLabel = new QLabel(tr("&Ширина:"));
    wLabel->setBuddy(wSpinBox);

    hSpinBox = new QSpinBox;
    hSpinBox->setRange(w/3, w);
    hSpinBox->setValue(h);
    hLabel = new QLabel(tr("&Высота:"));
    hLabel->setBuddy(hSpinBox);

    aSpinBox = new QSpinBox;
    aSpinBox->setRange(0, h/3);
    aSpinBox->setValue(a);
    aLabel = new QLabel(tr("&Правый верхний угол:"));
    aLabel->setBuddy(aSpinBox);

    bSpinBox = new QSpinBox;
    bSpinBox->setRange(0, h/3);
    bSpinBox->setValue(b);
    bLabel = new QLabel(tr("&Правый нижний угол:"));
    bLabel->setBuddy(bSpinBox);

    cSpinBox = new QSpinBox;
    cSpinBox->setRange(0, h/3);
    cSpinBox->setValue(c);
    cLabel = new QLabel(tr("&Левый нижний угол:"));
    cLabel->setBuddy(cSpinBox);

    dSpinBox = new QSpinBox;
    dSpinBox->setRange(0, h/3);
    dSpinBox->setValue(d);
    dLabel = new QLabel(tr("&Левый верхний угол:"));
    dLabel->setBuddy(dSpinBox);

    eSpinBox = new QSpinBox;
    eSpinBox->setRange(0, w/4);
    eSpinBox->setValue(e);
    eLabel = new QLabel(tr("&Верх:"));
    eLabel->setBuddy(eSpinBox);

    fSpinBox = new QSpinBox;
    fSpinBox->setRange(0, w/4);
    fSpinBox->setValue(f);
    fLabel = new QLabel(tr("&Низ:"));
    fLabel->setBuddy(fSpinBox);

    fiSpinBox = new QSpinBox;
    fiSpinBox->setRange(-180, 180);
    fiSpinBox->setValue(-fi);
    fiLabel = new QLabel(tr("&Угол:"));
    fiLabel->setBuddy(fiSpinBox);

    if(figureType) {// 2
        S = w*h-b*b-f*f/2-0.785375*c*c-0.214625*d*d-e*e/2;
        P = 2*h+2*w+f+f-0.42925*(c+d);
    }
    else {// 1
        S = w*h-0.785375*a*a-0.785375*b*b-1.57075*f*f-c*c/2-0.785375*d*d;
        P = 2*h+2*w-0.42925*(a+b+d)+0.57075*f-0.585786*c;
    }

    SLabel = new QLabel(tr("Площадь : ")+QString::number(S));
    PLabel = new QLabel(tr("Периметр : ")+QString::number(P));

    acceptButton = new QPushButton(tr("&Принять"), this);

    connect(wSpinBox, SIGNAL(valueChanged(int)),
            this,     SLOT(wValueChanged(int)));
    connect(hSpinBox, SIGNAL(valueChanged(int)),
            this,     SLOT(hValueChanged(int)));
    connect(aSpinBox, SIGNAL(valueChanged(int)),
            this,     SLOT(aValueChanged(int)));
    connect(bSpinBox, SIGNAL(valueChanged(int)),
            this,     SLOT(bValueChanged(int)));
    connect(cSpinBox, SIGNAL(valueChanged(int)),
            this,     SLOT(cValueChanged(int)));
    connect(dSpinBox, SIGNAL(valueChanged(int)),
            this,     SLOT(dValueChanged(int)));
    connect(eSpinBox, SIGNAL(valueChanged(int)),
            this,     SLOT(eValueChanged(int)));
    connect(fSpinBox, SIGNAL(valueChanged(int)),
            this,     SLOT(fValueChanged(int)));
    connect(fiSpinBox,SIGNAL(valueChanged(int)),
            this,     SLOT(fiValueChanged(int)));
    connect(acceptButton, SIGNAL(clicked()),
            this,         SLOT(accept()));

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(wLabel,   0, 0, Qt::AlignRight);
    layout->addWidget(wSpinBox, 0, 1);
    layout->addWidget(hLabel,   1, 0, Qt::AlignRight);
    layout->addWidget(hSpinBox, 1, 1);
    layout->addWidget(aLabel,   2, 0, Qt::AlignRight);
    layout->addWidget(aSpinBox, 2, 1);
    layout->addWidget(bLabel,   3, 0, Qt::AlignRight);
    layout->addWidget(bSpinBox, 3, 1);
    layout->addWidget(cLabel,   4, 0, Qt::AlignRight);
    layout->addWidget(cSpinBox, 4, 1);
    layout->addWidget(dLabel,   5, 0, Qt::AlignRight);
    layout->addWidget(dSpinBox, 5, 1);
    layout->addWidget(eLabel,   6, 0, Qt::AlignRight);
    layout->addWidget(eSpinBox, 6, 1);
    layout->addWidget(fLabel,   7, 0, Qt::AlignRight);
    layout->addWidget(fSpinBox, 7, 1);
    layout->addWidget(fiLabel,  8, 0, Qt::AlignRight);
    layout->addWidget(fiSpinBox,8, 1);
    layout->addWidget(SLabel,   9, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(PLabel,  10, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(acceptButton, 11, 0, 2, 2);
    setLayout(layout);

    setFixedSize(aLabel->width(),
                 aLabel->height());

    setWindowTitle(tr("Изменение фигуры"));
}

int EditDialog::getw() {return w;}
int EditDialog::geth() {return h;}
int EditDialog::geta() {return a;}
int EditDialog::getb() {return b;}
int EditDialog::getc() {return c;}
int EditDialog::getd() {return d;}
int EditDialog::gete() {return e;}
int EditDialog::getf() {return f;}
int EditDialog::getfi() {return fi;}
void EditDialog::setw(int val) {
    w = val;
    wSpinBox->setValue(w);
}
void EditDialog::seth(int val) {
    h = val;
    hSpinBox->setValue(h);
}
void EditDialog::seta(int val) {
    a = val;
    aSpinBox->setValue(a);
}
void EditDialog::setb(int val) {
    b = val;
    bSpinBox->setValue(b);
}
void EditDialog::setc(int val) {
    c = val;
    cSpinBox->setValue(c);
}
void EditDialog::setd(int val) {
    d = val;
    dSpinBox->setValue(d);
}
void EditDialog::sete(int val) {
    e = val;
    eSpinBox->setValue(e);
}
void EditDialog::setf(int val) {
    f = val;
    fSpinBox->setValue(f);
}
void EditDialog::setfi(int val) {
    fi = val;
    fiSpinBox->setValue(-fi);
}

//private slots:
void EditDialog::wValueChanged(int val) {
    w = val;
    if(w>=20 and w<=200) { // ручной ввод
        if(h>=w)
            hSpinBox->setValue(w-1);
        else if(h<=w/3)
            hSpinBox->setValue(w/3);
        if(e>=w/4)
            eSpinBox->setValue(w/4-1);
        if(f>=w/4)
            fSpinBox->setValue(w/4-1);
        hSpinBox->setRange(w/3, w);
        eSpinBox->setMaximum(w/4);
        fSpinBox->setMaximum(w/4);
        if(figureType) {// 2
            S = w*h-b*b-f*f/2-0.785375*c*c-0.214625*d*d-e*e/2;
            P = 2*h+2*w+f+f-0.42925*(c+d);
        }
        else {// 1
            S = w*h-0.785375*a*a-0.785375*b*b-1.57075*f*f-c*c/2-0.785375*d*d;
            P = 2*h+2*w-0.42925*(a+b+d)+0.57075*f-0.585786*c;
        }
        SLabel->setText(tr("Площадь : ")+QString::number(S));
        PLabel->setText(tr("Периметр : ")+QString::number(P));
    }
}
void EditDialog::hValueChanged(int val) {
    h = val;
    if(h>=w/3 and h<=w) {
        if(a>=h/3)
            aSpinBox->setValue(h/3-1);
        if(b>=h/3)
            bSpinBox->setValue(h/3-1);
        if(c>=h/3)
            cSpinBox->setValue(h/3-1);
        if(d>=h/3)
            dSpinBox->setValue(h/3-1);
        aSpinBox->setMaximum(h/3);
        bSpinBox->setMaximum(h/3);
        cSpinBox->setMaximum(h/3);
        dSpinBox->setMaximum(h/3);
        if(figureType) {// 2
            S = w*h-b*b-f*f/2-0.785375*c*c-0.214625*d*d-e*e/2;
            P = 2*h+2*w+f+f-0.42925*(c+d);
        }
        else {// 1
            S = w*h-0.785375*a*a-0.785375*b*b-1.57075*f*f-c*c/2-0.785375*d*d;
            P = 2*h+2*w-0.42925*(a+b+d)+0.57075*f-0.585786*c;
        }
        SLabel->setText(tr("Площадь : ")+QString::number(S));
        PLabel->setText(tr("Периметр : ")+QString::number(P));
    }
}
void EditDialog::aValueChanged(int val) {
    a = val;
    if(figureType) {// 2
        S = w*h-b*b-f*f/2-0.785375*c*c-0.214625*d*d-e*e/2;
        P = 2*h+2*w+f+f-0.42925*(c+d);
    }
    else {// 1
        S = w*h-0.785375*a*a-0.785375*b*b-1.57075*f*f-c*c/2-0.785375*d*d;
        P = 2*h+2*w-0.42925*(a+b+d)+0.57075*f-0.585786*c;
    }
    SLabel->setText(tr("Площадь : ")+QString::number(S));
    PLabel->setText(tr("Периметр : ")+QString::number(P));
}
void EditDialog::bValueChanged(int val) {
    b = val;
    if(figureType) {// 2
        S = w*h-b*b-f*f/2-0.785375*c*c-0.214625*d*d-e*e/2;
        P = 2*h+2*w+f+f-0.42925*(c+d);
    }
    else {// 1
        S = w*h-0.785375*a*a-0.785375*b*b-1.57075*f*f-c*c/2-0.785375*d*d;
        P = 2*h+2*w-0.42925*(a+b+d)+0.57075*f-0.585786*c;
    }
    SLabel->setText(tr("Площадь : ")+QString::number(S));
    PLabel->setText(tr("Периметр : ")+QString::number(P));
}
void EditDialog::cValueChanged(int val) {
    c = val;
    if(figureType) {// 2
        S = w*h-b*b-f*f/2-0.785375*c*c-0.214625*d*d-e*e/2;
        P = 2*h+2*w+f+f-0.42925*(c+d);
    }
    else {// 1
        S = w*h-0.785375*a*a-0.785375*b*b-1.57075*f*f-c*c/2-0.785375*d*d;
        P = 2*h+2*w-0.42925*(a+b+d)+0.57075*f-0.585786*c;
    }
    SLabel->setText(tr("Площадь : ")+QString::number(S));
    PLabel->setText(tr("Периметр : ")+QString::number(P));
}
void EditDialog::dValueChanged(int val) {
    d = val;
    if(figureType) {// 2
        S = w*h-b*b-f*f/2-0.785375*c*c-0.214625*d*d-e*e/2;
        P = 2*h+2*w+f+f-0.42925*(c+d);
    }
    else {// 1
        S = w*h-0.785375*a*a-0.785375*b*b-1.57075*f*f-c*c/2-0.785375*d*d;
        P = 2*h+2*w-0.42925*(a+b+d)+0.57075*f-0.585786*c;
    }
    SLabel->setText(tr("Площадь : ")+QString::number(S));
    PLabel->setText(tr("Периметр : ")+QString::number(P));
}
void EditDialog::eValueChanged(int val) {
    e = val;
    if(figureType) {// 2
        S = w*h-b*b-f*f/2-0.785375*c*c-0.214625*d*d-e*e/2;
        P = 2*h+2*w+f+f-0.42925*(c+d);
    }
    else {// 1
        S = w*h-0.785375*a*a-0.785375*b*b-1.57075*f*f-c*c/2-0.785375*d*d;
        P = 2*h+2*w-0.42925*(a+b+d)+0.57075*f-0.585786*c;
    }
    SLabel->setText(tr("Площадь : ")+QString::number(S));
    PLabel->setText(tr("Периметр : ")+QString::number(P));
}
void EditDialog::fValueChanged(int val) {
    f = val;
    if(figureType) {// 2
        S = w*h-b*b-f*f/2-0.785375*c*c-0.214625*d*d-e*e/2;
        P = 2*h+2*w+f+f-0.42925*(c+d);
    }
    else {// 1
        S = w*h-0.785375*a*a-0.785375*b*b-1.57075*f*f-c*c/2-0.785375*d*d;
        P = 2*h+2*w-0.42925*(a+b+d)+0.57075*f-0.585786*c;
    }
    SLabel->setText(tr("Площадь : ")+QString::number(S));
    PLabel->setText(tr("Периметр : ")+QString::number(P));
}
void EditDialog::fiValueChanged(int val) {
    fi = -val;
}

//RotateDialog
RotateDialog::RotateDialog(int fi, QWidget* parent)
    : QDialog(parent)
{
    setModal(true);
    setFixedSize(200, 200);
    setWindowTitle(tr("Поворот фигуры"));

    fiDial = new QDial(this);
    fiDial->setFocusPolicy(Qt::StrongFocus);
    fiDial->setRange(-180, 180);
    fiDial->setSingleStep(1);
    fiDial->setValue(fi);
    fiDial->setFixedSize(100, 100);

    fiLabel = new QLabel(tr("&Угол"));
    fiLabel->setBuddy(fiDial);

    acceptButton = new QPushButton(tr("&Принять"), this);
    connect(acceptButton, SIGNAL(clicked()),
            this,         SLOT(accept()));

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(fiLabel, 0, 0, Qt::AlignCenter);
    layout->addWidget(fiDial, 1, 0);
    layout->addWidget(acceptButton, 2, 0);
    setLayout(layout);

    connect(fiDial, SIGNAL(valueChanged(int)), this, SLOT(fiChanged(int)));
}
int RotateDialog::getFi() {
    return fiDial->value();
}
void RotateDialog::setFi(int val) {
    fiDial->setValue(val);
}

//private slots:
void RotateDialog::fiChanged(int val) {
    emit fiChangedSgn(val);
}

// Figure
//public:
Figure::Figure(QWidget *parent)
    : QWidget(parent)
    , w(QRandomGenerator::global()->bounded(20, 200))
    , h(QRandomGenerator::global()->bounded(w/3, w))
    , s(qSqrt(w*w+h*h))
    , a(QRandomGenerator::global()->bounded(0, h/3))
    , b(QRandomGenerator::global()->bounded(0, h/3))
    , c(QRandomGenerator::global()->bounded(0, h/3))
    , d(QRandomGenerator::global()->bounded(0, h/3))
    , e(QRandomGenerator::global()->bounded(0, w/4))
    , f(QRandomGenerator::global()->bounded(0, w/4))
    , fi(QRandomGenerator::global()->bounded(-180, 180))
    , selected(false)
    , lmHolds(false)
    , blocked(false)
{
    setFixedSize(s, s);
    _FigureMenu = new QMenu(this);
    _ActionFigureDelete = _FigureMenu->addAction(tr("Удалить"),
                                                 this,
                                                 SLOT(deleteFigure()));
    _ActionFigureEdit = _FigureMenu->addAction(tr("Изменить"),
                                                 this,
                                                 SLOT(showFigureEdit()));
    _ActionFigureMove = _FigureMenu->addAction(tr("Переместить"),
                                               this,
                                               SLOT(startMoving()));
    _ActionFigureRotate = _FigureMenu->addAction(tr("Повернуть"),
                                                 this,
                                                 SLOT(showFigureRotate()));
    _RotateDialog = new RotateDialog(fi, this);
    connect(_RotateDialog, SIGNAL(fiChangedSgn(int)),
            this,          SLOT(fiChanged(int)));
    update();
}

void Figure::deselect() {
    selected = false;
}
bool Figure::isSelected() {
    return selected;
}
bool Figure::isBlocked() {
    return blocked;
}
void Figure::block() {
    blocked = true;
    lmHolds = false;
    setMouseTracking(false);
}
void Figure::unblock() {
    blocked = false;
}
void Figure::minimize() {
    w = 20;
    h = 20;
    s = qSqrt(w*w+h*h);
    if(a>6)
        a = 6;
    if(b>6)
        b = 6;
    if(c>6)
        c = 6;
    if(d>6)
        d = 6;
    if(e>5)
        e = 5;
    if(f>5)
        f = 5;
    fi = 0;

    setFixedSize(s, s);
    update();
}

//protected:
void Figure::contextMenuEvent(QContextMenuEvent* e) {
    if(collidingWithDot(e->pos()))
        _FigureMenu->exec(e->globalPos());
    else
        emit contextMenuSgn(e);
}
void Figure::mousePressEvent(QMouseEvent* e) {
    if(collidingWithDot(e->pos())) {
        if(e->button()==Qt::LeftButton) {
            selected = true;
            emit selectedSgn(this);
            if(not blocked) {
                lmHolds = true;
                emit moveSgn(this, e->pos().x()-s/2, e->pos().y()-s/2);
            }
        }
        update();
    }
    else
        emit mousePressSgn(e);
}
void Figure::mouseMoveEvent(QMouseEvent* e) {
    if(not blocked) {
        if(hasMouseTracking() or lmHolds)
            emit moveSgn(this, e->pos().x()-s/2, e->pos().y()-s/2);
        update();
    }
}
void Figure::mouseReleaseEvent(QMouseEvent* e) {
    if(not blocked) {
        if(e->button()==Qt::LeftButton)
            lmHolds = false;
    }
}

//private slots:
void Figure::deleteFigure() {
    emit delSgn(this);
}
void Figure::showFigureEdit() {
    _EditDialog->setw(w);
    _EditDialog->seth(h);
    _EditDialog->seta(a);
    _EditDialog->setb(b);
    _EditDialog->setc(c);
    _EditDialog->setd(d);
    _EditDialog->sete(e);
    _EditDialog->setf(f);
    _EditDialog->setfi(fi);
    _EditDialog->exec();
}
void Figure::figureChanged() {
    w = _EditDialog->getw();
    h = _EditDialog->geth();
    a = _EditDialog->geta();
    b = _EditDialog->getb();
    c = _EditDialog->getc();
    d = _EditDialog->getd();
    e = _EditDialog->gete();
    f = _EditDialog->getf();
    fi = _EditDialog->getfi();

    int news = qSqrt(w*w+h*h);
    setFixedSize(news, news);
    emit moveSgn(this, (s-news)/2, (s-news)/2);
    s = news;

    emit chechCollisionsSgn(this);

    update();
}
void Figure::fiChanged(int val) {
    fi = val;
    emit chechCollisionsSgn(this);
    update();
}
void Figure::startMoving() {
    if(not blocked) {
        if(hasMouseTracking()) {
            setMouseTracking(false);
        }
        else {
            setMouseTracking(true);
            QPoint p = this->mapFromGlobal(QCursor::pos());
            emit moveSgn(this, p.x()-s/2, p.y()-s/2);
        }
    }
}
void Figure::showFigureRotate() {
    _RotateDialog->setFi(fi);
    _RotateDialog->exec();
}

// Figure1
//public:
Figure1::Figure1(QWidget *parent) : Figure(parent) {
    _EditDialog = new EditDialog(w, h, a, b, c, d, e, f, fi, false, this);
    connect(_EditDialog, SIGNAL(accepted()), this, SLOT(figureChanged()));
}
bool Figure1::getForm() {
    return false;
}
int Figure1::top() {
    int ix[] = {
           d,                   w-a,
        0,                           w,
        0,                           w,
           c, w/2-f/2, w/2+f/2, w-b
    };
    int iy[] = {
             0,       0,
        d,               a,
        h-c,             h-b,
             h, h, h, h
    };
    int miny = s, dy;
    float radfi = qDegreesToRadians(static_cast<float>(fi));

    for(int i=0; i<10; ++i) {
        dy = ix[i]*qSin(radfi)+iy[i]*qCos(radfi)
                + s/2-w/2*qSin(radfi)-h/2*qCos(radfi);
        if(dy<miny)
            miny = dy;
    }
    return miny;
}
int Figure1::bottom() {
    int ix[] = {
           d,                   w-a,
        0,                           w,
        0,                           w,
           c, w/2-f/2, w/2+f/2, w-b
    };
    int iy[] = {
             0,       0,
        d,               a,
        h-c,             h-b,
             h, h, h, h
    };
    int maxy = 0, dy;
    float radfi = qDegreesToRadians(static_cast<float>(fi));

    for(int i=0; i<10; ++i) {
        dy = ix[i]*qSin(radfi)+iy[i]*qCos(radfi)
                + s/2-w/2*qSin(radfi)-h/2*qCos(radfi);
        if(dy>maxy)
            maxy = dy;
    }
    return maxy;
}
int Figure1::left() {
    int ix[] = {
           d,                   w-a,
        0,                           w,
        0,                           w,
           c, w/2-f/2, w/2+f/2, w-b
    };
    int iy[] = {
             0,       0,
        d,               a,
        h-c,             h-b,
             h, h, h, h
    };
    int minx = s, dx;
    float radfi = qDegreesToRadians(static_cast<float>(fi));

    for(int i=0; i<10; ++i) {
        dx = ix[i]*qCos(radfi)-iy[i]*qSin(radfi)
                + s/2-w/2*qCos(radfi)+h/2*qSin(radfi);
        if(dx<minx)
            minx = dx;
    }
    return minx;
}
int Figure1::right() {
    int ix[] = {
           d,                   w-a,
        0,                           w,
        0,                           w,
           c, w/2-f/2, w/2+f/2, w-b
    };
    int iy[] = {
             0,       0,
        d,               a,
        h-c,             h-b,
             h, h, h, h
    };
    int maxx = 0, dx;
    float radfi = qDegreesToRadians(static_cast<float>(fi));

    for(int i=0; i<10; ++i) {
        dx = ix[i]*qCos(radfi)-iy[i]*qSin(radfi)
                + s/2-w/2*qCos(radfi)+h/2*qSin(radfi);
        if(dx>maxx)
            maxx = dx;
    }
    return maxx;
}

//protected:
void Figure1::paintEvent(QPaintEvent* e) {
    QPainter painter(this);

    if(selected)
        painter.setPen(Qt::blue);
    else
        painter.setPen(Qt::black);
    painter.translate(s/2+
                      -w/2*qCos(qDegreesToRadians(static_cast<float>(fi)))+
                      h/2*qSin(qDegreesToRadians(static_cast<float>(fi))),
                      s/2+
                      -w/2*qSin(qDegreesToRadians(static_cast<float>(fi)))-
                      h/2*qCos(qDegreesToRadians(static_cast<float>(fi))));
    painter.rotate(fi);

    painter.drawArc(w-a, -a, 2*a, 2*a, 180*16, 90*16); // A
    painter.drawLine(w, a, w, h-b);
    painter.drawArc(w-b, h-b, 2*b, 2*b, 90*16, 90*16); // B
    painter.drawLine(w-b, h, w/2+f/2, h);
    painter.drawArc(w/2-f/2, h-f/2, f, f, 0, 180*16);  // F
    painter.drawLine(w/2-f/2, h, c, h);
    painter.drawLine(c, h, 0, h-c);                    // C
    painter.drawLine(0, h-c, 0, d);
    painter.drawArc(-d, -d, 2*d, 2*d, 270*16, 90*16);  // D
    painter.drawLine(d, 0, w-a, 0);                    // E

}
bool Figure1::collidingWithDot(QPoint p) {
    return collidingWithDot(p.x(), p.y());
}
bool Figure1::collidingWithDot(int x, int y) {
    float radfi = qDegreesToRadians(static_cast<float>(fi));
    x -= s/2+-w/2*qCos(radfi)+h/2*qSin(radfi);
    y -= s/2+ -w/2*qSin(radfi)-h/2*qCos(radfi);
    int t = x*qCos(radfi)+y*qSin(radfi);
    y = -x*qSin(radfi)+y*qCos(radfi);
    x = t;

    if(x<0 or x>w or y<0 or y>h)
        return false;

    if(x<d and y<d) { // D
        if(x*x+y*y>d*d)
            return true;
        return false;
    }
    //else if(x>w/2-e/2 and x<w/2+e/2 and y<e/2) { // E
    //   return true;
    //}
    else if(x>w-a and y<a) { // A
        int dx = x-w;
        if(dx*dx+y*y>a*a)
            return true;
        return false;
    }
    else if(x>w-b and y>h-b) { // B
        int dx = x-w, dy = y-h;
        if(dx*dx+dy*dy>b*b)
            return true;
        return false;
    }
    else if(x>w/2-f/2 and x<w/2+f/2 and y>h-f/2) { // F
        int dx = x-w/2, dy = y-h;
        if(dx*dx+dy*dy>f*f/4)
            return true;
        return false;
    }
    else if(x<c and y>h-c) { // C
        if(y-h+c<x)
            return true;
        return false;
    }
    return true;
}
// Figure2
//public:
Figure2::Figure2(QWidget *parent) : Figure(parent) {
    _EditDialog = new EditDialog(w, h, a, b, c, d, e, f, fi, true, this);
    connect(_EditDialog, SIGNAL(accepted()), this, SLOT(figureChanged()));
}
bool Figure2::getForm() {return true;}
int Figure2::top() {
    int ix[] = {
            d, w/2-e/2, w/2+e/2, w,
           static_cast<int>(0.61731656*d), // ободок
          static_cast<int>(0.29289321*d),
         static_cast<int>(0.07612046*d),
        0,
        0,                           w,
           c, w/2-f/2, w/2+f/2, w-b
    };
    int iy[] = {
          0, 0, 0, 0,
        static_cast<int>(0.07612046*d), // ободок
       static_cast<int>(0.29289321*d),
      static_cast<int>(0.61731656*d),
     d,
     h-c,             h-b,
          h, h, h, h
    };
    int miny = s, dy;
    float radfi = qDegreesToRadians(static_cast<float>(fi));

    for(int i=0; i<14; ++i) {
        dy = ix[i]*qSin(radfi)+iy[i]*qCos(radfi)
                + s/2-w/2*qSin(radfi)-h/2*qCos(radfi);
        if(dy<miny)
            miny = dy;
    }
    return miny;
}
int Figure2::bottom() {
    int ix[] = {
            d, w/2-e/2, w/2+e/2, w,
           static_cast<int>(0.61731656*d), // ободок
          static_cast<int>(0.29289321*d),
         static_cast<int>(0.07612046*d),
        0,
        0,                           w,
           c, w/2-f/2, w/2+f/2, w-b
    };
    int iy[] = {
          0, 0, 0, 0,
        static_cast<int>(0.07612046*d), // ободок
       static_cast<int>(0.29289321*d),
      static_cast<int>(0.61731656*d),
     d,
     h-c,             h-b,
          h, h, h, h
    };
    int maxy = 0, dy;
    float radfi = qDegreesToRadians(static_cast<float>(fi));

    for(int i=0; i<14; ++i) {
        dy = ix[i]*qSin(radfi)+iy[i]*qCos(radfi)
                + s/2-w/2*qSin(radfi)-h/2*qCos(radfi);
        if(dy>maxy)
            maxy = dy;
    }
    return maxy;
}
int Figure2::left() {
    int ix[] = {
            d, w/2-e/2, w/2+e/2, w,
           static_cast<int>(0.61731656*d), // ободок
          static_cast<int>(0.29289321*d),
         static_cast<int>(0.07612046*d),
        0,
        0,                           w,
           c, w/2-f/2, w/2+f/2, w-b
    };
    int iy[] = {
          0, 0, 0, 0,
        static_cast<int>(0.07612046*d), // ободок
       static_cast<int>(0.29289321*d),
      static_cast<int>(0.61731656*d),
     d,
     h-c,             h-b,
          h, h, h, h
    };
    int minx = s, dx;
    float radfi = qDegreesToRadians(static_cast<float>(fi));

    for(int i=0; i<14; ++i) {
        dx = ix[i]*qCos(radfi)-iy[i]*qSin(radfi)
                + s/2-w/2*qCos(radfi)+h/2*qSin(radfi);
        if(dx<minx)
            minx = dx;
    }
    return minx;
}
int Figure2::right() {
    int ix[] = {
            d, w/2-e/2, w/2+e/2, w,
           static_cast<int>(0.61731656*d), // ободок
          static_cast<int>(0.29289321*d),
         static_cast<int>(0.07612046*d),
        0,
        0,                           w,
           c, w/2-f/2, w/2+f/2, w-b
    };
    int iy[] = {
          0, 0, 0, 0,
        static_cast<int>(0.07612046*d), // ободок
       static_cast<int>(0.29289321*d),
      static_cast<int>(0.61731656*d),
     d,
     h-c,             h-b,
          h, h, h, h
    };
    int maxx = 0, dx;
    float radfi = qDegreesToRadians(static_cast<float>(fi));

    for(int i=0; i<14; ++i) {
        dx = ix[i]*qCos(radfi)-iy[i]*qSin(radfi)
                + s/2-w/2*qCos(radfi)+h/2*qSin(radfi);
        if(dx>maxx)
            maxx = dx;
    }
    return maxx;
}
//protevted:
void Figure2::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    if(selected)
        painter.setPen(Qt::blue);
    else
        painter.setPen(Qt::black);
    painter.translate(s/2+
                      -w/2*qCos(qDegreesToRadians(static_cast<float>(fi)))+
                      h/2*qSin(qDegreesToRadians(static_cast<float>(fi))),
                      s/2+
                      -w/2*qSin(qDegreesToRadians(static_cast<float>(fi)))-
                      h/2*qCos(qDegreesToRadians(static_cast<float>(fi))));
    painter.rotate(fi);

    painter.drawLine(w, 0, w, h-b);                   // A
    painter.drawLine(w,    h-b, w-b, h-b);            // B
    painter.drawLine(w-b, h-b, w-b, h   );            // B
    painter.drawLine(w-b, h, w/2+f/2, h);
    painter.drawLine(w/2+f/2, h,     w/2+f/2, h-f/2); // F
    painter.drawLine(w/2+f/2, h-f/2, w/2-f/2, h-f/2); // F
    painter.drawLine(w/2-f/2, h-f/2, w/2-f/2, h    ); // F
    painter.drawLine(w/2-f/2, h, c, h);
    painter.drawArc(-c, h-c, 2*c, 2*c, 0, 90*16);     // C
    painter.drawLine(0, h-c, 0, d);
    painter.drawArc(0, 0, 2*d, 2*d, 90*16, 90*16);    // D
    painter.drawLine(d, 0, w/2-e/2, 0);
    painter.drawLine(w/2-e/2, 0,   w/2-e/2, e/2);     // E
    painter.drawLine(w/2-e/2, e/2, w/2+e/2, e/2);     // E
    painter.drawLine(w/2+e/2, e/2, w/2+e/2, 0  );     // E
    painter.drawLine(w/2+e/2, 0, w, 0);               // A

}
bool Figure2::collidingWithDot(QPoint p) {
    return collidingWithDot(p.x(), p.y());
}
bool Figure2::collidingWithDot(int x, int y) {
    float radfi = qDegreesToRadians(static_cast<float>(fi));
    x -= s/2+-w/2*qCos(radfi)+h/2*qSin(radfi);
    y -= s/2+ -w/2*qSin(radfi)-h/2*qCos(radfi);
    int t = x*qCos(radfi)+y*qSin(radfi);
    y = -x*qSin(radfi)+y*qCos(radfi);
    x = t;


    if(x<0 or y<0 or x>w or y>h)
        return false;
    if(x<d and y<d) { // D
        int dx = x-d, dy = y-d;
        if(dx*dx+dy*dy<d*d)
            return true;
        return false;
    }
    else if(x>w/2-e/2 and x<w/2+e/2 and y<e/2) { // E
        return false;
    }
    //else if(x>w-a and y<a) { // A
    //    return true;
    //}
    else if(x>w-b and y>h-b) { // B
        return false;
    }
    else if(x>w/2-f/2 and x<w/2+f/2 and y>h-f/2) { // F
        return false;
    }
    else if(x<c and y>h-c) { // C
        int dy = y-h;
        if(x*x+dy*dy>c*c)
            return true;
        return false;
    }
    return true;
}

bool figuresColliding(Figure* f1, Figure* f2, int dx, int dy) {
    if(f2->getForm()) {  // 2
        int ix[] = {
               f2->d, f2->w/2-f2->e/2, f2->w/2+f2->e/2, f2->w,
               static_cast<int>(0.61731656*f2->d), // ободок
              static_cast<int>(0.29289321*f2->d),
             static_cast<int>(0.07612046*f2->d),
            0,
            0,                                                      f2->w,
               f2->c, f2->w/2-f2->f/2, f2->w/2+f2->f/2, f2->w-f2->b
        };
        int iy[] = {
                      0,     0,     0,     0,
            static_cast<int>(0.07612046*f2->d), // ободок
           static_cast<int>(0.29289321*f2->d),
          static_cast<int>(0.61731656*f2->d),
         f2->d,
         f2->h-f2->c,                             f2->h-f2->b,
                      f2->h, f2->h, f2->h, f2->h
        };
        float radfi = qDegreesToRadians(static_cast<float>(f2->fi));
        int addx = f2->s/2-f2->w/2*qCos(radfi)+f2->h/2*qSin(radfi);
        int addy = f2->s/2-f2->w/2*qSin(radfi)-f2->h/2*qCos(radfi);
        for(int i=0; i<14; ++i) {
            if(f1->collidingWithDot(
                      ix[i]*qCos(radfi)-iy[i]*qSin(radfi) - dx + addx,
                      ix[i]*qSin(radfi)+iy[i]*qCos(radfi) - dy + addy))
                return true;
        }
        return false;
    }
    else { // 1
        int ix[] = {
               f2->d,                                   f2->w-f2->a,
            0,                                                       f2->w,
            0,                                                       f2->w,
               f2->c, f2->w/2-f2->f/2, f2->w/2+f2->f/2, f2->w-f2->b
        };
        int iy[] = {
                   0,                             0,
            f2->d,                                   f2->a,
            f2->h-f2->c,                             f2->h-f2->b,
                         f2->h, f2->h, f2->h, f2->h
        };
        float radfi = qDegreesToRadians(static_cast<float>(f2->fi));
        int addx = f2->s/2-f2->w/2*qCos(radfi)+f2->h/2*qSin(radfi);
        int addy = f2->s/2-f2->w/2*qSin(radfi)-f2->h/2*qCos(radfi);
        for(int i=0; i<10; ++i) {
            if(f1->collidingWithDot(
                      ix[i]*qCos(radfi)-iy[i]*qSin(radfi) - dx + addx,
                      ix[i]*qSin(radfi)+iy[i]*qCos(radfi) - dy + addy))
                return true;
        }
        return false;
    }
}

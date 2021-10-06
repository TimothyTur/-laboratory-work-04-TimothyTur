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
                       QWidget *parent)
    : QDialog(parent)
    , w(w), h(h), a(a), b(b), c(c), d(d), e(e), f(f)
{
    setModal(true);
    setFixedSize(100, 250);

    wSpinBox = new QSpinBox;
    wSpinBox->setRange(20, 200);
    wSpinBox->setValue(w);
    wLabel = new QLabel(tr("&Width:"));
    wLabel->setBuddy(wSpinBox);

    hSpinBox = new QSpinBox;
    hSpinBox->setRange(w/3, w);
    hSpinBox->setValue(h);
    hLabel = new QLabel(tr("&Height:"));
    hLabel->setBuddy(hSpinBox);

    aSpinBox = new QSpinBox;
    aSpinBox->setRange(0, h/3);
    aSpinBox->setValue(a);
    aLabel = new QLabel(tr("&A Size:"));
    aLabel->setBuddy(aSpinBox);

    bSpinBox = new QSpinBox;
    bSpinBox->setRange(0, h/3);
    bSpinBox->setValue(b);
    bLabel = new QLabel(tr("&B Size:"));
    bLabel->setBuddy(bSpinBox);

    cSpinBox = new QSpinBox;
    cSpinBox->setRange(0, h/3);
    cSpinBox->setValue(c);
    cLabel = new QLabel(tr("&C Size:"));
    cLabel->setBuddy(cSpinBox);

    dSpinBox = new QSpinBox;
    dSpinBox->setRange(0, h/3);
    dSpinBox->setValue(d);
    dLabel = new QLabel(tr("&D Size:"));
    dLabel->setBuddy(dSpinBox);

    eSpinBox = new QSpinBox;
    eSpinBox->setRange(0, w/4);
    eSpinBox->setValue(e);
    eLabel = new QLabel(tr("&E Size:"));
    eLabel->setBuddy(eSpinBox);

    fSpinBox = new QSpinBox;
    fSpinBox->setRange(0, w/4);
    fSpinBox->setValue(f);
    fLabel = new QLabel(tr("&F Size:"));
    fLabel->setBuddy(fSpinBox);

    acceptButton = new QPushButton(tr("&Accept"), this);

    //connect
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
    layout->addWidget(acceptButton, 8, 0, 2, 2);
    setLayout(layout);

    setWindowTitle(tr("Edit Figure"));
}

int EditDialog::getw() {return w;}
int EditDialog::geth() {return h;}
int EditDialog::geta() {return a;}
int EditDialog::getb() {return b;}
int EditDialog::getc() {return c;}
int EditDialog::getd() {return d;}
int EditDialog::gete() {return e;}
int EditDialog::getf() {return f;}

//private slots:
void EditDialog::wValueChanged(int val) {
    w = val;
    if(w>=20 and w<=200) { // ручной ввод
        if(h>=w)
            hSpinBox->setValue(w-1);
        else if(h<=w/3)
            hSpinBox->setValue(w/3);
        hSpinBox->setRange(w/3, w);
        if(e>=w/4)
            eSpinBox->setValue(w/4-1);
        eSpinBox->setMaximum(w/4);
        if(f>=w/4)
            fSpinBox->setValue(w/4-1);
        fSpinBox->setMaximum(w/4);
    }
}
void EditDialog::hValueChanged(int val) {
    h = val;
    if(h>=w/3 and h<w) {
        if(a>=h/3)
            aSpinBox->setValue(h/3-1);
        aSpinBox->setMaximum(h/3);
        if(b>=h/3)
            bSpinBox->setValue(h/3-1);
        bSpinBox->setMaximum(h/3);
        if(c>=h/3)
            cSpinBox->setValue(h/3-1);
        cSpinBox->setMaximum(h/3);
        if(d>=h/3)
            dSpinBox->setValue(h/3-1);
        dSpinBox->setMaximum(h/3);
    }
}
void EditDialog::aValueChanged(int val) {
    a = val;
}
void EditDialog::bValueChanged(int val) {
    b = val;
}
void EditDialog::cValueChanged(int val) {
    c = val;
}
void EditDialog::dValueChanged(int val) {
    d = val;
}
void EditDialog::eValueChanged(int val) {
    e = val;
}
void EditDialog::fValueChanged(int val) {
    f = val;
}

//RotateDialog
RotateDialog::RotateDialog(int& fi, QWidget* parent)
    : QDialog(parent)
{
    setModal(true);
    setFixedSize(200, 200);
    setWindowTitle(tr("Rotate Figure"));

    fiDial = new QDial(this);
    fiDial->setFocusPolicy(Qt::StrongFocus);
    fiDial->setRange(-180, 180);
    fiDial->setSingleStep(1);
    fiDial->setValue(fi);
    fiDial->setFixedSize(100, 100);

    fiLabel = new QLabel(tr("&Degree"));
    fiLabel->setBuddy(fiDial);

    acceptButton = new QPushButton(tr("&Accept"), this);
    connect(acceptButton, SIGNAL(clicked()),
            this,         SLOT(accept()));

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(fiLabel, 0, 0, Qt::AlignCenter);
    layout->addWidget(fiDial, 1, 0);
    layout->addWidget(acceptButton, 2, 0);
    setLayout(layout);

}

//private slots:
void RotateDialog::fiValueChanged(int val) {

}

// Figure
//public:
Figure::Figure(QWidget *parent)
    : QWidget(parent)
    , w(QRandomGenerator::global()->bounded(20, 200))
    , h(QRandomGenerator::global()->bounded(w/3, w))
    , a(QRandomGenerator::global()->bounded(0, h/3))
    , b(QRandomGenerator::global()->bounded(0, h/3))
    , c(QRandomGenerator::global()->bounded(0, h/3))
    , d(QRandomGenerator::global()->bounded(0, h/3))
    , e(QRandomGenerator::global()->bounded(0, w/4))
    , f(QRandomGenerator::global()->bounded(0, w/4))
    , fi(QRandomGenerator::global()->bounded(-180, 180))
    , selected(false)
    , lmHolds(false)
{
    setFixedSize((w+1)*abs(qCos(qDegreesToRadians(static_cast<float>(-fi))))+
                 (h+1)*abs(qSin(qDegreesToRadians(static_cast<float>(-fi)))),
                 (h+1)*abs(qCos(qDegreesToRadians(static_cast<float>(-fi))))+
                 (w+1)*abs(qSin(qDegreesToRadians(static_cast<float>(-fi)))));
    _FigureMenu = new QMenu(this);
    _ActionFigureDelete = _FigureMenu->addAction(tr("Delete"),
                                                 this,
                                                 SLOT(deleteFigure()));
    _ActionFigureEdit = _FigureMenu->addAction(tr("Edit"),
                                                 this,
                                                 SLOT(showFigureEdit()));
    _ActionFigureMove = _FigureMenu->addAction(tr("Move"),
                                               this,
                                               SLOT(startMoving()));
    _ActionFigureRotate = _FigureMenu->addAction(tr("Rotate"),
                                                 this,
                                                 SLOT(showFigureRotate()));
    _EditDialog = new EditDialog(w, h, a, b, c, d, e, f, this);
    connect(_EditDialog, SIGNAL(accepted()), this, SLOT(figureChanged()));
    _RotateDialog = new RotateDialog(fi, this);
    //connect(_RotateDialog, SIGNAL(accepted()), this, SLOT(fiChanged()));
    update();
}

void Figure::deselect() {
    selected = false;
}
bool Figure::isSelected() {
    return selected;
}

//protected:

void Figure::contextMenuEvent(QContextMenuEvent* e) {
    _FigureMenu->exec(e->globalPos());
}

void Figure::mousePressEvent(QMouseEvent* e) {
    selected = true;
    emit selectedSgn(this);
    if(e->button()==Qt::LeftButton) {
        lmHolds = true;
        emit moveSgn(this, e->pos().x()-w/2, e->pos().y()-h/2);
    }
    update();
}
void Figure::mouseMoveEvent(QMouseEvent* e) {
    if(hasMouseTracking())
        emit moveSgn(this, e->pos().x()-w/2, e->pos().y()-h/2);
    else if(lmHolds)
        emit moveSgn(this, e->pos().x()-w/2, e->pos().y()-h/2);
    update();
}
void Figure::mouseReleaseEvent(QMouseEvent* e) {
    if(e->button()==Qt::LeftButton)
        lmHolds = false;
}

//private slots:
void Figure::deleteFigure() {
    emit delSgn(this);
}

void Figure::showFigureEdit() {
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
    setFixedSize((w+1)*abs(qCos(qDegreesToRadians(static_cast<float>(-fi))))+
                 (h+1)*abs(qSin(qDegreesToRadians(static_cast<float>(-fi)))),
                 (h+1)*abs(qCos(qDegreesToRadians(static_cast<float>(-fi))))+
                 (w+1)*abs(qSin(qDegreesToRadians(static_cast<float>(-fi)))));
    update();
}
void Figure::fiChanged() {

}
void Figure::startMoving() {

    emit
    if(hasMouseTracking()) {
        setMouseTracking(false);
    }
    else {
        setMouseTracking(true);
        QPoint p = this->mapFromGlobal(QCursor::pos());
        emit moveSgn(this, p.x()-w/2, p.y()-h/2);
    }
}
void Figure::showFigureRotate() {
    _RotateDialog->exec();
}

// Figure1
Figure1::Figure1(QWidget *parent) : Figure(parent)                            {}

void Figure1::paintEvent(QPaintEvent* e) {
    QPainter painter(this);
    if(selected)
        painter.setPen(Qt::blue);
    else
        painter.setPen(Qt::black);

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

// Figure2
Figure2::Figure2(QWidget *parent) : Figure(parent)                            {}

void Figure2::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    if(selected)
        painter.setPen(Qt::blue);
    else
        painter.setPen(Qt::black);

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

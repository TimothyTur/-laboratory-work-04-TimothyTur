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
    //setFixedSize(250, 250);

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

    fiSpinBox = new QSpinBox;
    fiSpinBox->setRange(-180, 180);
    fiSpinBox->setValue(-fi);
    fiLabel = new QLabel(tr("&Fi Degree:"));
    fiLabel->setBuddy(fiSpinBox);

    if(figureType) {// 2
        S = w*h-b*b-f*f/2-0.785375*c*c-0.214625*d*d-e*e/2;
        P = 2*h+2*w+f+f-0.42925*(c+d);
    }
    else {// 1
        S = w*h-0.785375*a*a-0.785375*b*b-1.57075*f*f-c*c/2-0.785375*d*d;
        P = 2*h+2*w-0.42925*(a+b+d)+0.57075*f-0.585786*c;
    }

    SLabel = new QLabel(tr("S : ")+QString::number(S));
    PLabel = new QLabel(tr("P : ")+QString::number(P));

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
        SLabel->setText(tr("S : ")+QString::number(S));
        PLabel->setText(tr("P : ")+QString::number(P));
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
        SLabel->setText(tr("S : ")+QString::number(S));
        PLabel->setText(tr("P : ")+QString::number(P));
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
    SLabel->setText(tr("S : ")+QString::number(S));
    PLabel->setText(tr("P : ")+QString::number(P));
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
    SLabel->setText(tr("S : ")+QString::number(S));
    PLabel->setText(tr("P : ")+QString::number(P));
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
    SLabel->setText(tr("S : ")+QString::number(S));
    PLabel->setText(tr("P : ")+QString::number(P));
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
    SLabel->setText(tr("S : ")+QString::number(S));
    PLabel->setText(tr("P : ")+QString::number(P));
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
    SLabel->setText(tr("S : ")+QString::number(S));
    PLabel->setText(tr("P : ")+QString::number(P));
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
    SLabel->setText(tr("S : ")+QString::number(S));
    PLabel->setText(tr("P : ")+QString::number(P));
}
void EditDialog::fiValueChanged(int val) {
    fi = -val;
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

    connect(fiDial, SIGNAL(valueChanged(int)), this, SLOT(fiChanged(int)));
}
int RotateDialog::getFi() {
    return fiDial->value();
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
    setFixedSize((w+1)*abs(qCos(qDegreesToRadians(static_cast<float>(-fi))))+
                 (h+1)*abs(qSin(qDegreesToRadians(static_cast<float>(-fi))))+1,
                 (h+1)*abs(qCos(qDegreesToRadians(static_cast<float>(-fi))))+
                 (w+1)*abs(qSin(qDegreesToRadians(static_cast<float>(-fi))))+1);
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
    //_EditDialog = new EditDialog(w, h, a, b, c, d, e, f, fi, this);
    //connect(_EditDialog, SIGNAL(accepted()), this, SLOT(figureChanged()));
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
bool Figure::getForm() {return form;}
bool Figure::isBlocked() {return blocked;}
void Figure::block() {
    blocked = true;
    lmHolds = false;
    setMouseTracking(false);
}

void Figure::mouseMoveEvent(QMouseEvent* e) {
    if(not blocked) {
        if(hasMouseTracking())
            emit moveSgn(this,
                         e->pos().x()
                         -w/2*abs(qCos(qDegreesToRadians(static_cast<float>(fi))))
                         -h/2*abs(qSin(qDegreesToRadians(static_cast<float>(fi)))),
                         e->pos().y()
                         -h/2*abs(qCos(qDegreesToRadians(static_cast<float>(fi))))
                         -w/2*abs(qSin(qDegreesToRadians(static_cast<float>(fi)))));
        else if(lmHolds)
            emit moveSgn(this,
                         e->pos().x()
                         -w/2*abs(qCos(qDegreesToRadians(static_cast<float>(fi))))
                         -h/2*abs(qSin(qDegreesToRadians(static_cast<float>(fi)))),
                         e->pos().y()
                         -h/2*abs(qCos(qDegreesToRadians(static_cast<float>(fi))))
                         -w/2*abs(qSin(qDegreesToRadians(static_cast<float>(fi)))));
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
    if(not blocked) {
        w = _EditDialog->getw();
        h = _EditDialog->geth();
        a = _EditDialog->geta();
        b = _EditDialog->getb();
        c = _EditDialog->getc();
        d = _EditDialog->getd();
        e = _EditDialog->gete();
        f = _EditDialog->getf();
        fi = _EditDialog->getfi();
        setFixedSize((w+1)*abs(qCos(qDegreesToRadians(static_cast<float>(-fi))))+
                     (h+1)*abs(qSin(qDegreesToRadians(static_cast<float>(-fi))))+1,
                     (h+1)*abs(qCos(qDegreesToRadians(static_cast<float>(-fi))))+
                     (w+1)*abs(qSin(qDegreesToRadians(static_cast<float>(-fi))))+1);
        update();
    }
}
void Figure::fiChanged(int val) {
    if(not blocked) {
        fi = val;
        setFixedSize((w+1)*abs(qCos(qDegreesToRadians(static_cast<float>(-fi))))+
                     (h+1)*abs(qSin(qDegreesToRadians(static_cast<float>(-fi))))+1,
                     (h+1)*abs(qCos(qDegreesToRadians(static_cast<float>(-fi))))+
                     (w+1)*abs(qSin(qDegreesToRadians(static_cast<float>(-fi))))+1);
        update();
    }
}
void Figure::startMoving() {
    if(not blocked) {
        if(hasMouseTracking()) {
            setMouseTracking(false);
        }
        else {
            setMouseTracking(true);
            QPoint p = this->mapFromGlobal(QCursor::pos());
            emit moveSgn(this,
                         p.x()
                         -w/2*abs(qCos(qDegreesToRadians(static_cast<float>(fi))))
                         -h/2*abs(qSin(qDegreesToRadians(static_cast<float>(fi)))),
                         p.y()
                         -h/2*abs(qCos(qDegreesToRadians(static_cast<float>(fi))))
                         -w/2*abs(qSin(qDegreesToRadians(static_cast<float>(fi)))));
        }
    }
}
void Figure::showFigureRotate() {
    _RotateDialog->exec();
}

// Figure1
Figure1::Figure1(QWidget *parent) : Figure(parent) {
    form = false;
    _EditDialog = new EditDialog(w, h, a, b, c, d, e, f, fi, false, this);
    connect(_EditDialog, SIGNAL(accepted()), this, SLOT(figureChanged()));
}

void Figure1::paintEvent(QPaintEvent* e) {
    QPainter painter(this);
    // для тестов
    /*
    painter.setPen(Q t::red);
    //painter.drawEllipse(dx, dy, 2, 2); // это был клик по фигуре в 0
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
    */

    if(selected)
        painter.setPen(Qt::blue);
    else
        painter.setPen(Qt::black);

    if(fi>=-180 and fi<-90)
        painter.translate(
                -(w+1)*qCos(qDegreesToRadians(static_cast<float>(fi))),
                (w+1)*qSin(qDegreesToRadians(static_cast<float>(-fi)))-
                (h+1)*qCos(qDegreesToRadians(static_cast<float>(fi))));
    else if(fi>=-90 and fi<0)
        painter.translate(
                0,
                (w+1)*qSin(qDegreesToRadians(static_cast<float>(-fi))));
    else if(fi>0 and fi<=90)
        painter.translate(
                (h+1)*qSin(qDegreesToRadians(static_cast<float>(fi))),
                0);
    else if(fi>90 and fi<=180)
        painter.translate(
                (h+1)*qSin(qDegreesToRadians(static_cast<float>(fi)))-
                (w+1)*qCos(qDegreesToRadians(static_cast<float>(fi))),
                -(h+1)*qCos(qDegreesToRadians(static_cast<float>(fi))));
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
void Figure1::contextMenuEvent(QContextMenuEvent* e) {
    if(collidingWithBox(e->pos()))
        _FigureMenu->exec(e->globalPos());
    else
        emit contextMenuSgn(e);
}
void Figure1::mousePressEvent(QMouseEvent* e) {
    if(collidingWithBox(e->pos())) {
        if(e->button()==Qt::LeftButton) {
            selected = true;
            emit selectedSgn(this);
            if(not blocked) {
                lmHolds = true;
                emit moveSgn(this,
                     e->pos().x()
                     -w/2*abs(qCos(qDegreesToRadians(static_cast<float>(fi))))
                     -h/2*abs(qSin(qDegreesToRadians(static_cast<float>(fi)))),
                     e->pos().y()
                     -h/2*abs(qCos(qDegreesToRadians(static_cast<float>(fi))))
                     -w/2*abs(qSin(qDegreesToRadians(static_cast<float>(fi)))));
            }
        }
        update();
    }
    else
        emit mousePressSgn(e);
}

bool Figure1::collidingWithBox(QPoint p) {
    return collidingWithBox(p.x(), p.y());
}
bool Figure1::collidingWithBox(int x, int y) {
    // некоторые условия здесь можно убрать, но мб потом
    if(fi>-180 and fi<-90) {
        float radfi = qDegreesToRadians(static_cast<float>(fi));
        float k = qTan(radfi);
        if(y>x*k-h*qCos(radfi) or //y1
           y<-x/k-h*qCos(radfi) or //y2
           y<x*k+h*qSin(radfi)*k or //y3
           y>-x/k-w*qSin(radfi)-(w*qCos(radfi)+h*qSin(radfi))/k) //y4
            return false;
        x -= -w*qCos(radfi);
        y -= -w*qSin(radfi)-h*qCos(radfi);
        return collidingWith(x*qCos(radfi)+y*qSin(radfi),
                             -x*qSin(radfi)+y*qCos(radfi));
    }
    else if(fi==-90) {
        return collidingWith(-y+w, x);
    }
    else if(fi>-90 and fi<0) {
        float radfi = qDegreesToRadians(static_cast<float>(fi));
        float k = qTan(radfi);
        if(y<x*k-w*qSin(radfi) or //y1
           y<-x/k+w*qCos(radfi)/k or //y2
           y>x*k+h*qCos(radfi)-(w*qCos(radfi)-h*qSin(radfi))*k or //y3
           y>-x/k-w*qSin(radfi))
            return false;
        y -= -w*qSin(radfi);
        return collidingWith(x*qCos(radfi)+y*qSin(radfi),
                             -x*qSin(radfi)+y*qCos(radfi));
    }
    else if(fi==0) {
        return collidingWith(x, y);
    }
    else if(fi>0 and fi<90) {
        float radfi = qDegreesToRadians(static_cast<float>(fi));
        float k = qTan(radfi);
        if(y<x*k-h*qSin(radfi)*k or //y1
           y>-x/k+w*qSin(radfi)+(h*qSin(radfi)+w*qCos(radfi))/k or //y2
           y>x*k+h*qCos(radfi) or //y3
           y<-x/k+h*qCos(radfi)) //y4
            return false;
        x -= h*qSin(radfi);
        return collidingWith(x*qCos(radfi)+y*qSin(radfi),
                             -x*qSin(radfi)+y*qCos(radfi));
    }
    else if(fi==90) {
        return collidingWith(y, -x+h);
    }
    else if(fi>90 and fi<180) {
        float radfi = qDegreesToRadians(static_cast<float>(fi));
        float k = qTan(radfi);
        if(y>x*k-h*qCos(radfi)-(h*qSin(radfi)-w*qCos(radfi))*k or //y1
           y>-x/k+w*qSin(radfi) or //y2
           y<x*k+w*qSin(radfi) or //y3
           y<-x/k-w*qCos(radfi)/k) //y4
            return false;
        x -= h*qSin(radfi)-w*qCos(radfi);
        y -= -h*qCos(radfi);
        return collidingWith(x*qCos(radfi)+y*qSin(radfi),
                             -x*qSin(radfi)+y*qCos(radfi));
    }
    else { // fi == +-180
        return collidingWith(w-x, h-y);
    }
}
bool Figure1::collidingWith(QPoint p) {
    return collidingWith(p.x(), p.y());
}
bool Figure1::collidingWith(int x, int y) {
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
Figure2::Figure2(QWidget *parent) : Figure(parent) {
    form = true;
    _EditDialog = new EditDialog(w, h, a, b, c, d, e, f, fi, true, this);
    connect(_EditDialog, SIGNAL(accepted()), this, SLOT(figureChanged()));
}

void Figure2::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    // для тестов
    /*
    painter.setPen(Qt::red);
    //painter.drawEllipse(dx, dy, 2, 2); // это был клик по фигуре в 0
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
    */


    // оригинальный код
    if(selected)
        painter.setPen(Qt::blue);
    else
        painter.setPen(Qt::black);

    if(fi>=-180 and fi<-90)
        painter.translate(
                -(w+1)*qCos(qDegreesToRadians(static_cast<float>(fi))),
                (w+1)*qSin(qDegreesToRadians(static_cast<float>(-fi)))-
                (h+1)*qCos(qDegreesToRadians(static_cast<float>(fi))));
    else if(fi>=-90 and fi<0)
        painter.translate(
                0,
                (w+1)*qSin(qDegreesToRadians(static_cast<float>(-fi))));
    else if(fi>0 and fi<=90)
        painter.translate(
                (h+1)*qSin(qDegreesToRadians(static_cast<float>(fi))),
                0);
    else if(fi>90 and fi<=180)
        painter.translate(
                (h+1)*qSin(qDegreesToRadians(static_cast<float>(fi)))-
                (w+1)*qCos(qDegreesToRadians(static_cast<float>(fi))),
                -(h+1)*qCos(qDegreesToRadians(static_cast<float>(fi))));
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
void Figure2::contextMenuEvent(QContextMenuEvent* e) {
    if(collidingWithBox(e->pos()))
        _FigureMenu->exec(e->globalPos());
    else
        emit contextMenuSgn(e);
}

void Figure2::mousePressEvent(QMouseEvent* e) {
    if(collidingWithBox(e->pos())) {
        if(e->button()==Qt::LeftButton) {
            selected = true;
            emit selectedSgn(this);
            if(not blocked) {
                lmHolds = true;
                emit moveSgn(this,
                     e->pos().x()
                     -w/2*abs(qCos(qDegreesToRadians(static_cast<float>(fi))))
                     -h/2*abs(qSin(qDegreesToRadians(static_cast<float>(fi)))),
                     e->pos().y()
                     -h/2*abs(qCos(qDegreesToRadians(static_cast<float>(fi))))
                     -w/2*abs(qSin(qDegreesToRadians(static_cast<float>(fi)))));
            }
        }
        update();
    }
    else
        emit mousePressSgn(e);
}
bool Figure2::collidingWithBox(QPoint p) {
    return collidingWithBox(p.x(), p.y());
}
bool Figure2::collidingWithBox(int x, int y) {
    // некоторые условия здесь можно убрать, но мб потом
    if(fi>-180 and fi<-90) {
        float radfi = qDegreesToRadians(static_cast<float>(fi));
        float k = qTan(radfi);
        if(y>x*k-h*qCos(radfi) or //y1
           y<-x/k-h*qCos(radfi) or //y2
           y<x*k+h*qSin(radfi)*k or //y3
           y>-x/k-w*qSin(radfi)-(w*qCos(radfi)+h*qSin(radfi))/k) //y4
            return false;
        x -= -w*qCos(radfi);
        y -= -w*qSin(radfi)-h*qCos(radfi);
        return collidingWith(x*qCos(radfi)+y*qSin(radfi),
                             -x*qSin(radfi)+y*qCos(radfi));
    }
    else if(fi==-90) {
        return collidingWith(-y+w, x);
    }
    else if(fi>-90 and fi<0) {
        float radfi = qDegreesToRadians(static_cast<float>(fi));
        float k = qTan(radfi);
        if(y<x*k-w*qSin(radfi) or //y1
           y<-x/k+w*qCos(radfi)/k or //y2
           y>x*k+h*qCos(radfi)-(w*qCos(radfi)-h*qSin(radfi))*k or //y3
           y>-x/k-w*qSin(radfi))
            return false;
        y -= -w*qSin(radfi);
        return collidingWith(x*qCos(radfi)+y*qSin(radfi),
                             -x*qSin(radfi)+y*qCos(radfi));
    }
    else if(fi==0) {
        return collidingWith(x, y);
    }
    else if(fi>0 and fi<90) {
        float radfi = qDegreesToRadians(static_cast<float>(fi));
        float k = qTan(radfi);
        if(y<x*k-h*qSin(radfi)*k or //y1
           y>-x/k+w*qSin(radfi)+(h*qSin(radfi)+w*qCos(radfi))/k or //y2
           y>x*k+h*qCos(radfi) or //y3
           y<-x/k+h*qCos(radfi)) //y4
            return false;
        x -= h*qSin(radfi);
        return collidingWith(x*qCos(radfi)+y*qSin(radfi),
                             -x*qSin(radfi)+y*qCos(radfi));
    }
    else if(fi==90) {
        return collidingWith(y, -x+h);
    }
    else if(fi>90 and fi<180) {
        float radfi = qDegreesToRadians(static_cast<float>(fi));
        float k = qTan(radfi);
        if(y>x*k-h*qCos(radfi)-(h*qSin(radfi)-w*qCos(radfi))*k or //y1
           y>-x/k+w*qSin(radfi) or //y2
           y<x*k+w*qSin(radfi) or //y3
           y<-x/k-w*qCos(radfi)/k) //y4
            return false;
        x -= h*qSin(radfi)-w*qCos(radfi);
        y -= -h*qCos(radfi);
        return collidingWith(x*qCos(radfi)+y*qSin(radfi),
                             -x*qSin(radfi)+y*qCos(radfi));
    }
    else { // fi == +-180
        return collidingWith(w-x, h-y);
    }
}
bool Figure2::collidingWith(QPoint p) {
    return collidingWith(p.x(), p.y());
}
bool Figure2::collidingWith(int x, int y) {
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
    if(f1->getForm()) {  // 2
        if(f2->getForm()) { // 2
            return figuresColliding(dynamic_cast<Figure2*>(f1),
                                    dynamic_cast<Figure2*>(f2),
                                    dx, dy) or
                   figuresColliding(dynamic_cast<Figure2*>(f2),
                                    dynamic_cast<Figure2*>(f1),
                                    -dx, -dy);
        }
        else { // 1
          return figuresColliding(dynamic_cast<Figure2*>(f1),
                                  dynamic_cast<Figure1*>(f2),
                                  dx, dy) or
                 figuresColliding(dynamic_cast<Figure1*>(f2),
                                  dynamic_cast<Figure2*>(f1),
                                  -dx, -dy);
        }
      }
    else { // 1
      if(f2->getForm()) { // 2
          return figuresColliding(dynamic_cast<Figure1*>(f1),
                                  dynamic_cast<Figure2*>(f2),
                                  dx, dy) or
                 figuresColliding(dynamic_cast<Figure2*>(f2),
                                  dynamic_cast<Figure1*>(f1),
                                  -dx, -dy);
      }
      else { // 1
        return figuresColliding(dynamic_cast<Figure1*>(f1),
                                dynamic_cast<Figure1*>(f2),
                                dx, dy) or
               figuresColliding(dynamic_cast<Figure1*>(f2),
                                dynamic_cast<Figure1*>(f1),
                                -dx, -dy);
      }
    }
}
bool figuresColliding(Figure1* f1, Figure1* f2, int dx, int dy) {
    // aka f1.collidingWith(f2.dots());
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
    int addx = 0, addy = 0;
    if(f2->fi>-180 and f2->fi < -90) {
        addx = -f2->w*qCos(radfi);
        addy = -f2->w*qSin(radfi)-f2->h*qCos(radfi);
    }
    else if(f2->fi == -90) {
        addy = f2->w;
    }
    else if(f2->fi>-90 and f2->fi<0) {
        addy = -f2->w*qSin(radfi);
    }
    //else if (f2->fi==0) {
    //
    //}
    else if(f2->fi>0 and f2->fi<90) {
        addx = f2->h*qCos(radfi);
    }
    else if(f2->fi == 90) {
        addx = f2->h;
    }
    else if(f2->fi>90 and f2->fi<180) {
        addx = f2->h*qSin(radfi)-f2->w*qCos(radfi);
        addy = -f2->h*qCos(radfi);
    }
    else { // +-180
        addx = f2->w;
        addy = f2->h;
    }
    for(int i=0; i<10; ++i) {
        if(f1->collidingWithBox(
                  ix[i]*qCos(radfi)-iy[i]*qSin(radfi) - dx + addx,
                  ix[i]*qSin(radfi)+iy[i]*qCos(radfi)- dy + addy))
            return true;
    }
    return false;
}
bool figuresColliding(Figure2* f1, Figure2* f2, int dx, int dy) {
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
    int addx = 0, addy = 0;
    if(f2->fi>-180 and f2->fi < -90) {
        addx = -f2->w*qCos(radfi);
        addy = -f2->w*qSin(radfi)-f2->h*qCos(radfi);
    }
    else if(f2->fi == -90) {
        addy = f2->w;
    }
    else if(f2->fi>-90 and f2->fi<0) {
        addy = -f2->w*qSin(radfi);
    }
    //else if (f2->fi==0) {
    //
    //}
    else if(f2->fi>0 and f2->fi<90) {
        addx = f2->h*qCos(radfi);
    }
    else if(f2->fi == 90) {
        addx = f2->h;
    }
    else if(f2->fi>90 and f2->fi<180) {
        addx = f2->h*qSin(radfi)-f2->w*qCos(radfi);
        addy = -f2->h*qCos(radfi);
    }
    else { // +-180
        addx = f2->w;
        addy = f2->h;
    }
    for(int i=0; i<14; ++i) {
        if(f1->collidingWithBox(
                  ix[i]*qCos(radfi)-iy[i]*qSin(radfi) - dx + addx,
                  ix[i]*qSin(radfi)+iy[i]*qCos(radfi)- dy + addy))
            return true;
    }
    return false;
}
bool figuresColliding(Figure1* f1, Figure2* f2, int dx, int dy) {
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
    int addx = 0, addy = 0;
    if(f2->fi>-180 and f2->fi < -90) {
        addx = -f2->w*qCos(radfi);
        addy = -f2->w*qSin(radfi)-f2->h*qCos(radfi);
    }
    else if(f2->fi == -90) {
        addy = f2->w;
    }
    else if(f2->fi>-90 and f2->fi<0) {
        addy = -f2->w*qSin(radfi);
    }
    //else if (f2->fi==0) {
    //
    //}
    else if(f2->fi>0 and f2->fi<90) {
        addx = f2->h*qCos(radfi);
    }
    else if(f2->fi == 90) {
        addx = f2->h;
    }
    else if(f2->fi>90 and f2->fi<180) {
        addx = f2->h*qSin(radfi)-f2->w*qCos(radfi);
        addy = -f2->h*qCos(radfi);
    }
    else { // +-180
        addx = f2->w;
        addy = f2->h;
    }
    for(int i=0; i<14; ++i) {
        if(f1->collidingWithBox(
                  ix[i]*qCos(radfi)-iy[i]*qSin(radfi) - dx + addx,
                  ix[i]*qSin(radfi)+iy[i]*qCos(radfi)- dy + addy))
            return true;
    }
    return false;
}
bool figuresColliding(Figure2* f1, Figure1* f2, int dx, int dy) {
    // aka f1.collidingWith(f2.dots());
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
    int addx = 0, addy = 0;
    if(f2->fi>-180 and f2->fi < -90) {
        addx = -f2->w*qCos(radfi);
        addy = -f2->w*qSin(radfi)-f2->h*qCos(radfi);
    }
    else if(f2->fi == -90) {
        addy = f2->w;
    }
    else if(f2->fi>-90 and f2->fi<0) {
        addy = -f2->w*qSin(radfi);
    }
    //else if (f2->fi==0) {
    //
    //}
    else if(f2->fi>0 and f2->fi<90) {
        addx = f2->h*qCos(radfi);
    }
    else if(f2->fi == 90) {
        addx = f2->h;
    }
    else if(f2->fi>90 and f2->fi<180) {
        addx = f2->h*qSin(radfi)-f2->w*qCos(radfi);
        addy = -f2->h*qCos(radfi);
    }
    else { // +-180
        addx = f2->w;
        addy = f2->h;
    }
    for(int i=0; i<10; ++i) {
        if(f1->collidingWithBox(
                  ix[i]*qCos(radfi)-iy[i]*qSin(radfi) - dx + addx,
                  ix[i]*qSin(radfi)+iy[i]*qCos(radfi)- dy + addy))
            return true;
    }
    return false;
}


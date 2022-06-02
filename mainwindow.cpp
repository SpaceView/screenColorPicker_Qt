#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QCursor>

#include <QtDebug>
#include <QPixmap>
#include <QImage>
#include <QDesktopWidget>
#include <QScreen>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->start(400);
    image = new QImage;
    pm = new QPixmap;
    setWindowTitle("Screen Color Picker");

    connect(timer,&QTimer::timeout,this, [this](){
        this->pos = QCursor::pos();
        qDebug()<< "current screen pos = " << this->pos;

        QScreen *screen = QGuiApplication::primaryScreen();
        //*pm = QPixmap::grabWindow(QApplication::desktop()->winId());
        *pm = screen->grabWindow(QApplication::desktop()->winId());
        *image = pm->toImage();
        QRgb b = image->pixel(this->pos);
        //QColor *c = new QColor;
        color.setRgb(b);
        QColor ic = QColor(255- color.red(), 255-color.green(), 255-color.blue());
        //qDebug() << c->name();
        ui->lineEdit->setText(color.name());
        QString str = "QLabel { background-color :" + color.name() + " ; color :" + ic.name() + " ; }";
        ui->label->setStyleSheet(str);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    if(image){
        delete image;
        image = NULL;
    }

    if(pm){
        delete pm;
        pm = NULL;
    }

    if(timer){
        delete timer;
        timer = NULL;
    }
}

void MainWindow::grabColor()
{
    /*
    //m_selectionRect = m_selectionRect.normalized();
    QDesktopWidget* desktop = QApplication::desktop();
    int screenNum = desktop->screenNumber(m_selectionRect.topLeft());
    QScreen* screen = QGuiApplication::screens()[screenNum];
    QPixmap screenGrab = screen->grabWindow(desktop->winId(),
        m_selectionRect.x(), m_selectionRect.y(), m_selectionRect.width(), m_selectionRect.height());
    QImage image = screenGrab.toImage();
    int numPixel = image.width() * image.height();
    int sumR = 0;
    int sumG = 0;
    int sumB = 0;

    for (int x = 0; x < image.width(); ++x) {
        for (int y = 0; y < image.height(); ++y) {
            QColor color = image.pixel(x, y);
            sumR += color.red();
            sumG += color.green();
            sumB += color.blue();
        }
    }

    QColor avgColor(sumR / numPixel, sumG / numPixel, sumB / numPixel);
    emit colorPicked(avgColor);
    */
}
/*
void test{
    QPixmap *a = new QPixmap;
        *a = QPixmap::grabWindow(QApplication::desktop()->winId());
        QImage *img = new QImage;
        *img = a->toImage();
        QRgb b = img->pixel(10,33);
        QColor *c = new QColor;
        c->setRgb(b);
        qDebug() << c->name();
}
*/

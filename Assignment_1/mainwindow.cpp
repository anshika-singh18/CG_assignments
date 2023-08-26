#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
using namespace std;
QImage img (500,500,QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    float dx, dy, x, y, len, Xinc, Yinc;
    int x1, y1, x2, y2, i;
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    x2=ui->textEdit_3->toPlainText().toInt();
    y2=ui->textEdit_4->toPlainText().toInt();

    dx=x2-x1;
    dy=y2-y1;

    if (abs(dx)>=abs(dy))
    {
        len=abs(dx);
    }
    else
    {
        len=abs(dy);
    }

    x=x1, y=y1;
    i=0;
    img.setPixel(x,y,qRgb(255,255,255));
    Xinc=dx/len;
    Yinc=dy/len;
    while (i<len)
    {
        x=x+Xinc;
        y=y+Yinc;
        img.setPixel(x,y,qRgb(255,255,255));
        i++;
    }



    ui->label->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::on_pushButton_2_clicked()
{
    int Xc, Yc, r;

    Xc=ui->textEdit_5->toPlainText().toInt();
    Yc=ui->textEdit_6->toPlainText().toInt();
    r=ui->textEdit_7->toPlainText().toInt();
    int x=0, y=r;
    int d=3-2*r;
    while (x<=y)
    {
        img.setPixel(Xc+x, Yc+y, qRgb(255,255,255));
        img.setPixel(Xc+y, Yc+x, qRgb(255,255,255));
        img.setPixel(Xc-x, Yc+y, qRgb(255,255,255));
        img.setPixel(Xc+y, Yc-x, qRgb(255,255,255));
        img.setPixel(Xc-x, Yc-y, qRgb(255,255,255));
        img.setPixel(Xc-y, Yc-x, qRgb(255,255,255));
        img.setPixel(Xc+x, Yc-y, qRgb(255,255,255));
        img.setPixel(Xc-y, Yc+x, qRgb(255,255,255));

        if (d<0)
        {
            d=d+(4*x)+6;
        }
        else
        {
            d=d+(4*(x-y))+10;
            y=y-1;
        }

        x=x+1;

    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}




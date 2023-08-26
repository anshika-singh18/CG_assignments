#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include "math.h"

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

void MainWindow::dda(int x1, int y1, int x2, int y2)
{
    int i;
    float dx, dy, x, y, len, Xinc, Yinc;
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


void MainWindow::on_pushButton_clicked()    //making of quadrants
{
    dda(0,250,500,250);
    dda(250,0,250,500);
}

void MainWindow::on_pushButton_2_clicked()  //line making
{

    int x1, y1, x2, y2;
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    x2=ui->textEdit_3->toPlainText().toInt();
    y2=ui->textEdit_4->toPlainText().toInt();

    dda(x1+250,y1+250,x2+250,y2+250);
}

void MainWindow::on_pushButton_3_clicked()      //translation
{

    int x1, y1, x2, y2, tx, ty;
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    x2=ui->textEdit_3->toPlainText().toInt();
    y2=ui->textEdit_4->toPlainText().toInt();
    tx=ui->textEdit_5->toPlainText().toInt();
    ty=ui->textEdit_6->toPlainText().toInt();

    dda(x1+250+tx,y1+250+ty,x2+250+tx,y2+250+ty);


}

void MainWindow::on_pushButton_4_clicked()       //scaling
{
//    float dx, dy, x, y, len, Xinc, Yinc;
    int x1, y1, x2, y2;
    float sx, sy;
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    x2=ui->textEdit_3->toPlainText().toInt();
    y2=ui->textEdit_4->toPlainText().toInt();
    sx=ui->textEdit_7->toPlainText().toInt();
    sy=ui->textEdit_8->toPlainText().toInt();


    dda((x1*sx)+250,(y1*sy)+250,(x2*sx)+250,(y2*sy)+250);

    ui->label->setPixmap(QPixmap::fromImage(img));
}



void MainWindow::on_pushButton_5_clicked()
{

        int x1, y1, x2, y2;

        double angle,b,s,c;
        x1=ui->textEdit->toPlainText().toInt();
        y1=ui->textEdit_2->toPlainText().toInt();
        x2=ui->textEdit_3->toPlainText().toInt();
        y2=ui->textEdit_4->toPlainText().toInt();
        angle=ui->textEdit_9->toPlainText().toDouble();



        b=(angle*3.14159)/180;
        s=sin(b);
        c=cos(b);

        dda(((x1*c)-(y1*s))+250, ((y1*c)+(x1*s))+250,((x2*c)-(y2*s))+250,((y2*c)+(x2*s))+250);

}


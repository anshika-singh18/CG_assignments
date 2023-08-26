#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;
QImage img(500, 500, QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    globalcolor=qRgb(100, 150, 250);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dda(int x1, int y1, int x2, int y2)
{
    float dx, dy, len, x, y, xinc, yinc;
       dx=x2-x1;
       dy=y2-y1;
       if(abs(dx)>=abs(dy)){
           len=abs(dx);
       }
       else{
           len=abs(dy);
       }
       xinc=dx/len;
       yinc=dy/len;
       x=x1;
       y=y1;
       for(int i=0; i<len; i++){
           x+=xinc;
           y+=yinc;
           img.setPixel(x, y, globalcolor);
       }
       ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::kochcurve(float x1, float y1, float x2, float y2, int level)
{

    if (level==0){
        dda(x1,y1,x2,y2);
        return;
    }

    else{
        float p1_x = ((2*x1)+x2)/3;
        float p1_y = ((2*y1)+y2)/3;
        float p2_x = ((2*x2)+x1)/3;
        float p2_y = ((2*y2)+y1)/3;

       float p_x=(p1_x+p2_x)*0.5 - (p2_y-p1_y)*0.867; //x coordinate of triangle ka vertex
       float p_y=(p2_x-p1_x)*0.867 + (p1_y+p2_y)*0.5; // y coordinate of triangle ka vertex

       kochcurve(x1, y1, p1_x, p1_y, level-1);
       kochcurve(p2_x, p2_y, x2, y2, level-1);
       kochcurve(p1_x, p1_y, p_x, p_y, level-1);
       kochcurve(p_x, p_y, p2_x, p2_y, level-1);
    }
}

void MainWindow::snowflake2(float x, float y, float r, int level){

    float s=0.577;

    kochcurve(x-0.5*r, y+0.5*r*s, x+0.5*r, y+0.5*r*s, level);
    kochcurve(x+0.5*r, y+0.5*r*s, x, y-r*s, level);
    kochcurve(x, y-r*s, x-0.5*r, y+0.5*r*s, level);
}

void MainWindow::on_pushButton_clicked()
{
   int level=ui->textEdit->toPlainText().toInt();
    snowflake2(200, 200, 200, level);
}

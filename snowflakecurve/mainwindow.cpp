#include "mainwindow.h"
#include "ui_mainwindow.h"
QImage img(500,500,QImage::Format_RGB888);

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




void MainWindow::dda(int x1, int y1, int x2, int y2){
    float dx, dy, xinc, yinc, x, y, len;
    dx=x2-x1;
    dy=y2-y1;

    if (abs(dx)>=abs(dy)){
        len=abs(dx);
    }
    else{
        len=abs(dy);
    }

    xinc=dx/len;
    yinc=dy/len;

    x=x1;
    y=y1;

    for(int i=0; i<=len; i++){
        x=x+xinc;
        y=y+yinc;
img.setPixel(x,y,qRgb(255,211,120)) ;

    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::kochcurve(float x1, float y1, float x2, float y2, int level){

    if (level==0){
        dda(x1,y1,x2,y2);
        return;
    }

    else{
        float p1x = (2*x1 + x2)/3;
        float p1y = (2*y1 + y2)/3;
        float p2x = (2*x2 + x1)/3;
        float p2y = (2*y2 + y1)/3;

        float px= (p2x+p1x)*0.5 - (p2y-p1y)*0.867;
        float py= (p2x-p1x)*0.867 + (p2y+p1y)*0.5;

        kochcurve(x1,y1,p1x,p1y,level-1);
        kochcurve(p2x,p2y,x2,y2,level-1);
        kochcurve(p1x,p1y,px,py,level-1);
        kochcurve(px,py,p2x,p2y, level-1);
    }
}

void MainWindow::snowflake(float x, float y, float r, int level){
    float s=0.577;

    kochcurve(x-0.5*r, y+0.5*r*s, x+0.5*r, y+0.5*r*s, level);
    kochcurve( x+0.5*r, y+0.5*r*s, x, y-r*s, level );
    kochcurve( x, y-r*s, x-0.5*r, y+0.5*r*s, level );
}

void MainWindow::on_pushButton_clicked()
{
 int level=ui->textEdit->toPlainText().toInt();
 snowflake(200,200,200,level);
}





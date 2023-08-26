#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include <QColorDialog>
#include "iostream"
using namespace std;
#include <QTime>
QImage img(500,500,QImage::Format_RGB888);
QColor c;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ver=0;
    start=true;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked() //colour
{
    c=QColorDialog::getColor();
}

void delay(){
    QTime t = QTime::currentTime().addMSecs(100);
    while(QTime::currentTime()<t){
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

void MainWindow::dda(int x1, int y1, int x2, int y2){
    float dx,dy,len,xinc,yinc,x,y;

    dx=x2-x1;
    dy=y2-y1;

    if (abs(dx)>=abs(dy)){
        len=abs(dx);
    }
    else{
        len=abs(dy);
    }

    x=x1;
    y=y1;
    xinc=dx/len;
    yinc=dy/len;

    int i=0;

    while(i<len){
        x=x+xinc;
        y=y+yinc;
        img.setPixel(x,y,c.rgb());
        i++;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::on_pushButton_2_clicked() //filling
{
    float dx,dy;
    int xmax=500;
    int xmin=0;
    int ymax=0;
    int ymin=500;
    for (int i=0; i<ver; i++){
        if (b[i]<ymin){
            ymin=b[i];
        }
        if (b[i]>ymax){
            ymax=b[i];
        }
    }
    cout<<"ymax= "<<ymax<<"\tymin= "<<ymin<<endl;

    a[ver]=a[0];
    b[ver]=b[0];

    for (int i=0; i<ver; i++){
        dx=a[i+1]-a[i];
        dy=b[i+1]-b[i];

        if (dy==0){
            slope[i]=1.0;
        }
        if (dx==0){
            slope[i]=0.0;
        }
        if (dx!=0 && dy!=0){
            slope[i]=dx/dy;
        }
    }

    for (int y=ymin; y<ymax; y++){
        int k=0;
        for (int i=0; i<ver; i++){
            if ((b[i]<=y && b[i+1]>y) || (b[i+1]<=y && b[i]>y)){
                x1[k] = int(a[i] + ((slope[i])*(y-b[i])));
                k++;
            }
        }

        for (int j=0; j<k-1; j++){
            for (int i=0; i<k-j-1; i++){
                if (x1[i]>x1[i+1]){
                    int temp;
                    temp=x1[i];
                    x1[i]=x1[i+1];
                    x1[i+1]=temp;
                }
            }

            for (int i=0; i<k; i+=2){
                delay();
                dda(x1[i],y,x1[i+1]+1,y);
            }
        }
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if (start){
        int p= event->pos().x();
        int q= event->pos().y();
        a[ver]=p;
        b[ver]=q;
        if(event->button()==Qt::RightButton){
            dda(a[ver-1],b[ver-1],a[0],b[0]);
            start=false;
        }

        else{
            if (ver>0){
                dda(a[ver-1],b[ver-1],a[ver],b[ver]);
            }
        }
        ver++;
    }
}



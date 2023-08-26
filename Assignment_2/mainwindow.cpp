#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include <iostream>
#include <algorithm>
#include <QTime>
#include <QColorDialog>
using namespace std;

QColor c;
QImage img(600,600,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    start=true;
    ver=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void delay(){
    QTime t = QTime::currentTime().addMSecs(100);
    while(QTime::currentTime()<t){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void MainWindow::on_pushButton_clicked()
{

    int ymax=0,xmax=600,i;
    int ymin=600,xmin=0;
    float dx,dy;
    // ymin and ymax of
    for(i=0;i<ver;i++)
    {
        if(b[i]>ymax)
            ymax=b[i];
        if(b[i]<ymin)
            ymin=b[i];
    }
    cout<<"ymax= "<<ymax<<" "<<"ymin= "<<ymin<<endl;
    a[ver]=a[0];
    b[ver]=b[0];

    for(i=0;i<ver;i++)
    {
        //Calculation of slope of each line
        dx= a[i+1]-a[i];
        dy= b[i+1]-b[i];
        if(dy==0)
            slope[i]=1.0;
        if(dx==0)
            slope[i]=0.0;
        if((dy!=0)&&(dx!=0)) //calculate inverse slope
            {
             slope[i]=dx/dy;
             //cout<<"Slope of the line= "<<i<<"is"<<slope[i]<<endl;
             }
    }

    for(int y=ymin;y<ymax;y++)
    {
        k=0;
        for(i=0;i<ver;i++)
        {
            if(((b[i]<=y)&&(b[i+1]>y))||((b[i]>y)&&(b[i+1]<=y)))
            {
                xi[k]=int(a[i]+(slope[i]*(y-b[i])));
                k++;
            }
        }



    for(j=0;j<k-1;j++)
        for(i=0;i<k-j-1;i++)
        {
            if(xi[i]>xi[i+1])
            {
                temp=xi[i];
                xi[i]=xi[i+1];
                xi[i+1]=temp;

            }
        }
    for(i=0;i<k;i+=2)
    {
        delay();
        dda(xi[i],y,xi[i+1]+1,y);

    }
    }
}



void MainWindow::dda(int x1, int y1, int x2, int y2)
{
    float xinc,yinc,dx,dy,len,x,y;
    int i;
    dx=x2-x1;
    dy=y2-y1;
    if(abs(dx)>=abs(dy))
        len=abs(dx);
    else
        len=abs(dy);
    x=x1;
    y=y1;
    i=0;
    img.setPixel(x,y,c.rgb());
    xinc=dx/len;
    yinc=dy/len;

    while(i<len)
    {
        x=x+xinc;
        y=y+yinc;
        img.setPixel(x,y,c.rgb());
        i++;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(start)
    {
        int p= event->pos().x();
        int q= event->pos().y();
        a[ver]=p;
        b[ver]=q;

        if(event->button()==Qt::RightButton)
        {
            dda(a[ver-1],b[ver-1],a[0],b[0]);
            start=false;
        }
        else
        {
            if(ver>0)
            {
                dda(a[ver],b[ver],a[ver-1],b[ver-1]);
            }
        }
        ver++;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    c= QColorDialog::getColor();
}


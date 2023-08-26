#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <iostream>
using namespace std ;
QImage img(500, 500, QImage :: Format_RGB888);
QImage img2(500, 500, QImage :: Format_RGB888);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    start = true ;
    ver = 0 ;
}

MainWindow::~MainWindow()
{
    delete ui;
}
int INSIDE = 0 ;
int LEFT = 1 ;
int RIGHT = 2 ;
int BOTTOM = 4 ;
int TOP = 8 ;

int Xmin = 100;
int Xmax = 400;
int Ymin = 100;
int Ymax = 400;

void MainWindow::DDA(int x1, int y1, int x2, int y2, int color)
{
    float dx, dy, x, y, len, Xinc, Yinc;
    dx = x2 - x1 ;
    dy = y2 - y1 ;
    if (abs(dx)>=abs(dy))
    {
        len = abs(dx);
    }
    else
    {
        len = abs(dy);
    }
    x = x1 ;
    y = y1 ;
    int i = 0 ;
    Xinc = dx/len;
    Yinc = dy/len ;

    while (i<len)
    {
        img.setPixel(x,y, qRgb(color, color , color));
        x = x + Xinc;
        y = y + Yinc ;
        i++;
       };

        ui -> label->setPixmap(QPixmap :: fromImage(img));
}

void MainWindow::DDA1(int x1, int y1, int x2, int y2, int colour)
{
    float dx, dy, x, y, len, Xinc, Yinc;
    dx = x2 - x1 ;
    dy = y2 - y1 ;

    if (abs(dx)>=abs(dy))
    {
        len = abs(dx);
    }

    else
    {
        len = abs(dy);
    }

    x = x1 ;
    y = y1 ;
    int i = 0 ;
    Xinc = dx/len;
    Yinc = dy/len ;

 if ( (x >= Xmin) && (x <= Xmax) &&(y>=Ymin)&&(y<=Ymax) )
 {
    while (i<len)
    {
        img2.setPixel(x,y,qRgb(colour-255 ,colour, colour));
        x = x + Xinc;
        y = y + Yinc ;
        i++;
       };
}
        ui -> label->setPixmap(QPixmap :: fromImage(img2));
}

int get_code(int x, int y )
{
    int code = INSIDE ;
    if (x < Xmin )
    {
        code = code | LEFT ;
    }

    else if ( x > Xmax )
    {
        code |= RIGHT ;
    }

    if ( y < Ymin )
    {
        code |= TOP ;
    }

    else if (y>Ymax)
    {
        code |= BOTTOM ;
    }

    return code ;
}


void MainWindow::cohen_sutherland_clip(int x1, int y1 , int x2, int y2 )
{
    int new_x ;
    int new_y ;
    float dx = (x2-x1) ;
    float dy = (y2-y1) ;
    float slope = (dy/dx) ;

    DDA1(100,100, 400,100,255);
    DDA1(100,400,400,400,255) ;
    DDA1(100,100,100,400,255) ;
    DDA1(400,100,400,400,255) ;

    if ( get_code(x1,y1) == 0 && get_code(x2,y2) == 0 )
    {
        DDA1(x1,y1,x2,y2,255);
    }

    else if( (get_code(x1,y1) != 0 && get_code(x2,y2) == 0) ||  (get_code(x1,y1) == 0 && get_code(x2,y2) != 0) )
    {

        if ( get_code(x1,y1) == 1)
        {
            new_x = Xmin ;
            new_y =y1 - slope * (x1 - Xmin);
            DDA1(new_x, new_y,x2,y2,255);

        }

        else if ( get_code(x1,y1) == 2 )
        {
            new_x = Xmax ;
            new_y = y1 - slope * ( x1 - Xmax ) ;
            DDA1(new_x, new_y, x2, y2, 255);
        }

        else if ( get_code(x1,y1) == 4 )
        {
            new_y = Ymax ;
            new_x = x1 + ((new_y - y1)/slope );
            DDA1(new_x,new_y,x2,y2,255);
        }

        else if ( get_code(x1,y1) == 8)
        {
            new_y = Ymin ;
            new_x = x1 + ((new_y - y1)/slope );
            DDA1(new_x,new_y,x2,y2,255);
        }

        if ( get_code(x2,y2) == 1)
        {
            new_x = Xmin ;
            new_y =y2 - slope * (x2 - Xmin);
            DDA1(new_x, new_y,x1,y1,255);

        }

        else if ( get_code(x2,y2) == 2 )
        {
            new_x = Xmax ;
            new_y = y2 - slope * ( x2 - Xmax ) ;
            DDA1(new_x, new_y, x1, y1, 255);
        }

        else if ( get_code(x2,y2) == 4 )
        {
            new_y = Ymax ;
            new_x = x2 + ((new_y - y2)/slope );
            DDA1(new_x,new_y,x1,y1,255);
        }

        else if ( get_code(x2,y2) == 8)
        {
            new_y = Ymin ;
            new_x = x2 + ((new_y - y2)/slope );
            DDA1(new_x,new_y,x1,y1,255);
        }
    }

    else if ( get_code(x1,y1) != 0 && get_code(x2,y2) != 0  )
    {
        int new_x1 ;
        int new_y1 ;
        int new_x2 ;
        int new_y2 ;
        if ( get_code(x1,y1) == 1 && get_code(x2,y2) == 8 )
        {
            new_x1 = Xmin ;
            new_y1 = y1 - slope * (x1 - Xmin);

            new_x2 = x2 + ((Ymin - y2)/slope );
            new_y2 = Ymin ;
            DDA1(new_x1,new_y1,new_x2,new_y2,255);
        }

        else if ( get_code(x2,y2) == 1 && get_code(x1,y1) == 8 )
        {
            new_x2 = Xmin ;
            new_y2 = y2 - slope * (x2 - Xmin);

            new_x1 = x1 + ((Ymin - y1)/slope );
            new_y1 = Ymin ;
            DDA1(new_x1,new_y1,new_x2,new_y2,255);
        }

        else if ( get_code(x1,y1) == 8 && get_code(x2,y2) == 2 )
        {
            new_y1 = Ymin ;
            new_x1 = x1 + ((new_y1 - y1)/slope );

            new_x2 = Xmax ;
            new_y2 = y2 - slope * ( x2 - Xmax ) ;

            DDA1(new_x1,new_y1,new_x2,new_y2,255);
        }

        else if ( get_code(x2,y2) == 8 && get_code(x1,y1) == 2 )
        {
            new_y2 = Ymin ;
            new_x2 = x2 + ((new_y2 - y2)/slope );

            new_x1 = Xmax ;
            new_y1 = y1 - slope * ( x1 - Xmax ) ;

            DDA1(new_x1,new_y1,new_x2,new_y2,255);
        }

        else if ( get_code(x1,y1) == 2 && get_code(x2,y2) == 4 )
        {
            new_x1 = Xmax ;
            new_y1 = y1 - slope * ( x1 - Xmax ) ;

            new_y2 = Ymax ;
            new_x2 = x2 + ((new_y2 - y2)/slope );

            DDA1(new_x1,new_y1,new_x2,new_y2,255);
        }

        else if ( get_code(x2,y2) == 2 && get_code(x1,y1) == 4 )
        {
            new_x2 = Xmax ;
            new_y2 = y2 - slope * ( x2 - Xmax ) ;

            new_y1 = Ymax ;
            new_x1 = x1 + ((new_y1 - y1)/slope );

            DDA1(new_x1,new_y1,new_x2,new_y2,255);
        }

        else if ( get_code(x1,y1) == 4 && get_code(x2,y2) == 1 )
        {
            new_y1 = Ymax ;
            new_x1 = x1 + ((new_y1 - y1)/slope );

            new_x2 = Xmin ;
            new_y2 =y2 - slope * (x2 - Xmin);

            DDA1(new_x1,new_y1,new_x2,new_y2,255);
        }

        else if ( get_code(x2,y2) == 4 && get_code(x1,y1) == 1 )
        {
            new_y2 = Ymax ;
            new_x2 = x2 + ((new_y2 - y2)/slope );

            new_x1 = Xmin ;
            new_y1 =y1 - slope * (x1 - Xmin);

            DDA1(new_x1,new_y1,new_x2,new_y2,255);
        }

    }


     ui -> label->setPixmap(QPixmap :: fromImage(img2));
}

void MainWindow::on_pushButton_clicked()
{
    for ( int i = 0 ; i < ver ; i+=2 )
    {
        cohen_sutherland_clip(a[i],b[i], a[i+1],b[i+1]);
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (start)
    {

        int p = event -> pos().x();
        int q = event -> pos().y() ;
        a[ver] = p ;
        b[ver] = q ;

        if (event->button() == Qt::LeftButton){
             if (ver % 2 != 0 )
             {
                 DDA(a[ver], b[ver], a[ver-1], b[ver-1],255);
             }
        }
        ver++;
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    DDA(100,100,400,100,255);
    DDA(100,400,400,400,255) ;
    DDA(100,100,100,400,255) ;
    DDA(400,100,400,400,255) ;
}


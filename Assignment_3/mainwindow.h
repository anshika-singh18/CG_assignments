#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();
    void DDA (int x1 , int y1, int x2, int y2, int color) ;
    void mousePressEvent(QMouseEvent *event );
    void on_pushButton_2_clicked();
    void cohen_sutherland_clip(int x1, int y1 , int x2, int y2 );
    void DDA1(int x1, int y1, int x2, int y2, int colour) ;

private:
    int a[20], b[20], ver;
    float slopes[20];
    bool start ;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

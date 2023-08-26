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

    void on_pushButton_2_clicked();
    void dda(int x1, int y1, int x2, int y2);
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    int a[20],b[20], x1[20];
    float slope[20];
    int ver;
    bool start;
};
#endif // MAINWINDOW_H

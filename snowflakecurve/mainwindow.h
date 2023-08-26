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
    void dda(int x1, int y1, int x2, int y2);
    void snowflake(float x, float y, float r, int level);
    void kochcurve(float x1, float y1, float x2, float y2, int level);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

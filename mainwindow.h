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

public:
    void grabColor();
private:
    Ui::MainWindow *ui;
    QPoint pos;
    QPixmap * pm = NULL;
    QImage * image = NULL;
    QTimer* timer = NULL;
    QColor color;
};
#endif // MAINWINDOW_H

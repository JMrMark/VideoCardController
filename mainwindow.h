#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cardinfo.h"
#include "cardmode.h"
#include "cardlogger.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_infoCard_b_clicked();

    void on_modeCard_b_clicked();

    void on_monitorCard_b_clicked();

private:
    Ui::MainWindow *ui;
    cardinfo *infoWindow = nullptr;
    CardMode *modeWindow = nullptr;
    CardLogger *loggerWindow = nullptr;
};
#endif // MAINWINDOW_H

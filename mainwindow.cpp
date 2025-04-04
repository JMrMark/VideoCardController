#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cardinfo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Video Card Controller");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_infoCard_b_clicked()
{
    if (infoWindow && !infoWindow->isHidden()) {
        infoWindow->raise();   // Піднімає вікно поверх інших
        infoWindow->activateWindow(); // Робить його активним
    } else {
        infoWindow = new cardinfo(this); // Створюємо вікно, якщо його ще немає
        infoWindow->setAttribute(Qt::WA_DeleteOnClose); // Автоматично видаляється при закритті
        infoWindow->show();

        // При закритті обнуляємо вказівник
        connect(infoWindow, &QObject::destroyed, this, [this]() {
            infoWindow = nullptr;
        });
    }
}


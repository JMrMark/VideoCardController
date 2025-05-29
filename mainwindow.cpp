#include <QMessageBox>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cardinfo.h"
#include "cardmode.h"
#include "cardlogger.h"

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


void MainWindow::on_modeCard_b_clicked()
{
    //modeWindow
    if (modeWindow && !modeWindow->isHidden()) {
        modeWindow->raise();   // Піднімає вікно поверх інших
        modeWindow->activateWindow(); // Робить його активним
    } else {
        modeWindow = new CardMode(this); // Створюємо вікно, якщо його ще немає
        modeWindow->setAttribute(Qt::WA_DeleteOnClose); // Автоматично видаляється при закритті
        modeWindow->show();

        // При закритті обнуляємо вказівник
        connect(modeWindow, &QObject::destroyed, this, [this]() {
            modeWindow = nullptr;
        });
    }
}


void MainWindow::on_monitorCard_b_clicked()
{
    if (loggerWindow && !loggerWindow->isHidden()) {
        loggerWindow->raise();   // Піднімає вікно поверх інших
        loggerWindow->activateWindow(); // Робить його активним
    } else {
        loggerWindow = new CardLogger(this); // Створюємо вікно, якщо його ще немає
        loggerWindow->setAttribute(Qt::WA_DeleteOnClose); // Автоматично видаляється при закритті
        loggerWindow->show();

        // При закритті обнуляємо вказівник
        connect(loggerWindow, &QObject::destroyed, this, [this]() {
            loggerWindow = nullptr;
        });
    }
}

// Детальніше про автора
void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox::information(this, "Інформація", "Автор: Чесановський Артем\nГрупа: КІ-306 \nДата розробки: 27.05.2025");
}


void MainWindow::on_pushButton_clicked()
{
    if (!interfaceHelper) {
        interfaceHelper = new InterfaceHelper();
        interfaceHelper->setAttribute(Qt::WA_DeleteOnClose);

        connect(interfaceHelper, &InterfaceHelper::destroyed, this, [=]() {
            interfaceHelper = nullptr;
        });

        interfaceHelper->show();
    } else {
        interfaceHelper->raise();
        interfaceHelper->activateWindow();
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    qApp->quit();
}


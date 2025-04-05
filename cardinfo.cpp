#include "cardinfo.h"
#include "ui_cardinfo.h"
#include "graphwindow.h"
#include <QProcess>
#include <QDebug>

cardinfo::cardinfo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cardinfo)
{
    ui->setupUi(this);
    setWindowTitle("Video Card Information");

    CounterOfVideoCards = -1;
    GetNumberOfVedioCards();

    PaintNotAvailableButtons();

    if (CounterOfVideoCards != -1){
        CurrentVideoCard = 0;
        ShowMainDataFromVideoCard(CurrentVideoCard);
        ShowCurrentDataFromVideoCard(CurrentVideoCard);
    }
}

cardinfo::~cardinfo()
{
    delete ui;
}

void cardinfo::PaintNotAvailableButtons() {
    // Стиль неактивної червоної кнопки
    QString redStyle = R"(
        QPushButton {
            border: 3px solid transparent;
            border-color: #373B44;
            padding: 8px 14px;
            font-size: 16px;
            color: #373B44;
            background-color: #ff766a;
            background-image: conical-gradient(from 90deg, transparent 90deg, #373B44 90deg);
            background-position: center;
            background-repeat: no-repeat;
            background-origin: content;
            outline: none;
        }

        QPushButton:hover {
            outline: none;
            background-color: #e60000;
        }

        QPushButton:pressed {
            background-color: #373B44;
            color: white;
        }
    )";

    if (CounterOfVideoCards == 1) {
        ui->InfoCard3_b->setStyleSheet(redStyle);
    }
    else if (CounterOfVideoCards == 0) {
        ui->InfoCard2_b->setStyleSheet(redStyle);
        ui->InfoCard3_b->setStyleSheet(redStyle);
    }
    else {
        ui->InfoCard1_b->setStyleSheet(redStyle);
        ui->InfoCard2_b->setStyleSheet(redStyle);
        ui->InfoCard3_b->setStyleSheet(redStyle);
    }
}

bool cardinfo::ShowMainDataFromVideoCard(int NumberOfAskedVideoCard){
    if (NumberOfAskedVideoCard < 0 || NumberOfAskedVideoCard > CounterOfVideoCards) {
        qWarning("Invalid GPU index");
        return false;
    }

    if (!GetMainDataFromVideoCard(NumberOfAskedVideoCard)) {
        qWarning("Failed to get main data");
        return false;
    }

    // Заміна значень у UI
    ui->modelText->setText(modelCard);
    ui->driverText->setText(driverVersion);

    return true;
}

bool cardinfo::ShowCurrentDataFromVideoCard(int NumberOfAskedVideoCard){
    if (NumberOfAskedVideoCard < 0 || NumberOfAskedVideoCard > CounterOfVideoCards) {
        qWarning("Invalid GPU index");
        return false;
    }

    if (!GetCurrentDataFromVideoCard(NumberOfAskedVideoCard)) {
        qWarning("Failed to get current data");
        return false;
    }

    // Завантаженість (%)
    ui->loadText->setText(QString::number(loadCard) + "%");

    // Відеопам'ять: "1024 MB used of 4096 MB"
    ui->capacityText->setText(QString::number(capacityUsedCard) + " MB used of " + QString::number(capacityCard) + " MB");

    // Температура (°C)
    ui->tempText->setText(QString::number(tempCard) + " °C");

    return true;
}

void cardinfo::on_InfoCard1_b_clicked()
{
    if (CounterOfVideoCards == -1){
        qDebug() << "No such videoCard available";
    }
    else {
        CurrentVideoCard = 0;
        ShowMainDataFromVideoCard(CurrentVideoCard);
        ShowCurrentDataFromVideoCard(CurrentVideoCard);
    }
}


void cardinfo::on_InfoCard2_b_clicked()
{
    if (CounterOfVideoCards == 0 || CounterOfVideoCards == -1){
        qDebug() << "No such videoCard available";
    }
    else {
        CurrentVideoCard = 1;
        ShowMainDataFromVideoCard(CurrentVideoCard);
        ShowCurrentDataFromVideoCard(CurrentVideoCard);
    }
}


void cardinfo::on_InfoCard3_b_clicked()
{
    if (CounterOfVideoCards == 1 || CounterOfVideoCards == 0 || CounterOfVideoCards == -1){
        qDebug() << "No such videoCard available";
    }
    else {
        CurrentVideoCard = 2;
        ShowMainDataFromVideoCard(CurrentVideoCard);
        ShowCurrentDataFromVideoCard(CurrentVideoCard);
    }
}


void cardinfo::on_loadButton_clicked()
{
    int gpuIndex = 0;

    if (!graphWindows[gpuIndex]) {
        graphWindows[gpuIndex] = new GraphWindow(CurrentVideoCard, 0);
        graphWindows[gpuIndex]->setAttribute(Qt::WA_DeleteOnClose);

        connect(graphWindows[gpuIndex], &GraphWindow::destroyed, this, [=]() {
            graphWindows[gpuIndex] = nullptr;
        });

        graphWindows[gpuIndex]->show();
    } else {
        graphWindows[gpuIndex]->raise();
        graphWindows[gpuIndex]->activateWindow();
    }
}


void cardinfo::on_capacityButton_clicked()
{
    int gpuIndex = 1;

    if (!graphWindows[gpuIndex]) {
        graphWindows[gpuIndex] = new GraphWindow(CurrentVideoCard, 1);
        graphWindows[gpuIndex]->setAttribute(Qt::WA_DeleteOnClose);

        connect(graphWindows[gpuIndex], &GraphWindow::destroyed, this, [=]() {
            graphWindows[gpuIndex] = nullptr;
        });

        graphWindows[gpuIndex]->show();
    } else {
        graphWindows[gpuIndex]->raise();
        graphWindows[gpuIndex]->activateWindow();
    }
}


void cardinfo::on_tempButton_clicked()
{
    int gpuIndex = 2;

    if (!graphWindows[gpuIndex]) {
        graphWindows[gpuIndex] = new GraphWindow(CurrentVideoCard, 2);
        graphWindows[gpuIndex]->setAttribute(Qt::WA_DeleteOnClose);

        connect(graphWindows[gpuIndex], &GraphWindow::destroyed, this, [=]() {
            graphWindows[gpuIndex] = nullptr;
        });

        graphWindows[gpuIndex]->show();
    } else {
        graphWindows[gpuIndex]->raise();
        graphWindows[gpuIndex]->activateWindow();
    }
}


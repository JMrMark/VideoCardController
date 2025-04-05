#include "cardinfo.h"
#include "ui_cardinfo.h"
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
        ShowMainDataFromVideoCard(0);
        ShowCurrentDataFromVideoCard(0);
    }
}

cardinfo::~cardinfo()
{
    delete ui;
}

bool cardinfo::AddVideoCardCounter(int number){
    int temp = number + CounterOfVideoCards;
    qDebug() << "The number of videocards is (temp): " << temp;
    if (temp > 3 || temp < 0){
        return false;
    }
    CounterOfVideoCards = temp;
    return true;
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

bool cardinfo::GetNumberOfVedioCards() {
    QProcess process;
    QStringList arguments;
    arguments << "--query-gpu=name"
              << "--format=csv,noheader";

    process.start("nvidia-smi", arguments);
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    QStringList gpus = output.split('\n', Qt::SkipEmptyParts);

    int result = gpus.count();
    qDebug() << "The number of videocards is: " << result;

    if (AddVideoCardCounter(result)) {
        return true;
    }

    qDebug("More than 3 or less than 0 video cards");
    return false;
}

bool cardinfo::GetMainDataFromVideoCard(int NumberOfAskedVideoCard){
    if (NumberOfAskedVideoCard < 0 || NumberOfAskedVideoCard > CounterOfVideoCards) {
        qWarning("Invalid GPU index");
        return false;
    }

    QProcess process;
    QStringList arguments;
    arguments << "-i" << QString::number(NumberOfAskedVideoCard)
              << "--query-gpu=name,memory.total,driver_version"
              << "--format=csv,noheader,nounits";

    process.start("nvidia-smi", arguments);
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    qDebug() << "Result of main data: " << output;

    QStringList values = output.trimmed().split(", ");
    if (values.size() < 3) return false;

    modelCard = values[0];
    capacityCard = values[1].toInt();
    driverVersion = values[2];

    return true;
}

bool cardinfo::GetCurrentDataFromVideoCard(int NumberOfAskedVideoCard) {
    if (NumberOfAskedVideoCard < 0 || NumberOfAskedVideoCard > CounterOfVideoCards) {
        qWarning("Invalid GPU index");
        return false;
    }

    QProcess process;
    QStringList arguments;
    arguments << "-i" << QString::number(NumberOfAskedVideoCard)
              << "--query-gpu=utilization.gpu,temperature.gpu,memory.used"
              << "--format=csv,noheader,nounits";

    process.start("nvidia-smi", arguments);
    process.waitForFinished();

    QString output = process.readAllStandardOutput().trimmed();
    qDebug() << "Current GPU data: " << output;

    QStringList values = output.split(",", Qt::SkipEmptyParts);
    if (values.size() < 3) return false;

    loadCard = values[0].trimmed().toInt();
    tempCard = values[1].trimmed().toInt();
    capacityUsedCard = values[2].trimmed().toInt();

    return true;
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
        ShowMainDataFromVideoCard(0);

        ShowCurrentDataFromVideoCard(0);
    }
}


void cardinfo::on_InfoCard2_b_clicked()
{
    if (CounterOfVideoCards == 0 || CounterOfVideoCards == -1){
        qDebug() << "No such videoCard available";
    }
    else {
        ShowMainDataFromVideoCard(1);

        ShowCurrentDataFromVideoCard(1);
    }
}


void cardinfo::on_InfoCard3_b_clicked()
{
    if (CounterOfVideoCards == 1 || CounterOfVideoCards == 0 || CounterOfVideoCards == -1){
        qDebug() << "No such videoCard available";
    }
    else {
        ShowMainDataFromVideoCard(2);

        ShowCurrentDataFromVideoCard(2);
    }
}


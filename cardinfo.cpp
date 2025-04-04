#include "cardinfo.h"
#include "ui_cardinfo.h"
#include <QProcess>

cardinfo::cardinfo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cardinfo)
{
    ui->setupUi(this);
    setWindowTitle("Video Card Information");
}

cardinfo::~cardinfo()
{
    delete ui;
}

bool cardinfo::AddVideoCardCounter(int number){
    int temp = number + CounterOfVideoCards;
    if (temp > 3 || temp <= 0){
        return false;
    }
    CounterOfVideoCards = temp;
    return true;
}

bool cardinfo::GetNumberOfVedioCards(){
    QProcess process;
    process.start("nvidia-smi --query-gpu=name --format=csv,noheader");
    process.waitForFinished();
    QString output = process.readAllStandardOutput();

    QStringList gpus = output.split('\n', Qt::SkipEmptyParts);
    int result = gpus.count();

    if (AddVideoCardCounter(result)) {
        return true;
    }
    qDebug("More than 3 video cards");
    return false;
}

bool cardinfo::GetMainDataFromVideoCard(int NumberOfAskedVideoCard){
    if (NumberOfAskedVideoCard < 0 || NumberOfAskedVideoCard >= CounterOfVideoCards) {
        qWarning("Invalid GPU index");
        return false;
    }

    QProcess process;
    QString command = QString("nvidia-smi -i %1 --query-gpu=name,memory.total,driver_version --format=csv,noheader,nounits")
                          .arg(NumberOfAskedVideoCard);
    process.start(command);
    process.waitForFinished();
    QString output = process.readAllStandardOutput();

    QStringList values = output.trimmed().split(", ");
    if (values.size() < 3) return false;

    modelCard = values[0];
    capacityCard = values[1].toInt();
    driverVersion = values[2].toInt();

    return true;
}

bool cardinfo::GetCurrentDataFromVideoCard(int NumberOfAskedVideoCard){
    if (NumberOfAskedVideoCard < 0 || NumberOfAskedVideoCard >= CounterOfVideoCards) {
        qWarning("Invalid GPU index");
        return false;
    }

    QProcess process;
    QString command = QString("nvidia-smi -i %1 --query-gpu=utilization.gpu,temperature.gpu,memory.used --format=csv,noheader,nounits")
                          .arg(NumberOfAskedVideoCard);
    process.start(command);
    process.waitForFinished();
    QString output = process.readAllStandardOutput();

    QStringList values = output.trimmed().split(", ");
    if (values.size() < 3) return false;

    loadCard = values[0].toInt();
    tempCard = values[1].toInt();
    capacityUsedCard = values[2].toInt();

    return true;
}

void cardinfo::on_InfoCard1_b_clicked()
{
    // Перша відеокарта

}


void cardinfo::on_InfoCard2_b_clicked()
{
    // Друга відеокарта
}


void cardinfo::on_InfoCard3_b_clicked()
{
    // Третя відеокарта
}


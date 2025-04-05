#include "videocardcollector.h"
#include <QProcess>
#include <QDebug>

VideoCardCollector::VideoCardCollector() {}

bool VideoCardCollector::AddVideoCardCounter(int number){
    int temp = number + CounterOfVideoCards;
    qDebug() << "The number of videocards is (temp): " << temp;
    if (temp > 3 || temp < 0){
        return false;
    }
    CounterOfVideoCards = temp;
    return true;
}

bool VideoCardCollector::GetNumberOfVedioCards() {
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

bool VideoCardCollector::GetMainDataFromVideoCard(int NumberOfAskedVideoCard){
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

bool VideoCardCollector::GetCurrentDataFromVideoCard(int NumberOfAskedVideoCard) {
    if (NumberOfAskedVideoCard < 0 || NumberOfAskedVideoCard > CounterOfVideoCards) {
        qWarning("Invalid GPU index");
        qDebug() << "[MAIN] Index is:" << NumberOfAskedVideoCard;
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

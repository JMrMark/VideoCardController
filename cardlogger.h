#ifndef CARDLOGGER_H
#define CARDLOGGER_H

#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>

#include <QMainWindow>
#include "videocardcollector.h"
#include <QProcess>

namespace Ui {
class CardLogger;
}

class CardLogger : public QMainWindow, public VideoCardCollector
{
    Q_OBJECT

public:
    explicit CardLogger(QWidget *parent = nullptr);
    ~CardLogger();

    //
    bool ShowLoggerDataFromVideoCard();

private slots:
    void on_buttonUpdate_clicked();

private:
    Ui::CardLogger *ui;

    QProcess *nvidiaProcess;

    QTableWidget *loggerTable;

    QVector<std::string> loggerData;
};

#endif // CARDLOGGER_H

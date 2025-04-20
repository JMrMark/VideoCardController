#include <QProcess>
#include "cardlogger.h"
#include "ui_cardlogger.h"

CardLogger::CardLogger(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CardLogger)
{
    ui->setupUi(this);
    setWindowTitle("Video Card Logger");

    nvidiaProcess = new QProcess(this);

    ui->tableLogger->setColumnCount(3);
    ui->tableLogger->setHorizontalHeaderLabels({"PID", "Назва процесу", "Використано відеопам'яті"});

    // Стилізація таблиці
    ui->tableLogger->setStyleSheet(R"(
    QTableWidget {
        background-color: #1e1e1e;
        color: #dddddd;
        gridline-color: #444444;
        border: 1px solid #333333;
        font-family: Consolas;
        font-size: 12px;
    }
    QHeaderView::section {
        background-color: #2e2e2e;
        color: #ffffff;
        padding: 4px;
        border: 1px solid #444444;
    }
    QTableWidget::item:selected {
        background-color: #3d6fa5;
        color: white;
    }
)");

    // Поведінка та розміри
    ui->tableLogger->horizontalHeader()->setStretchLastSection(true);
    ui->tableLogger->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableLogger->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableLogger->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView *header = ui->tableLogger->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::Interactive); // PID
    header->setSectionResizeMode(1, QHeaderView::Stretch);     // Назва процесу
    header->setSectionResizeMode(2, QHeaderView::Interactive); // Відеопам'ять

    ui->tableLogger->setColumnWidth(0, 80);   // PID
    ui->tableLogger->setColumnWidth(2, 140);  // Відеопам'ять

    ui->tableLogger->verticalHeader()->setVisible(false);

    ShowLoggerDataFromVideoCard();
}

CardLogger::~CardLogger()
{
    nvidiaProcess->kill();
    nvidiaProcess->waitForFinished();
    delete ui;
}

bool CardLogger::ShowLoggerDataFromVideoCard()
{
    loggerData.clear();

    nvidiaProcess->start("nvidia-smi",
                         QStringList() << "--query-compute-apps=pid,process_name,used_gpu_memory"
                                       << "--format=csv,noheader,nounits");

    if (!nvidiaProcess->waitForFinished(2000)) { // максимум 2 секунди
        qWarning() << "nvidia-smi timeout or failed.";
        return false;
    }

    QString output = nvidiaProcess->readAllStandardOutput();
    QTextStream stream(&output);

    while (!stream.atEnd()) {
        QString line = stream.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(',', Qt::SkipEmptyParts);
        if (parts.size() < 3) continue;

        loggerData.append(parts[0].trimmed().toStdString());
        loggerData.append(parts[1].trimmed().toStdString());
        loggerData.append(parts[2].trimmed().toStdString());
    }

    ui->tableLogger->setRowCount(0);

    for (int i = 0; i + 2 < loggerData.size(); i += 3)
    {
        int row = ui->tableLogger->rowCount();
        ui->tableLogger->insertRow(row);
        ui->tableLogger->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(loggerData[i])));
        ui->tableLogger->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(loggerData[i + 1])));
        ui->tableLogger->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(loggerData[i + 2])));
    }

    return true;
}

void CardLogger::on_buttonUpdate_clicked()
{
    ShowLoggerDataFromVideoCard();
}


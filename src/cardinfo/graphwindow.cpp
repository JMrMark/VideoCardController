#include "./graphwindow.h"
#include "./interface/ui_graphwindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QTimer>
#include <QMessageBox>

GraphWindow::GraphWindow(int gpuIndex, int plotIndex, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GraphWindow)
    , gpuIndex(gpuIndex)
    , plotIndex(plotIndex)
{
    ui->setupUi(this);

    CounterOfVideoCards = gpuIndex;

    qDebug() << "Current gpuIndex is: " << gpuIndex;

    // Заголовок вікна
    if (plotIndex == 0)
        setWindowTitle("GPU Load (%)");
    else if (plotIndex == 1)
        setWindowTitle("Memory Used (MB)");
    else
        setWindowTitle("Temperature (°C)");

    // Ініціалізація графіка
    series = new QLineSeries();
    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);

    axisX = new QValueAxis();
    axisX->setTitleText("Time");
    axisX->setLabelFormat("%d");
    axisX->setRange(0, 100);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY = new QValueAxis();
    axisY->setTitleText("Value");
    axisY->setLabelFormat("%d");
    axisY->setRange(0, 100);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Layout для графіка
    QVBoxLayout *mainLayout = new QVBoxLayout(ui->centralwidget);
    mainLayout->addWidget(chartView);

    // Створення елементів керування
    setupTimerControls();

    // QProcess для запитів
    nvidiaProcess = new QProcess(this);

    // Таймер для оновлення графіка
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &GraphWindow::updateGraph);

    // Початковий запуск таймера (5000 мс)
    restartUpdateTimer(5000);
}

GraphWindow::~GraphWindow()
{
    nvidiaProcess->kill();
    nvidiaProcess->waitForFinished();
    delete ui;
}

void GraphWindow::updateGraph()
{
    bool success = false;

    // Оновлюємо відповідне значення в залежності від plotIndex
    if (plotIndex == 0)
        success = UpdateCurrentLoadCard(gpuIndex, *nvidiaProcess);
    else if (plotIndex == 1)
        success = UpdateCurrentCapacityUsedCard(gpuIndex, *nvidiaProcess);
    else if (plotIndex == 2)
        success = UpdateCurrentTempCard(gpuIndex, *nvidiaProcess);

    if (!success)
        return;

    int value = 0;
    if (plotIndex == 0)
        value = loadCard;
    else if (plotIndex == 1)
        value = capacityUsedCard;
    else if (plotIndex == 2)
        value = tempCard;

    // Додаємо точку на графік
    series->append(timeStep, value);
    timeStep++;

    // Зсуваємо вікно по X
    if (timeStep > axisX->max())
        axisX->setRange(axisX->min() + 1, axisX->max() + 1);

    // Оновлюємо верхню межу Y, якщо значення близьке до поточного максимуму
    if (value > axisY->max() - 5)
        axisY->setRange(0, value + 10);
}

void GraphWindow::setupTimerControls()
{
    updateLabel = new QLabel("Частота оновлення (мс):");
    updateLineEdit = new QLineEdit("5000");
    updateButton = new QPushButton("Оновити");

    // Стилі (можеш налаштувати ще глибше за бажанням)
    updateLabel->setStyleSheet("font-size: 12px;");
    updateLineEdit->setStyleSheet("width: 60px; font-size: 12px;");
    updateButton->setStyleSheet("QPushButton { background-color: #2B6CB0;\
        color: white;\
        border: none;\
        border-radius: 8px;\
        padding: 6px 14px;\
        font: 12px 'Segoe UI';}\
        QPushButton:hover {\
            background-color: #2C5282; }\
        QPushButton:pressed {\
            background-color: #1A365D; }");


    // Layout для контролів таймера
    QHBoxLayout *controlsLayout = new QHBoxLayout();
    controlsLayout->addWidget(updateLabel);
    controlsLayout->addWidget(updateLineEdit);
    controlsLayout->addWidget(updateButton);
    controlsLayout->addStretch(); // Штовхає контролі вправо

    // Додаємо контролі в нижню частину основного layout
    qobject_cast<QVBoxLayout*>(ui->centralwidget->layout())->addLayout(controlsLayout);

    // Підключення кнопки
    connect(updateButton, &QPushButton::clicked, this, [=]() {
        bool ok;
        int interval = updateLineEdit->text().toInt(&ok);
        if (ok && interval > 0) {
            restartUpdateTimer(interval);
        } else {
            QMessageBox::warning(this, "Помилка", "Введіть коректне число більше 0.");
        }
    });
}

void GraphWindow::restartUpdateTimer(int ms)
{
    if (updateTimer->isActive())
        updateTimer->stop();
    updateTimer->start(ms);
}

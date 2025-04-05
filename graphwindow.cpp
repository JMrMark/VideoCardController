#include "graphwindow.h"
#include "ui_graphwindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QTimer>
#include <algorithm>

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

    // Ініціалізація
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
    axisY->setRange(0, 100); // тимчасово
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Додаємо графік у layout
    QVBoxLayout *layout = new QVBoxLayout(ui->centralwidget);
    layout->addWidget(chartView);

    // Таймер для оновлення графіка
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &GraphWindow::updateGraph);
    updateTimer->start(1000); // кожні 10 секунд
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::updateGraph()
{
    if (!GetCurrentDataFromVideoCard(gpuIndex))
        return;

    int value = 0;
    if (plotIndex == 0)
        value = loadCard;
    else if (plotIndex == 1)
        value = capacityUsedCard;
    else if (plotIndex == 2)
        value = tempCard;

    // Додаємо точку
    series->append(timeStep, value);
    timeStep++;

    // Оновлюємо межі осей
    if (timeStep > axisX->max())
        axisX->setRange(axisX->min() + 1, axisX->max() + 1);

    int maxY = std::max(value + 10, static_cast<int>(axisY->max()));
    if (value > axisY->max() - 5)
        axisY->setRange(0, maxY);
}

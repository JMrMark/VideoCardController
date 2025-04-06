#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include "videocardcollector.h"

#include <QMainWindow>
#include <QTimer>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QMainWindow, public VideoCardCollector
{
    Q_OBJECT

public:
    GraphWindow(int gpuIndex, int plotIndex, QWidget *parent = nullptr);
    ~GraphWindow();

private slots:
    void updateGraph(); // буде викликатись таймером

private:
    Ui::GraphWindow *ui;

    // Номер використовуваної ідеокарти
    const int gpuIndex;

    // Номер потрібного нам параметру для відображення графіку
    //  * 0 -> load (int) -- Завантаженість
    //  * 1 -> capacity (int) -- Об'єм використаної пам'яті
    //  * 2 -> temp (int) -- Температура
    const int plotIndex;

    QChart *chart;
    QChartView *chartView;
    QLineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QTimer *updateTimer;

    int timeStep = 0; // для осі X (час)

    QProcess *nvidiaProcess;

    QLabel *updateLabel;
    QLineEdit *updateLineEdit;
    QPushButton *updateButton;

    void setupTimerControls();
    void restartUpdateTimer(int ms);
};
#endif // GRAPHWINDOW_H

#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include "videocardcollector.h"
#include <QMainWindow>

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QMainWindow, public VideoCardCollector
{
    Q_OBJECT

public:
    GraphWindow(int gpuIndex, int plotIndex, QWidget *parent = nullptr);
    ~GraphWindow();

private:
    Ui::GraphWindow *ui;

    // Номер використовуваної ідеокарти
    const int gpuIndex;

    // Номер потрібного нам параметру для відображення графіку
    //  * 0 -> load (int) -- Завантаженість
    //  * 1 -> capacity (int) -- Об'єм використаної пам'яті
    //  * 2 -> temp (int) -- Температура
    const int plotIndex;
};

#endif // GRAPHWINDOW_H

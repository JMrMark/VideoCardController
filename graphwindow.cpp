#include "graphwindow.h"
#include "ui_graphwindow.h"

GraphWindow::GraphWindow(int gpuIndex, int plotIndex, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GraphWindow)
    , gpuIndex(gpuIndex)
    , plotIndex(plotIndex)
{
    ui->setupUi(this);

    if (plotIndex == 0){
        setWindowTitle("Using a video card");
    }
    else if (plotIndex == 1){
        setWindowTitle("Amount of memory used");
    }
    else {
        setWindowTitle("Temperature");
    }
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

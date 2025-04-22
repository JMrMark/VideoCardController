#include "cardmode.h"
#include "ui_cardmode.h"
#include <QComboBox>
#include <QPushButton>

CardMode::CardMode(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CardMode)
{
    ui->setupUi(this);

    setWindowTitle("Video Card Mode");
}

CardMode::~CardMode()
{
    delete ui;
}

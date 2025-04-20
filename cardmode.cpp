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

    QComboBox *modeCombo = new QComboBox(this);
    modeCombo->addItem("Performance");
    modeCombo->addItem("Balanced");
    modeCombo->addItem("Power Saving");

    QPushButton *applyModeBtn = new QPushButton("Apply", this);
    connect(applyModeBtn, &QPushButton::clicked, this, [=]() {
        QString selectedMode = modeCombo->currentText();
        //applyPowerMode(selectedMode);
    });
}

CardMode::~CardMode()
{
    delete ui;
}

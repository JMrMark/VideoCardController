#ifndef CARDMODE_H
#define CARDMODE_H

#include <QMainWindow>
#include "videocardcollector.h"

namespace Ui {
class CardMode;
}

class CardMode : public QMainWindow, public VideoCardCollector
{
    Q_OBJECT

public:
    explicit CardMode(QWidget *parent = nullptr);
    ~CardMode();

private:
    Ui::CardMode *ui;
};

#endif // CARDMODE_H

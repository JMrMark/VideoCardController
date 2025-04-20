#ifndef CARDINFO_H
#define CARDINFO_H

#include "videocardcollector.h"
#include "graphwindow.h"
#include <QMainWindow>

namespace Ui {
class cardinfo;
}

class cardinfo : public QMainWindow, public VideoCardCollector
{
    Q_OBJECT

public:
    explicit cardinfo(QWidget *parent = nullptr);
    ~cardinfo();

    // Вивід інформації у користувацьке вікно
    // Ця функція заміняє:
    //  * modelText(ui) -> modelCard(QString)
    //  * driverText(ui) -> driverVersion(QString)
    // NumberOfAskedVideoCard -> номер відеокарти
    // Ця функція викликається лише один раз
    bool ShowMainDataFromVideoCard(int NumberOfAskedVideoCard);

    // Вивід інформації у користувацьке вікно
    // Ця функція заміняє:
    //  * loadText(ui) -> loadCard(int)
    //  * capacityText(ui) -> capacityUsedCard(int) "used of " capacityCard(int)
    //  * tempText(ui) -> tempCard(int)
    // NumberOfAskedVideoCard -> номер відеокарти
    // Викликається постійно для оновлення актуальності інформації
    bool ShowCurrentDataFromVideoCard(int NumberOfAskedVideoCard);

    // Вивід інформації у користувацьке вікно
    // Ця функція заміняє:
    //  * modelText(ui) -> modelCard(QString)
    //  * driverText(ui) -> driverVersion(QString)
    //  * tempText(ui) -> tempCard(int)
    //  * capacityText(ui) -> capacityCard(int)
    bool ShowIntegratedGraphicsCard();

    // Фарбуємо кнопки, які не є доступними користувачу
    void PaintNotAvailableButtons();

    // Розфарбовуємо вибрану кнопку
    void PaintCurrentlySelectedButton();


private slots:
    void on_InfoCard1_b_clicked();

    void on_InfoCard2_b_clicked();

    void on_InfoCard3_b_clicked();

    void on_loadButton_clicked();

    void on_capacityButton_clicked();

    void on_tempButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::cardinfo *ui;

    GraphWindow* graphWindows[3] = {nullptr, nullptr, nullptr};

    // Вибрана відеокарта у даний момент
    // -10 = IntegratedGraphicsCard
    int CurrentVideoCard;

    bool IntegratedGraphicsCard;
};

#endif // CARDINFO_H

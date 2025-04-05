#ifndef CARDINFO_H
#define CARDINFO_H

#include <QMainWindow>

namespace Ui {
class cardinfo;
}

class cardinfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit cardinfo(QWidget *parent = nullptr);
    ~cardinfo();

    // Збільшує кількість відеокард на значення number
    // Якщо number + CounterOfVideoCards > 3, тоді return False
    bool AddVideoCardCounter(int number);

    // Підрахунок кількості відеокарт на пристрої
    // Записує ціле число у змінну CounterOfVideoCards
    bool GetNumberOfVedioCards();

    // Отримання інформації по відеокарті:
    //  * modelCard (QString)
    //  * capacityCard (int)
    //  * driverVersion (QString)
    // NumberOfAskedVideoCard -> номер відеокарти
    // Ця функція викликається лише один раз
    bool GetMainDataFromVideoCard(int NumberOfAskedVideoCard);

    // Постійне отримання даних по відеокарті:
    //  * loadCard (int)
    //  * tempCard (int)
    //  * capacityUsedCard (int)
    // NumberOfAskedVideoCard -> номер відеокарти
    // Викликається постійно для оновлення актуальності інформації
    bool GetCurrentDataFromVideoCard(int NumberOfAskedVideoCard);

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

    // Фарбуємо кнопки, які не є доступними користувачу
    void PaintNotAvailableButtons();


private slots:
    void on_InfoCard1_b_clicked();

    void on_InfoCard2_b_clicked();

    void on_InfoCard3_b_clicked();

private:
    Ui::cardinfo *ui;

    // MIN = 0, MAX = 3
    int CounterOfVideoCards; // Кількість відеокард на пристрої

    QString modelCard; // Модель відеокарти (+)
    int loadCard; // Завантаженість відеокарти (+)
    int tempCard; // Температура відеокарти (+)
    int capacityCard; // Об'єм відеопам'яті (+)
    int capacityUsedCard; // Об'єм використаної відеопам'яті (++)
    QString driverVersion; // Версія драйвера (+)

};

#endif // CARDINFO_H

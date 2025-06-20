#ifndef VIDEOCARDCOLLECTOR_H
#define VIDEOCARDCOLLECTOR_H

#include <QString>
#include <QProcess>
#include <QVector>

class VideoCardCollector
{
private:

    // Збільшує кількість відеокард на значення number
    // Якщо number + CounterOfVideoCards > 3, тоді return False
    bool AddVideoCardCounter(int number);

public:
    VideoCardCollector();

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

    // Оновлення змінної loadCard(int) -- Швидкий спосіб
    bool UpdateCurrentLoadCard(int NumberOfAskedVideoCard, QProcess &process);

    // Оновлення змінної capacityUsedCard(int) -- Швидкий спосіб
    bool UpdateCurrentCapacityUsedCard(int NumberOfAskedVideoCard, QProcess &process);

    // Оновлення змінної tempCard(int) -- Швидкий спосіб
    bool UpdateCurrentTempCard(int NumberOfAskedVideoCard, QProcess &process);

    // Передаємо вектор Data зта записуємо в нього по три значення:
    //  * PID
    //  * name
    //  * memoryUsed
    bool GetLoggerOfVideoCard(QVector<std::string> *Data, QProcess &process);

    // Отримуємо наступні дані про вбудовану відеокарту:
    //  * modelCard (QString)
    //  * capacityCard (int)
    //  * driverVersion (QString)
    //  * tempCard (int)
    bool GetIntegratedGraphicsCard();

    // MIN = 0, MAX = 3
    int CounterOfVideoCards; // Кількість відеокард на пристрої

    QString modelCard; // Модель відеокарти
    int loadCard; // Завантаженість відеокарти
    int tempCard; // Температура відеокарти
    int capacityCard; // Об'єм відеопам'яті
    int capacityUsedCard; // Об'єм використаної відеопам'яті
    QString driverVersion; // Версія драйвера
};

#endif // VIDEOCARDCOLLECTOR_H

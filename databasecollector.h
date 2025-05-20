#ifndef DATABASECOLLECTOR_H
#define DATABASECOLLECTOR_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVector>

class DataBaseCollector
{
public:
    DataBaseCollector();
    ~DataBaseCollector();

    bool saveProfileData(const QString &profileName, int VertSyncS, int AntModeS, int AnisFilteringS,
                         int TextFiltQualityS, int AmbOcculusionS, int PowManagModeS, int TripBufferingS,
                         int ThrOptiS, int CUDAS);

    QVector<int> loadProfileData(const QString &profileName);

private:
    QSqlDatabase db; // Об'єкт для роботи з БД
    void createTable(); // Функція для створення таблиці

};

#endif // DATABASECOLLECTOR_H

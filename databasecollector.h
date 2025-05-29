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

    // **--**

    bool saveProfileData(const QString &profileName, int VertSyncS, int AntModeS, int AnisFilteringS,
                         int TextFiltQualityS, int AmbOcculusionS, int PowManagModeS, int TripBufferingS,
                         int ThrOptiS, int CUDAS);
    QVector<int> loadProfileData(const QString &profileName);

    // **--**

    bool saveApplicationData(const QString &profileName, const QString &application);
    QVector<QString> loadApplicationData(const QString &profileName);
    void clearApplicationData();

    // **--**

    bool saveInformationData(const QString &name, const QString &information);
    QString loadInformationData(const QString &name);

private:
    QSqlDatabase db; // Об'єкт для роботи з БД

    // Таблиця з профілями та їх параметрами
    void createTableProfile();

    // Таблиця з профілями та їх програмами
    void createTableApplication();

    // Таблиця з інформацією для допомоги користувачу
    void createTableInformation();
};

#endif // DATABASECOLLECTOR_H

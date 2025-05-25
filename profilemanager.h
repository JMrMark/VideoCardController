#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include <QMainWindow>
#include <QString>
#include <QVector>
#include "databasecollector.h"

namespace Ui {
class ProfileManager;
}

class ProfileManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProfileManager(QString profile, QWidget *parent = nullptr);
    ~ProfileManager();

    void Interface_Show();

    // Не дивіться на її реалізацію, просто використовуйте :)
    QString Param_GetName(const int &index);

private:
    Ui::ProfileManager *ui;
    QString profile;
    QVector<int> Data;
    DataBaseCollector db;
};

#endif // PROFILEMANAGER_H

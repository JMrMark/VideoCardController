#ifndef LINKINGWINDOW_H
#define LINKINGWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>
#include "../database/databasecollector.h"
#include "nvapi.h"
#include <NvApiDriverSettings.h>

namespace Ui {
class linkingWindow;
}

class linkingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit linkingWindow(QString profile, QWidget *parent = nullptr);
    ~linkingWindow();

    void SetProfile();

    // Не дивіться на її реалізацію, просто використовуйте :)
    QString Param_GetName(const int &index);

    bool Profile_AttachToApplication(const QString &appPath);

    QString Application_GetName(const QString &path);

    void Interface_Make_Red();
    void Interface_Make_Green(const int &index);

private slots:
    void on_button_profileCheck_clicked();

    void on_button_AppCheck_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::linkingWindow *ui;

    DataBaseCollector db;

    QString profile;
    QString application;

    QVector<int> Data;

    QVector<bool> VerFic = {false, false};

    QVector<QString> AppPaths;

    void Application_AddAllAvaliable();
};

#endif // LINKINGWINDOW_H

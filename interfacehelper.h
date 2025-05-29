#ifndef INTERFACEHELPER_H
#define INTERFACEHELPER_H

#include <QMainWindow>
#include <QPushButton>
#include "databasecollector.h"
#include "ui_interfacehelper.h"

namespace Ui {
class InterfaceHelper;
}

class InterfaceHelper : public QMainWindow
{
    Q_OBJECT

public:
    explicit InterfaceHelper(QWidget *parent = nullptr);
    ~InterfaceHelper();

    void update_AllData(bool check);

    void Button_CurrentPaint(QPushButton *buttonNext);

private slots:
    void on_pushButton_VertSync_clicked();

    void on_pushButton_AntMode_clicked();

    void on_pushButton_AnisFiltering_clicked();

    void on_pushButton_TextFiltQuality_clicked();

    void on_pushButton_AmbOcculusion_clicked();

    void on_pushButton_PowManagMode_clicked();

    void on_pushButton_TripBuffering_clicked();

    void on_pushButton_ThrOpti_clicked();

    void on_pushButton_CUDA_clicked();

    void on_pushButton_about_clicked();

    void on_pushButton_works_clicked();

    void on_pushButton_abilities_clicked();

    void on_pushButton_how_clicked();

private:
    Ui::InterfaceHelper *ui;
    DataBaseCollector db;

    QPushButton *buttonNow = nullptr;
};

#endif // INTERFACEHELPER_H

// 0 - VertSync 		Vertical Sync
// 1 - AntMode          Antialiasing Setting
// 2 - AnisFiltering	Anisotropic Filtering
// 3 - TextFiltQuality	Texture Filtering - Quality
// 4 - AmbOcculusion	Ambient Occlusion
// 5 - PowManagMode		Power Management Mode
// 6 - TripBuffering	Triple Buffering
// 7 - ThrOpti          Threaded Optimization
// 8 - CUDA             CUDA - GPUs

#define VERT_SYNC_ID 0x10DE0023

#ifndef CARDMODE_H
#define CARDMODE_H

#include <QMainWindow>
#include <QVector>
#include "nvapi.h"

namespace Ui {
class CardMode;
}

class CardMode : public QMainWindow
{
    Q_OBJECT

public:
    explicit CardMode(QWidget *parent = nullptr);
    ~CardMode();

    // Функція, яка відповідає за скидання змінних до стандартних значень
    // Отримуємо данні з QVector<int> StandartData та вносимо їх у змінні
    bool ResetAllData();

    // Вносить усі данні у віконий інтерфейс
    // Використувує змінні, а не вектор
    bool ShowAllData();

    // Обновлює усі параметри, змінюючи їх у відеокарті
    bool UpdateAllData();

    void find();
    void CreateProfile();
    void ListProfileSettings();
    void DeleteProfile();
    void AddSettingToProfile();
    void AttachApplicationToProfile(const QString &appPath);

    // Add to our profile settings (+)
    void AddVertSyncToProfile();
    void AddAntialiasingModeToProfile();
    void AddAnisotropicFilteringToProfile();
    void AddTextureFilteringToProfile();
    void AddAmbientOcclusionToProfile();
    void AddPowerManagementModeToProfile();
    void AddTripleBufferingToProfile();
    void AddThreadedOptimizationToProfile();
    void AddCUDAtoProfile();
private:
    Ui::CardMode *ui;

    // Перевіряємо данні у QVector<int> StandartData.
    bool SheckAllDataFromNVAPI();

    // Отримуємо дані з NVAPI (+)
    int CollectVertSync();
    int CollectAntMode();
    int CollectAnisFiltering();
    int CollectTextFiltQuality();
    int CollectAmbOcculusion();
    int CollectPowManagMode();
    int CollectTripBuffering();
    int CollectThrOpti();
    int CollectCUDA();

    // Вносимо данні у змінні
    bool SetVertSync(int num);
    bool SetAntMode(int num);
    bool SetAnisFiltering(int num);
    bool SetTextFiltQuality(int num);
    bool SetAmbOcculusion(int num);
    bool SetPowManagMode(int num);
    bool SetTripBuffering(int num);
    bool SetThrOpti(int num);
    bool SetCUDA(int num);

    // Оновлюємо данні у відеокарті, використовуючи змінні
    bool UpdateVertSync();
    bool UpdateAntMode();
    bool UpdateAnisFiltering();
    bool UpdateTextFiltQuality();
    bool UpdateAmbOcculusion();
    bool UpdatePowManagMode();
    bool UpdateTripBuffering();
    bool UpdateThrOpti();
    bool UpdateCUDA();

    QString profileName = "MyProf";

    // Vertical Sync
    // 0 = Вимкнено
    // 1 = Увімкнено
    // 2 = Залежить від 3D-програми
    int VertSync;

    // Antialiasing Mode
    // 0 = Вимк.
    // 1 = 2х
    // 2 = 4х
    // 3 = 8х
    // 4 = 16х
    int AntMode;

    // Anisotropic Filtering
    // 0 = Керування програмою
    // 1 = Примусово 2x, 4x, 8x, 16x
    int AnisFiltering;

    // Texture Filtering - Quality
    // 0 = Висока продуктивність
    // 1 = Продуктивність
    // 2 = Якість
    // 3 = Висока якість
    int TextFiltQuality;

    // Ambient Occlusion
    // 0 = Вимкнено
    // 1 = Увімкнено
    // 2 = Висока якість
    int AmbOcculusion;

    // Power Management Mode
    // 0 = Адаптивний
    // 1 = Максимальна продуктивність
    int PowManagMode;

    // Triple Buffering
    // 0 = Увімкнено
    // 1 = Вимкнено
    int TripBuffering;

    // Threaded Optimization
    // 0 = Авто
    // 1 = Увімкнено
    // 2 = Вимкнено
    int ThrOpti;

    // CUDA - GPUs
    // 0 = Усі
    // 1 = Вибрані
    int CUDA;

    // У цей вектор вносяться стандартні параметри, які використовує пристрій користувача по замовчуванню
    // Не змінювати ні у якому разі!!! Він потрібен для скидання!
    // 0 - VertSync
    // 1 - AntMode
    // 2 - AnisFiltering
    // 3 - TextFiltQuality
    // 4 - AmbOcculusion
    // 5 - PowManagMode
    // 6 - TripBuffering
    // 7 - ThrOpti
    // 8 - CUDA
    QVector<int> StandartData;

};

#endif // CARDMODE_H

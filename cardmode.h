#define VERT_SYNC_ID 0x00A879CF
#define ANT_MODE_ID 0x10D773D2
#define ANIS_FILT_ID 0x101E61A9
#define TEXT_FILT_ID 0x00E73211
#define AMD_OCCUL_ID 0x00667329
#define POW_MAN_ID 0x1057EB71
#define TRIP_BUFF_ID 0x20FDD1F9
#define THR_OPTI_ID 0x20C1221E
#define CUDA_ID 0x10354FF8

#ifndef CARDMODE_H
#define CARDMODE_H

#include <QMainWindow>
#include <QVector>
#include "nvapi.h"
#include <NvApiDriverSettings.h>
#include "databasecollector.h"
#include "linkingwindow.h"
#include "profilemanager.h"

namespace Ui {
class CardMode;
}

class CardMode : public QMainWindow
{
    Q_OBJECT

public:
    explicit CardMode(QWidget *parent = nullptr);
    ~CardMode();

    // Вносить усі данні у віконий інтерфейс
    // Використувує змінні, а не вектор
    bool ShowAllData();

    // Ініціалізує сесію та профіль
    bool StartSessionAndProfile();

    // ---- [ Profile functions ] ----

    // Додаємо усі можливі параметри до профілю та вносимо їх у вектор
    bool Profile_Insert_All_Data();

    // Обновлює усі параметри, змінюючи їх у відеокарті
    bool Profile_Update_All_Data();

    // Вносимо параметри у вектор
    void Profile_Insert_All_Vector();

    // Перевіряємо чи немає некоректних значень
    bool Profile_Check_Vector();

    // Створюємо профіль
    bool Profile_Create();

    // Прив'язуємо профіль до програми
    bool Profile_AttachToApplication(const QString &appPath);

    // Видаляємо профіль
    bool Profile_Delete(QString prof);

    // Додаємо відповідні параметри до профілю
    bool Profile_AddParam(int id, int value = 0);

    // Функція, яка відповідає за скидання змінних до стандартних значень
    // Отримуємо данні з QVector<int> StandartData та вносимо їх у змінні
    bool Profile_Reset_All_Data();

    QVector<QString> Profile_GetConnectedApp();

    // ---- [ Profile functions ] ----

    void find();
    void ListProfileSettings();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_profile_button_clicked();

    void on_connectToApp_clicked();

    void on_pushButton_3_clicked();

    void on_profile_box_currentIndexChanged(int index);

private:
    Ui::CardMode *ui;
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;

    DataBaseCollector db;

    linkingWindow* linkingWindowON[3] = {nullptr, nullptr, nullptr};
    ProfileManager* profileManager[3] = {nullptr, nullptr, nullptr};

    // Отримуємо дані з NVAPI
    int Collect_ParamFromProfile(int id);

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

    bool UpdateData(int value, int id);

    QString profileName = "Profile_1";

    QVector<bool> profileCheck = {true, false, false};
    QVector<bool> profileCheckTwo = {true, true};

    // Vertical Sync (+)
    // 0 = Вимкнено
    // 1 = Увімкнено
    // 2 = Залежить від 3D-програми
    int VertSync;

    // Antialiasing Mode (+)
    // 0  = Вимк.
    // 1  = Автоиатично
    // 2  = 2х (MSAA)
    // 3  = 4х (MSAA)
    // 4  = 8х (MSAA)
    // 5  = 16x (MSAA)
    // 6  = Класичний режим згладжування (SSAA)
    // 7  = 2x (SSAA)
    // 8  = 4x (SSAA)
    // 9  = 8x (SSAA)
    // 10 = 16x (SSAA)
    // 11 = FXAA
    // 12 = TXAA
    // 13 = MFAA
    // 14 = Hybrid (MSAA & SSAA)
    // 15 = Залежить від програми
    int AntMode;

    // Anisotropic Filtering (+)
    // 0 = Вимкнено
    // 1 = 2х
    // 2 = 4x
    // 3 = 8x
    // 4 = 16x
    int AnisFiltering;

    // Texture Filtering - Quality (+)
    // 0 = Автоматично
    // 1 = Висока продуктивність
    // 2 = Продуктивність
    // 3 = Якість
    // 4 = Висока якість
    int TextFiltQuality;

    // Ambient Occlusion (+)
    // 0 = Вимкнено
    // 1 = Примусово
    // 2 = Автоматично
    // 3 = Висока якість
    int AmbOcculusion;

    // Power Management Mode (+)
    // 0 = Адаптивний
    // 1 = Максимальна продуктивність
    int PowManagMode;

    // Triple Buffering
    // 0 = Увімкнено
    // 1 = Вимкнено
    int TripBuffering;

    // Threaded Optimization (+)
    // 0 = Вимкнено
    // 1 = Автоматично
    // 2 = Увімкнено
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

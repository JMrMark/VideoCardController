#include "cardmode.h"
#include "ui_cardmode.h"
#include "nvapi.h"
#include <QMessageBox>
#include <NvApiDriverSettings.h>


CardMode::CardMode(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CardMode)
{
    ui->setupUi(this);

    setWindowTitle("Video Card Settings");

    //qDebug() << CollectVertSync() << " <- Here VertSync";

    //qDebug() << "STARTED";
    //find();
    CreateProfile();
    AttachApplicationToProfile("C:\Users\Артем\Desktop\СПЗ (Курсова)\VideoCardControl\build\Desktop_x86_windows_msvc2019_pe_64bit-Release\VideoCardControl");

    AddVertSyncToProfile();
    AddAntialiasingModeToProfile();
    AddAnisotropicFilteringToProfile();
    AddTextureFilteringToProfile();
    AddAmbientOcclusionToProfile();
    AddPowerManagementModeToProfile();
    AddTripleBufferingToProfile();
    AddThreadedOptimizationToProfile();
    AddCUDAtoProfile();

    ListProfileSettings();

    StandartData = {CollectVertSync()
                    , CollectAntMode()
                    , CollectAnisFiltering()
                    , CollectTextFiltQuality()
                    , CollectAmbOcculusion()
                    , CollectPowManagMode()
                    , CollectTripBuffering()
                    , CollectThrOpti()
                    , CollectCUDA()};

    VertSync = StandartData.at(0);
    AntMode = StandartData.at(1);
    AnisFiltering = StandartData.at(2);
    TextFiltQuality = StandartData.at(3);
    AmbOcculusion = StandartData.at(4);
    PowManagMode = StandartData.at(5);
    TripBuffering = StandartData.at(6);
    ThrOpti = StandartData.at(7);
    CUDA = StandartData.at(8);
    DeleteProfile();
    //sh();
}

CardMode::~CardMode()
{
    delete ui;
}

QString NvUnicodeToQString(const NvAPI_UnicodeString& src) {
    return QString::fromWCharArray(reinterpret_cast<const wchar_t*>(src));
}

void CardMode::AddVertSyncToProfile() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося створити сесію DRS.";
        return;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Пошук профілю за назвою
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Додавання параметра VertSync
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = 0x00A879CF;  // ID для VSYNC
    setting.settingType = NVDRS_DWORD_TYPE;
    setting.u32CurrentValue = 0x1; // 0x1 = Увімкнути V-Sync

    if (NvAPI_DRS_SetSetting(hSession, hProfile, &setting) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося додати VertSync до профілю!";
    } else {
        qDebug() << "✅ VertSync успішно додано до профілю:" << profileName;

    }

    // Збереження змін
    NvAPI_DRS_SaveSettings(hSession);
    NvAPI_DRS_DestroySession(hSession);
}

void CardMode::AddAntialiasingModeToProfile() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося створити сесію DRS.";
        return;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Пошук профілю за назвою
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Додавання параметра Antialiasing Mode
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = 0x10D773D2;  // ID для Antialiasing Mode
    setting.settingType = NVDRS_DWORD_TYPE;
    setting.u32CurrentValue = 0x2; // 0x2 = 2x мультисемплінг (можна змінити)

    if (NvAPI_DRS_SetSetting(hSession, hProfile, &setting) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося додати Antialiasing Mode до профілю!";
    } else {
        qDebug() << "✅ Antialiasing Mode успішно додано до профілю:" << profileName;
    }

    // Збереження змін
    NvAPI_DRS_SaveSettings(hSession);
    NvAPI_DRS_DestroySession(hSession);
}

void CardMode::AddAnisotropicFilteringToProfile() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося створити сесію DRS.";
        return;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Пошук профілю за назвою
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Додавання параметра анізотропної фільтрації
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = 0x101E61A9;  // ID для Anisotropic Filtering
    setting.settingType = NVDRS_DWORD_TYPE;
    setting.u32CurrentValue = 0x4; // 0x4 = 4x анізотропна фільтрація (можна змінити)

    if (NvAPI_DRS_SetSetting(hSession, hProfile, &setting) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося додати Anisotropic Filtering до профілю!";
    } else {
        qDebug() << "✅ Anisotropic Filtering успішно додано до профілю:" << profileName;
    }

    // Збереження змін
    NvAPI_DRS_SaveSettings(hSession);
    NvAPI_DRS_DestroySession(hSession);
}

void CardMode::AddTextureFilteringToProfile() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося створити сесію DRS.";
        return;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Пошук профілю за назвою
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Додавання параметра Texture Filtering
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = 0x00E73211;  // ID для Texture Filtering
    setting.settingType = NVDRS_DWORD_TYPE;
    setting.u32CurrentValue = 0x1; // 0x1 = Оптимізація згладжування текстур (можна змінити)

    if (NvAPI_DRS_SetSetting(hSession, hProfile, &setting) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося додати Texture Filtering до профілю!";
    } else {
        qDebug() << "✅ Texture Filtering успішно додано до профілю:" << profileName;
    }

    // Збереження змін
    NvAPI_DRS_SaveSettings(hSession);
    NvAPI_DRS_DestroySession(hSession);
}

void CardMode::AddAmbientOcclusionToProfile() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося створити сесію DRS.";
        return;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Пошук профілю за назвою
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Додавання параметра Ambient Occlusion
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = 0x00667329;  // ID для Ambient Occlusion
    setting.settingType = NVDRS_DWORD_TYPE;
    setting.u32CurrentValue = 0x2; // 0x2 = Увімкнути AO (можна змінити)

    if (NvAPI_DRS_SetSetting(hSession, hProfile, &setting) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося додати Ambient Occlusion до профілю!";
    } else {
        qDebug() << "✅ Ambient Occlusion успішно додано до профілю:" << profileName;
    }

    // Збереження змін
    NvAPI_DRS_SaveSettings(hSession);
    NvAPI_DRS_DestroySession(hSession);
}

void CardMode::AddPowerManagementModeToProfile() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося створити сесію DRS.";
        return;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Пошук профілю за назвою
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Додавання параметра Power Management Mode
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = 0x1057EB71;  // ID для Power Management Mode
    setting.settingType = NVDRS_DWORD_TYPE;
    setting.u32CurrentValue = 0x1; // 0x1 = Максимальна продуктивність (можна змінити)

    if (NvAPI_DRS_SetSetting(hSession, hProfile, &setting) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося додати Power Management Mode до профілю!";
    } else {
        qDebug() << "✅ Power Management Mode успішно додано до профілю:" << profileName;
    }

    // Збереження змін
    NvAPI_DRS_SaveSettings(hSession);
    NvAPI_DRS_DestroySession(hSession);
}

void CardMode::AddTripleBufferingToProfile() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося створити сесію DRS.";
        return;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Пошук профілю за назвою
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Додавання параметра Triple Buffering
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = 0x20FDD1F9;  // ID для Triple Buffering
    setting.settingType = NVDRS_DWORD_TYPE;
    setting.u32CurrentValue = 0x1; // 0x1 = Увімкнути Triple Buffering

    if (NvAPI_DRS_SetSetting(hSession, hProfile, &setting) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося додати Triple Buffering до профілю!";
    } else {
        qDebug() << "✅ Triple Buffering успішно додано до профілю:" << profileName;
    }

    // Збереження змін
    NvAPI_DRS_SaveSettings(hSession);
    NvAPI_DRS_DestroySession(hSession);
}

void CardMode::AddThreadedOptimizationToProfile() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося створити сесію DRS.";
        return;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Пошук профілю за назвою
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Додавання параметра Threaded Optimization
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = 0x20C1221E;  // ID для Threaded Optimization
    setting.settingType = NVDRS_DWORD_TYPE;
    setting.u32CurrentValue = 0x1; // 0x1 = Автоматичне увімкнення (можна змінити)

    if (NvAPI_DRS_SetSetting(hSession, hProfile, &setting) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося додати Threaded Optimization до профілю!";
    } else {
        qDebug() << "✅ Threaded Optimization успішно додано до профілю:" << profileName;
    }

    // Збереження змін
    NvAPI_DRS_SaveSettings(hSession);
    NvAPI_DRS_DestroySession(hSession);
}

void CardMode::AddCUDAtoProfile() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося створити сесію DRS.";
        return;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Пошук профілю за назвою
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Додавання параметра CUDA
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = 0x10354FF8;  // ID для CUDA
    setting.settingType = NVDRS_DWORD_TYPE;
    setting.u32CurrentValue = 0x0; // 0x0 = Використовувати всі доступні GPU (можна змінити)

    if (NvAPI_DRS_SetSetting(hSession, hProfile, &setting) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося додати CUDA до профілю!";
    } else {
        qDebug() << "✅ CUDA успішно додано до профілю:" << profileName;
    }

    // Збереження змін
    NvAPI_DRS_SaveSettings(hSession);
    NvAPI_DRS_DestroySession(hSession);
}


void CardMode::AttachApplicationToProfile(const QString &appPath) {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося створити сесію DRS.";
        return;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Пошук профілю за назвою
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Створення застосунку в профілі
    NVDRS_APPLICATION app;
    memset(&app, 0, sizeof(app));
    app.version = NVDRS_APPLICATION_VER;
    wcscpy_s((wchar_t*)app.appName, NVAPI_UNICODE_STRING_MAX, appPath.toStdWString().c_str());

    if (NvAPI_DRS_CreateApplication(hSession, hProfile, &app) != NVAPI_OK) {
        qDebug() << "Не вдалося додати програму до профілю!";
    } else {
        qDebug() << "✅ Програму" << appPath << "успішно прив’язано до профілю" << profileName;
    }

    // Збереження змін
    NvAPI_DRS_SaveSettings(hSession);
    NvAPI_DRS_DestroySession(hSession);
}

void CardMode::AddSettingToProfile() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося створити сесію DRS.";
        return;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Пошук профілю за назвою
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Додавання налаштування V-Sync
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = 0x1023d;  // ID налаштування V-Sync
    setting.settingType = NVDRS_DWORD_TYPE;
    setting.u32CurrentValue = 0x0; // 0x1 = Увімкнути V-Sync

    if (NvAPI_DRS_SetSetting(hSession, hProfile, &setting) != NVAPI_OK) {
        qDebug() << "Не вдалося додати налаштування до профілю!";
    } else {
        qDebug() << "Налаштування V-Sync успішно додане!";
    }

    // Збереження змін
    NvAPI_DRS_SaveSettings(hSession);
    NvAPI_DRS_DestroySession(hSession);
}

void CardMode::CreateProfile() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;

    // Ініціалізація NVAPI
    if (NvAPI_Initialize() != NVAPI_OK) {
        qDebug() << "Помилка ініціалізації NVAPI!";
        return;
    }

    // Створення сесії DRS
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося створити сесію DRS.";
        return;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Створення нового профілю
    NVDRS_PROFILE newProfile;
    memset(&newProfile, 0, sizeof(newProfile));
    newProfile.version = NVDRS_PROFILE_VER;
    wcscpy_s((wchar_t*)newProfile.profileName, NVAPI_UNICODE_STRING_MAX, profileName.toStdWString().c_str());

    if (NvAPI_DRS_CreateProfile(hSession, &newProfile, &hProfile) != NVAPI_OK) {
        qDebug() << "Не вдалося створити профіль.";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    qDebug() << "✅ Створено профіль:" << profileName;

    NvAPI_DRS_SaveSettings(hSession);
    NvAPI_DRS_DestroySession(hSession);
}

void CardMode::ListProfileSettings() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;

    // Створення сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося створити сесію DRS.";
        return;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Пошук профілю
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "❌ Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    qDebug() << "🔍 Перелічення можливих налаштувань для профілю:" << profileName;

    // Перелічення налаштувань
    NvU32 settingIndex = 0;
    NvU32 settingsCount = 3;
    NVDRS_SETTING setting;

    while (settingIndex < settingsCount) {
        memset(&setting, 0, sizeof(setting));
        setting.version = NVDRS_SETTING_VER;

        NvAPI_Status status = NvAPI_DRS_EnumSettings(hSession, hProfile, settingIndex, &settingsCount, &setting);
        if (status == NVAPI_END_ENUMERATION) {
            qDebug() << "⚠️ Досягнута межа налаштувань.";
            break;
        }

        if (status != NVAPI_OK) {
            qDebug() << "Помилка отримання параметра на індексі" << settingIndex;
            break;
        }

        qDebug() << "🔧 Налаштування #" << settingIndex
                 << "| ID: 0x" << QString::number(setting.settingId, 16)
                 << "| Значення: 0x" << QString::number(setting.u32CurrentValue, 16)
                 << "| Тип: " << setting.settingType;

        ++settingIndex;
    }

    NvAPI_DRS_DestroySession(hSession);
}

void CardMode::DeleteProfile() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося створити сесію DRS.";
        return;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Пошук профілю за назвою
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return;
    }

    // Видалення профілю
    if (NvAPI_DRS_DeleteProfile(hSession, hProfile) != NVAPI_OK) {
        qDebug() << "Не вдалося видалити профіль.";
    } else {
        qDebug() << "Профіль" << profileName << "успішно видалений.";
    }

    // Збереження змін
    NvAPI_DRS_SaveSettings(hSession);
    NvAPI_DRS_DestroySession(hSession);
}

void CardMode::find(){
    NvDRSSessionHandle hSession;
    NvAPI_DRS_CreateSession(&hSession);
    NvAPI_DRS_LoadSettings(hSession);

    NvU32 profileIndex = 0;
    NvDRSProfileHandle hProfile;
    NVDRS_PROFILE profileInfo;

    while (NvAPI_DRS_EnumProfiles(hSession, profileIndex, &hProfile) == NVAPI_OK) {
        memset(&profileInfo, 0, sizeof(profileInfo));
        profileInfo.version = NVDRS_PROFILE_VER;

        if (NvAPI_DRS_GetProfileInfo(hSession, hProfile, &profileInfo) == NVAPI_OK) {
            if (NvUnicodeToQString(profileInfo.profileName) == "Half life 2"){
                qDebug() << "Profile #" << profileIndex << ": " << NvUnicodeToQString(profileInfo.profileName);
            }
        }
        profileIndex++;
    }

    NvAPI_DRS_DestroySession(hSession);
}

bool CardMode::UpdateAllData(){

    if (UpdateVertSync() ||
        UpdateAntMode() ||
        UpdateAnisFiltering() ||
        UpdateTextFiltQuality() ||
        UpdateAmbOcculusion() ||
        UpdatePowManagMode() ||
        UpdateTripBuffering() ||
        UpdateThrOpti() ||
        UpdateCUDA())
    {
        return true;
    }
    else{
        return false;
    }
}

bool CardMode::SheckAllDataFromNVAPI(){

    if (StandartData.at(0) == -1 ||
        StandartData.at(1) == -1 ||
        StandartData.at(2) == -1 ||
        StandartData.at(3) == -1 ||
        StandartData.at(4) == -1 ||
        StandartData.at(5) == -1 ||
        StandartData.at(6) == -1 ||
        StandartData.at(7) == -1 ||
        StandartData.at(8) == -1)
    {
        return false;
    }
    return true;
}

bool CardMode::ResetAllData(){

    if (!SheckAllDataFromNVAPI()){
        return false;
    }
    else {
        if (SetVertSync(StandartData.at(0)) ||
            SetAntMode(StandartData.at(1)) ||
            SetAnisFiltering(StandartData.at(2)) ||
            SetTextFiltQuality(StandartData.at(3)) ||
            SetAmbOcculusion(StandartData.at(4)) ||
            SetPowManagMode(StandartData.at(5)) ||
            SetTripBuffering(StandartData.at(6)) ||
            SetThrOpti(StandartData.at(7)) ||
            SetCUDA(StandartData.at(8)))
        {
            return true;
        }
        else {
            return false;
        }
    }
}

bool CardMode::SetVertSync(int num){
    if (num < 0 || num > 2){
        qDebug() << "VertSyc was not seted:" << num;
        return false;
    }
    VertSync = num;
    return true;
}
bool CardMode::SetAntMode(int num){
    if (num < 0 || num > 2){
        qDebug() << "AntMode was not seted:" << num;
        return false;
    }
    AntMode = num;
    return true;
}
bool CardMode::SetAnisFiltering(int num){
    if (num < 0 || num > 1){
        qDebug() << "AnisFiltering was not seted:" << num;
        return false;
    }
    AnisFiltering = num;
    return true;
}
bool CardMode::SetTextFiltQuality(int num){
    if (num < 0 || num > 3){
        qDebug() << "TextFiltQuality was not seted:" << num;
        return false;
    }
    TextFiltQuality = num;
    return true;
}
bool CardMode::SetAmbOcculusion(int num){
    if (num < 0 || num > 2){
        qDebug() << "AmbOcculusion was not seted:" << num;
        return false;
    }
    AmbOcculusion = num;
    return true;
}
bool CardMode::SetPowManagMode(int num){
    if (num < 0 || num > 1){
        qDebug() << "PowManagMode was not seted:" << num;
        return false;
    }
    PowManagMode = num;
    return true;
}
bool CardMode::SetTripBuffering(int num){
    if (num < 0 || num > 1){
        qDebug() << "TripBuffering was not seted:" << num;
        return false;
    }
    TripBuffering = num;
    return true;
}
bool CardMode::SetThrOpti(int num){
    if (num < 0 || num > 2){
        qDebug() << "ThrOpti was not seted:" << num;
        return false;
    }
    ThrOpti = num;
    return true;
}
bool CardMode::SetCUDA(int num){
    if (num < 0 || num > 1){
        qDebug() << "CUDA was not seted:" << num;
        return false;
    }
    CUDA = num;
    return true;
}

bool CardMode::UpdateVertSync(){
    return true;
}
bool CardMode::UpdateAntMode(){
    return true;
}
bool CardMode::UpdateAnisFiltering(){
    return true;
}
bool CardMode::UpdateTextFiltQuality(){
    return true;
}
bool CardMode::UpdateAmbOcculusion(){
    return true;
}
bool CardMode::UpdatePowManagMode(){
    return true;
}
bool CardMode::UpdateTripBuffering(){
    return true;
}
bool CardMode::UpdateThrOpti(){
    return true;
}
bool CardMode::UpdateCUDA(){
    return true;
}

int CardMode::CollectVertSync() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;
    NvU32 vertSyncValue = -1; // Значення за замовчуванням (-1 = не знайдено)

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося створити сесію DRS.";
        return vertSyncValue;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return vertSyncValue;
    }

    // Пошук профілю
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "❌ Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return vertSyncValue;
    }

    // Отримання налаштування Vertical Sync
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = 0x00A879CF;  // ID для Vertical Sync

    if (NvAPI_DRS_GetSetting(hSession, hProfile, setting.settingId, &setting) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося отримати параметр Vertical Sync!";
    } else {
        vertSyncValue = setting.u32CurrentValue; // Отримуємо значення
        qDebug() << "✅ Vertical Sync у профілі " << profileName << ": " << vertSyncValue;
    }

    NvAPI_DRS_DestroySession(hSession);
    return vertSyncValue;
}


int CardMode::CollectAntMode() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;
    NvU32 antialiasingValue = -1; // Значення за замовчуванням (-1 = не знайдено)

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося створити сесію DRS.";
        return antialiasingValue;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return antialiasingValue;
    }

    // Пошук профілю
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "❌ Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return antialiasingValue;
    }

    // Отримання налаштування Antialiasing Mode
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = 0x10D773D2;  // ID для Antialiasing Mode

    if (NvAPI_DRS_GetSetting(hSession, hProfile, setting.settingId, &setting) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося отримати параметр Antialiasing Mode!";
    } else {
        antialiasingValue = setting.u32CurrentValue; // Отримуємо значення
        qDebug() << "✅ Antialiasing Mode у профілі " << profileName << ": " << antialiasingValue;
    }

    NvAPI_DRS_DestroySession(hSession);
    return antialiasingValue;
}


int CardMode::CollectAnisFiltering() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;
    NvU32 anisotropicFilteringValue = -1; // Значення за замовчуванням (-1 = не знайдено)

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося створити сесію DRS.";
        return anisotropicFilteringValue;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return anisotropicFilteringValue;
    }

    // Пошук профілю
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "❌ Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return anisotropicFilteringValue;
    }

    // Отримання налаштування Anisotropic Filtering
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = 0x101E61A9;  // ID для Anisotropic Filtering

    if (NvAPI_DRS_GetSetting(hSession, hProfile, setting.settingId, &setting) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося отримати параметр Anisotropic Filtering!";
    } else {
        anisotropicFilteringValue = setting.u32CurrentValue; // Отримуємо значення
        qDebug() << "✅ Anisotropic Filtering у профілі " << profileName << ": " << anisotropicFilteringValue;
    }

    NvAPI_DRS_DestroySession(hSession);
    return anisotropicFilteringValue;
}


int CardMode::CollectTextFiltQuality() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;
    NvU32 textureFilteringValue = -1; // Значення за замовчуванням (-1 = не знайдено)

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося створити сесію DRS.";
        return textureFilteringValue;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return textureFilteringValue;
    }

    // Пошук профілю
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "❌ Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return textureFilteringValue;
    }

    // Отримання налаштування Texture Filtering
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = 0x00E73211;  // ID для Texture Filtering

    if (NvAPI_DRS_GetSetting(hSession, hProfile, setting.settingId, &setting) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося отримати параметр Texture Filtering!";
    } else {
        textureFilteringValue = setting.u32CurrentValue; // Отримуємо значення
        qDebug() << "✅ Texture Filtering у профілі " << profileName << ": " << textureFilteringValue;
    }

    NvAPI_DRS_DestroySession(hSession);
    return textureFilteringValue;
}


int CardMode::CollectAmbOcculusion() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;
    NvU32 ambientOcclusionValue = -1; // Значення за замовчуванням (-1 = не знайдено)

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося створити сесію DRS.";
        return ambientOcclusionValue;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return ambientOcclusionValue;
    }

    // Пошук профілю
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "❌ Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return ambientOcclusionValue;
    }

    // Отримання налаштування Ambient Occlusion
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = 0x00667329;  // ID для Ambient Occlusion

    if (NvAPI_DRS_GetSetting(hSession, hProfile, setting.settingId, &setting) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося отримати параметр Ambient Occlusion!";
    } else {
        ambientOcclusionValue = setting.u32CurrentValue; // Отримуємо значення
        qDebug() << "✅ Ambient Occlusion у профілі " << profileName << ": " << ambientOcclusionValue;
    }

    NvAPI_DRS_DestroySession(hSession);
    return ambientOcclusionValue;
}


int CardMode::CollectPowManagMode() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;
    NvU32 powerManagementValue = -1; // Значення за замовчуванням (-1 = не знайдено)

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося створити сесію DRS.";
        return powerManagementValue;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return powerManagementValue;
    }

    // Пошук профілю
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "❌ Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return powerManagementValue;
    }

    // Отримання налаштування Power Management Mode
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = 0x1057EB71;  // ID для Power Management Mode

    if (NvAPI_DRS_GetSetting(hSession, hProfile, setting.settingId, &setting) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося отримати параметр Power Management Mode!";
    } else {
        powerManagementValue = setting.u32CurrentValue; // Отримуємо значення
        qDebug() << "✅ Power Management Mode у профілі " << profileName << ": " << powerManagementValue;
    }

    NvAPI_DRS_DestroySession(hSession);
    return powerManagementValue;
}


int CardMode::CollectTripBuffering() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;
    NvU32 tripleBufferingValue = -1; // Значення за замовчуванням (-1 = не знайдено)

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося створити сесію DRS.";
        return tripleBufferingValue;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return tripleBufferingValue;
    }

    // Пошук профілю
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "❌ Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return tripleBufferingValue;
    }

    // Отримання налаштування Triple Buffering
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = 0x20FDD1F9;  // ID для Triple Buffering

    if (NvAPI_DRS_GetSetting(hSession, hProfile, setting.settingId, &setting) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося отримати параметр Triple Buffering!";
    } else {
        tripleBufferingValue = setting.u32CurrentValue; // Отримуємо значення
        qDebug() << "✅ Triple Buffering у профілі " << profileName << ": " << tripleBufferingValue;
    }

    NvAPI_DRS_DestroySession(hSession);
    return tripleBufferingValue;
}


int CardMode::CollectThrOpti() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;
    NvU32 threadedOptimizationValue = -1; // Значення за замовчуванням (-1 = не знайдено)

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося створити сесію DRS.";
        return threadedOptimizationValue;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return threadedOptimizationValue;
    }

    // Пошук профілю
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "❌ Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return threadedOptimizationValue;
    }

    // Отримання налаштування Threaded Optimization
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = 0x20C1221E;  // ID для Threaded Optimization

    if (NvAPI_DRS_GetSetting(hSession, hProfile, setting.settingId, &setting) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося отримати параметр Threaded Optimization!";
    } else {
        threadedOptimizationValue = setting.u32CurrentValue; // Отримуємо значення
        qDebug() << "✅ Threaded Optimization у профілі " << profileName << ": " << threadedOptimizationValue;
    }

    NvAPI_DRS_DestroySession(hSession);
    return threadedOptimizationValue;
}


int CardMode::CollectCUDA() {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;
    NvU32 cudaValue = -1; // Значення за замовчуванням (-1 = не знайдено)

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося створити сесію DRS.";
        return cudaValue;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return cudaValue;
    }

    // Пошук профілю
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "❌ Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return cudaValue;
    }

    // Отримання налаштування CUDA
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = 0x10354FF8;  // ID для CUDA

    if (NvAPI_DRS_GetSetting(hSession, hProfile, setting.settingId, &setting) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося отримати параметр CUDA!";
    } else {
        cudaValue = setting.u32CurrentValue; // Отримуємо значення
        qDebug() << "✅ CUDA у профілі " << profileName << ": " << cudaValue;
    }

    NvAPI_DRS_DestroySession(hSession);
    return cudaValue;
}



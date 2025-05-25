#include "cardmode.h"
#include "ui_cardmode.h"
#include "nvapi.h"
#include <QMessageBox>
#include <NvApiDriverSettings.h>
#include <QComboBox>


CardMode::CardMode(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CardMode)
{
    ui->setupUi(this);

    setWindowTitle("Video Card Settings");
    ui->profile_label->setText("Обраний профіль: Профіль 1");

    if(StartSessionAndProfile()){
        if (!Profile_Create())
        {
            qDebug() << "[ERROR] Profile is not active!";
        }
        else {
            if (Profile_Insert_All_Data()){
                qDebug() << "Success!!!";
            }
            else {
                qDebug() << "[ERROR] Data is not inserted!";
            }
        }
    }
    else {
        qDebug() << "[CRITICAL ERROR] NVAPI is not initialized!";
    }
}

CardMode::~CardMode()
{

    if (profileCheck[0]){
        Profile_Delete("Profile_1");
    }

    if (profileCheck[1]){
        Profile_Delete("Profile_2");
    }

    if (profileCheck[2]){
        Profile_Delete("Profile_3");
    }

    db.clearApplicationData();

    NvAPI_DRS_DestroySession(hSession);
    delete ui;
}

QString NvUnicodeToQString(const NvAPI_UnicodeString& src) {
    return QString::fromWCharArray(reinterpret_cast<const wchar_t*>(src));
}

bool CardMode::Profile_Insert_All_Data(){

    if (!Profile_AddParam(VERT_SYNC_ID) ||
        !Profile_AddParam(ANT_MODE_ID)  ||
        !Profile_AddParam(ANIS_FILT_ID) ||
        !Profile_AddParam(TEXT_FILT_ID) ||
        !Profile_AddParam(AMD_OCCUL_ID) ||
        !Profile_AddParam(POW_MAN_ID)   ||
        !Profile_AddParam(TRIP_BUFF_ID) ||
        !Profile_AddParam(THR_OPTI_ID)  ||
        !Profile_AddParam(CUDA_ID))
    {
        qDebug() << "Error with adding parameters to profile!";
        return false;
    }
    else {
        Profile_Insert_All_Vector();
        if (!Profile_Check_Vector()){
            qDebug() << "[Error] Some value in StandartData vector is equal to -1";
            return false;
        }
        else {
            StandartData = db.loadProfileData(profileName);
            VertSync = StandartData.at(0);
            AntMode = StandartData.at(1);
            AnisFiltering = StandartData.at(2);
            TextFiltQuality = StandartData.at(3);
            AmbOcculusion = StandartData.at(4);
            PowManagMode = StandartData.at(5);
            TripBuffering = StandartData.at(6);
            ThrOpti = StandartData.at(7);
            CUDA = StandartData.at(8);

            ui->VertSync_box->setCurrentIndex(VertSync);
            ui->AntMode_box->setCurrentIndex(AntMode);
            ui->AnisFiltering_box->setCurrentIndex(AnisFiltering);
            ui->TextFiltQuality_box->setCurrentIndex(TextFiltQuality);
            ui->AmbOcculusion_box->setCurrentIndex(AmbOcculusion);
            ui->PowManagMode_box->setCurrentIndex(PowManagMode);
            ui->TripBuffering_box->setCurrentIndex(TripBuffering);
            ui->ThrOpti_box->setCurrentIndex(ThrOpti);
            ui->CUDA_box->setCurrentIndex(CUDA);
            return true;
        }
    }
}

bool CardMode::StartSessionAndProfile(){
    if (NvAPI_Initialize() != NVAPI_OK) {
        qDebug() << "Помилка ініціалізації NVAPI!";
        return false;
    }

    // Створення та завантаження сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося створити сесію DRS.";
        return false;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return false;
    }
    return true;
}

void CardMode::Profile_Insert_All_Vector(){
    StandartData = {Collect_ParamFromProfile(VERT_SYNC_ID)
                  , Collect_ParamFromProfile(ANT_MODE_ID)
                  , Collect_ParamFromProfile(ANIS_FILT_ID)
                  , Collect_ParamFromProfile(TEXT_FILT_ID)
                  , Collect_ParamFromProfile(AMD_OCCUL_ID)
                  , Collect_ParamFromProfile(POW_MAN_ID)
                  , Collect_ParamFromProfile(TRIP_BUFF_ID)
                  , Collect_ParamFromProfile(THR_OPTI_ID)
                  , Collect_ParamFromProfile(CUDA_ID)};
}

bool CardMode::Profile_AddParam(int id, int value){
    // Пошук профілю за назвою
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return false;
    }

    // Додавання параметра VertSync
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = id;
    setting.settingType = NVDRS_DWORD_TYPE;
    setting.u32CurrentValue = value;

    if (NvAPI_DRS_SetSetting(hSession, hProfile, &setting) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося додати " << id << " до профілю!";
        return false;
    } else {
        qDebug() << id << " успішно додано до профілю:" << profileName;
    }

    // Збереження змін
    NvAPI_DRS_SaveSettings(hSession);
    return true;
}

bool CardMode::Profile_AttachToApplication(const QString &appPath) {
    // Пошук профілю за назвою
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return false;
    }

    // Створення застосунку в профілі
    NVDRS_APPLICATION app;
    memset(&app, 0, sizeof(app));
    app.version = NVDRS_APPLICATION_VER;
    wcscpy_s((wchar_t*)app.appName, NVAPI_UNICODE_STRING_MAX, appPath.toStdWString().c_str());

    if (NvAPI_DRS_CreateApplication(hSession, hProfile, &app) != NVAPI_OK) {
        qDebug() << "Не вдалося додати програму до профілю!";
        return false;
    } else {
        qDebug() << "✅ Програму" << appPath << "успішно прив’язано до профілю" << profileName;
    }

    // Збереження змін
    NvAPI_DRS_SaveSettings(hSession);
    return true;
}

bool CardMode::Profile_Create() {

    // Створення нового профілю
    NVDRS_PROFILE newProfile;
    memset(&newProfile, 0, sizeof(newProfile));
    newProfile.version = NVDRS_PROFILE_VER;
    wcscpy_s((wchar_t*)newProfile.profileName, NVAPI_UNICODE_STRING_MAX, profileName.toStdWString().c_str());

    if (NvAPI_DRS_CreateProfile(hSession, &newProfile, &hProfile) != NVAPI_OK) {
        qDebug() << "Не вдалося створити профіль.";
        NvAPI_DRS_DestroySession(hSession);
        return false;
    }

    qDebug() << "✅ Створено профіль:" << profileName;

    NvAPI_DRS_SaveSettings(hSession);
    return true;
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

bool CardMode::Profile_Delete(QString prof) {

    // Пошук профілю за назвою
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, prof.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "Профіль" << prof << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return false;
    }

    // Видалення профілю
    if (NvAPI_DRS_DeleteProfile(hSession, hProfile) != NVAPI_OK) {
        qDebug() << "Не вдалося видалити профіль.";
        return false;
    } else {
        qDebug() << "Профіль" << prof << "успішно видалений.";
    }

    // Збереження змін
    NvAPI_DRS_SaveSettings(hSession);
    return true;
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

bool CardMode::Profile_Update_All_Data(){

    if (UpdateData(VertSync, VERT_SYNC_ID) &&
        UpdateData(AntMode, ANT_MODE_ID) &&
        UpdateData(AnisFiltering, ANIS_FILT_ID) &&
        UpdateData(TextFiltQuality, TEXT_FILT_ID) &&
        UpdateData(AmbOcculusion, AMD_OCCUL_ID) &&
        UpdateData(PowManagMode, POW_MAN_ID) &&
        UpdateData(TripBuffering, TRIP_BUFF_ID) &&
        UpdateData(ThrOpti, THR_OPTI_ID) &&
        UpdateData(CUDA, CUDA_ID))
    {
        return true;
    }
    else{
        return false;
    }
}

bool CardMode::Profile_Check_Vector(){

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

bool CardMode::Profile_Reset_All_Data(){

    if (!Profile_Check_Vector()){
        return false;
    }
    else {
        if (SetVertSync(StandartData.at(0)) &&
            SetAntMode(StandartData.at(1)) &&
            SetAnisFiltering(StandartData.at(2)) &&
            SetTextFiltQuality(StandartData.at(3)) &&
            SetAmbOcculusion(StandartData.at(4)) &&
            SetPowManagMode(StandartData.at(5)) &&
            SetTripBuffering(StandartData.at(6)) &&
            SetThrOpti(StandartData.at(7)) &&
            SetCUDA(StandartData.at(8)))
        {
            qDebug() << "Reset data is success!";
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
    if (num < 0 || num > 15){
        qDebug() << "AntMode was not seted:" << num;
        return false;
    }
    AntMode = num;
    return true;
}
bool CardMode::SetAnisFiltering(int num){
    if (num < 0 || num > 4){
        qDebug() << "AnisFiltering was not seted:" << num;
        return false;
    }
    AnisFiltering = num;
    return true;
}
bool CardMode::SetTextFiltQuality(int num){
    if (num < 0 || num > 4){
        qDebug() << "TextFiltQuality was not seted:" << num;
        return false;
    }
    TextFiltQuality = num;
    return true;
}
bool CardMode::SetAmbOcculusion(int num){
    if (num < 0 || num > 3){
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

bool CardMode::UpdateData(int value, int id){
    // Пошук профілю
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "❌ Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return false;
    }

    // Отримання налаштування
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = id;

    if (NvAPI_DRS_GetSetting(hSession, hProfile, setting.settingId, &setting) != NVAPI_OK) {
        qDebug() << "❌ Не вдалося оновити параметр Vertical Sync!";
        return false;
    } else {
        if (value != -1) {
            setting.u32CurrentValue = value;
            qDebug() << id << "\t(змінено) у профілі\t" << profileName << ":\t" << setting.u32CurrentValue;
        }
        else { // VertSync == -1
            qDebug() << "Erorr value: VertSync == -1!";
            return false;
        }
    }
    NvAPI_DRS_SaveSettings(hSession);
    return true;
}

int CardMode::Collect_ParamFromProfile(int id){
    NvU32 value = -1; // Значення за замовчуванням (-1 = не знайдено)

    // Пошук профілю
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profileName.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "❌ Профіль" << profileName << "не знайдено!";
        NvAPI_DRS_DestroySession(hSession);
        return value;
    }

    // Отримання налаштування id
    NVDRS_SETTING setting;
    memset(&setting, 0, sizeof(setting));
    setting.version = NVDRS_SETTING_VER;
    setting.settingId = id;

    if (NvAPI_DRS_GetSetting(hSession, hProfile, setting.settingId, &setting) != NVAPI_OK) {
        qDebug() << "Не вдалося отримати параметр:" << id;
    } else {
        value = setting.u32CurrentValue; // Отримуємо значення
        qDebug() << id << " у профілі " << profileName << ": " << value;
    }

    return value;
}

void CardMode::on_pushButton_clicked()
{
    // Отримуємо значення profileName

    Profile_Reset_All_Data();
    Profile_Update_All_Data();

    db.saveProfileData(profileName, VertSync, AntMode, AnisFiltering, TextFiltQuality, AmbOcculusion, PowManagMode, TripBuffering, ThrOpti, CUDA);

    // Оновлюємо інтерфейс
    ui->VertSync_box->setCurrentIndex(VertSync);
    ui->AntMode_box->setCurrentIndex(AntMode);
    ui->AnisFiltering_box->setCurrentIndex(AnisFiltering);
    ui->TextFiltQuality_box->setCurrentIndex(TextFiltQuality);
    ui->AmbOcculusion_box->setCurrentIndex(AmbOcculusion);
    ui->PowManagMode_box->setCurrentIndex(PowManagMode);
    ui->TripBuffering_box->setCurrentIndex(TripBuffering);
    ui->ThrOpti_box->setCurrentIndex(ThrOpti);
    ui->CUDA_box->setCurrentIndex(CUDA);
}


void CardMode::on_pushButton_2_clicked()
{
    int index = ui->profile_box->currentIndex();
    profileName = "Profile_" + QString::number(index + 1);

    // Отримуємо значення profileName
    VertSync = ui->VertSync_box->currentIndex();
    AntMode = ui->AntMode_box->currentIndex();
    AnisFiltering = ui->AnisFiltering_box->currentIndex();
    TextFiltQuality = ui->TextFiltQuality_box->currentIndex();
    AmbOcculusion = ui->AmbOcculusion_box->currentIndex();
    PowManagMode = ui->PowManagMode_box->currentIndex();
    TripBuffering = ui->TripBuffering_box->currentIndex();
    ThrOpti = ui->ThrOpti_box->currentIndex();
    CUDA = ui->CUDA_box->currentIndex();


    // Отримуємо значення від користувача (параметри)

    Profile_Update_All_Data();

    db.saveProfileData(profileName, VertSync, AntMode, AnisFiltering, TextFiltQuality, AmbOcculusion, PowManagMode, TripBuffering, ThrOpti, CUDA);

}

// Кнопка обирання профілю
void CardMode::on_profile_button_clicked()
{
    int index = ui->profile_box->currentIndex();
    profileName = "Profile_" + QString::number(index + 1);

    if (index == 0){
        ui->profile_label->setText("Обраний профіль: Профіль 1");
        Profile_Insert_All_Data();
    }
    else if (index == 1){
        ui->profile_label->setText("Обраний профіль: Профіль 2");
        if (profileCheckTwo[0]){
            profileCheckTwo[0] = false;
            profileCheck[1] = true;
            Profile_Create();
        }
        Profile_Insert_All_Data();
    }
    else {
        ui->profile_label->setText("Обраний профіль: Профіль 3");
        if (profileCheckTwo[1]){
            profileCheckTwo[1] = false;
            profileCheck[2] = true;
            Profile_Create();
        }
        Profile_Insert_All_Data();
    }
    qDebug() << "Обрано профіль: " << profileName;
    QVector<QString> result = Profile_GetConnectedApp();
}


void CardMode::on_connectToApp_clicked()
{

    int gpuIndex;
    if (profileName == "Profile_1"){
        gpuIndex = 0;
    }
    else if (profileName == "Profile_2"){
        gpuIndex = 1;
    }
    else if (profileName == "Profile_3"){
        gpuIndex = 2;
    }
    else {
        return;
    }

    if (!linkingWindowON[gpuIndex]) {
        linkingWindowON[gpuIndex] = new linkingWindow(profileName);
        linkingWindowON[gpuIndex]->setAttribute(Qt::WA_DeleteOnClose);

        connect(linkingWindowON[gpuIndex], &linkingWindow::destroyed, this, [=]() {
            linkingWindowON[gpuIndex] = nullptr;
        });

        linkingWindowON[gpuIndex]->show();
    } else {
        linkingWindowON[gpuIndex]->raise();
        linkingWindowON[gpuIndex]->activateWindow();
    }
}

QVector<QString> CardMode::Profile_GetConnectedApp() {
    QVector<QString> appNames; // Вектор для збереження назв програм

    return appNames;
}

// Детальніше
void CardMode::on_pushButton_3_clicked()
{
    int gpuIndex;
    if (profileName == "Profile_1"){
        gpuIndex = 0;
    }
    else if (profileName == "Profile_2"){
        gpuIndex = 1;
    }
    else if (profileName == "Profile_3"){
        gpuIndex = 2;
    }
    else {
        return;
    }

    if (!profileManager[gpuIndex]) {
        profileManager[gpuIndex] = new ProfileManager(profileName);
        profileManager[gpuIndex]->setAttribute(Qt::WA_DeleteOnClose);

        connect(profileManager[gpuIndex], &ProfileManager::destroyed, this, [=]() {
            profileManager[gpuIndex] = nullptr;
        });

        profileManager[gpuIndex]->show();
    } else {
        profileManager[gpuIndex]->raise();
        profileManager[gpuIndex]->activateWindow();
    }
}


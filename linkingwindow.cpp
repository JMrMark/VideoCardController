#include <QRegularExpression>
#include <QMessageBox>
#include "linkingwindow.h"
#include "ui_linkingwindow.h"

linkingWindow::linkingWindow(QString profile, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::linkingWindow)
    , profile(profile)
{
    ui->setupUi(this);
    setWindowTitle("Profile to Application");

    SetProfile();

    Application_AddAllAvaliable();
}

linkingWindow::~linkingWindow()
{
    delete ui;
}

void linkingWindow::SetProfile(){
    if (profile == "Profile_1"){
        ui->label_profileName->setText("Профіль 1");
    }
    else if (profile == "Profile_2"){
        ui->label_profileName->setText("Профіль 2");
    }
    else {
        ui->label_profileName->setText("Профіль 3");
    }
}

void linkingWindow::on_button_profileCheck_clicked()
{
    Data = db.loadProfileData(profile);

    ui->label_VertSync->setText(Param_GetName(0));
    ui->label_AntMode->setText(Param_GetName(1));
    ui->label_AnisFiltering->setText(Param_GetName(2));
    ui->label_TextFiltQuality->setText(Param_GetName(3));
    ui->label_AmbOcculusion->setText(Param_GetName(4));
    ui->label_PowManagMode->setText(Param_GetName(5));
    ui->label_TripBuffering->setText(Param_GetName(6));
    ui->label_ThrOpti->setText(Param_GetName(7));
    ui->label_CUDA->setText(Param_GetName(8));

    VerFic[0] = true;
}

bool linkingWindow::Profile_AttachToApplication(const QString &appPath) {
    NvDRSSessionHandle hSession;
    NvDRSProfileHandle hProfile;

    // Створення сесії
    if (NvAPI_DRS_CreateSession(&hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося створити сесію DRS.";
        return false;
    }

    if (NvAPI_DRS_LoadSettings(hSession) != NVAPI_OK) {
        qDebug() << "Не вдалося завантажити налаштування.";
        NvAPI_DRS_DestroySession(hSession);
        return false;
    }

    // Пошук профілю за назвою
    NvU16 profileNameBuffer[256];
    wcscpy_s((wchar_t*)profileNameBuffer, 256, profile.toStdWString().c_str());

    if (NvAPI_DRS_FindProfileByName(hSession, profileNameBuffer, &hProfile) != NVAPI_OK) {
        qDebug() << "Профіль" << profile << "не знайдено!";
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
        qDebug() << "✅ Програму" << appPath << "успішно прив’язано до профілю" << profile;
    }

    // Збереження змін
    NvAPI_DRS_SaveSettings(hSession);
    return true;
}

QString linkingWindow::Application_GetName(const QString &path){
    return path.split(QRegularExpression("[\\\\/]"), Qt::SkipEmptyParts).last();
}

void linkingWindow::Application_AddAllAvaliable(){

    ui->comboBox_pathToApp->addItem("Не обрано");

    AppPaths.append("C:\\Users\\Артем\\Desktop\\СПЗ (Курсова)\\VideoCardControl\\build\\Desktop_x86_windows_msvc2019_pe_64bit-Release\\VideoCardControl");
    AppPaths.append("E:\\Far Cry 3\\bin\\FC3Updater");

    for (auto &app : AppPaths){
        ui->comboBox_pathToApp->addItem(Application_GetName(app));
    }
}

void linkingWindow::on_button_AppCheck_clicked()
{
    if (ui->lineEdit_pathToApp->text().isEmpty()){
        int index = ui->comboBox_pathToApp->currentIndex();
        if (index == 0){
            QMessageBox::critical(this, "Помилка", "⚠️ Ви не обрали жодну з програм!");
        }
        else {
            index--;
            application = AppPaths.at(index);
            ui->label_programName->setText(Application_GetName(application));
            VerFic[1] = true;
        }
    }
    else {
        application = ui->lineEdit_pathToApp->text();
        ui->label_programName->setText(Application_GetName(application));
        VerFic[1] = true;
    }
}


void linkingWindow::on_pushButton_2_clicked()
{
    if (VerFic.at(0) && VerFic.at(1)){
        if (!Profile_AttachToApplication(application)){
            QMessageBox::critical(this, "Помилка", "⚠️ Профіль не було під'єднано до програми");
        }
        else {
            QMessageBox::information(this, "Успіх", "Профіль було успішно під'єднано до програми");
            this->deleteLater();
        }
    }
    else if (!VerFic.at(0)){
        QMessageBox::critical(this, "Помилка", "⚠️ Ви не підтвердили данні профіль!");
    }
    else {
        QMessageBox::critical(this, "Помилка", "⚠️ Ви не вказали програму!");
    }
}

QString linkingWindow::Param_GetName(const int &index){

    if (index == 0){

        if (Data.at(index) == 0){
            return "Вимкнено";
        }
        else if (Data.at(index) == 1){
            return "Увімкнено";
        }
        else {
            return "Залежить";
        }

    }
    else if (index == 1){

        if (Data.at(index) == 0){
            return "Вимкнено";
        }
        else if (Data.at(index) == 1){
            return "Автоматично";
        }
        else if (Data.at(index) == 2){
            return "2х (MSAA)";
        }
        else if (Data.at(index) == 3){
            return "4х (MSAA)";
        }
        else if (Data.at(index) == 4){
            return "8х (MSAA)";
        }
        else if (Data.at(index) == 5){
            return "16х (MSAA)";
        }
        else if (Data.at(index) == 6){
            return "SSAA";
        }
        else if (Data.at(index) == 7){
            return "2x (SSAA)";
        }
        else if (Data.at(index) == 8){
            return "4x (SSAA)";
        }
        else if (Data.at(index) == 9){
            return "8x (SSAA)";
        }
        else if (Data.at(index) == 10){
            return "16x (SSAA)";
        }
        else if (Data.at(index) == 11){
            return "FXAA";
        }
        else if (Data.at(index) == 12){
            return "TXAA";
        }
        else if (Data.at(index) == 13){
            return "MFAA";
        }
        else if (Data.at(index) == 14){
            return "MSAA & SSAA";
        }
        else {
            return "Залежить";
        }

    }
    else if (index == 2){

        if (Data.at(index) == 0){
            return "Вимкнено";
        }
        else if (Data.at(index) == 1){
            return "2х";
        }
        else if (Data.at(index) == 2){
            return "4х";
        }
        else if (Data.at(index) == 3){
            return "8х";
        }
        else {
            return "16х";
        }

    }
    else if (index == 3){

        if (Data.at(index) == 0){
            return "Автоматично";
        }
        else if (Data.at(index) == 1){
            return "Висока продуктивність";
        }
        else if (Data.at(index) == 2){
            return "Продуктивність";
        }
        else if (Data.at(index) == 3){
            return "Якість";
        }
        else {
            return "Висока якість";
        }

    }
    else if (index == 4){

        if (Data.at(index) == 0){
            return "Вимкнено";
        }
        else if (Data.at(index) == 1){
            return "Примусово";
        }
        else if (Data.at(index) == 2){
            return "Автоматично";
        }
        else {
            return "Висока якість";
        }

    }
    else if (index == 5){

        if (Data.at(index) == 0){
            return "Адаптивний";
        }
        else {
            return "Макс. продуктивність";
        }

    }
    else if (index == 6){

        if (Data.at(index) == 0){
            return "Увімкнено";
        }
        else {
            return "Вимкнено";
        }

    }
    else if (index == 7){

        if (Data.at(index) == 0){
            return "Вимкнено";
        }
        else if (Data.at(index) == 1){
            return "Автоматично";
        }
        else {
            return "Увімкнено";
        }

    }
    else { // 8

        if (Data.at(index) == 0){
            return "Усі";
        }
        else {
            return "Вибрані";
        }

    }
}

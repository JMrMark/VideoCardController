#include "profilemanager.h"
#include "interface/ui_profilemanager.h"

ProfileManager::ProfileManager(QString profile, QWidget *parent)
    : QMainWindow(parent)
    , profile(profile)
    , ui(new Ui::ProfileManager)
{
    ui->setupUi(this);

    Interface_Show();
}

ProfileManager::~ProfileManager()
{
    delete ui;
}

void ProfileManager::Interface_Show(){

    if (profile == "Profile_1"){
        ui->label_profileName->setText("Профіль 1");
    }
    else if (profile == "Profile_2") {
        ui->label_profileName->setText("Профіль 2");
    }
    else {
        ui->label_profileName->setText("Профіль 3");
    }


    QVector<QString> data = db.loadApplicationData(profile);

    if (data.empty()){
        ui->label_appUsed->setText("Немає підв'язаних програм");
    }
    else {
        QString message;
        for (auto &el : data) {
            if (!message.isEmpty()) {
                message += ", ";
            }
            message += el;
        }

        ui->label_appUsed->setText(message);
    }

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

}

QString ProfileManager::Param_GetName(const int &index){

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

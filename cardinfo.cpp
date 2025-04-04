#include "cardinfo.h"
#include "ui_cardinfo.h"

cardinfo::cardinfo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cardinfo)
{
    ui->setupUi(this);
    setWindowTitle("Video Card Information");
}

cardinfo::~cardinfo()
{
    delete ui;
}

bool cardinfo::AddVideoCardCounter(int number){
    int temp = number + CounterOfVideoCards;
    if (temp > 3 || temp <= 0){
        return false;
    }
    CounterOfVideoCards = temp;
    return true;
}

bool cardinfo::GetNumberOfVedioCards(){

    // Отримуємо кількість відеокарт та записуємо у result ***

    int result = 0;
    if (AddVideoCardCounter(result)){
        return true;
    }
    qDebug("More than 3 video cards");
    return false;
}

bool cardinfo::GetMainDataFromVideoCard(){

    // Отримуємо інформацію по відеокарті на записуємо їх у modelCard(QString), capacityCard (int) та driverVersion (int)
    return true;
}

bool cardinfo::GetCurrentDataFromVideoCard(){

    // Отримуємо інформацію по відеокарті на записуємо їх у loadCard(int), tempCard(int) та capacityUsedCard(int)
    return true;
}

void cardinfo::on_InfoCard1_b_clicked()
{
    // Перша відеокарта
}


void cardinfo::on_InfoCard2_b_clicked()
{
    // Друга відеокарта
}


void cardinfo::on_InfoCard3_b_clicked()
{
    // Третя відеокарта
}


#include "interfacehelper.h"
#include "interface/ui_interfacehelper.h"
#include <QDebug>

InterfaceHelper::InterfaceHelper(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InterfaceHelper)
{
    ui->setupUi(this);
    setWindowTitle("Helper");

    update_AllData(true);

    ui->label_main->setWordWrap(true);

    ui->label_main->setText(db.loadInformationData("about"));
    ui->pushButton_about->setStyleSheet("background-color: #78f5e9;");
    buttonNow = ui->pushButton_about;
}

void InterfaceHelper::update_AllData(bool check){
    if (check){
        qDebug() << "Початок завантаження даних --||";
        db.saveInformationData("VertSync", "Vertical Sync (VSync) - це технологія, яка синхронізує частоту кадрів (FPS) у відеограмах з частотою оновлення екрана монітора, що допомагає уникнути розривів зображення (tearing). Вона дозволяє уникнути розривів, коли один кадр частково відображається на екрані, поки решта кадру ще не виведена, що може призвести до незручностей для користувача.");
        db.saveInformationData("AntMode", "Antialiasing Setting (Згладжування) в іграх — це функція, яка зменшує \"зубчастість\" або \"лест\" на краях об'єктів, роблячи зображення більш плавним і природним. Це досягається шляхом обробки зображення для пом'якшення цих країв. Antialiasing використовується в іграх та інших програмах, що генерують зображення, щоб поліпшити якість зображення та усунути візуальні артефакти.");
        db.saveInformationData("AnisFiltering", "Анізотропний фільтр (Anisotropic Filtering, AF) - це техніка, яка поліпшує якість текстур у 3D-графіці, особливо на поверхнях, що значно нахилені відносно камери. Він робить текстури більш чіткими і деталізованими, зменшуючи розмиття та ефекти накладання пікселів (aliasing), які можуть виникати при великих кутах огляду.");
        db.saveInformationData("TextFiltQuality", "Texture Filtering - Quality - це параметр в налаштуваннях відеокарти (наприклад, у NVIDIA Control Panel), який дозволяє налаштувати якість фільтрації текстур для кращого зображення у грі. Цей параметр впливає на чіткість та деталізацію текстур.");
        db.saveInformationData("AmbOcculusion", "Ambient occlusion (AO) — модель затінення, яка використовується в тривимірній графіці і дозволяє додати реалістичності зображення шляхом обчислення інтенсивності світла, що доходить до точки поверхні. На відміну від локальних методів, як, наприклад, затемнення за Фонгом, ambient occlusion є глобальним методом, тобто значення яскравості кожної точки об'єкта залежить від інших об'єктів сцени. В принципі, це досить віддалено нагадує глобальне освітлення.");
        db.saveInformationData("PowManagMode", "Power Management Mode (Режим керування енергією) - це функція в BIOS або UEFI, яка дозволяє вам налаштувати, як ваш комп'ютер буде використовувати енергію. Це дає вам контроль над споживанням енергії, що може допомогти збільшити тривалість роботи від батареї на ноутбуках та знизити енерговитрати загалом.");
        db.saveInformationData("TripBuffering", "Тріпл-буферинг (Triple Buffering) - це метод обробки графіки в комп'ютерах, який використовує три буфери для відображення зображення на екрані. Він призначений для зменшення або уникнення артефактів (наприклад, розривів зображення), а також для підвищення швидкості відображення.");
        db.saveInformationData("ThrOpti", "Threaded Optimization (Потокова оптимізація) - це процес оптимізації програми або системи для використання множинних потоків (threads) процесора одночасно. Це допомагає збільшити продуктивність та ефективність, особливо коли програма виконує роботи, які можна паралелізувати (розбити на частини, які можна виконувати одночасно). Наприклад, в іграх, оптимізація потоків може покращити графіку та зменшити лаг.");
        db.saveInformationData("CUDA", "CUDA (Compute Unified Device Architecture) - це програмно-апаратна архітектура, яка дозволяє використовувати графічні процесори (GPU) для розрахунків, що раніше виконувались виключно центральним процесором (CPU). Вона забезпечує паралельні обчислення та значно підвищує продуктивність завдяки використанню GPU Nvidia.");

        db.saveInformationData("about", "Дана програма є майже точною копією NVidia control Panel. Вона може працювати з вбудованими чи простими відеокартами компаній Intel та NVidia. Ця програма була розроблена в цілях навчання, вона дозволяє змінювати вхідні параметри відеокарти для обраних програм, що у свою чергу надає можливість комплексно вивчати вміст відеокарти та взаємодіяти з нею. Також ми можемо переглядати параметри наявних відеокарт, а саме: їх завантаженість, температуру та об'єм використаної пам'яті. Ще є доступним отримати усі процеси, що використовують обрану відеокарту.");
        db.saveInformationData("works", "Програма працює з великою кількістю бібліотек, найважливіші з яких є: nvapi та SQLite. Для отримання інформації про наявні відеокарти та їх використання ми використовуємо прості консольні запити, які в результаті отримання аналізуємо та витягуємо потрібну інформацію. Для створення профілів ми використовуємо nvapi - яка надає потрібний функціонал для роботи з відеокартами. SQLite - використовується для збереження великої кількості інформації (включно з цим текстом :) та просто параметрів профілів для подальшого використання.");
        db.saveInformationData("abilities", "Програма може змінювати вхідні параметри відеокарти для різних програм за принципом створення профілів, які у свою чергу прив'язуються до програм. Завдяки графікам ми можемо досліджувати завантаженість заліза як у цей момент так і декілька секунд тому. Процеси, що використовують нашу дорогоцінну відеокарту, ми можемо відслідковувати та думати чи то добре чи ні, що якийсь лівий процес бере сто відсотків нашої відеокарти :D (вбити його ви не зможете, але спостерігати - без проблем).");
        db.saveInformationData("how", "Усе тут є зрозумілим, можливо, крім профілів та їх прив'язки до програм. Профілі - це лиш набір параметрів, параметрів - які програма використовує при старті для задання ритму відеокарті. Відеокарта приймає наш профіль (набір параметрів) та застосовує їх для подальшої роботи програми. Це і є основний принцип створення профілів та їх прив'язки. Важливо зазначити, що один профіль можна прив'язувати до великої кількості програм.");
        qDebug() << "Кінець завантаження даних --||";
    }
}

void InterfaceHelper::Button_CurrentPaint(QPushButton *buttonNext){
    buttonNow->setStyleSheet("background-color: transparent;");
    buttonNext->setStyleSheet("background-color: #78f5e9;");
}

InterfaceHelper::~InterfaceHelper()
{
    delete ui;
}

void InterfaceHelper::on_pushButton_VertSync_clicked()
{
    ui->label_main->setText(db.loadInformationData("VertSync"));
    Button_CurrentPaint(ui->pushButton_VertSync);
    buttonNow = ui->pushButton_VertSync;
}


void InterfaceHelper::on_pushButton_AntMode_clicked()
{
    ui->label_main->setText(db.loadInformationData("AntMode"));
    Button_CurrentPaint(ui->pushButton_AntMode);
    buttonNow = ui->pushButton_AntMode;
}


void InterfaceHelper::on_pushButton_AnisFiltering_clicked()
{
    ui->label_main->setText(db.loadInformationData("AnisFiltering"));
    Button_CurrentPaint(ui->pushButton_AnisFiltering);
    buttonNow = ui->pushButton_AnisFiltering;
}


void InterfaceHelper::on_pushButton_TextFiltQuality_clicked()
{
    ui->label_main->setText(db.loadInformationData("TextFiltQuality"));
    Button_CurrentPaint(ui->pushButton_TextFiltQuality);
    buttonNow = ui->pushButton_TextFiltQuality;
}


void InterfaceHelper::on_pushButton_AmbOcculusion_clicked()
{
    ui->label_main->setText(db.loadInformationData("AmbOcculusion"));
    Button_CurrentPaint(ui->pushButton_AmbOcculusion);
    buttonNow = ui->pushButton_AmbOcculusion;
}


void InterfaceHelper::on_pushButton_PowManagMode_clicked()
{
    ui->label_main->setText(db.loadInformationData("PowManagMode"));
    Button_CurrentPaint(ui->pushButton_PowManagMode);
    buttonNow = ui->pushButton_PowManagMode;
}


void InterfaceHelper::on_pushButton_TripBuffering_clicked()
{
    ui->label_main->setText(db.loadInformationData("TripBuffering"));
    Button_CurrentPaint(ui->pushButton_TripBuffering);
    buttonNow = ui->pushButton_TripBuffering;
}


void InterfaceHelper::on_pushButton_ThrOpti_clicked()
{
    ui->label_main->setText(db.loadInformationData("ThrOpti"));
    Button_CurrentPaint(ui->pushButton_ThrOpti);
    buttonNow = ui->pushButton_ThrOpti;
}


void InterfaceHelper::on_pushButton_CUDA_clicked()
{
    ui->label_main->setText(db.loadInformationData("CUDA"));
    Button_CurrentPaint(ui->pushButton_CUDA);
    buttonNow = ui->pushButton_CUDA;
}


void InterfaceHelper::on_pushButton_about_clicked()
{
    ui->label_main->setText(db.loadInformationData("about"));
    Button_CurrentPaint(ui->pushButton_about);
    buttonNow = ui->pushButton_about;
}


void InterfaceHelper::on_pushButton_works_clicked()
{
    ui->label_main->setText(db.loadInformationData("works"));
    Button_CurrentPaint(ui->pushButton_works);
    buttonNow = ui->pushButton_works;
}


void InterfaceHelper::on_pushButton_abilities_clicked()
{
    ui->label_main->setText(db.loadInformationData("abilities"));
    Button_CurrentPaint(ui->pushButton_abilities);
    buttonNow = ui->pushButton_abilities;
}


void InterfaceHelper::on_pushButton_how_clicked()
{
    ui->label_main->setText(db.loadInformationData("how"));
    Button_CurrentPaint(ui->pushButton_how);
    buttonNow = ui->pushButton_how;
}


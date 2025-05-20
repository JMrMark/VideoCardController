#include "databasecollector.h"

DataBaseCollector::DataBaseCollector() {
    // Відкриваємо або створюємо базу даних SQLite
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("profiles.db"); // Файл бази даних

    if (!db.open()) {
        qDebug() << "[DB] Не вдалося відкрити базу даних!";
        return;
    }

    qDebug() << "[DB] База даних успішно відкрита!";

    // Викликаємо функцію створення таблиці, якщо вона ще не існує
    createTable();
}

DataBaseCollector::~DataBaseCollector() {
    db.close();
    qDebug() << "[DB] База даних закрита!";
}

void DataBaseCollector::createTable() {
    QSqlQuery query;

    QString createTableQuery =
        "CREATE TABLE IF NOT EXISTS ProfileBD ("
        "ProfileS TEXT(16) PRIMARY KEY, "
        "VertSyncS INTEGER, "
        "AntModeS INTEGER, "
        "AnisFilteringS INTEGER, "
        "TextFiltQualityS INTEGER, "
        "AmbOcculusionS INTEGER, "
        "PowManagModeS INTEGER, "
        "TripBufferingS INTEGER, "
        "ThrOptiS INTEGER, "
        "CUDAS INTEGER);";

    if (!query.exec(createTableQuery)) {
        qDebug() << "[DB] Помилка створення таблиці ProfileBD:" << query.lastError().text();
    } else {
        qDebug() << "[DB] Таблиця ProfileBD успішно створена!";
    }
}

bool DataBaseCollector::saveProfileData(const QString &profileName, int VertSyncS, int AntModeS, int AnisFilteringS,
                     int TextFiltQualityS, int AmbOcculusionS, int PowManagModeS, int TripBufferingS,
                     int ThrOptiS, int CUDAS) {
    // Переконуємося, що profileName коректний
    if (profileName != "Profile_1" && profileName != "Profile_2" && profileName != "Profile_3") {
        qDebug() << "[DB] Невірне ім'я профілю!";
        return false;
    }

    QSqlQuery query;

    // Перевірка, чи існує запис
    query.prepare("SELECT COUNT(*) FROM ProfileBD WHERE ProfileS = :profileName");
    query.bindValue(":profileName", profileName);

    if (!query.exec()) {
        qDebug() << "[DB] Помилка перевірки існування профілю:" << query.lastError().text();
        return false;
    }

    query.next();
    int recordCount = query.value(0).toInt();

    if (recordCount > 0) {
        // Оновлення існуючого запису
        query.prepare("UPDATE ProfileBD SET "
                      "VertSyncS = :VertSyncS, AntModeS = :AntModeS, AnisFilteringS = :AnisFilteringS, "
                      "TextFiltQualityS = :TextFiltQualityS, AmbOcculusionS = :AmbOcculusionS, "
                      "PowManagModeS = :PowManagModeS, TripBufferingS = :TripBufferingS, "
                      "ThrOptiS = :ThrOptiS, CUDAS = :CUDAS WHERE ProfileS = :profileName");
    } else {
        // Створення нового запису
        query.prepare("INSERT INTO ProfileBD (ProfileS, VertSyncS, AntModeS, AnisFilteringS, TextFiltQualityS, "
                      "AmbOcculusionS, PowManagModeS, TripBufferingS, ThrOptiS, CUDAS) VALUES "
                      "(:profileName, :VertSyncS, :AntModeS, :AnisFilteringS, :TextFiltQualityS, "
                      ":AmbOcculusionS, :PowManagModeS, :TripBufferingS, :ThrOptiS, :CUDAS)");
    }

    // Прив’язка значень
    query.bindValue(":profileName", profileName);
    query.bindValue(":VertSyncS", VertSyncS);
    query.bindValue(":AntModeS", AntModeS);
    query.bindValue(":AnisFilteringS", AnisFilteringS);
    query.bindValue(":TextFiltQualityS", TextFiltQualityS);
    query.bindValue(":AmbOcculusionS", AmbOcculusionS);
    query.bindValue(":PowManagModeS", PowManagModeS);
    query.bindValue(":TripBufferingS", TripBufferingS);
    query.bindValue(":ThrOptiS", ThrOptiS);
    query.bindValue(":CUDAS", CUDAS);

    if (!query.exec()) {
        qDebug() << "[DB] Помилка збереження профілю:" << query.lastError().text();
        return false;
    }

    qDebug() << "[DB] Профіль" << profileName << (recordCount > 0 ? " оновлено!" : " створено!");
    return true;
}

QVector<int> DataBaseCollector::loadProfileData(const QString &profileName) {
    QVector<int> vBase(9, 0); // Ініціалізуємо вектор (0 означає "дані не знайдено")

    // Переконуємося, що profileName коректний
    if (profileName != "Profile_1" && profileName != "Profile_2" && profileName != "Profile_3") {
        qDebug() << "[DB] Невірне ім'я профілю!";
        return vBase;
    }

    QSqlQuery query;
    query.prepare("SELECT VertSyncS, AntModeS, AnisFilteringS, TextFiltQualityS, AmbOcculusionS, "
                  "PowManagModeS, TripBufferingS, ThrOptiS, CUDAS FROM ProfileBD WHERE ProfileS = :profileName");
    query.bindValue(":profileName", profileName);

    if (!query.exec()) {
        qDebug() << "[DB] Помилка завантаження профілю:" << query.lastError().text();
        return vBase;
    }

    if (query.next()) {
        // Заповнюємо вектор отриманими даними
        for (int i = 0; i < vBase.size(); ++i) {
            vBase[i] = query.value(i).toInt();
        }
        qDebug() << "[DB] Дані профілю" << profileName << "успішно завантажено!";
    } else {
        qDebug() << "[DB] Профіль" << profileName << "не знайдено!";
    }

    return vBase;
}

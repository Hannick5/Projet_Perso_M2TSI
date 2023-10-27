#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QList>
#include <QPair>

class Database {
public:
    Database();
    Database(const QString& dbName);
    ~Database();

    bool addUser(const QString& username, const QString& password);
    QList<QPair<int, QString>> listUsers();
    bool userExists(const QString& username, const QString& password);
    bool isUserAdmin(const QString& username);
    QString hashPassword(const QString &password);
    bool deleteReservation(const QString& nom_utilisateur, const QString& nom_spectacle, int num_place);
    int getIsCovidValue(const QString &spectacleName);
    QList<int> getAlreadyPurchasedSeats(const QString& selectedShow);
    bool areAllSeatsPurchased(const QString& selectedShow, int totalSeats);
    bool isCovidShow(const QString& selectedShow);
private:
    QSqlDatabase db;
};

#endif // DATABASE_H

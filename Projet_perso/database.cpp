#include "database.h"

Database::Database(){
    // Configuration de la base de données SQLite sans argument
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("ProjetBillet.db");

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données : " << db.lastError().text();
    }
}

Database::Database(const QString& dbName) {
    // Configuration de la base de données SQLite avec argument
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données : " << db.lastError().text();
    }
}

Database::~Database() {
    db.close();
}

bool Database::addUser(const QString& username, const QString& password) {
    QSqlQuery query;
    query.prepare("INSERT INTO Utilisateurs (Nom, Admin, MotDePasse) VALUES (?, 0, ?)");
    query.bindValue(0, username);
    query.bindValue(1, hashPassword(password));

    return query.exec();
}

QList<QPair<int, QString>> Database::listUsers() {
    QList<QPair<int, QString>> users;

    QSqlQuery query("SELECT Id, Nom FROM Utilisateurs");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString username = query.value(1).toString();
        users.append(qMakePair(id, username));
    }

    return users;
}

bool Database::userExists(const QString& username, const QString& password) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Utilisateurs WHERE Nom = ? AND MotDePasse = ?");
    query.bindValue(0, username);
    query.bindValue(1, password);
    query.exec();

    if (query.next()) {
        return query.value(0).toInt() > 0;
    }

    return false;
}

bool Database::isUserAdmin(const QString& username) {
    QSqlQuery query;
    query.prepare("SELECT Admin FROM Utilisateurs WHERE Nom = ?");
    query.bindValue(0, username);
    query.exec();

    if (query.next()) {
        return query.value(0).toBool();
    }

    return false;
}

QString Database::hashPassword(const QString &password) {
    QCryptographicHash cryptoHash(QCryptographicHash::Sha256);
    cryptoHash.addData(password.toUtf8());
    return QString(cryptoHash.result().toHex());
}

bool Database::deleteReservation(const QString& nom_utilisateur, const QString& nom_spectacle, int num_place) {
    // Ouvrir la base de données
    if (!db.isOpen()) {
        return false;
    }

    // Préparer la requête de suppression
    QSqlQuery query(db);
    query.prepare("DELETE FROM Spectateur WHERE nom_utilisateur = :nom_utilisateur AND nom_spectacle = :nom_spectacle AND num_place = :num_place");
    query.bindValue(":nom_utilisateur", nom_utilisateur);
    query.bindValue(":nom_spectacle", nom_spectacle);
    query.bindValue(":num_place", num_place);

    // Exécuter la requête de suppression
    if (query.exec()) {
        // La suppression s'est bien passée
        return true;
    } else {
        return false;
    }
}

int Database::getIsCovidValue(const QString &spectacleName) {
    QSqlQuery query;
    query.prepare("SELECT covid FROM spectacles WHERE titre = :spectacleName");
    query.bindValue(":spectacleName", spectacleName);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }

    // En cas d'erreur, vous pouvez renvoyer une valeur par défaut (par exemple, -1) pour indiquer qu'aucune information n'a été trouvée.
    return -1;
}

QList<int> Database::getAlreadyPurchasedSeats(const QString& selectedShow) {
    QList<int> purchasedSeats;

    QSqlQuery query;
    query.prepare("SELECT num_place FROM Spectateur WHERE nom_spectacle = :spectacle");
    query.bindValue(":spectacle", selectedShow);

    if (query.exec()) {
        while (query.next()) {
            int seatNumber = query.value(0).toInt();
            purchasedSeats.append(seatNumber);
        }
    } else {
        qDebug() << "Erreur lors de la récupération des sièges déjà achetés : " << query.lastError().text();
    }

    return purchasedSeats;
}

// Méthode pour vérifier si un spectacle a des restrictions COVID
bool Database::isCovidShow(const QString& selectedShow) {
    QSqlQuery query;
    query.prepare("SELECT covid FROM spectacles WHERE titre = :titre");
    query.bindValue(":titre", selectedShow);

    if (query.exec() && query.next()) {
        int isCovid = query.value(0).toInt();
        return isCovid == 1;
    }

    // Valeur par défaut si la requête échoue
    return false;
}

// Méthode pour vérifier si toutes les places pour un spectacle donné sont déjà achetées
bool Database::areAllSeatsPurchased(const QString& selectedShow, int totalSeats) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Spectateur WHERE nom_spectacle = :spectacle");
    query.bindValue(":spectacle", selectedShow);

    if (query.exec() && query.next()) {
        int seatsPurchased = query.value(0).toInt();
        return seatsPurchased >= totalSeats;
    }

    // Valeur par défaut si la requête échoue
    return false;
}


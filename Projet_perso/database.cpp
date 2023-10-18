#include "database.h"

Database::Database(){
    // Configuration de la base de données SQLite
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("ProjetBillet.db");

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données : " << db.lastError().text();
    }
}

Database::Database(const QString& dbName) {
    // Configuration de la base de données SQLite
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
        // Gérez l'ouverture de la base de données ici
        return false;
    }

    // Préparez la requête de suppression
    QSqlQuery query(db);
    query.prepare("DELETE FROM Spectateur WHERE nom_utilisateur = :nom_utilisateur AND nom_spectacle = :nom_spectacle AND num_place = :num_place");
    query.bindValue(":nom_utilisateur", nom_utilisateur);
    query.bindValue(":nom_spectacle", nom_spectacle);
    query.bindValue(":num_place", num_place);

    // Exécutez la requête de suppression
    if (query.exec()) {
        // La suppression s'est bien passée
        return true;
    } else {
        // Gérez l'erreur de suppression ici
        return false;
    }
}

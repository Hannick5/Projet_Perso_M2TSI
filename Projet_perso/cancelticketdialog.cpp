#include "cancelticketdialog.h"
#include <QPushButton>



CancelReservationDialog::CancelReservationDialog(QWidget *parent, const QString& username)
    : QDialog(parent), username(username) {
    setFixedSize(800, 600);
    setupUI();
    loadReservations();
}

void CancelReservationDialog::setupUI() {
    reservationTable = new QTableWidget(this);
    reservationTable->setColumnCount(3); // Trois colonnes : nom_utilisateur, nom_spectacle, num_place
    reservationTable->setHorizontalHeaderLabels(QStringList() << "Nom Utilisateur" << "Nom Spectacle" << "Num Place");

    QPushButton *deleteButton = new QPushButton("Supprimer la réservation");

        QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(reservationTable);
    layout->addWidget(deleteButton);

    connect(deleteButton, &QPushButton::clicked, this, &CancelReservationDialog::onDeleteButtonClicked);
}

void CancelReservationDialog::loadReservations() {
    QSqlQuery query;
    query.prepare("SELECT nom_utilisateur, nom_spectacle, num_place FROM Spectateur WHERE nom_utilisateur = ?");
    query.bindValue(0, username);
    if (query.exec()) {
        while (query.next()) {
            QString nom_utilisateur = query.value(0).toString();
            QString nom_spectacle = query.value(1).toString();
            int num_place = query.value(2).toInt();

            int row = reservationTable->rowCount();
            reservationTable->insertRow(row);

            QTableWidgetItem *item1 = new QTableWidgetItem(nom_utilisateur);
            QTableWidgetItem *item2 = new QTableWidgetItem(nom_spectacle);
            QTableWidgetItem *item3 = new QTableWidgetItem(QString::number(num_place));

            reservationTable->setItem(row, 0, item1);
            reservationTable->setItem(row, 1, item2);
            reservationTable->setItem(row, 2, item3);
        }
    }
}

void CancelReservationDialog::deleteReservation(int row) {
    if (row >= 0 && row < reservationTable->rowCount()) {
        QString nom_utilisateur = reservationTable->item(row, 0)->text();
        QString nom_spectacle = reservationTable->item(row, 1)->text();
        int num_place = reservationTable->item(row, 2)->text().toInt();

        if (db.deleteReservation(nom_utilisateur, nom_spectacle, num_place)) {
            reservationTable->removeRow(row);
        }
    }
}

void CancelReservationDialog::onDeleteButtonClicked() {
    int row = reservationTable->currentRow();
    deleteReservation(row);
}

#ifndef CANCELTICKETDIALOG_H
#define CANCELTICKETDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QTableWidget>
#include "database.h"

class CancelReservationDialog : public QDialog {
    Q_OBJECT

public:
    CancelReservationDialog(QWidget *parent = nullptr,const QString& username = "u");

private:
    QTableWidget *reservationTable; // Tableau pour afficher les réservations
    Database db;
    void setupUI();
    void loadReservations();
    void deleteReservation(int row);
    QString username;

private slots:
    void onDeleteButtonClicked();
};

#endif // CANCELTICKETDIALOG_H

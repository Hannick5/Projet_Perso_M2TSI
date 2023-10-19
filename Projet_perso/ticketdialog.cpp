// ticketdialog.cpp
#include "ticketdialog.h"
#include "qsqlquery.h"
#include "database.h"

TicketDialog::TicketDialog(const QString& selectedShow, const QString& username, QWidget *parent)
    : QDialog(parent), username(username), selectedShow(selectedShow)
{
    totalSeats = 100; // Nombre total de places
    setupUI(selectedShow);
}

void TicketDialog::setupUI(const QString& selectedShow)
{
    setWindowTitle("Achat de billets pour " + selectedShow);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Conteneur pour représenter la salle de spectacle
    QFrame *stage = new QFrame(this);
    stage->setStyleSheet("background-color: #2c3e50;");

    QGridLayout *seatingLayout = new QGridLayout(stage);
    seatingLayout->setSpacing(20); // Espacement entre les sièges

    const int totalRows = 10; // Nombre total de rangées
    const int seatsPerRow = 10; // Nombre de sièges par rangée

    Database db;
    int isCovid = db.getIsCovidValue(selectedShow); // la valeur isCovid du spectacle

    for (int row = 0; row < totalRows; ++row) {
        for (int seat = 0; seat < seatsPerRow; ++seat) {
            int seatNumber = row * seatsPerRow + seat + 1;
            QPushButton *seatButton = new QPushButton(QString::number(seatNumber));
            seatButton->setFixedSize(40, 40); // Taille de chaque bouton de place

            // Vérifier si le siège est cliquable en fonction de la valeur isCovid
            bool isClickable = (isCovid == 0) || (isCovid == 1 && seatNumber % 2 == 0);

            if (isClickable) {
                seatButton->setStyleSheet("QPushButton {"
                                          "background-color: #3498db;"
                                          "color: white;"
                                          "border: none;"
                                          "padding: 5px 10px;"
                                          "border-radius: 5px;"
                                          "font-size: 14px;"
                                          "}"
                                          "QPushButton:hover {"
                                          "background-color: #2980b9;"
                                          "}");
                connect(seatButton, &QPushButton::clicked, this, [seatNumber, this]() {
                    onSeatClicked(seatNumber);
                });
            } else {
                seatButton->setStyleSheet("QPushButton {"
                                          "background-color: #CCCCCC;"
                                          "color: white;"
                                          "border: none;"
                                          "padding: 5px 10px;"
                                          "border-radius: 5px;"
                                          "font-size: 14px;"
                                          "}"
                                          ); // Grisé
            }

            seatButtons.push_back(seatButton);
            seatingLayout->addWidget(seatButton, row, seat);
        }
    }

    QHBoxLayout *bottomLayout = new QHBoxLayout;

    QPushButton *confirmButton = new QPushButton("Confirmer");
    confirmButton->setStyleSheet("background-color: #E0E0E0;");
    bottomLayout->addWidget(confirmButton);

    seatingLayout->addLayout(bottomLayout, seatingLayout->rowCount(), 0, 1, seatingLayout->columnCount());
    connect(confirmButton, &QPushButton::clicked, this, &TicketDialog::onConfirm);

    mainLayout->addWidget(stage);
}


void TicketDialog::onSeatClicked(int seatNumber)
{
    QPushButton *seatButton = seatButtons[seatNumber - 1]; // -1 car les indices commencent à 0

    if (selectedSeats.contains(seatNumber)) {
        // Si le siège est déjà sélectionné, désélectionnez-le
        selectedSeats.removeOne(seatNumber); // Utilisez removeOne pour supprimer l'élément s'il existe
        seatButton->setStyleSheet("QPushButton {"
                                  "background-color: #3498db;"
                                  "color: white;"
                                  "border: none;"
                                  "padding: 5px 10px;"
                                  "border-radius: 5px;"
                                  "font-size: 14px;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: #2980b9;"
                                  "}"); // Style par défaut
    } else {
        // Si le siège n'est pas encore sélectionné, sélectionnez-le
        selectedSeats.append(seatNumber);
        seatButton->setStyleSheet("QPushButton {"
                                  "background-color: #aea4eb;"
                                  "color: white;"
                                  "border: none;"
                                  "padding: 5px 10px;"
                                  "border-radius: 5px;"
                                  "font-size: 14px;"
                                  "}"
                                  ); // Couleur de sélection
    }
}




void TicketDialog::onConfirm(){
    Database db;
    QSqlQuery query;
    query.prepare("INSERT INTO Spectateur (nom_utilisateur, nom_spectacle, num_place) VALUES (:username, :spectacle, :seat)");
    query.bindValue(":username", username);
    query.bindValue(":spectacle", selectedShow);

    for (int seat : selectedSeats) {
        qDebug() << "Siège sélectionné : " << seat << username << selectedShow;
        query.bindValue(":seat", seat);

        // Insertion pour chaque siège
        if (!query.exec()) {
            qDebug() << "Erreur d'insertion pour le siège : " << seat << query.lastError().text();
        }
    }

    accept();
}

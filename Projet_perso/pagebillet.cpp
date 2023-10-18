// pagebillet.cpp
#include "pagebillet.h"
#include "cancelticketdialog.h"
#include "ticketdialog.h" // La boîte de dialogue pour l'achat de billets
#include "database.h"

PageBillet::PageBillet(const QString& username, QWidget *parent)
    : QDialog(parent), username(username)
{
    setupUI();
    populateShowSelection();
}

void PageBillet::setupUI()
{
    setWindowTitle("Page de Billet");
    setFixedSize(400, 300);  // Définir la taille de la fenêtre (ajustez-la selon vos besoins)

    layout = new QVBoxLayout(this);

    titleLabel = new QLabel("Bienvenue sur la page de billet.");
    titleLabel->setAlignment(Qt::AlignCenter);

    showLabel = new QLabel("Sélectionnez un spectacle :");

    showSelection = new QComboBox;

    buyTicketsButton = new QPushButton("Acheter des billets");
    buyTicketsButton->setStyleSheet("background-color: #007ACC; color: white; font-weight: bold;");

    cancelTicketButton = new QPushButton("Annuler des billets");
    cancelTicketButton->setStyleSheet("background-color: #007ACC; color: white; font-weight: bold;");

    logoutButton = new QPushButton("Se Déconnecter");
    logoutButton->setStyleSheet("background-color: #FF5733; color: white; font-weight: bold;");

    layout->addWidget(titleLabel);
    layout->addWidget(showLabel);
    layout->addWidget(showSelection);
    layout->addWidget(buyTicketsButton);
    layout->addWidget(cancelTicketButton);
    layout->addWidget(logoutButton);

    connect(buyTicketsButton, &QPushButton::clicked, this, &PageBillet::onBuyTicketsClicked);

    connect(showSelection, QOverload<int>::of(&QComboBox::activated), this, &PageBillet::onShowSelected);

    connect(cancelTicketButton, &QPushButton::clicked, this, &PageBillet::onCancelTicketClicked);

    connect(logoutButton, SIGNAL(clicked()), this, SLOT(close()));
}

void PageBillet::onBuyTicketsClicked()
{
    // Récupérez le spectacle sélectionné (showSelection->currentText()) pour afficher la grille correspondante
    selectedShow = showSelection->currentText();

    // Affichez la boîte de dialogue pour l'achat de billets
    TicketDialog ticketDialog(selectedShow, username, this);
    ticketDialog.exec();
}

void PageBillet::onCancelTicketClicked() {
    // Créez une instance de la fenêtre d'annulation de billet (CancelReservationDialog)
    CancelReservationDialog cancelDialog(this, username);
    cancelDialog.exec();
}

void PageBillet::populateShowSelection()
{
    Database db; // Créez une instance de votre classe Database

    // Effectuez une requête pour obtenir les noms des spectacles depuis la base de données
    QSqlQuery query;

    if (query.exec("SELECT titre, date FROM spectacles")) {
        while (query.next()) {
            QString showTitle = query.value(0).toString();
            QDateTime showDate = query.value(1).toDateTime();

            // Vérifiez si la date du spectacle est dépassée
            if (showDate < QDateTime::currentDateTime()) {
                showSelection->addItem(showTitle, QVariant(true));
            } else {
                showSelection->addItem(showTitle, QVariant(false));
            }
        }
    }
}

void PageBillet::onShowSelected(int index)
{
    Database db; // Créez une instance de votre classe Database


    // Affichez les informations du spectacle sélectionné dans le QLabel showInfoLabel
    QString selectedShow = showSelection->itemText(index);
    QVariant isShowExpired = showSelection->itemData(index);

    if (isShowExpired.toBool()) {
        // Spectacle dépassé
        buyTicketsButton->setEnabled(false);
        buyTicketsButton->setStyleSheet("background-color: gray;"); // Fond gris
    } else {
        buyTicketsButton->setEnabled(true);
        buyTicketsButton->setStyleSheet("background-color: #007ACC; color: white; font-weight: bold;"); // Fond normal
    }

    // Effectuez une requête pour obtenir les informations du spectacle depuis la base de données
    QSqlQuery query;
    query.prepare("SELECT description, artiste, prix, date, heure FROM spectacles WHERE titre = :titre");
    query.bindValue(":titre", selectedShow);
    if (query.exec() && query.next()) {
        QString description = query.value(0).toString();
        QString artiste = query.value(1).toString();
        QString prix = query.value(2).toString();
        QString date = query.value(3).toString();
        QString heure = query.value(4).toString();
        QString infoText = QString("Description : %1\nArtiste : %2\nPrix : %3\nDate : %4\nHeure : %5").arg(description, artiste, prix, date, heure);
        showLabel->setText(infoText);

    }
}

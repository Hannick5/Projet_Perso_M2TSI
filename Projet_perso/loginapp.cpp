#include "loginapp.h"

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QMessageBox>
#include "pagebillet.h"
#include "adminpagebillet.h"
#include "database.h"
#include "inscriptiondialog.h"

LoginApp::LoginApp(QWidget *parent)
    : QWidget(parent) {
    // Configuration de l'interface utilisateur
    setWindowTitle("Interface de Connexion");

    QString styleSheet = "QLabel {"
                         "font-size: 14px;"
                         "color: #333333;"
                         "}"
                         "QLineEdit {"
                         "border: 1px solid #aaaaaa;"
                         "border-radius: 5px;"
                         "padding: 2px;"
                         "font-size: 14px;"
                         "}"
                         "QPushButton {"
                         "background-color: #3498db;"
                         "color: white;"
                         "border: none;"
                         "padding: 5px 10px;"
                         "border-radius: 5px;"
                         "font-size: 14px;"
                         "}"
                         "QPushButton:hover {"
                         "background-color: #2980b9;"
                         "}";

    editUsername.setStyleSheet(styleSheet);
    editPassword.setStyleSheet(styleSheet);
    buttonLogin.setStyleSheet(styleSheet);
    buttonSignUp.setStyleSheet(styleSheet);

    setFixedSize(500,250);

    QVBoxLayout *layout = new QVBoxLayout(this);  // Création d'une mise en page

    QLabel *labelUsername = new QLabel("Identifiant :");  // Création des labels
    QLabel *labelPassword = new QLabel("Mot de passe :");

    editPassword.setEchoMode(QLineEdit::Password);

    buttonLogin.setText("Se connecter");
    buttonSignUp.setText("S'inscrire");

    layout->addWidget(labelUsername);  // Ajout des widgets à la mise en page
    layout->addWidget(&editUsername);
    layout->addWidget(labelPassword);
    layout->addWidget(&editPassword);
    layout->addWidget(&buttonLogin);
    layout->addWidget(&buttonSignUp);

    // Connexion du bouton de connexion
    QObject::connect(&buttonLogin, &QPushButton::clicked, this, &LoginApp::handleLogin);
    QObject::connect(&buttonSignUp, &QPushButton::clicked, this, &LoginApp::handleInscription);

    stackedWidget.addWidget(this);
    stackedWidget.show();
}

void LoginApp::handleLogin() {
    QString username = editUsername.text();
    QString password = editPassword.text();
    Database db;

    // Hachage du mot de passe fourni par l'utilisateur
    QString hashedPassword = db.hashPassword(password);

    // Vérification de si l'utilisateur existe en utilisant le mot de passe haché
    bool userExists = db.userExists(username, hashedPassword);

    if (userExists) {
        stackedWidget.hide();

        // Récupération du rôle de l'utilisateur depuis la base de données
        bool isAdmin = db.isUserAdmin(username);

        if (isAdmin) {
            AdminPageBillet apb;
            apb.setModal(true);
            apb.exec();
        } else {
            PageBillet pb(username);
            pb.setModal(true);
            pb.exec();
        }
    } else {
        QMessageBox::critical(this, "Échec de la connexion", "Identifiant ou mot de passe incorrect.");
    }
}

// loginapp.cpp (dans la classe LoginApp)

void LoginApp::handleInscription() {
    InscriptionDialog inscriptionDialog;
    if (inscriptionDialog.exec() == QDialog::Accepted) {
        // L'utilisateur a confirmé l'inscription
        QString username = inscriptionDialog.getUsername();
        QString password = inscriptionDialog.getPassword();

        Database db;

        if (db.addUser(username, password)) {
            QMessageBox::information(this, "Inscription réussie", "Votre inscription a été enregistrée.");
        } else {
            QMessageBox::warning(this, "Erreur d'inscription", "L'inscription a échoué. Veuillez réessayer.");
        }
    }
}

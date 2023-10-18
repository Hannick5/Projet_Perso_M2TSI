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

LoginApp::LoginApp(QWidget *parent)
    : QWidget(parent) {
    // Configuration de l'interface utilisateur
    setWindowTitle("Interface de Connexion");

    QVBoxLayout *layout = new QVBoxLayout(this);  // Créez une mise en page

    QLabel *labelUsername = new QLabel("Identifiant :");  // Créez des labels
    QLabel *labelPassword = new QLabel("Mot de passe :");

    editPassword.setEchoMode(QLineEdit::Password);

    buttonLogin.setText("Se connecter");

    layout->addWidget(labelUsername);  // Ajoutez les labels à la mise en page
    layout->addWidget(&editUsername);
    layout->addWidget(labelPassword);
    layout->addWidget(&editPassword);
    layout->addWidget(&buttonLogin);

    // Connexion du bouton de connexion
    QObject::connect(&buttonLogin, &QPushButton::clicked, this, &LoginApp::handleLogin);

    stackedWidget.addWidget(this);
    stackedWidget.show();
}

void LoginApp::handleLogin() {
    QString username = editUsername.text();
    QString password = editPassword.text();
    Database db;

    // Hachez le mot de passe fourni par l'utilisateur
    QString hashedPassword = db.hashPassword(password);

    // Vérifiez si l'utilisateur existe en utilisant le mot de passe haché
    bool userExists = db.userExists(username, hashedPassword);

    if (userExists) {
        stackedWidget.hide();

        // Récupérer le rôle de l'utilisateur depuis la base de données
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


#include "inscriptiondialog.h"
#include "QVBoxLayout"

InscriptionDialog::InscriptionDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Inscription");

    usernameLabel = new QLabel("Nom d'utilisateur:");
    passwordLabel = new QLabel("Mot de passe:");
    usernameLineEdit = new QLineEdit;
    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setEchoMode(QLineEdit::Password); // Pour masquer le mot de passe

    confirmButton = new QPushButton("Confirmer");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(usernameLabel);
    layout->addWidget(usernameLineEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordLineEdit);
    layout->addWidget(confirmButton);

    connect(confirmButton, &QPushButton::clicked, this, &InscriptionDialog::accept);

    setLayout(layout);
}

QString InscriptionDialog::getUsername() const {
    return usernameLineEdit->text();
}

QString InscriptionDialog::getPassword() const {
    return passwordLineEdit->text();
}

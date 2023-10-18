// inscriptiondialog.h

#ifndef INSCRIPTIONDIALOG_H
#define INSCRIPTIONDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class InscriptionDialog : public QDialog {
    Q_OBJECT

public:
    InscriptionDialog(QWidget *parent = nullptr);
    QString getUsername() const;
    QString getPassword() const;

private:
    QLabel *usernameLabel;
    QLabel *passwordLabel;
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *confirmButton;
};

#endif // INSCRIPTIONDIALOG_H

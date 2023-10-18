#ifndef LOGINAPP_H
#define LOGINAPP_H

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QMessageBox>

class LoginApp : public QWidget {
public:
    LoginApp(QWidget *parent = nullptr);
    void handleLogin();
    void handleInscription();
    QLineEdit editUsername;
    QLineEdit editPassword;
    QPushButton buttonLogin;
    QStackedWidget stackedWidget;
    QPushButton buttonSignUp;
};

#endif // LOGINAPP_H

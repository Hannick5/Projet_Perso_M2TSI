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
private:
    QLineEdit editUsername;
    QLineEdit editPassword;
    QPushButton buttonLogin;
    QStackedWidget stackedWidget;
};

#endif // LOGINAPP_H

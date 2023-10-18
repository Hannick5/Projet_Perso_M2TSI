#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QStackedWidget>
#include <QtSql/QSqlDatabase>
#include <iostream>
#include <QSqlQuery>
#include <QSqlError>
#include <adminpagebillet.h>
#include <loginapp.h>
#include <QCryptographicHash>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    LoginApp loginApp;
    return app.exec();
}

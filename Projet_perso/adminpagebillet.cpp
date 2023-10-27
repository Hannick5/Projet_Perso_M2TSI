#include "adminpagebillet.h"
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QTableView>
#include "database.h"

AdminPageBillet::AdminPageBillet(QWidget *parent) : QDialog(parent)
{
    setupUI();
}

AdminPageBillet::~AdminPageBillet()
{

}

void AdminPageBillet::setupUI()
{
    setFixedSize(1200, 900);
    setWindowTitle("Interface d'administration");
    tabWidget = new QTabWidget(this);
    setupShowsTab();
    setupReservationsTab();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tabWidget);
}

void AdminPageBillet::setupShowsTab()
{
    showsTab = new QWidget();
    tabWidget->addTab(showsTab, "Spectacles");
    Database db;
    QSqlQuery query;
    query.prepare("SELECT * FROM spectacles");
    if (query.exec()) {
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(query);

        QTableView *tableView = new QTableView();
        tableView->setModel(model);

        QVBoxLayout *layout = new QVBoxLayout();
        layout->addWidget(tableView);
        showsTab->setLayout(layout);
    } else {
        qDebug() << "Erreur de requête pour les spectacles : " << query.lastError().text();
    }
}

void AdminPageBillet::setupReservationsTab()
{
    reservationsTab = new QWidget();
    tabWidget->addTab(reservationsTab, "Réservations");
    Database db;
    QSqlQuery query;
    query.prepare("SELECT * FROM Spectateur");
    if (query.exec()) {
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(query);

        QTableView *tableView = new QTableView();
        tableView->setModel(model);

        QVBoxLayout *layout = new QVBoxLayout();
        layout->addWidget(tableView);
        reservationsTab->setLayout(layout);
    } else {
        qDebug() << "Erreur de requête pour les réservations : " << query.lastError().text();
    }
}

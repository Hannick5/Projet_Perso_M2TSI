#ifndef ADMINPAGEBILLET_H
#define ADMINPAGEBILLET_H

#include <QDialog>
#include <QTabWidget>

class AdminPageBillet : public QDialog
{
    Q_OBJECT

public:
    AdminPageBillet(QWidget *parent = nullptr);
    ~AdminPageBillet();

private:
    void setupUI();
    void setupShowsTab();
    void setupReservationsTab();


    // Widgets pour les onglets
    QTabWidget *tabWidget;
    QWidget *showsTab;
    QWidget *reservationsTab;
};

#endif // ADMINPAGEBILLET_H

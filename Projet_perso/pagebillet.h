// pagebillet.h
#ifndef PAGEBILLET_H
#define PAGEBILLET_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>

class PageBillet : public QDialog
{
    Q_OBJECT

public:
    explicit PageBillet(const QString& username, QWidget *parent = nullptr);
    void populateShowSelection();
    void onShowSelected(int index);
private:
    QLabel *titleLabel;
    QLabel *showLabel;
    QComboBox *showSelection;
    QPushButton *buyTicketsButton;
    QPushButton *cancelTicketButton;
    QPushButton *logoutButton;
    QVBoxLayout *layout;
    QString username;
    QString selectedShow;
    void setupUI();

private slots:
    void onBuyTicketsClicked();
    void onCancelTicketClicked();
};

#endif // PAGEBILLET_H


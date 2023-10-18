// ticketdialog.h
#ifndef TICKETDIALOG_H
#define TICKETDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

class TicketDialog : public QDialog
{
    Q_OBJECT

public:
    TicketDialog(const QString& selectedShow, const QString& username, QWidget *parent = nullptr);

private:
    QGridLayout *layout;
    int totalSeats;
    QVector<QPushButton*> seatButtons;
    QList<int> selectedSeats;
    QString username;
    QString selectedShow;
    void setupUI(const QString& selectedShow);
private slots:
    void onSeatClicked(int seatNumber);
    void onConfirm();
};

#endif // TICKETDIALOG_H

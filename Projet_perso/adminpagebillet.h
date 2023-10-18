#ifndef ADMINPAGEBILLET_H
#define ADMINPAGEBILLET_H

#include <QDialog>

namespace Ui {
class AdminPageBillet;
}

class AdminPageBillet : public QDialog
{
    Q_OBJECT

public:
    explicit AdminPageBillet(QWidget *parent = nullptr);
    ~AdminPageBillet();

private:
    Ui::AdminPageBillet *ui;
};

#endif // ADMINPAGEBILLET_H

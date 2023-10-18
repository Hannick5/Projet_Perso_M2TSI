#include "adminpagebillet.h"
#include "ui_adminpagebillet.h"

AdminPageBillet::AdminPageBillet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminPageBillet)
{
    ui->setupUi(this);
}

AdminPageBillet::~AdminPageBillet()
{
    delete ui;
}

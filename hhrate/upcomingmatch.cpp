#include "upcomingmatch.h"
#include "ui_upcomingmatch.h"

UpcomingMatch::UpcomingMatch(Town p1, Town p2) :
    QWidget(),
    ui(new Ui::UpcomingMatch)
{
    ui->setupUi(this);

    ui->p1Label->setText(townIdxToString(p1));
    ui->p2Label->setText(townIdxToString(p2));
}

UpcomingMatch::~UpcomingMatch()
{
    delete ui;
}

#include "matchresultadder.h"
#include "ui_matchresultadder.h"
#include "utils.h"

MatchResultAdder::MatchResultAdder(hhrate* parent)
    : QWidget()
    , ui(new Ui::MatchResultAdder)
    , m_app( parent )
{
    ui->setupUi(this);
    fillTownComboBox(ui->p1Town);
    fillTownComboBox(ui->p2Town);
}

MatchResultAdder::~MatchResultAdder()
{
    delete ui;
}

void MatchResultAdder::on_okBtn_clicked()
{
    Town p1T = static_cast<Town>(ui->p1Town->currentIndex());
    Town p2T = static_cast<Town>(ui->p2Town->currentIndex());
    size_t winnerIdx = NoWinner;
    if (ui->p1IsWinner->isChecked()) {
        winnerIdx = 1;
    } else if (ui->p2IsWinner->isChecked()) {
        winnerIdx = 2;
    }

    if (winnerIdx != NoWinner) {
        m_app->addMatchResult({p1T, p2T, winnerIdx});
        close();
    }

}


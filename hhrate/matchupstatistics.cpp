#include "matchupstatistics.h"
#include "ui_matchupstatistics.h"

MatchupStatistics::MatchupStatistics(MatchResultsPtr matches)
    : QWidget()
    , ui(new Ui::MatchupStatistics)
    , m_matches(matches)
{
    ui->setupUi(this);
    fillTownComboBox(ui->matchupTown);
    updateTable();
}

MatchupStatistics::~MatchupStatistics()
{
    delete ui;
}

void MatchupStatistics::updateTable()
{
    QVector<WinrateData> windata;
    for(int town = 0; town < Town::Size; ++town)
        windata.push_back({ 0, 0, 0, static_cast<Town>(town) });

    for(const auto& match : *m_matches) {
        if(match.player1 == ui->matchupTown->currentIndex()) {
            if(match.winnerIdx == 1) {
                windata[match.player2].winCount++;
            } else {
                windata[match.player2].loseCount++;
            }
        } else if(match.player2 == ui->matchupTown->currentIndex()) {
            if(match.winnerIdx == 2) {
                windata[match.player1].winCount++;
            } else {
                windata[match.player1].loseCount++;
            }
        }
    }

    ui->matchesTable->setColumnCount(5);
    ui->matchesTable->setRowCount(Town::Size);
    ui->matchesTable->verticalHeader()->setVisible(false);

    QStringList colLabels;
    colLabels.append("Town");
    colLabels.append("Win");
    colLabels.append("Lose");
    colLabels.append("Winrate");
    colLabels.append("Games");

    ui->matchesTable->setHorizontalHeaderLabels(colLabels);

    QBrush *brush = new QBrush();
    brush->setStyle(Qt::SolidPattern);

    QTableWidgetItem *protoItem = new QTableWidgetItem();
    protoItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    protoItem->setBackground(*brush);

    for(int row = 0; row < Town::Size; ++row) {
        QString townName = townIdxToString(windata[row].town);
        QString winCount = QString::number(windata[row].winCount);
        QString loseCount = QString::number(windata[row].loseCount);
        unsigned int games = windata[row].winCount + windata[row].loseCount;
        QString gamesStr = QString::number(games);
        double winrate = games ? 100 * windata[row].winCount / games : 0;
        QString winrateStr = QString::number(winrate, 'f', 2) + '%';

        updateBrushByTown(brush, windata[row].town);
        QTableWidgetItem* townItem = protoItem->clone();
        townItem->setBackground(*brush);

        QTableWidgetItem *item = townItem->clone();
        item->setText(townName);
        ui->matchesTable->setItem(row, 0, item);

        item = townItem->clone();
        item->setText(winCount);
        ui->matchesTable->setItem(row, 1, item);

        item = townItem->clone();
        item->setText(loseCount);
        ui->matchesTable->setItem(row, 2, item);

        item = townItem->clone();
        item->setText(winrateStr);
        ui->matchesTable->setItem(row, 3, item);

        item = townItem->clone();
        item->setText(gamesStr);
        ui->matchesTable->setItem(row, 4, item);
    }

    ui->matchesTable->resizeColumnsToContents();
}

void MatchupStatistics::on_matchupTown_currentIndexChanged(int /*index*/)
{
    updateTable();
}


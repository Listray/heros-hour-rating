#include "showstatistics.h"
#include "ui_showstatistics.h"
#include "utils.h"

ShowStatistics::ShowStatistics(MatchResultsPtr matchResults)
    : QWidget()
    , ui(new Ui::ShowStatistics)
    , m_matchResults(matchResults)
{
    ui->setupUi(this);

    QVector<WinrateData> winrates;
    for(int town = 0; town < Town::Size; ++town)
        winrates.push_back({ 0, 0, 0, static_cast<Town>(town) });

    for(auto& matchResult : *m_matchResults) {
        if(matchResult.winnerIdx == 1) {
            winrates[matchResult.player1].winCount++;
            winrates[matchResult.player2].loseCount++;
        } else {
            winrates[matchResult.player1].loseCount++;
            winrates[matchResult.player2].winCount++;
        }
    }

    for(auto& winrate : winrates)
        winrate.winrate = 100 * winrate.winCount / (0. + winrate.winCount + winrate.loseCount);

    std::sort(winrates.begin(), winrates.end(),
              [](const WinrateData& lhs, const WinrateData& rhs){return lhs.winrate > rhs.winrate;});

    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(Town::Size);
    ui->tableWidget->verticalHeader()->setVisible(false);

    QStringList colLabels;
    colLabels.append("Town");
    colLabels.append("Win");
    colLabels.append("Lose");
    colLabels.append("Winrate");
    colLabels.append("Games");

    ui->tableWidget->setHorizontalHeaderLabels(colLabels);

    QBrush *brush = new QBrush();
    brush->setStyle(Qt::SolidPattern);

    QTableWidgetItem *protoItem = new QTableWidgetItem();
    protoItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    protoItem->setBackground(*brush);

    for(int row = 0; row < Town::Size; ++row) {
        QString townName = townIdxToString(winrates[row].town);
        QString winCount = QString::number(winrates[row].winCount);
        QString loseCount = QString::number(winrates[row].loseCount);
        QString games = QString::number(winrates[row].winCount + winrates[row].loseCount);
        QString winrate = QString::number(winrates[row].winrate, 'f', 2) + '%';

        updateBrushByTown(brush, winrates[row].town);
        QTableWidgetItem* townItem = protoItem->clone();
        townItem->setBackground(*brush);

        QTableWidgetItem *item = townItem->clone();
        item->setText(townName);
        ui->tableWidget->setItem(row, 0, item);

        item = townItem->clone();
        item->setText(winCount);
        ui->tableWidget->setItem(row, 1, item);

        item = townItem->clone();
        item->setText(loseCount);
        ui->tableWidget->setItem(row, 2, item);

        item = townItem->clone();
        item->setText(winrate);
        ui->tableWidget->setItem(row, 3, item);

        item = townItem->clone();
        item->setText(games);
        ui->tableWidget->setItem(row, 4, item);
    }

    ui->tableWidget->resizeColumnsToContents();
}

ShowStatistics::~ShowStatistics()
{
    delete ui;
}

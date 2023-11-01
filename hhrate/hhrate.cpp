#include "hhrate.h"
#include "ui_hhrate.h"
#include "matchresultadder.h"
#include "showstatistics.h"
#include "upcomingmatch.h"
#include "matchupstatistics.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

hhrate::hhrate(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::hhrate)
    , m_matches(MatchResultsPtr().create())
    , m_changesPresented(false)
{
    ui->setupUi(this);
    QFile file;
    file.setFileName("matches.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString matches;
    matches = file.readAll();
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(matches.toUtf8());
    QJsonArray matchesArr = d.array();

    for(auto match : matchesArr) {
        m_matches->push_back({ static_cast<Town>  (match.toObject().take(jsonP1TownKey).toInt()),
                               static_cast<Town>  (match.toObject().take(jsonP2TownKey).toInt()),
                               static_cast<size_t>(match.toObject().take(jsonWinnedIdxKey).toInt()) });

    }
}


hhrate::~hhrate()
{
    if(m_changesPresented) {
        QFile file;
        file.setFileName("matches.json");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QJsonArray matchesJsonArr;
        for(const auto& match : *m_matches) {
            QJsonObject jsonMatch;
            jsonMatch.insert(jsonP1TownKey, match.player1);
            jsonMatch.insert(jsonP2TownKey, match.player2);
            jsonMatch.insert(jsonWinnedIdxKey, static_cast<int>(match.winnerIdx));
            matchesJsonArr.push_back(jsonMatch);
        }
        QJsonDocument dataJson(matchesJsonArr);
        file.write(dataJson.toJson());
        file.close();
    }
    delete ui;
}


void hhrate::addMatchResult(const MatchResult & result)
{
    m_matches->push_back(result);
    m_changesPresented = true;
}


void hhrate::on_pushButton_clicked()
{
    QWidget *wdg = new MatchResultAdder( this );
    wdg->show();
}


void hhrate::on_showStat_clicked()
{
    QWidget *wdg = new ShowStatistics(m_matches);
    wdg->show();
}


void hhrate::on_upcomingMatchBtn_clicked()
{
    QVector<WinrateData> winrates;
    for(int town = 0; town < Town::Size; ++town)
        winrates.push_back({ 0, 0, 0, static_cast<Town>(town) });

    for(auto& matchResult : *m_matches) {
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
              [](const WinrateData& lhs, const WinrateData& rhs){
        return lhs.winCount + lhs.loseCount < rhs.winCount + rhs.loseCount;
    });

    unsigned int minGamesCnt = winrates[0].loseCount + winrates[0].winCount;
    for(int i = 1; i < winrates.size(); ++i) {
        if(winrates[i].loseCount + winrates[i].winCount > minGamesCnt) {
            winrates.resize(i);
            break;
        }
    }

    std::sort(winrates.begin(), winrates.end(),
              [](const WinrateData& lhs, const WinrateData& rhs){ return lhs.winrate > rhs.winrate; });

    if(winrates[0].winrate > winrates[1].winrate)
        std::swap(winrates[0], winrates[1]);

    QWidget *wdg = new UpcomingMatch(winrates[0].town, winrates[1].town);
    wdg->show();
}


void hhrate::on_matchupBtn_clicked()
{
    QWidget *wdg = new MatchupStatistics(m_matches);
    wdg->show();
}


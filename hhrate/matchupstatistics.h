#pragma once

#include "utils.h"
#include <QWidget>

namespace Ui {
class MatchupStatistics;
}

class MatchupStatistics : public QWidget
{
    Q_OBJECT

public:
    explicit MatchupStatistics(MatchResultsPtr);
    ~MatchupStatistics();

private slots:
    void on_matchupTown_currentIndexChanged(int index);

private:
    void updateTable();

private:
    Ui::MatchupStatistics *ui;
    MatchResultsPtr m_matches;
};

#pragma once

#include "hhrate.h"
#include <QWidget>

namespace Ui {
class ShowStatistics;
}

class ShowStatistics : public QWidget
{
    Q_OBJECT

public:
    explicit ShowStatistics(MatchResultsPtr);
    ~ShowStatistics();

private:
    Ui::ShowStatistics *ui;
    hhrate* m_app;
    MatchResultsPtr m_matchResults;
};

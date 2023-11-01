#pragma once
#include "utils.h"
#include <QWidget>

namespace Ui {
class UpcomingMatch;
}

class UpcomingMatch : public QWidget
{
    Q_OBJECT

public:
    explicit UpcomingMatch(Town p1, Town p2);
    ~UpcomingMatch();

private:
    Ui::UpcomingMatch *ui;
};

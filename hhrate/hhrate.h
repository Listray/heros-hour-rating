#pragma once

#include "utils.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class hhrate; }
QT_END_NAMESPACE

class hhrate : public QMainWindow
{
    Q_OBJECT

public:
    hhrate(QWidget *parent = nullptr);
    ~hhrate();

    void addMatchResult(MatchResult const&);
    MatchResultsPtr matches() const { return m_matches; }

private slots:
    void on_pushButton_clicked();
    void on_showStat_clicked();
    void on_upcomingMatchBtn_clicked();

    void on_matchupBtn_clicked();

private:
    Ui::hhrate *ui;

    MatchResultsPtr m_matches;
    bool m_changesPresented;
};

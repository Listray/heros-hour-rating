#pragma once

#include <QString>
#include <QSharedPointer>
#include <QComboBox>

#define NoWinner 0

enum Town {
    Order,
    Pillars,
    Arcane,
    Decay,
    Pyro,
    Lament,
    Horde,
    Nature,
    Tide,
    Earth,
    Enclave,
    Delirum,
    Size,
};

extern const QString jsonP1TownKey;
extern const QString jsonP2TownKey;
extern const QString jsonWinnedIdxKey;

struct MatchResult
{
    Town player1;
    Town player2;
    size_t winnerIdx;
};

typedef QVector<MatchResult> MatchResults;
typedef QSharedPointer<MatchResults> MatchResultsPtr;

struct WinrateData
{
    unsigned int winCount;
    unsigned int loseCount;
    double winrate;
    Town town;
};

extern QString townIdxToString(const Town);
extern void updateBrushByTown(QBrush*, const Town);
extern void fillTownComboBox(QComboBox*);

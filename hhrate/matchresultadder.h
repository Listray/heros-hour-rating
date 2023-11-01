#pragma once

#include "hhrate.h"

#include <QWidget>

namespace Ui {
class MatchResultAdder;
}


class MatchResultAdder : public QWidget
{
    Q_OBJECT

public:
    explicit MatchResultAdder(hhrate* parent);
    ~MatchResultAdder();

private slots:
    void on_okBtn_clicked();

private:
    Ui::MatchResultAdder *ui;
    hhrate* m_app;
};

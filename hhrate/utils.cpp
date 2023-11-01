#include "utils.h"

#include <QRgb>
#include <QBrush>

extern const QString jsonP1TownKey = "p1t";
extern const QString jsonP2TownKey = "p2t";
extern const QString jsonWinnedIdxKey = "wIdx";

QString townIdxToString(const Town t)
{
   switch(t) {
       case Town::Order: return "Order";
       case Town::Pillars: return "Pillars";
       case Town::Arcane: return "Arcane";
       case Town::Decay: return "Decay";
       case Town::Pyro: return "Pyro";
       case Town::Lament: return "Lament";
       case Town::Horde: return "Horde";
       case Town::Nature: return "Nature";
       case Town::Tide: return "Tide";
       case Town::Earth: return "Earth";
       case Town::Enclave: return "Enclave";
       case Town::Delirum: return "Delirum";
       default: return "Unknown";
   }
}

void updateBrushByTown(QBrush* b, const Town t)
{
    switch(t) {
        case Town::Order: return b->setColor(QRgb(0xE0E0E0));
        case Town::Pillars: return b->setColor(QRgb(0x99FFCC));
        case Town::Arcane: return b->setColor(QRgb(0x9999FF));
        case Town::Decay: return b->setColor(QRgb(0xA0A0A0));
        case Town::Pyro: return b->setColor(QRgb(0xFF9999));
        case Town::Lament: return b->setColor(QRgb(0x994C00));
        case Town::Horde: return b->setColor(QRgb(0xFFB2C6));
        case Town::Nature: return b->setColor(QRgb(0x00CC66));
        case Town::Tide: return b->setColor(QRgb(0x99CCFF));
        case Town::Earth: return b->setColor(QRgb(0xCC6600));
        case Town::Enclave: return b->setColor(QRgb(0x00994C));
        case Town::Delirum: return b->setColor(QRgb(0xB266FF));
        default: return b->setColor(Qt::white);
    }
}

void fillTownComboBox(QComboBox* combo)
{
    for(int i = 0; i < Town::Size; ++i)
        combo->addItem(townIdxToString(static_cast<Town>(i)));
}

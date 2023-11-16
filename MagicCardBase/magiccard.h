#ifndef MAGICCARD_H
#define MAGICCARD_H

#include <QString>
#include <QJsonObject>

class MagicCard {
public:
    MagicCard();
    void readFromJsonObject(const QJsonObject &json);
    void writeToJsonObject(QJsonObject &json) const;

    QString name;
    QString type;
    double price;
    QString color;
    QString power; // QString вместо int, так как может быть null
    QString toughness;
    QString features;
    QString text;
};

#endif // MAGICCARD_H

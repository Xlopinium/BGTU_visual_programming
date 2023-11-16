#include "magiccard.h"

MagicCard::MagicCard() : price(0.0) {}

void MagicCard::readFromJsonObject(const QJsonObject &json) {
    name = json["name"].toString();
    type = json["type"].toString();
    price = json["price"].toDouble();
    color = json["color"].toString();
    power = json["power"].toString();
    toughness = json["toughness"].toString();
    features = json["features"].toString();
    text = json["text"].toString();
}

void MagicCard::writeToJsonObject(QJsonObject &json) const {
    json["name"] = name;
    json["type"] = type;
    json["price"] = price;
    json["color"] = color;
    json["power"] = power;
    json["toughness"] = toughness;
    json["features"] = features;
    json["text"] = text;
}

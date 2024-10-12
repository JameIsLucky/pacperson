//
// Created by jame on 12.10.24.
//

#include "Punkt.h"


// Konstruktor zur Initialisierung des Punkts
Punkt::Punkt(float x, float y, float radius, sf::Color farbe) {
    kreis.setRadius(radius);               // Setzt den Radius des Kreises
    kreis.setPosition(x, y);               // Setzt die Position des Punkts
    kreis.setFillColor(farbe);             // Setzt die Farbe des Punkts
    kreis.setOrigin(radius, radius);       // Setzt den Ursprung in die Mitte des Kreises
}

// Methode zum Zeichnen des Punkts
void Punkt::zeichne(sf::RenderWindow& fenster) const {
    fenster.draw(kreis);  // Zeichnet den Punkt im angegebenen Fenster
}

// Getter-Methode, um die Position des Punkts abzurufen
sf::Vector2f Punkt::getPosition() const {
    return kreis.getPosition();  // Gibt die aktuelle Position des Kreises zurück
}

// Getter-Methode, um den Radius des Punkts abzurufen
float Punkt::getRadius() const {
    return kreis.getRadius();  // Gibt den Radius des Kreises zurück
}
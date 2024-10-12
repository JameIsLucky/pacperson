//
// Created by jame on 12.10.24.
//

#include "Spieler.h"

Spieler::Spieler(float x, float y, float radius, sf::Color farbe, float schrittGroesse)
        : schrittGroesse(schrittGroesse), spielfeldGroesse(512.0f) {
    spielerKreis.setRadius(radius);
    spielerKreis.setPosition(x, y);
    spielerKreis.setFillColor(farbe);
    spielerKreis.setOrigin(radius, radius);  // Ursprung in die Mitte setzen
    richtung = sf::Vector2f(1.0f, 0.0f);     // Anfangsbewegung nach rechts
}

// Methode zum automatischen Bewegen des Spielers in die aktuelle Richtung
void Spieler::bewegeAutomatisch() {
    // Berechne die nächste Position
    sf::Vector2f neuePosition = spielerKreis.getPosition() + richtung * schrittGroesse;

    // Begrenze die Bewegung auf das Spielfeld (keine Bewegung außerhalb der Grenzen)
    if (neuePosition.x >= 0 && neuePosition.x <= spielfeldGroesse &&
        neuePosition.y >= 0 && neuePosition.y <= spielfeldGroesse) {
        spielerKreis.setPosition(neuePosition);
    }
}

// Methode zum Setzen der Bewegungsrichtung basierend auf der gedrückten Pfeiltaste
void Spieler::setzeRichtung(sf::Keyboard::Key taste) {
    if (taste == sf::Keyboard::Up) {
        richtung = sf::Vector2f(0.0f, -1.0f);  // Bewegung nach oben
    }
    else if (taste == sf::Keyboard::Down) {
        richtung = sf::Vector2f(0.0f, 1.0f);   // Bewegung nach unten
    }
    else if (taste == sf::Keyboard::Left) {
        richtung = sf::Vector2f(-1.0f, 0.0f);  // Bewegung nach links
    }
    else if (taste == sf::Keyboard::Right) {
        richtung = sf::Vector2f(1.0f, 0.0f);   // Bewegung nach rechts
    }
}

// Methode zum Rendern des Spielers
void Spieler::zeichne(sf::RenderWindow& fenster) const {
    fenster.draw(spielerKreis);
}

// Methode zum Abrufen der aktuellen Position des Spielers
sf::Vector2f Spieler::getPosition() const {
    return spielerKreis.getPosition();
}

// Methode zum Abrufen des Radius des Spielers
float Spieler::getRadius() const {
    return spielerKreis.getRadius();
}

// Methode zur Begrenzung auf das Spielfeld
void Spieler::setzeSpielfeldGrenze(float groesse) {
    spielfeldGroesse = groesse;
}
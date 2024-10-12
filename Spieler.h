//
// Created by jame on 12.10.24.
//

#ifndef PACPERSON_SPIELER_H
#define PACPERSON_SPIELER_H

#include <SFML/Graphics.hpp>

class Spieler {
public:
    Spieler(float x, float y, float radius, sf::Color farbe, float schrittGroesse);

    // Methode zum automatischen Bewegen des Spielers
    void bewegeAutomatisch();

    // Methode zum Setzen der Bewegungsrichtung
    void setzeRichtung(sf::Keyboard::Key taste);

    // Methode zum Rendern des Spielers
    void zeichne(sf::RenderWindow& fenster) const;

    // Methode zum Abrufen der aktuellen Position
    sf::Vector2f getPosition() const;

    // Methode zum Abrufen des Radius
    float getRadius() const;

    // Methode zur Begrenzung auf das Spielfeld
    void setzeSpielfeldGrenze(float groesse);

private:
    sf::CircleShape spielerKreis;
    sf::Vector2f richtung;  // Richtung des Spielers
    float schrittGroesse;   // Schrittgröße (Größe des Gitters)
    float spielfeldGroesse; // Spielfeldgröße, um die Bewegungen zu begrenzen
};


#endif //PACPERSON_SPIELER_H

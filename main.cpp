#include <SFML/Graphics.hpp>
#include "Punkt.h"
#include "Spieler.h"
#include <vector>
#include <cmath>

//so ganz verstehe ich selber nicht was hier abgeht
float berechneAbstand(sf::Vector2f p1, sf::Vector2f p2) {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return std::sqrt(dx * dx + dy * dy);
}

int main()
{
    sf::RenderWindow fenster(sf::VideoMode(512, 512), "Pacperson Prototype", sf::Style::Close);
    fenster.setFramerateLimit(60);

    const int anzahlPunkte = 16;
    const float fensterGroesse = 512.f;
    const float punktRadius = fensterGroesse /  (3 *anzahlPunkte);
    const float abstand = fensterGroesse / anzahlPunkte * 1.5;

    std::vector<Punkt> punkte;

    // Initialisiere die Punkte und füge sie dem Vektor hinzu
    for (int i = 0; i < anzahlPunkte; ++i) {
        for (int j = 0; j < anzahlPunkte; ++j) {
            float x = j * abstand + punktRadius;  // Berechne die x-Position
            float y = i * abstand + punktRadius;  // Berechne die y-Position
            punkte.emplace_back(x, y, punktRadius, sf::Color::White);
        }
    }

    Spieler spieler(256.f, 256.f, 15.f, sf::Color::Yellow, abstand);

    spieler.setzeSpielfeldGrenze(fensterGroesse);
    const float geschwindigkeit = 0.13f; //Dieser Wert fühlt sich am natürlichsten an, ist aber nach Gefühl geschätzt

    sf::Clock uhr;

    //Hauptflow des Programms
    while(fenster.isOpen()){

        sf::Event event;
        while(fenster.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                fenster.close();
            if(event.type == sf::Event::KeyPressed){
                spieler.setzeRichtung(event.key.code);
            }
        }

        if (uhr.getElapsedTime().asSeconds() > geschwindigkeit) {
            spieler.bewegeAutomatisch();
            uhr.restart();
        }

        for (auto it = punkte.begin(); it != punkte.end(); ){
            float abstand = berechneAbstand(spieler.getPosition(), it->getPosition());
            if (abstand < spieler.getRadius() + it->getRadius()) {
                it = punkte.erase(it);  // Punkt entfernen, wenn er berührt wird
            } else {
                ++it;  // Zum nächsten Punkt übergehen
            }
        }

        fenster.clear(sf::Color::Black);

        for (const auto& punkt : punkte) {
            punkt.zeichne(fenster);
        }

        spieler.zeichne(fenster);

        fenster.display();

    }

    return 0;
}
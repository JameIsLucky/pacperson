#include <SFML/Graphics.hpp>
#include "Punkt.h"
#include "Spieler.h"
#include <vector>
#include <cmath>

// sehr interessante Funktion
float berechneAbstand(sf::Vector2f p1, sf::Vector2f p2) {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return std::sqrt(dx * dx + dy * dy);
}

int main()
{
    sf::RenderWindow fenster(sf::VideoMode(512, 512), "Pacperson Prototype", sf::Style::Close);
    fenster.setFramerateLimit(144);

    bool spielGestartet = false;

    sf::Font schriftart;
    if (!schriftart.loadFromFile("../assets/fonts/HomeVideo-BLG6G.ttf")){
        return -1; // Fehler beim Laden
    }

    sf::Text titelText("Pac Person", schriftart, 50);
    titelText.setFillColor(sf::Color::White);
    titelText.setPosition(110.f, 200.f);

    sf::Text anweisungsText("Press Space to start", schriftart, 20);
    anweisungsText.setFillColor(sf::Color::White);
    anweisungsText.setPosition(130.f, 300.f);



    const int anzahlPunkte = 16; //die Zahl darf nicht mehr geändert werden sonst gibt es große Probleme
    const float fensterGroesse = 512.f;
    const float punktRadius = fensterGroesse /  (3 * anzahlPunkte);
    const float abstand = fensterGroesse / anzahlPunkte; //*1.5

    std::vector<Punkt> punkte;

    Spieler spieler(8 * abstand + punktRadius, 8 * abstand + punktRadius, fensterGroesse /  (2 * anzahlPunkte), sf::Color::Yellow, abstand);

    spieler.setzeSpielfeldGrenze(fensterGroesse);
    const float geschwindigkeit = 0.13f; //Dieser Wert fühlt sich am natürlichsten an, ist aber nach Gefühl geschätzt

    sf::Clock uhr;

    // Initialisiere die Punkte und füge sie dem Vektor hinzu
    for (int i = 0; i < anzahlPunkte; ++i) {
        for (int j = 0; j < anzahlPunkte; ++j) {
            float x = j * abstand + punktRadius;  // Berechne die x-Position
            float y = i * abstand + punktRadius;  // Berechne die y-Position
            punkte.emplace_back(x, y, punktRadius, sf::Color::White);
        }
    }

    //Hauptflow des Programms
    while(fenster.isOpen()){

        sf::Event event;
        while(fenster.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                fenster.close();
            if(!spielGestartet && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
                spielGestartet = true;
            }
            if(spielGestartet && event.type == sf::Event::KeyPressed){
                spieler.setzeRichtung(event.key.code);
            }
        }
        if (spielGestartet) {
            if (uhr.getElapsedTime().asSeconds() > geschwindigkeit) {
                spieler.bewegeAutomatisch();
                uhr.restart();
            }

            for (auto it = punkte.begin(); it != punkte.end();) {
                float abstand = berechneAbstand(spieler.getPosition(), it->getPosition());
                if (abstand < spieler.getRadius() + it->getRadius()) {
                    it = punkte.erase(it);  // Punkt entfernen, wenn er berührt wird
                } else {
                    ++it;  // Zum nächsten Punkt übergehen
                }
            }

            fenster.clear(sf::Color::Blue);

            for (const auto &punkt: punkte) {
                punkt.zeichne(fenster);
            }
            spieler.zeichne(fenster);
        } else{
            fenster.clear(sf::Color::Black);  // Hintergrund Schwarz
            fenster.draw(titelText);
            fenster.draw(anweisungsText);
        }

        fenster.display();
    }
    return 0;
}
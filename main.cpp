#include <SFML/Graphics.hpp>
#include "Punkt.h"
#include "Spieler.h"
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

//#define DEBUG
//#define ZUFALL_ANORDNUNG

/*
 * Wird der Kommentar vor ZUFALL_ANORDNUNG entfernt, so erscheint das Spielfeld in einem zufälligen Raster, d.h.
 *  alle Punkte sind mit einer 50% Wahrscheinlichkeit entweder da oder nicht da. Dies verkürzt das Spiel und fügt
 *  eine gewisse "Schwierigkeit" hinzu.
 *
 *  DEBUG fügt einen Debug-Modus hinzu, der beim Drücken der Taste "D" nach Beginn des Spiels sofort alle Punkte zählt
 *  und zum Endbildschirm springt.
 *  TO-DO: DEBUG addiert sich immer auf 256 Punkte.
 */

// sehr interessante Funktion
float berechneAbstand(sf::Vector2f p1, sf::Vector2f p2) {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return std::sqrt(dx * dx + dy * dy);
}

int main()
{
    sf::RenderWindow fenster(sf::VideoMode(512, 512), "Pacperson Alpha 0.3", sf::Style::Close);
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    fenster.setPosition(sf::Vector2i((desktopMode.width - 512) / 2, (desktopMode.height - 512) / 2));
    fenster.setVerticalSyncEnabled(true);

    //Zufallsgenerator
    std::srand(static_cast<unsigned int>(std::time(0)));


    bool spielGestartet = false;
    bool spielBeendet = false;
    int gesammeltePunkte = 0;

    sf::Font schriftart;
    if (!schriftart.loadFromFile("assets/fonts/HomeVideo-BLG6G.ttf")){
        return -1; // Fehler beim Laden
    }

    //Willkommensbildschirm Text
    sf::Text titelText("Pac Person", schriftart, 50);
    titelText.setFillColor(sf::Color::White);
    titelText.setPosition(110.f, 200.f);

    sf::Text anweisungsText("Press Space to start", schriftart, 20);
    anweisungsText.setFillColor(sf::Color::White);
    anweisungsText.setPosition(130.f, 300.f);

    //Endbildschirm Text
    sf::Text endText("Du hast gewonnen!", schriftart, 35);
    endText.setFillColor(sf::Color::White);
    endText.setPosition(50.f, 200.f);

    sf::Text punktzahlText("", schriftart, 20);
    punktzahlText.setFillColor(sf::Color::White);
    punktzahlText.setPosition(130.f, 300.f);


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
#ifdef ZUFALL_ANORDNUNG
            //50/50 Wahrscheinlichkeit für das Erscheinen einer Kugel
            if(std::rand() % 2 == 0) {
#endif
                float x = j * abstand + punktRadius;  // Berechne die x-Position
                float y = i * abstand + punktRadius;  // Berechne die y-Position
                punkte.emplace_back(x, y, punktRadius, sf::Color::White);
#ifdef ZUFALL_ANORDNUNG
            }
#endif
        }
    }

    //Hauptflow des Programms
    while(fenster.isOpen()) {

        sf::Event event;

        while (fenster.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                fenster.close();
            }
            //Spiel startet, wenn die Leertaste gedrückt wird
            if (!spielGestartet && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                spielGestartet = true;
            }
            //Spieler wird während des Spiels gesteuert
            if (spielGestartet && !spielBeendet && event.type == sf::Event::KeyPressed) {
                spieler.setzeRichtung(event.key.code);
            }

#ifdef DEBUG
        // Debug-Modus: Zum Endbildschirm springen (Taste 'D')
        if (spielGestartet && !spielBeendet && event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::D) {
            punkte.clear();  // Alle Punkte "aufessen"
            gesammeltePunkte = anzahlPunkte * anzahlPunkte;  // Maximale Punktzahl setzen
            spielBeendet = true;
            punktzahlText.setString("DEBUG: " + std::to_string(gesammeltePunkte));
            }
#endif
        }

        // Spielende überprüfen
        if (spielGestartet && punkte.empty() && !spielBeendet) {
            spielBeendet = true;

            // Punktzahltext aktualisieren
            punktzahlText.setString("Gesammelte Punkte: " + std::to_string(gesammeltePunkte));

        }

        if (spielGestartet && !spielBeendet) {
            if (uhr.getElapsedTime().asSeconds() > geschwindigkeit) {
                spieler.bewegeAutomatisch();
                uhr.restart();
            }

            for (auto it = punkte.begin(); it != punkte.end();) {
                float abstand = berechneAbstand(spieler.getPosition(), it->getPosition());
                if (abstand < spieler.getRadius() + it->getRadius()) {
                    it = punkte.erase(it);  // Punkt entfernen, wenn er berührt wird
                    gesammeltePunkte++;
                } else {
                    ++it;  // Zum nächsten Punkt übergehen
                }
            }

            fenster.clear(sf::Color::Blue);

            for (const auto &punkt: punkte) {
                punkt.zeichne(fenster);
            }
            spieler.zeichne(fenster);
        }else if(spielBeendet){
            fenster.clear(sf::Color::Black);  // Hintergrund Schwarz
            fenster.draw(endText);
            fenster.draw(punktzahlText);
        }
        else{
            fenster.clear(sf::Color::Black);  // Hintergrund Schwarz
            fenster.draw(titelText);
            fenster.draw(anweisungsText);
        }

        fenster.display();
    }
    return 0;
}

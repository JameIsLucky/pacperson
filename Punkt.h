//
// Created by jame on 12.10.24.
//

#ifndef PACPERSON_PUNKT_H
#define PACPERSON_PUNKT_H

#include <SFML/Graphics.hpp>

class Punkt {
public:
    Punkt(float x, float y, float radius, sf::Color farbe);

    void zeichne(sf::RenderWindow& fenster) const;

    // Öffentlich zugängliche Getter für Position und Radius
    sf::Vector2f getPosition() const;
    float getRadius() const;

private:
    sf::CircleShape kreis;
};


#endif //PACPERSON_PUNKT_H

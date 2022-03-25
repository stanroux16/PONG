#ifndef INPUT_HPP
#define INPUT_HPP

#include <SFML/Graphics.hpp>

class Input
{

    struct Button { bool left, right, up, down, escape; };
public:
    Input();
    Button getButton() const;
    void inputHandler(sf::Event event, sf::RenderWindow& window);

private:
    Button m_button;
    
};

#endif
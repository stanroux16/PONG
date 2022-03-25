#include <string>
#include <cmath>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "header/Input.hpp"

using namespace sf;
using namespace std;

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;

void setText(Text& text, String str);
void checkBtn();

// UI
RenderWindow window;
Input input;
Font font;
Text txt;

// Raquettes
int posRaquetteLeftX = 50;
int posRaquetteRightX = WIN_WIDTH - 70;
int posRaquetteLeftY = WIN_HEIGHT / 2;
int posRaquetteRightY = posRaquetteLeftY;
int raquetteSpeed = 1;
int raquetteHeight = 150;
int raquetteWidth = 20;

// Balle
float balleSpeed = 0.7f;
Vector2f ballDir = Vector2f(1.5f, 2.0f);
int ballePosX = WIN_WIDTH / 2;
int ballePosY = WIN_HEIGHT / 2;

// Score
int scoreJ1 = 0;
int scoreJ2 = 0;

void updateBall()
{
    ballePosX += ballDir.x * balleSpeed;
    ballePosY += ballDir.y * balleSpeed;

    // Verification des collisions

    // Raquettes
    if(
        (ballePosX < posRaquetteLeftX + raquetteWidth &&
        ballePosX > posRaquetteLeftX &&
        ballePosY < posRaquetteLeftY + raquetteHeight &&
        ballePosY > posRaquetteLeftY)
        ||
        (ballePosX > posRaquetteRightX - raquetteWidth &&
        ballePosX < posRaquetteRightX &&
        ballePosY < posRaquetteRightY + raquetteHeight &&
        ballePosY > posRaquetteRightY)
    )
    {
        ballDir.x *= -1;
    }

    // Murs

    // Gauche
    if (ballePosX < 0)
    {
        scoreJ2++;
        ballePosX = WIN_WIDTH / 2;
        ballePosY = WIN_HEIGHT / 2;
        ballDir.x = fabs(ballDir.x);
        ballDir.y *= -1;
        setText(txt, to_string(scoreJ1) + " - " + to_string(scoreJ2));
    }
    
    // Droit
    if (ballePosX > WIN_WIDTH)
    {
        scoreJ1++;
        ballePosX = WIN_WIDTH / 2;
        ballePosY = WIN_HEIGHT / 2;
        ballDir.x = -fabs(ballDir.x);
        ballDir.y *= -1;
        setText(txt, to_string(scoreJ1) + " - " + to_string(scoreJ2));
    }

    // Haut et Bas
    if (ballePosY > WIN_HEIGHT || ballePosY < 0)
    {
        ballDir.y *= -1;
    }
    
}

void raquetteIA()
{
    posRaquetteRightY = ballePosY;
}

int main()
{
    window.create(VideoMode(WIN_WIDTH, WIN_HEIGHT, 32), "PONG", Style::Default);
    font.loadFromFile("res/font.ttf");
    setText(txt, to_string(scoreJ1) + " - " + to_string(scoreJ2));

    CircleShape balle(15);
    balle.setPosition(ballePosX, ballePosY);

    RectangleShape raquetteLeft(Vector2f(raquetteWidth, raquetteHeight));
    raquetteLeft.setPosition(posRaquetteLeftX, posRaquetteLeftY);

    RectangleShape raquetteRight(Vector2f(raquetteWidth, raquetteHeight));
    raquetteRight.setPosition(posRaquetteRightX, posRaquetteRightY);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            input.inputHandler(event, window);
        }
        checkBtn();

        raquetteLeft.setPosition(posRaquetteLeftX, posRaquetteLeftY);
        raquetteRight.setPosition(posRaquetteRightX, posRaquetteRightY);

        updateBall();
        balle.setPosition(ballePosX, ballePosY);
        raquetteIA();

        window.clear(Color::Black);
        window.draw(txt);
        window.draw(raquetteLeft);
        window.draw(raquetteRight);
        window.draw(balle);

        window.display();
    }
    
    return 0;
}

void setText(Text& txt, String str)
{
    txt.setFont(font);
    txt.setString(str);
    txt.setCharacterSize(26);
    txt.setFillColor(Color::White);
    txt.setPosition(((WIN_WIDTH / 2) - 40), 10);
}

void checkBtn()
{
    if (input.getButton().up == true)
    {
        posRaquetteLeftY -= raquetteSpeed;
        if (posRaquetteLeftY < 0)
        {
            posRaquetteLeftY = 0;
        }
    }

    if (input.getButton().down == true)
    {
        posRaquetteLeftY += raquetteSpeed;
        if (posRaquetteLeftY + raquetteHeight > WIN_HEIGHT)
        {
            posRaquetteLeftY = WIN_HEIGHT - raquetteHeight;
        }
    }

    if (input.getButton().left == true)
    {
        posRaquetteRightY -= raquetteSpeed;
        if (posRaquetteRightY < 0)
        {
            posRaquetteRightY = 0;
        }
    }

    if (input.getButton().right == true)
    {
        posRaquetteRightY += raquetteSpeed;
        if (posRaquetteRightY + raquetteHeight > WIN_HEIGHT)
        {
            posRaquetteRightY = WIN_HEIGHT - raquetteHeight;
        }
    }

    if (input.getButton().escape == true)
    {
        window.close();
    }
    
}
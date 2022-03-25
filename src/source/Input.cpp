#include "../header/Input.hpp"

using namespace sf;

Input::Input()
{
    m_button.down = m_button.escape = m_button.left = m_button.right = m_button.up = false;
}

Input::Button Input::getButton() const
{
    return m_button;
}

void Input::inputHandler(Event event, RenderWindow& window)
{
    if (event.type == Event::Closed)
    {
        window.close();
    }
    if (event.type == Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case Keyboard::Escape:
            m_button.escape = true;
            break;
        case Keyboard::Left:
            m_button.left = true;
            break;
        case Keyboard::Right:
            m_button.right = true;
            break;
        case Keyboard::Up:
            m_button.up = true;
            break;
        case Keyboard::Down:
            m_button.down = true;
            break;
        
        default:
            break;
        }
    }
    if (event.type == Event::KeyReleased)
    {
        switch (event.key.code)
        {
        case Keyboard::Escape:
            m_button.escape = false;
            break;
        case Keyboard::Left:
            m_button.left = false;
            break;
        case Keyboard::Right:
            m_button.right = false;
            break;
        case Keyboard::Up:
            m_button.up = false;
            break;
        case Keyboard::Down:
            m_button.down = false;
            break;
        
        default:
            break;
        }
    }
    
}
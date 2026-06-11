
#include "Balloon.h"
#include <string>
#include "Window.h"

Balloon::Balloon(Window* window)
{
    m_pos = Pos{ 0.0f, 0.0f };
    this->window = window;
}

Balloon::Balloon(float x, float y, const std::string& image)
{

}

void Balloon::move(float dx, float dy)
{
    m_pos.x += dx;
    m_pos.y += dy;
}

void Balloon::render() const
{
    // drawSprite(m_image, m_pos.x, m_pos.y);
}

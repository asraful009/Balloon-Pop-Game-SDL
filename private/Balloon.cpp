
#include "Balloon.h"
#include <string>
#include <iostream>
#include "Window.h"

Balloon::Balloon(Window *window)
{
    if (window == nullptr)
    {
        std::cerr << "Error: Window pointer is null in Balloon constructor.\n";
        return;
    }
    m_pos = Pos{0.0f, 0.0f};
    this->window = window;
    m_image = imageToTexture("assets/balloon.png");
}

Balloon::Balloon(float x, float y, const std::string &image, Window *window)
{
    if (window == nullptr)
    {
        std::cerr << "Error: Window pointer is null in Balloon constructor.\n";
        return;
    }
    m_pos = Pos{x, y};
    this->window = window;
    m_image = imageToTexture(image);
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

SDL_Texture *Balloon::imageToTexture(std::string imagePath)
{
    if (window == nullptr)
    {
        std::cerr << "Error: Window pointer is null in Balloon constructor.\n";
        return nullptr;
    }
    SDL_Texture *texture = window->loadTexture(imagePath);
    if (!texture)
    {
        std::cerr << "Failed to load image: " << imagePath << "\n";
    }
    return texture;
}

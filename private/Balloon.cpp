
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

Balloon::Balloon(float x, float y, const std::string &image, const std::string &image_pop, Window *window)
{
    if (window == nullptr)
    {
        std::cerr << "Error: Window pointer is null in Balloon constructor.\n";
        return;
    }
    m_pos = Pos{x, y};
    this->window = window;
    m_image = imageToTexture(image);
    m_image_pop = imageToTexture(image_pop);
}

void Balloon::move(float dt)
{
    if (popped) {
        m_pos.y += +98.8*dt;
        if (m_pos.y > window->getHeight()) {
            m_pos.y = window->getHeight();
            popped = false;
        }
    } else {
        m_pos.y += -60.0f * dt;
        // m_pos.y += dy;
    }
}

void Balloon::render() const
{
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

bool Balloon::isPop(float mx, float my, int *score)
{
    if (mx >= m_pos.x 
        && mx < m_pos.x + m_pos.w 
        && my >= m_pos.y 
        && my < m_pos.y + m_pos.h
        && !popped
    )
    {
        popped = true;
        (*score)++;
        return true;
    }
    return false;
}
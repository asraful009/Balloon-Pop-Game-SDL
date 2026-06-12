
#include "Balloon.h"
#include <string>
#include <iostream>
#include "Window.h"
#include <SDL2/SDL_mixer.h>

Balloon::Balloon(Window *window)
{
    if (window == nullptr)
    {
        std::cerr << "Error: Window pointer is null in Balloon constructor.\n";
        return;
    }
    m_pos = Pos{0.0f, 0.0f};
    speed = rand() % 30 + 60.0f;
    this->window = window;
    m_image = imageToTexture("assets/balloon.png");
    m_image_pop = imageToTexture("assets/balloon_pop.png");
    popSound = window->loadWav("assets/pop.wav");
}

Balloon::Balloon(float x, float y, const std::string &image, const std::string &image_pop, Window *window)
{
    if (window == nullptr)
    {
        std::cerr << "Error: Window pointer is null in Balloon constructor.\n";
        return;
    }
    m_pos = Pos{x, y};
    m_initialPos = Pos{x, y};
    speed = rand() % 30 + 60.0f;
    this->window = window;
    m_image = imageToTexture(image);
    m_image_pop = imageToTexture(image_pop);
    if (this->window == nullptr) {
        std::cerr << "Error: Window pointer is null in Balloon constructor.\n";
    } else {
        popSound = window->loadWav("assets/pop.wav");
    }
}

void Balloon::move(float dt)
{
    if (popped) {
        m_pos.y += +98.8*dt;
        if (m_pos.y > window->getHeight() + 40) {
            m_pos.y = m_pos.y - rand() % 10; // Random y position near the bottom
            popped = false;
        }
    } else {
        m_pos.y += -speed * dt;
        if (m_pos.y < -40.0f) {
            m_pos.y = window->getHeight() + 32 + rand() % 10; // Reset to bottom of the window
        }
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
        Mix_PlayChannel(-1, popSound, 0);
        return true;
    }
    return false;
}
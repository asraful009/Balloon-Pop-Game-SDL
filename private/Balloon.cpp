
#include "Balloon.h"
#include <string>
#include <iostream>
#include "Window.h"
#include <SDL2/SDL_mixer.h>
#include "../images/balloon.h"
#include "../images/balloon_pop.h"
#include "../sounds/pop.h"

Balloon::Balloon(float x, float y, Window *window)
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
    m_image = imageToTexture(balloon_png, balloon_png_len);
    m_image_pop = imageToTexture(balloon_pop_png, balloon_pop_png_len);    
    popSound = wavToSound(pop_wav, pop_wav_len);
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

SDL_Texture *Balloon::imageToTexture(const unsigned char *imageData, const int size)
{
    if (window == nullptr)
    {
        std::cerr << "Error: Window pointer is null in Balloon constructor.\n";
        return nullptr;
    }
    SDL_Texture *texture = window->loadTexture(imageData, size);
    if (!texture)
    {
        std::cerr << "Failed to load image\n";
    }
    return texture;
}


Mix_Chunk *Balloon::wavToSound(const unsigned char *imageData, const int size)
{
    if (window == nullptr)
    {
        std::cerr << "Error: Window pointer is null in Balloon constructor.\n";
        return nullptr;
    }
    Mix_Chunk *chunk = window->loadWav(imageData, size);
    if (!chunk)
    {
        std::cerr << "Failed to load sound\n";
    }
    return chunk;
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
#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Window.h"

struct Pos
{
    float x;
    float y;
};

class Balloon
{
private:
    Pos m_pos;
    SDL_Texture *m_image;
    Window *window;

public:
    Balloon(Window *window);
    Balloon(float x, float y, const std::string &image);

    // Getters
    Pos getXY() const { return m_pos; };
    float getX() const { return m_pos.x; }
    float getY() const { return m_pos.y; }
    SDL_Texture *getImage() const { return m_image; }

    // Setters
    void setXY(float x, float y)
    {
        m_pos.x = x;
        m_pos.y = y;
    }
    void setX(float x) { m_pos.x = x; }
    void setY(float y) { m_pos.y = y; }

    // Utility
    void move(float dx, float dy);
    void render() const;

private:
    SDL_Texture *imageToTexture(std::string imagePath);
};
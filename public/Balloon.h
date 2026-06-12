#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Window.h"

struct Pos
{
    float x;
    float y;
    float w = 32.0f;
    float h = 32.0f;
    float speed;

};

class Balloon
{
private:
    Pos m_pos;
    SDL_Texture *m_image;
    SDL_Texture *m_image_pop;
    bool popped = false;
    Window *window;

public:
    Balloon(Window *window);
    Balloon(float x, float y, const std::string &image, const std::string &image_pop, Window *window);

    // Getters
    Pos getXY() const { return m_pos; };
    float getX() const { return m_pos.x; }
    float getY() const { return m_pos.y; }
    SDL_Texture *getImage() const { return popped ? m_image_pop : m_image; }


    // Utility
    void move(float dt);
    void render() const;
    bool isPop(float mx, float my, int *score);

private:
    SDL_Texture *imageToTexture(std::string imagePath);
};
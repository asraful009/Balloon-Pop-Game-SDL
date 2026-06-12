#pragma once

#include <string>
#include <vector>
#include <functional>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

struct TextItem
{
    std::string text;
    float x, y;
    SDL_Color color;
};

struct LineItem
{
    float x1, y1, x2, y2;
    SDL_Color color;
};

struct ImageItem
{
    float x, y;
    SDL_Texture *texture;
};

class Window
{
public:
    Window(const std::string &title, int width, int height);
    ~Window();

    using UpdateCallback = std::function<void(float)>;

    void run();
    bool isRunning() const { return m_running; }
    void drawText(const std::string &text, float x, float y, SDL_Color color);
    void drawLine(float x1, float y1, float x2, float y2, SDL_Color color);
    void drawImage(SDL_Texture *texture, float x, float y);

    SDL_Texture *loadTexture(const std::string &path);
    Mix_Chunk *loadWav(const std::string &path);
    void setUpdateCallback(UpdateCallback callback);

    SDL_Color hexToRGBA(uint32_t hexValue)
    {
        SDL_Color color;
        color.r = (hexValue >> 24) & 0xFF;
        color.g = (hexValue >> 16) & 0xFF;
        color.b = (hexValue >> 8) & 0xFF;
        color.a = hexValue & 0xFF;
        return color;
    }

    float getMouseX() const { return static_cast<float>(m_mouseX); }
    float getMouseY() const { return static_cast<float>(m_mouseY); }
    int getWidth() const { return m_window ? SDL_GetWindowSurface(m_window)->w : 0; }
    int getHeight() const { return m_window ? SDL_GetWindowSurface(m_window)->h : 0; }
    bool isMouseButtonDown(int button) const { return m_mouseButtons & SDL_BUTTON(button); }

private:
    void handleEvents();
    void render();
    void renderText(const TextItem &item);
    void renderLine(const LineItem &item);
    void renderImage(const ImageItem &item, float x, float y);

    Uint32 m_lastTime = 0;
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;
    TTF_Font *m_font = nullptr;
    bool m_running = false;
    std::vector<TextItem> m_texts;
    std::vector<LineItem> m_lines;
    std::vector<ImageItem> m_images;
    UpdateCallback m_updateCallback = nullptr;

    int m_mouseX = 0;
    int m_mouseY = 0;
    Uint32 m_mouseButtons = 0;
};
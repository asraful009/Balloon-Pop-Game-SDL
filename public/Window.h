#pragma once

#include <string>
#include <vector>
#include <functional>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


struct TextItem {
    std::string text;
    int x, y;
    SDL_Color color;
};

struct LineItem {
    int x1, y1, x2, y2;
    SDL_Color color;
};

struct ImageItem {
    int x, y;
    SDL_Texture* texture;
};

class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    using UpdateCallback = std::function<void(float)>;

    void run();
    bool isRunning() const { return m_running; }
    void drawText(const std::string& text, int x, int y, SDL_Color color);
    void drawLine(int x1, int y1, int x2, int y2, SDL_Color color);
    SDL_Texture* loadTexture(const std::string& path);
    void drawImage(SDL_Texture* texture, int x, int y);
    void setUpdateCallback(UpdateCallback callback);

    SDL_Color hexToRGBA(uint32_t hexValue) {
        SDL_Color color;
        color.r = (hexValue >> 24) & 0xFF;
        color.g = (hexValue >> 16) & 0xFF;
        color.b = (hexValue >> 8) & 0xFF;
        color.a = hexValue & 0xFF;
        return color;
    }

    int getMouseX() const { return m_mouseX; }
    int getMouseY() const { return m_mouseY; }
    bool isMouseButtonDown(int button) const { return m_mouseButtons & SDL_BUTTON(button); }


private:
    void handleEvents();
    void render();
    void renderText(const TextItem& item);
    void renderLine(const LineItem& item);

    Uint32        m_lastTime = 0;
    SDL_Window*   m_window   = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    TTF_Font*     m_font     = nullptr;
    bool          m_running  = false;
    std::vector<TextItem> m_texts;
    std::vector<LineItem> m_lines;
    std::vector<ImageItem> m_images;
    UpdateCallback m_updateCallback = nullptr;

    int m_mouseX = 0;
    int m_mouseY = 0;
    Uint32 m_mouseButtons = 0;
};
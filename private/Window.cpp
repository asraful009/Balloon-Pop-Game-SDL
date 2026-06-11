
#include "Window.h"
#include "../fonts/NotoSanBenglaRegular.h"
#include <iostream>

Window::Window(const std::string& title, int width, int height) {
    
    // init SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return;
    }
    
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
    }

    m_window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI
    );

    if (!m_window) {
        std::cerr << "Window Creation Error: " << SDL_GetError() << "\n";
        return;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer) {
        std::cerr << "Renderer Creation Error: " << SDL_GetError() << "\n";
        return;
    }
    SDL_RWops* rw = SDL_RWFromMem(
        font_ttf, 
        font_ttf_len);
    m_font = TTF_OpenFontRW(rw, 1, 12);
    if (!m_font) {
        std::cerr << "Font error: " << TTF_GetError() << "\n";
    } else {
        #if SDL_TTF_VERSION_ATLEAST(2, 20, 0)
            TTF_SetFontScriptName(m_font, "Beng");
        #endif
    }

    m_lastTime = SDL_GetTicks();
    m_running  = true;
}

Window::~Window() {
    
    TTF_CloseFont(m_font);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    
    TTF_Quit();
    SDL_Quit();
}

void Window::handleEvents() {
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            m_running = false;
        }
    }
    m_mouseButtons = SDL_GetMouseState(&m_mouseX, &m_mouseY);

}

void Window::render() {
    
    SDL_SetRenderDrawColor(m_renderer, 238, 238, 238, 1);  // black    
    SDL_RenderClear(m_renderer);

    // Calculate Delta Time (seconds elapsed since last frame)
        Uint32 currentTime = SDL_GetTicks();
        float dt = (currentTime - m_lastTime) / 1000.0f;
        m_lastTime = currentTime;

        // Fire your custom game loop logic if registered!
        if (m_updateCallback) {
            m_updateCallback(dt);
        }

    for (const auto& line : m_lines) {
        renderLine(line);
    }

    for (const auto& item : m_texts) {
        renderText(item);
    }

    SDL_RenderPresent(m_renderer);

    m_lines.clear();
    m_texts.clear();
}

void Window::run() {

    while (m_running) {
        handleEvents();
        render();
    }
}

void Window::drawText(const std::string& text, int x, int y, SDL_Color color) {
    m_texts.push_back({text, x, y, color});
}

void Window::drawLine(int x1, int y1, int x2, int y2, SDL_Color color) {
    m_lines.push_back({x1, y1, x2, y2, color});
}

void Window::setUpdateCallback(Window::UpdateCallback callback) {
    m_updateCallback = callback;
}

void Window::renderText(const TextItem& item) {
    
    if (!m_font || item.text.empty()) {
        return;
    }

    SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(m_font, item.text.c_str(), item.color, 0);
    if (!surface) {
        std::cerr << "TTF error: " << TTF_GetError() << "\n";
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    if (texture) {
        SDL_FRect dstRect = {
            static_cast<float>(item.x),
            static_cast<float>(item.y),
            static_cast<float>(surface->w),
            static_cast<float>(surface->h)
        };

        // Render the textures cleanly
        SDL_RenderCopyF(m_renderer, texture, nullptr, &dstRect);
        
        // Clean up immediate allocations on the spot to avoid severe memory leaks!
        SDL_DestroyTexture(texture);
    }
    SDL_FreeSurface(surface);
}

void Window::renderLine(const LineItem& line) {
    
    SDL_SetRenderDrawColor(m_renderer, line.color.r, line.color.g, line.color.b, line.color.a);
    SDL_RenderDrawLine(m_renderer, line.x1, line.y1, line.x2, line.y2);

}

SDL_Texture* Window::loadTexture(const std::string& path)
{
    SDL_Texture* texture = IMG_LoadTexture(m_renderer, path.c_str());
    if (!texture)
        SDL_Log("Failed to load texture '%s': %s", path.c_str(), IMG_GetError());
    return texture;
}
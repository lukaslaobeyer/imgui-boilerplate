#include "gui_util.hpp"

#include <stdexcept>
#include <memory>

#include <GL/glew.h>

#include "imgui_impl_sdl_gl3.h"

gui_util::Window::Window(std::string title, ImVec4 *clear_color) {
    _clear_color = (clear_color == nullptr) ? &_default_color : clear_color;
    
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        throw std::runtime_error("SDL Error: " + std::to_string(*SDL_GetError()));
    }

    // Setup window
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    _glcontext = SDL_GL_CreateContext(_window);
    glewInit();

    // Setup ImGui binding
    ImGui_ImplSdlGL3_Init(_window);

    // Apply default style
    apply_style();
}

gui_util::Window::~Window() {
    // Cleanup
    ImGui_ImplSdlGL3_Shutdown();
    SDL_GL_DeleteContext(_glcontext);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void gui_util::Window::run(std::function<void()> gui) {
    bool done = false;
    while(!done) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            ImGui_ImplSdlGL3_ProcessEvent(&event);
            if(event.type == SDL_QUIT) {
		done = true;
	    }
        }
        ImGui_ImplSdlGL3_NewFrame(_window);

        // User code
	gui();
	    
        // Rendering
        glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
        glClearColor(_clear_color->x, _clear_color->y, _clear_color->z, _clear_color->w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        SDL_GL_SwapWindow(_window);
    }
}

SDL_Window *gui_util::Window::window() {
    return _window;
}

void gui_util::Window::apply_style() {
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.00f, 0.08f, 0.12f, 0.88f);
}

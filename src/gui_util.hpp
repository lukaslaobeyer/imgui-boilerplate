#ifndef GUI_UTIL_H
#define GUI_UTIL_H

#include <string>
#include <functional>

#include <imgui.h>
#include <SDL.h>

namespace gui_util {
    class Window {
    public:
	Window(std::string title, ImVec4 *clear_color=nullptr);
	~Window();

	void run(std::function<void()> gui);

	SDL_Window *window();
    private:
	void apply_style();
    private:
	SDL_Window *_window;
	SDL_GLContext _glcontext;
	ImVec4 *_clear_color;

        ImVec4 _default_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    };
}

#endif

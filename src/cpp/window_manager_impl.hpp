#pragma once

#include "window_manager.hpp"
#include "window.hpp"

namespace cpp_universe {

class WindowManagerImpl : public WindowManager {
public:
    WindowManagerImpl(const std::shared_ptr<GuiWrapper>& gui_wrapper,
                      const std::shared_ptr<WindowManagerCallback>& callback);

    void load_windows() override;

    std::vector<Window> get_windows() override;

    void toggle_fullscreen(const std::string& uid) override;

    void update_window(const std::string& uid, int32_t width, int32_t height,
                       int32_t top, int32_t left, int32_t z_index) override;

private:
    std::vector<Window>::iterator window_of(const std::string& uid);
    std::vector<Window>::iterator current_fc();

    std::shared_ptr<GuiWrapper> gui_wrapper_;
    std::shared_ptr<WindowManagerCallback> callback_;

    std::vector<Window> windows_;
};
}

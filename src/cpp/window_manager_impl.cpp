

#include <string>

#include <cpprest/http_client.h>

#include "window_manager_callback.hpp"
#include "gui_wrapper.hpp"
#include "window_manager_impl.hpp"
#include "window_ext.hpp"

namespace cpp_universe {

std::shared_ptr<WindowManager> WindowManager::create(
    const std::shared_ptr<GuiWrapper>& gui_wrapper,
    const std::shared_ptr<WindowManagerCallback>& callback) {
    return std::make_shared<WindowManagerImpl>(gui_wrapper, callback);
}

WindowManagerImpl::WindowManagerImpl(
    const std::shared_ptr<GuiWrapper>& gui_wrapper,
    const std::shared_ptr<WindowManagerCallback>& callback)
    : gui_wrapper_(gui_wrapper), callback_(callback) {}

void WindowManagerImpl::load_windows() {
    web::http::client::http_client http_client_("https://imgs.babits.top/");
    web::uri_builder builder("windows_4.json");

    http_client_.request(web::http::methods::GET, builder.to_string())
        .then([this](pplx::task<web::http::http_response> task) {
            web::http::http_response response = task.get();

            if (response.status_code() != 200) {
                callback_->on_error(ERR_API_FAIL);
            } else {
                web::json::array windows =
                    response.extract_json().get().as_array();
                std::transform(windows.begin(), windows.end(),
                               std::back_inserter(windows_),
                               [](web::json::value& w) {
                                   return Window(w[U("width")].as_integer(),
                                                 w[U("height")].as_integer(),
                                                 w[U("top")].as_integer(),
                                                 w[U("left")].as_integer(),
                                                 w[U("z_index")].as_integer(),
                                                 w[U("uid")].as_string());
                               });
                std::for_each(
                    windows_.begin(), windows_.end(),
                    [this](Window& w) { gui_wrapper_->create_view(w); });
                std::for_each(
                    windows_.begin(), windows_.end(),
                    [this](Window& w) { callback_->on_window_added(w); });
            }
        });
}

std::vector<Window> WindowManagerImpl::get_windows() { return windows_; }

void WindowManagerImpl::toggle_fullscreen(const std::string& uid) {
    auto newFc = window_of(uid);
    auto oldFc = current_fc();
    if (newFc != std::end(windows_) && oldFc != std::end(windows_) &&
        newFc != oldFc) {
        gui_wrapper_->swap_view(*newFc, *oldFc);

        int width = newFc->width;
        int height = newFc->height;
        int top = newFc->top;
        int left = newFc->left;
        int z_index = newFc->z_index;
        update_window(newFc->uid, oldFc->width, oldFc->height, oldFc->top,
                      oldFc->left, oldFc->z_index);
        update_window(oldFc->uid, width, height, top, left, z_index);
    }
}

void WindowManagerImpl::update_window(const std::string& uid, int32_t width,
                                      int32_t height, int32_t top, int32_t left,
                                      int32_t z_index) {
    auto window = window_of(uid);
    if (window != std::end(windows_)) {
        window->width = width;
        window->height = height;
        window->top = top;
        window->left = left;
        window->z_index = z_index;
    }
}

std::vector<Window>::iterator WindowManagerImpl::window_of(
    const std::string& uid) {
    return std::find_if(windows_.begin(), windows_.end(),
                        [&uid](Window& w) { return w.uid == uid; });
}

std::vector<Window>::iterator WindowManagerImpl::current_fc() {
    return std::find_if(windows_.begin(), windows_.end(),
                        [](Window& w) { return WindowExt::is_fullscreen(w); });
}
}

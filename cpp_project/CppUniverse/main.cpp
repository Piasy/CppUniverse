//
/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Piasy
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
//

#include <iostream>
#include <unistd.h>

#include "window_manager.hpp"
#include "mock_gui_wrapper.hpp"
#include "mock_window_manager_callback.hpp"

using namespace cpp_universe;

int main(int argc, const char* argv[]) {
    std::shared_ptr<GuiWrapper> gui_wrapper =
        std::make_shared<MockGuiWrapper>();
    std::shared_ptr<WindowManagerCallback> callback =
        std::make_shared<MockWindowManagerCallback>();
    std::shared_ptr<cpp_universe::WindowManager> manager =
        cpp_universe::WindowManager::create(gui_wrapper, callback);

    manager->load_windows();

    sleep(3);
    
    manager->toggle_fullscreen("dijkstra");
    manager->toggle_fullscreen("heisenberg");
    manager->toggle_fullscreen("knuth");

    return 0;
}

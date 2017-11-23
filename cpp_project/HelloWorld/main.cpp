//
//  main.cpp
//  HelloWorld
//
//  Created by Piasy on 29/07/2017.
//  Copyright © 2017 Piasy. All rights reserved.
//

#include <iostream>

#include "hello_world.hpp"

int main(int argc, const char* argv[]) {
    std::shared_ptr<helloworld::HelloWorld> hw =
        helloworld::HelloWorld::create();

    std::cout << hw->get_hello_world() << std::endl;

    return 0;
}

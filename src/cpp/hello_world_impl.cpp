#include "hello_world_impl.hpp"
#include <string>

namespace helloworld {

    std::shared_ptr<HelloWorld> HelloWorld::create() {
        return std::make_shared<HelloWorldImpl>();
    }

    HelloWorldImpl::HelloWorldImpl() {

    }

    std::string HelloWorldImpl::get_hello_world() {

        std::string myString = "Hello World! ";

        time_t t = time(0);
        tm now=*localtime(&t);
        char tmdescr[200]={0};
        const char fmt[]="%r";
        if (strftime(tmdescr, sizeof(tmdescr)-1, fmt, &now)>0) {
            myString += tmdescr;
        }

        return myString;

    }

}

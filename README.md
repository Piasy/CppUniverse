# CppUniverse

A demo project that showcase how to use C++ to conquer the universe, with the help of [Djinni](https://github.com/dropbox/djinni) and [WebAssembly](http://webassembly.org/) :)

This demo implement exactly the same feature as [JavaUniverse](https://github.com/Piasy/JavaUniverse), but write the main logic in C++.

## Dependencies

+ [C++ REST SDK](https://github.com/Microsoft/cpprestsdk)
+ [Djinni](https://github.com/dropbox/djinni)
+ [xcake](https://github.com/jcampbell05/xcake)

## CPP Project

+ `./run_djinni.sh`
+ `cd cpp_project`
+ `xcake make`
+ `open CppUniverse.xcodeproj`

## Android Project

+ `./run_djinni.sh`
+ Just open the `android_project` folder in Android Studio.

## iOS Project

+ `./run_djinni.sh`
+ `cd ios_project`
+ `xcake make`
+ `open CppUniverse.xcodeproj`

## Web Project

WIP...

## Caveat

+ Add ``-DCMAKE_INSTALL_PREFIX=`pwd`/out`` to cmake command to specify install dir;
+ `'cpprest/http_client.h' file not found with <angled> include; use "quotes" instead` [problem solution](https://stackoverflow.com/a/47542681/3077508);
+ `Arithmetic on a pointer to an incomplete type 'cpp_universe::Window'`: add `#include "window.hpp"` to get the complete type info of `cpp_universe::Window`;
+ Extend djinni record to add utility method which is only used by one language;
+ Djinni record is immutable;

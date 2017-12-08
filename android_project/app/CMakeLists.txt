cmake_minimum_required(VERSION 3.4.1)

set(CWD ${CMAKE_CURRENT_LIST_DIR})

include_directories(
    /Users/piasy/tools/vagrant/ubuntu_xenial64/cpprestsdk/Build_android/build/openssl/armeabi-v7a/include/
    /Users/piasy/tools/vagrant/ubuntu_xenial64/cpprestsdk/Build_android/build/Boost-for-Android/build/out/armeabi-v7a/include/boost-1_65_1/
    /Users/piasy/tools/vagrant/ubuntu_xenial64/cpprestsdk/Build_android/build/build.armv7.debug/out/include/
    ../../djinni/support-lib/
    ../../djinni/support-lib/jni/
    ../../generated_src/cpp/
    ../../generated_src/jni/
    ../../src/cpp/
)

file(GLOB cpp_universe_sources
    ../../generated_src/cpp/*.cpp
    ../../src/cpp/*.cpp
    ../../djinni/support-lib/jni/*.cpp
    ../../generated_src/jni/*.cpp
    ./src/main/jni/*.cpp
)

add_library(
             cpp_universe
             SHARED
             ${cpp_universe_sources}
           )

target_link_libraries(
                       cpp_universe

                       android
                       log

                       ${CWD}/../../libs/android/armeabi-v7a/libcpprest.a
                       ${CWD}/../../libs/android/armeabi-v7a/libboost_thread-clang-mt-1_65_1.a
                       ${CWD}/../../libs/android/armeabi-v7a/libboost_system-clang-mt-1_65_1.a
                       ${CWD}/../../libs/android/armeabi-v7a/libboost_random-clang-mt-1_65_1.a
                       ${CWD}/../../libs/android/armeabi-v7a/libboost_filesystem-clang-mt-1_65_1.a
                       ${CWD}/../../libs/android/armeabi-v7a/libboost_date_time-clang-mt-1_65_1.a
                       ${CWD}/../../libs/android/armeabi-v7a/libboost_chrono-clang-mt-1_65_1.a
                       ${CWD}/../../libs/android/armeabi-v7a/libboost_atomic-clang-mt-1_65_1.a
                       ${CWD}/../../libs/android/armeabi-v7a/libssl.a
                       ${CWD}/../../libs/android/armeabi-v7a/libcrypto.a
                     )
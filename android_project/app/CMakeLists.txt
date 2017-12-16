cmake_minimum_required(VERSION 3.4.1)

set(CWD ${CMAKE_CURRENT_LIST_DIR})

include_directories(
    ../../libs/android_armeabi_v7a/openssl/include/
    ../../libs/android_armeabi_v7a/boost/include/
    ../../libs/android_armeabi_v7a/cpprestsdk/include/
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

                       ${CWD}/../../libs/android_armeabi_v7a/cpprestsdk/lib/libcpprest.a
                       ${CWD}/../../libs/android_armeabi_v7a/boost/lib/libboost_thread-clang-mt-1_65_1.a
                       ${CWD}/../../libs/android_armeabi_v7a/boost/lib/libboost_system-clang-mt-1_65_1.a
                       ${CWD}/../../libs/android_armeabi_v7a/boost/lib/libboost_random-clang-mt-1_65_1.a
                       ${CWD}/../../libs/android_armeabi_v7a/boost/lib/libboost_filesystem-clang-mt-1_65_1.a
                       ${CWD}/../../libs/android_armeabi_v7a/boost/lib/libboost_date_time-clang-mt-1_65_1.a
                       ${CWD}/../../libs/android_armeabi_v7a/boost/lib/libboost_chrono-clang-mt-1_65_1.a
                       ${CWD}/../../libs/android_armeabi_v7a/boost/lib/libboost_atomic-clang-mt-1_65_1.a
                       ${CWD}/../../libs/android_armeabi_v7a/openssl/lib/libssl.a
                       ${CWD}/../../libs/android_armeabi_v7a/openssl/lib/libcrypto.a
                     )

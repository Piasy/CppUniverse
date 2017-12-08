#include <jni.h>
#include <pplx/pplxtasks.h>

extern "C" {

JNIEXPORT void JNICALL
Java_com_github_piasy_cpp_1universe_CppUniverse_globalInitialize(JNIEnv* env, jclass type) {
    JavaVM *vm;
    env->GetJavaVM(&vm);
    cpprest_init(vm);
}

}

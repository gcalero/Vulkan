# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 3.4.1)

# build native_app_glue as a static lib
set(APP_GLUE_DIR ${ANDROID_NDK}/sources/android/native_app_glue)
include_directories(${APP_GLUE_DIR})
add_library( app-glue STATIC ${APP_GLUE_DIR}/android_native_app_glue.c)

add_library(vulkan-template SHARED
            src/main/jni/main.cpp
            src/main/jni/vulkan/vulkan_wrapper.cpp
            src/main/jni/vulkan/pipeline.cpp
            src/main/jni/vulkan/VDeleter.h
            )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -std=c++11 \
                     -DVK_USE_PLATFORM_ANDROID_KHR")
target_link_libraries(vulkan-template app-glue log android)


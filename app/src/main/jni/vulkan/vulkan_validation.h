#include <vulkan/vulkan.h>
#include <android/log.h>

// Android log function wrappers
static const char* _VALIDATION_LOG_TAG = "Vulkan-validation";
#define _VALIDATION_LAYER_LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, _VALIDATION_LOG_TAG, __VA_ARGS__))
#define _VALIDATION_LAYER_LOGW(...) \
  ((void)__android_log_print(ANDROID_LOG_WARN, _VALIDATION_LOG_TAG, __VA_ARGS__))
#define _VALIDATION_LAYER_LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, _VALIDATION_LOG_TAG, __VA_ARGS__))
#define _VALIDATION_LAYER_LOGD(...) \
  ((void)__android_log_print(ANDROID_LOG_DEBUG, _VALIDATION_LOG_TAG, __VA_ARGS__))

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugReportFlagsEXT flags,
        VkDebugReportObjectTypeEXT objType,
        uint64_t obj,
        size_t location,
        int32_t code,
        const char* layerPrefix,
        const char* msg,
        void* userData) {

    if ((flags & VK_DEBUG_REPORT_ERROR_BIT_EXT) != 0) {
        _VALIDATION_LAYER_LOGE("Validation layer: %s", msg);
    } else if ( ((flags & VK_DEBUG_REPORT_WARNING_BIT_EXT) != 0) || ((flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT ) != 0)) {
        _VALIDATION_LAYER_LOGW("Validation layer: %s", msg);
    } else if ( (flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) != 0) {
        _VALIDATION_LAYER_LOGI("Validation layer: %s", msg);
    } else if ((flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT) != 0) {
        _VALIDATION_LAYER_LOGD("Validation layer: %s", msg);
    } else {
        _VALIDATION_LAYER_LOGW("Validation layer: %s", msg);
    }
    return VK_FALSE;
}

void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
    if (func != nullptr) {
        func(instance, callback, pAllocator);
    }
}
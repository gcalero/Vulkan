#include "pipeline.h"
#include <jni.h>
#include <vector>
#include <android/asset_manager.h>

VkResult createShaderModule(android_app* androidAppCtx, VkDevice  device, const char* filePath, VkShaderModule* shaderOut) {
    // Read the file
    AAsset* file = AAssetManager_open(androidAppCtx->activity->assetManager, filePath, AASSET_MODE_BUFFER);
    size_t fileLength = AAsset_getLength(file);

    char* fileContent = new char[fileLength];

    AAsset_read(file, fileContent, fileLength);

    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = fileLength;
    createInfo.pCode = (uint32_t*) fileContent;
    VkResult result = vkCreateShaderModule( device, &createInfo, nullptr, shaderOut);
    assert(result == VK_SUCCESS);
    delete[] fileContent;
    return result;
}
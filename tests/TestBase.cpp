#include "TestBase.h"

#if (CC_PLATFORM == CC_PLATFORM_MAC_OSX && defined(MAC_USE_METAL))
#include "gfx-metal/GFXMTL.h"
#else
#include "gfx-vulkan/GFXVulkan.h"
#include "gfx-gles3/GFXGLES3.h"
#include "gfx-gles2/GFXGLES2.h"
#endif

NS_CC_BEGIN

GFXDevice* TestBaseI::_device                = nullptr;
GFXFramebuffer* TestBaseI::_fbo              = nullptr;
std::vector<GFXCommandBuffer*> TestBaseI::_commandBuffers(1, nullptr);

TestBaseI::TestBaseI(const WindowInfo& info)
{
    if(_device == nullptr)
    {
#if (CC_PLATFORM == CC_PLATFORM_MAC_OSX && defined(MAC_USE_METAL))
        _device = CC_NEW(CCMTLDevice);
#else

#if defined(USE_VULKAN)
    _device = CC_NEW(CCVKDevice);
#elif defined(USE_GLES2)
    _device = CC_NEW(GLES2Device);
#else
    _device = CC_NEW(GLES3Device);
#endif
        
#endif // (CC_PLATFORM == CC_PLATFORM_MAC_OSX)

    
        GFXDeviceInfo dev_info;
        dev_info.windowHandle = info.windowHandle;
        dev_info.width = info.screen.width;
        dev_info.height = info.screen.height;
        dev_info.nativeWidth = info.physicalWidth;
        dev_info.nativeHeight = info.physicalHeight;
        _device->initialize(dev_info);
    }

    for(uint i = 0; i< static_cast<uint>(_commandBuffers.size()); i++)
    {
        if(_commandBuffers[i] != nullptr)
            continue;
        
        GFXCommandBufferInfo cmd_buff_info;
        cmd_buff_info.allocator = _device->getCommandAllocator();
        cmd_buff_info.type = GFXCommandBufferType::PRIMARY;
        _commandBuffers[i] = _device->createCommandBuffer(cmd_buff_info);
    }
    
    if(_fbo == nullptr)
    {
        _fbo = _device->getMainWindow()->getFramebuffer();
    }
}

void TestBaseI::destroyGlobal()
{
    for (auto& cmdBuff : _commandBuffers)
    {
        CC_SAFE_DESTROY(cmdBuff);
    }
    CC_SAFE_DESTROY(_device);
    _fbo = nullptr;
}

NS_CC_END

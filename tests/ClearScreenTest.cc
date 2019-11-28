#include "ClearScreenTest.h"
#include "gfx-gles2/GFXGLES2.h"
#include "gfx-gles3/GFXGLES3.h"

NS_CC_BEGIN

ClearScreen::ClearScreen() {
}

ClearScreen::~ClearScreen() {
}

void ClearScreen::Destroy()
{
    CC_SAFE_DESTROY(_commandBuffer);
    CC_SAFE_DESTROY(_device);
}

bool ClearScreen::initialize(intptr_t windowHandle, GFXRect windowRect, int screenWidth, int screenHeight) 
{
#if 0
  device_ = CC_NEW(GLES3Device);
#else
    _device = CC_NEW(GLES2Device);
#endif

  GFXDeviceInfo dev_info;
  dev_info.window_handle = windowHandle;
  dev_info.width = windowRect.width;
  dev_info.height = windowRect.height;
  dev_info.native_width = screenWidth;
  dev_info.native_height = screenHeight;
  if (!_device->Initialize(dev_info)) {
    return false;
  }

  // Init primary command buffer
  GFXCommandBufferInfo cmd_buff_info;
  cmd_buff_info.allocator = _device->cmd_allocator();
  cmd_buff_info.type = GFXCommandBufferType::PRIMARY;
  _commandBuffer = _device->CreateGFXCommandBuffer(cmd_buff_info);
  
  _fbo = _device->window()->framebuffer();

  return true;
}

void ClearScreen::tick(float dt) {

    GFXRect render_area = {0, 0, _device->width(), _device->height() };
    _time += dt;
    GFXColor clear_color;
    clear_color.r = 1.0f;
    clear_color.g = std::abs(std::sin(_time));
    clear_color.b = 0.0f;
    clear_color.a = 1.0f;

    _commandBuffer->Begin();
    _commandBuffer->BeginRenderPass(_fbo, render_area, GFXClearFlagBit::ALL, &clear_color, 1, 1.0f, 0);
    _commandBuffer->EndRenderPass();
    _commandBuffer->End();

    _device->queue()->submit(&_commandBuffer, 1);
    _device->Present();
}

NS_CC_END

#ifndef __MYAPP_H__
#define __MYAPP_H__

#include "TestBase.h"

NS_CC_BEGIN

class ClearScreen: public TestBaseI
{
 public:
    DEFINE_CREATE_METHOD(ClearScreen)
    ClearScreen() = default;
    ~ClearScreen();

 public:
     virtual void tick(float dt) override;
     virtual bool initialize(intptr_t windowHandle, GFXRect windowRect, int screenWidth, int screenHeight) override;
     virtual void Destroy();

 private:
     GFXCommandBuffer* _commandBuffer = nullptr;
     GFXFramebuffer* _fbo = nullptr;
     GFXDevice* _device = nullptr;

     float _time = 0.0f;
};

NS_CC_END

#endif
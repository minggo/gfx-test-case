#pragma once

#include "TestBase.h"

NS_CC_BEGIN

class ClearScreen: public TestBaseI
{
 public:
    DEFINE_CREATE_METHOD(ClearScreen)
    ClearScreen(const WindowInfo& info) : TestBaseI(info) {};
    ~ClearScreen() = default;

 public:
     virtual void tick(float dt) override;
     virtual bool initialize() override;
     virtual void Destroy();

 private:
     GFXCommandBuffer* _commandBuffer = nullptr;
     float _time = 0.0f;
};

NS_CC_END

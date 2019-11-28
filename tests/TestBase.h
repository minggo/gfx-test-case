#pragma once
#include "Core.h"

NS_CC_BEGIN

typedef struct WindowInfo
{
    intptr_t windowHandle;
    GFXRect screen;
    int physicalWidth;
    int physicalHeight;
}WindowInfo;

#define DEFINE_CREATE_METHOD(className) \
static TestBaseI* create(const WindowInfo& info) { \
    return CC_NEW(className(info)); \
}

class TestBaseI : public Object
{
public:
    TestBaseI(const WindowInfo& info);
    virtual void tick(float dt) = 0;

    virtual bool initialize() = 0;
    virtual void Destroy();
    virtual ~TestBaseI() = default;

protected:
    GFXDevice* _device = nullptr;
    GFXFramebuffer* _fbo = nullptr;

};

NS_CC_END

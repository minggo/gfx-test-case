#pragma once
#include "Core.h"

NS_CC_BEGIN

#define DEFINE_CREATE_METHOD(className) \
static TestBaseI* create() {\
    return CC_NEW(className); \
}

class TestBaseI : public Object
{
public:
    virtual void tick(float dt) = 0;
    virtual bool initialize(intptr_t windowHandle, GFXRect windowRect, int screenWidth, int screenHeight) = 0;
    virtual void Destroy(){};
    virtual ~TestBaseI(){};
};

NS_CC_END

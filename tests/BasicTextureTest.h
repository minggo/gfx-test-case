#pragma once

#include "TestBase.h"
#include "GLES2Std.h"
#include "math/Mat4.h"

NS_CC_BEGIN

class BasicTexture: public TestBaseI
{
public:
    DEFINE_CREATE_METHOD(BasicTexture)
    BasicTexture(const WindowInfo& info) : TestBaseI(info) {};
    ~BasicTexture() = default;

public:
     virtual void tick(float dt) override;
     virtual bool initialize() override;
     virtual void Destroy() override;

private:
    void createShader();
    void createVertexBuffer();
    void createPipeline();
    void createInputAssembler();
    void createTexture();

    GFXShader* _shader = nullptr;
    GFXBuffer* _vertexBuffer = nullptr;
    GFXBuffer* _uniformBuffer = nullptr;
    GFXPipelineState* _pipelineState = nullptr;
    GFXInputAssembler* _inputAssembler = nullptr;
    GFXBindingLayout* _bindingLayout = nullptr;
    GFXTexture* _texture = nullptr;
    GFXBuffer* _image = nullptr;
    GFXSampler* _sampler = nullptr;
    GFXTextureView* _texView = nullptr;
    GFXBufferTextureCopy textureRegion;
    
    Mat4 _transformToLeft;
    Mat4 _transformToRight;
    float _time = 0.0f;
};

NS_CC_END

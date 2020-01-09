#pragma once
#include <string>
#include "math/CCGeometry.h"
#include "base/CCData.h"
#include "base/ccTypes.h"
NS_CC_BEGIN
/** @struct TextVAlignment
 * Vertical text alignment type.
 */
enum class TextVAlignment : char
{
    TOP,
    CENTER,
    BOTTOM
};

/** @struct TextHAlignment
 * Horizontal text alignment type.
 */
enum class TextHAlignment : char
{
    LEFT,
    CENTER,
    RIGHT
};

/** @struct FontShadow
 * Shadow attributes.
 */
struct FontShadow
{
public:

    // shadow is not enabled by default
    FontShadow()
        : _shadowEnabled(false)
        , _shadowBlur(0)
        , _shadowOpacity(0)
    {}

    /// true if shadow enabled
    bool   _shadowEnabled;
    /// shadow x and y offset
    cocos2d::Size   _shadowOffset;
    /// shadow blurrines
    float  _shadowBlur;
    /// shadow opacity
    float  _shadowOpacity;
};

/** @struct FontStroke
 * Stroke attributes.
 */
struct FontStroke
{
public:

    // stroke is disabled by default
    FontStroke()
        : _strokeSize(0.0f)
    , _strokeColor(cocos2d::Color3B::BLACK)
        , _strokeAlpha(255)
        , _strokeEnabled(false)
    {}

    /// stroke size
    float     _strokeSize;
    /// stroke color
    cocos2d::Color3B   _strokeColor;
    /// stroke alpha
    uint8_t   _strokeAlpha;
    /// true if stroke enabled
    bool      _strokeEnabled;
};

/** @struct FontDefinition
 * Font attributes.
 */
struct FontDefinitions
{
public:
    FontDefinitions()
        : _fontSize(0)
        , _alignment(TextHAlignment::CENTER)
        , _vertAlignment(TextVAlignment::TOP)
    , _dimensions(cocos2d::Size::ZERO)
    , _fontFillColor(cocos2d::Color3B::WHITE)
        , _fontAlpha(255)
        , _enableWrap(true)
        , _overflow(0)
    {}

    /// font name
    std::string           _fontName;
    /// font size
    int                   _fontSize;
    /// enable shrink font size
    int                  _overflow;
    /// rendering box
    cocos2d::Size                  _dimensions;
    /// font color
    cocos2d::Color3B               _fontFillColor;
    /// font alpha
    uint8_t               _fontAlpha;
    /// font shadow
    FontShadow            _shadow;
    /// font stroke
    FontStroke            _stroke;
    /// horizontal alignment
    TextHAlignment        _alignment;
    /// vertical alignment
    TextVAlignment _vertAlignment;
    /// enable text wrap
    bool                  _enableWrap;
    bool                 _enableBold;
};

class Font
{
public:
/** Defines the alignment of text. */
    enum class TextAlign
    {
        CENTER        = 0x33, /** Horizontal center and vertical center. */
        TOP           = 0x13, /** Horizontal center and vertical top. */
        TOP_RIGHT     = 0x12, /** Horizontal right and vertical top. */
        RIGHT         = 0x32, /** Horizontal right and vertical center. */
        BOTTOM_RIGHT  = 0x22, /** Horizontal right and vertical bottom. */
        BOTTOM        = 0x23, /** Horizontal center and vertical bottom. */
        BOTTOM_LEFT   = 0x21, /** Horizontal left and vertical bottom. */
        LEFT          = 0x31, /** Horizontal left and vertical center. */
        TOP_LEFT      = 0x11, /** Horizontal left and vertical top. */
    };

    /**
     * Gets texture data for text.
     */
    static Data getTextureDataForText(const char * text, const FontDefinitions& textDefinition, Font::TextAlign align, int &width, int &height, bool& hasPremultipliedAlpha);
};
NS_CC_END

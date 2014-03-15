#ifndef FREETYPEGX_H_
#define FREETYPEGX_H_

#include <gccore.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_BITMAP_H
#include "Metaphrasis.h"

#include <malloc.h>
#include <string.h>
#include <map>

/*! \struct ftgxCharData_
 * 
 * Font face character glyph relevant data structure.
 */
typedef struct ftgxCharData_ {
        uint16_t glyphAdvanceX; /**< Character glyph X coordinate advance in pixels. */
        uint16_t glyphIndex;    /**< Character glyph index in the font face. */

        uint16_t textureWidth;  /**< Texture width in pixels/bytes. */
        uint16_t textureHeight; /**< Texture glyph height in pixels/bytes. */

        uint16_t renderOffsetY; /**< Texture Y axis bearing offset. */
        uint16_t renderOffsetMax;       /**< Texture Y axis bearing maximum value. */
        uint16_t renderOffsetMin;       /**< Texture Y axis bearing minimum value. */

        uint32_t* glyphDataTexture;     /**< Glyph texture bitmap data buffer. */
} ftgxCharData;

#define _TEXT(t) L ## t /**< Unicode helper macro. */
#define EXPLODE_UINT8_TO_UINT32(x) (x << 24) | (x << 16) | (x << 8) | x

#define FTGX_NULL                               0x0000

#define FTGX_JUSTIFY_MASK               0x000f
#define FTGX_JUSTIFY_LEFT               0x0001
#define FTGX_JUSTIFY_CENTER             0x0002
#define FTGX_JUSTIFY_RIGHT              0x0004

#define FTGX_ALIGN_MASK                 0x00f0
#define FTGX_ALIGN_TOP                  0x0010
#define FTGX_ALIGN_MIDDLE               0x0020
#define FTGX_ALIGN_BOTTOM               0x0040

#define FTGX_STYLE_MASK                 0x0f00
#define FTGX_STYLE_UNDERLINE    0x0100
#define FTGX_STYLE_STRIKE               0x0200

#define FTGX_COMPATIBILITY_DEFAULT_TEVOP_GX_MODULATE    0X0001
#define FTGX_COMPATIBILITY_DEFAULT_TEVOP_GX_DECAL               0X0002
#define FTGX_COMPATIBILITY_DEFAULT_TEVOP_GX_BLEND               0X0004
#define FTGX_COMPATIBILITY_DEFAULT_TEVOP_GX_REPLACE             0X0008
#define FTGX_COMPATIBILITY_DEFAULT_TEVOP_GX_PASSCLR             0X0010

#define FTGX_COMPATIBILITY_DEFAULT_VTXDESC_GX_NONE              0X0100
#define FTGX_COMPATIBILITY_DEFAULT_VTXDESC_GX_DIRECT    0X0200
#define FTGX_COMPATIBILITY_DEFAULT_VTXDESC_GX_INDEX8    0X0400
#define FTGX_COMPATIBILITY_DEFAULT_VTXDESC_GX_INDEX16   0X0800

#define FTGX_COMPATIBILITY_NONE                                                 0x0000
#define FTGX_COMPATIBILITY_GRRLIB                                               FTGX_COMPATIBILITY_DEFAULT_TEVOP_GX_PASSCLR | FTGX_COMPATIBILITY_DEFAULT_VTXDESC_GX_NONE
#define FTGX_COMPATIBILITY_LIBWIISPRITE                                 FTGX_COMPATIBILITY_DEFAULT_TEVOP_GX_MODULATE | FTGX_COMPATIBILITY_DEFAULT_VTXDESC_GX_DIRECT

const GXColor ftgxWhite = (GXColor){0xff, 0xff, 0xff, 0xff}; /**< Constant color value used only to sanitize Doxygen documentation. */

/*! \class FreeTypeGX
 * \brief Wrapper class for the FreeType library with GX rendering.
 * \author Armin Tamzarian
 * \version 0.3.2
 * 
 * FreeTypeGX acts as a wrapper class for the FreeType library. It supports precaching of transformed glyph data into
 * a specified texture format. Rendering of the data to the EFB is accomplished through the application of high performance
 * GX texture functions resulting in high throughput of string rendering.  
 */
class FreeTypeGX {

        private:
                FT_Library ftLibrary;           /**< FreeType FT_Library instance. */
                FT_Byte * ftFontBuffer;         /**< Pointer to the current font buffer */
                FT_Long ftFontBufferSize;       /**< Size of the current font buffer */
                FT_UInt ftPointSize;            /**< Requested size of the rendered font. */
                FT_Short ftAscender;            /**< Ascender value of the rendered font. */
                FT_Short ftDescender;           /**< Descender value of the rendered font. */

                bool ftKerningEnabled;          /**< Flag indicating the availability of font kerning data. */
                FT_Face ftFace;                         /**< Reusable FreeType FT_Face object. */
                
                uint8_t textureFormat;          /**< Defined texture format of the target EFB. */
                uint8_t vertexIndex;            /**< Vertex format descriptor index. */
                uint32_t compatibilityMode;     /**< Compatibility mode for default tev operations and vertex descriptors. */   
                std::map<wchar_t, ftgxCharData> fontData; /**< Map which holds the glyph data structures for the corresponding characters. */

                bool widthCachingEnabled;
                std::map<const wchar_t*, uint16_t> cacheTextWidth;

                static uint16_t maxVideoWidth; /**< Maximum width of the video screen. */

                static uint16_t adjustTextureWidth(uint16_t textureWidth, uint8_t textureFormat);
                static uint16_t adjustTextureHeight(uint16_t textureHeight, uint8_t textureFormat);

                uint16_t getStyleOffsetWidth(uint16_t width, uint16_t format);
                uint16_t getStyleOffsetHeight(uint16_t format);
                ftgxCharData* getCharacter(wchar_t character);

                void unloadFont();
                ftgxCharData *cacheGlyphData(wchar_t charCode);
                uint16_t cacheGlyphDataComplete();
                void loadGlyphData(FT_Bitmap *bmp, ftgxCharData *charData);

                void setDefaultMode();

                void drawTextFeature(int16_t x, int16_t y, uint16_t width, uint16_t format, GXColor color);
                void copyTextureToFramebuffer(GXTexObj *texObj, f32 texWidth, f32 texHeight, int16_t screenX, int16_t screenY, GXColor color);
                void copyFeatureToFramebuffer(f32 featureWidth, f32 featureHeight, int16_t screenX, int16_t screenY,  GXColor color);
                
        public:
                FreeTypeGX(uint8_t textureFormat = GX_TF_RGBA8, uint8_t vertexIndex = GX_VTXFMT1);
                ~FreeTypeGX();

                bool setKerningEnabled(bool enabled);
                bool getKerningEnabled();
                bool setTextWidthCachingEnabled(bool enabled);
                bool getTextWidthCachingEnabled();
                void clearTextWidthCache();

                static wchar_t* charToWideChar(char* p);
                static wchar_t* charToWideChar(const char* p);
                void setVertexFormat(uint8_t vertexIndex);
                void setCompatibilityMode(uint32_t compatibilityMode);
                static uint16_t setMaxVideoWidth(uint16_t width);

                uint16_t loadFont(uint8_t* fontBuffer, FT_Long bufferSize, FT_UInt pointSize, bool cacheAll = false);
                uint16_t loadFont(const uint8_t* fontBuffer, FT_Long bufferSize, FT_UInt pointSize, bool cacheAll = false);
                
                uint16_t drawText(int16_t x, int16_t y, wchar_t *text, GXColor color = ftgxWhite, uint16_t textStyling = FTGX_NULL);
                uint16_t drawText(int16_t x, int16_t y, wchar_t const *text, GXColor color = ftgxWhite, uint16_t textStyling = FTGX_NULL);

                uint16_t getWidth(wchar_t *text);
                uint16_t getWidth(wchar_t const *text);
                uint16_t getHeight(wchar_t *text);
                uint16_t getHeight(wchar_t const *text);
};

#endif /* FREETYPEGX_H_ */
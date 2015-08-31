#import <GLKit/GLKit.h>
#import <OpenGL/OpenGL.h>
#import "GMglobals.h"

// OpenGL 3.2 is only supported on MacOS X Lion and later
// CGL_VERSION_1_3 is defined as 1 on MacOS X Lion and later
#if CGL_VERSION_1_3
// Set to 0 to run on the Legacy OpenGL Profile
#define ESSENTIAL_GL_PRACTICES_SUPPORT_GL3 1
#else
#define ESSENTIAL_GL_PRACTICES_SUPPORT_GL3 0
#endif //!CGL_VERSION_1_3

#if ESSENTIAL_GL_PRACTICES_SUPPORT_GL3
#import <OpenGL/gl3.h>
#else
#import <OpenGL/gl.h>
#endif //!ESSENTIAL_GL_PRACTICES_SUPPORT_GL3


//The name of the VertexArrayObject are slightly different in
// OpenGLES, OpenGL Core Profile, and OpenGL Legacy
// The arguments are exactly the same across these APIs however
#if TARGET_IOS
#define glBindVertexArray glBindVertexArrayOES
#define glGenVertexArrays glGenVertexArraysOES
#define glDeleteVertexArrays glDeleteVertexArraysOES
#else
#if ESSENTIAL_GL_PRACTICES_SUPPORT_GL3
#define glBindVertexArray glBindVertexArray
#define glGenVertexArrays glGenVertexArrays
#define glGenerateMipmap glGenerateMipmap
#define glDeleteVertexArrays glDeleteVertexArrays
#else
#define glBindVertexArray glBindVertexArrayAPPLE
#define glGenVertexArrays glGenVertexArraysAPPLE
#define glGenerateMipmap glGenerateMipmapEXT
#define glDeleteVertexArrays glDeleteVertexArraysAPPLE
#endif //!ESSENTIAL_GL_PRACTICES_SUPPORT_GL3
#endif //!TARGET_IOS

static inline const char * GetGLErrorString(GLenum error)
{
    const char *str;
    switch( error )
    {
        case GL_NO_ERROR:
            str = "GL_NO_ERROR";
            break;
        case GL_INVALID_ENUM:
            str = "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            str = "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            str = "GL_INVALID_OPERATION";
            break;
#if defined __gl_h_ || defined __gl3_h_
        case GL_OUT_OF_MEMORY:
            str = "GL_OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            str = "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
#endif
#if defined __gl_h_
        case GL_STACK_OVERFLOW:
            str = "GL_STACK_OVERFLOW";
            break;
        case GL_STACK_UNDERFLOW:
            str = "GL_STACK_UNDERFLOW";
            break;
        case GL_TABLE_TOO_LARGE:
            str = "GL_TABLE_TOO_LARGE";
            break;
#endif
        default:
            str = "(ERROR: Unknown Error Enum)";
            break;
    }
    return str;
}

#define GetGLError()									\
{														\
GLenum err = glGetError();							\
while (err != GL_NO_ERROR) {						\
NSLog(@"GLError %s set in File:%s Line:%d\n",   \
GetGLErrorString(err), __FILE__, __LINE__);	    \
err = glGetError();								\
}													\
}


// -------------------------------------------- //
// ---------------- BUFFER MODE --------------- //
// -------------------------------------------- //
#pragma mark Buffer Mode

enum GE_BUFFER_MODE
{
    GE_BUFFER_MODE_POSITION,
    GE_BUFFER_MODE_POSITION_TEXTURE,
    GE_BUFFER_MODE_POSITION_NORMAL,
    GE_BUFFER_MODE_ALL
};


// -------------------------------------------- //
// ---------------- UNIFORM IDs --------------- //
// -------------------------------------------- //
#pragma mark Uniform IDs
enum
{
    GE_UNIFORM_MODELVIEWPROJECTION_MATRIX,
    GE_UNIFORM_MATERIAL_TEXTURE_COMPRESSION,
    GE_UNIFORM_MATERIAL_DIFFUSE_MAP,
    GE_UNIFORM_MATERIAL_DIFFUSE_MAP_ENABLED,
    GE_UNIFORM_MATERIAL_SPECULAR_MAP,
    GE_UNIFORM_MATERIAL_SPECULAR_MAP_ENABLED,
    GE_UNIFORM_MATERIAL_DIFFUSE_COLOR,
    GE_UNIFORM_MATERIAL_AMBIENT_COLOR,
    GE_UNIFORM_MATERIAL_SPECULAR_COLOR,
    GE_UNIFORM_MATERIAL_SHININESS,
    GE_UNIFORM_MATERIAL_OPASITY,
    GE_UNIFORM_NUMBER_OF_LIGHTS,
    GE_NUM_UNIFORMS
};
enum
{
    GE_UNIFORM_LIGHT_TYPE,
    GE_UNIFORM_LIGHT_POSITION,
    GE_UNIFORM_LIGHT_DIRECTION,
    GE_UNIFORM_LIGHT_CUTOFF,
    GE_UNIFORM_LIGHT_DIFFUSE_COLOR,
    GE_UNIFORM_LIGHT_AMBIENT_COLOR,
    GE_UNIFORM_LIGHT_SPECULAR_COLOR,
    GE_UNIFORM_LIGHT_MODELVIEWPROJECTION_MATRIX,
    GE_UNIFORM_LIGHT_SHADOW_MAP,
    GE_UNIFORM_LIGHT_SHADOW_MAP_TEXTEL_SIZE,
    GE_UNIFORM_LIGHT_SHADOWS_ENABLED,
    GE_NUM_LIGHT_UNIFORMS
};

// -------------------------------------------- //
// ---------------- Light Types --------------- //
// -------------------------------------------- //
#pragma mark Light Types

enum GE_LIGHT_TYPE
{
    GE_LIGHT_DIRECTIONAL,
    GE_LIGHT_POINT,
    GE_LIGHT_SPOT
};

// -------------------------------------------- //
// ---------------- BUFFER MODE --------------- //
// -------------------------------------------- //
#pragma mark Buffer Mode

enum GE_MODEL_TYPE
{
    GE_MODEL_TYPE_MD5
};

// -------------------------------------------- //
// ------------------- COLORS ----------------- //
// -------------------------------------------- //
#pragma mark Colors

#define     color_indian_red              GLKVector3Make(0.690196078f,  0.090196078f,   0.121568627f)
#define     color_crimson                 GLKVector3Make(0.862745098f,  0.078431373f,   0.235294118f)
#define     color_lightpink               GLKVector3Make(1.0f,          0.71372549f,    0.756862745f)
#define     color_lightpink_1             GLKVector3Make(1.0f,          0.682352941f,   0.725490196f)
#define     color_lightpink_2             GLKVector3Make(0.933333333f,  0.635294118f,   0.678431373f)
#define     color_lightpink_3             GLKVector3Make(0.803921569f,  0.549019608f,   0.584313725f)
#define     color_lightpink_4             GLKVector3Make(0.545098039f,  0.37254902f,    0.396078431f)
#define     color_pink                    GLKVector3Make(1.0f,          0.752941176f,   0.796078431f)
#define     color_pink_1                  GLKVector3Make(1.0f,          0.709803922f,   0.77254902f)
#define     color_pink_2                  GLKVector3Make(0.933333333f,  0.662745098f,   0.721568627f)
#define     color_pink_3                  GLKVector3Make(0.803921569f,  0.568627451f,   0.619607843f)
#define     color_pink_4                  GLKVector3Make(0.545098039f,  0.388235294f,   0.423529412f)
#define     color_palevioletred           GLKVector3Make(0.858823529f,  0.439215686f,   0.576470588f)
#define     color_palevioletred_1         GLKVector3Make(1.0f,          0.509803922f,   0.670588235f)
#define     color_palevioletred_2         GLKVector3Make(0.933333333f,  0.474509804f,   0.623529412f)
#define     color_palevioletred_3         GLKVector3Make(0.803921569f,  0.407843137f,   0.537254902f)
#define     color_palevioletred_4         GLKVector3Make(0.545098039f,  0.278431373f,   0.364705882f)
#define     color_lavenderblush           GLKVector3Make(1.0f,          0.941176471f,   0.960784314f)
#define     color_lavenderblush_2         GLKVector3Make(0.933333333f,  0.878431373f,   0.898039216f)
#define     color_lavenderblush_3         GLKVector3Make(0.803921569f,  0.756862745f,   0.77254902f)
#define     color_lavenderblush_4         GLKVector3Make(0.545098039f,  0.51372549f,    0.525490196f)
#define     color_violetred_1             GLKVector3Make(1.0f,          0.243137255f,   0.588235294f)
#define     color_violetred_2             GLKVector3Make(0.933333333f,  0.22745098f,    0.549019608f)
#define     color_violetred_3             GLKVector3Make(0.803921569f,  0.196078431f,   0.470588235f)
#define     color_violetred_4             GLKVector3Make(0.545098039f,  0.133333333f,   0.321568627f)
#define     color_hotpink                 GLKVector3Make(1.0f,          0.411764706f,   0.705882353f)
#define     color_hotpink_1               GLKVector3Make(1.0f,          0.431372549f,   0.705882353f)
#define     color_hotpink_2               GLKVector3Make(0.933333333f,  0.415686275f,   0.654901961f)
#define     color_hotpink_3               GLKVector3Make(0.803921569f,  0.376470588f,   0.564705882f)
#define     color_hotpink_4               GLKVector3Make(0.545098039f,  0.22745098f,    0.384313725f)
#define     color_raspberry               GLKVector3Make(0.529411765f,  0.149019608f,   0.341176471f)
#define     color_deeppink_1              GLKVector3Make(1.0f,          0.078431373f,   0.576470588f)
#define     color_deeppink_2              GLKVector3Make(0.933333333f,  0.070588235f,   0.537254902f)
#define     color_deeppink_3              GLKVector3Make(0.803921569f,  0.062745098f,   0.462745098f)
#define     color_deeppink_4              GLKVector3Make(0.545098039f,  0.039215686f,   0.31372549f)
#define     color_maroon_1                GLKVector3Make(1.0f,          0.203921569f,   0.701960784f)
#define     color_maroon_2                GLKVector3Make(0.933333333f,  0.188235294f,   0.654901961f)
#define     color_maroon_3                GLKVector3Make(0.803921569f,  0.160784314f,   0.564705882f)
#define     color_maroon_4                GLKVector3Make(0.545098039f,  0.109803922f,   0.384313725f)
#define     color_mediumvioletred         GLKVector3Make(0.780392157f,  0.082352941f,   0.521568627f)
#define     color_violetred               GLKVector3Make(0.815686275f,  0.125490196f,   0.564705882f)
#define     color_orchid                  GLKVector3Make(0.854901961f,  0.439215686f,   0.839215686f)
#define     color_orchid_1                GLKVector3Make(1.0f,          0.51372549f,    0.980392157f)
#define     color_orchid_2                GLKVector3Make(0.933333333f,  0.478431373f,   0.91372549f)
#define     color_orchid_3                GLKVector3Make(0.803921569f,  0.411764706f,   0.788235294f)
#define     color_orchid_4                GLKVector3Make(0.545098039f,  0.278431373f,   0.537254902f)
#define     color_thistle                 GLKVector3Make(0.847058824f,  0.749019608f,   0.847058824f)
#define     color_thistle_1               GLKVector3Make(1.0f,          0.882352941f,   1.0f)
#define     color_thistle_2               GLKVector3Make(0.933333333f,  0.823529412f,   0.933333333f)
#define     color_thistle_3               GLKVector3Make(0.803921569f, 0.709803922f, 0.803921569f)
#define     color_thistle_4               GLKVector3Make(0.545098039f, 0.482352941f, 0.545098039f)
#define     color_plum_1                  GLKVector3Make(1.0f, 0.733333333f, 1.0f)
#define     color_plum_2                  GLKVector3Make(0.933333333f, 0.682352941f, 0.933333333f)
#define     color_plum_3                  GLKVector3Make(0.803921569f, 0.588235294f, 0.803921569f)
#define     color_plum_4                  GLKVector3Make(0.545098039f, 0.4f, 0.545098039f)
#define     color_plum                    GLKVector3Make(0.866666667f, 0.62745098f, 0.866666667f)
#define     color_violet                  GLKVector3Make(0.933333333f, 0.509803922f, 0.933333333f)
#define     color_magenta                 GLKVector3Make(1.0f, 0.0f, 1.0f)
#define     color_magenta_2               GLKVector3Make(0.933333333f, 0.0f, 0.933333333f)
#define     color_magenta_3               GLKVector3Make(0.803921569f, 0.0f, 0.803921569f)
#define     color_magenta_4               GLKVector3Make(0.545098039f, 0.0f, 0.545098039f)
#define     color_purple                  GLKVector3Make(0.501960784f, 0.0f, 0.501960784f)
#define     color_mediumorchid            GLKVector3Make(0.729411765f, 0.333333333f, 0.82745098f)
#define     color_mediumorchid_1          GLKVector3Make(0.878431373f, 0.4f, 1.0f)
#define     color_mediumorchid_2          GLKVector3Make(0.819607843f, 0.37254902f, 0.933333333f)
#define     color_mediumorchid_3          GLKVector3Make(0.705882353f, 0.321568627f, 0.803921569f)
#define     color_mediumorchid_4          GLKVector3Make(0.478431373f, 0.215686275f, 0.545098039f)
#define     color_darkviolet              GLKVector3Make(0.580392157f, 0.0f, 0.82745098f)
#define     color_darkorchid              GLKVector3Make(0.6f, 0.196078431f, 0.8f)
#define     color_darkorchid_1            GLKVector3Make(0.749019608f, 0.243137255f, 1.0f)
#define     color_darkorchid_2            GLKVector3Make(0.698039216f, 0.22745098f, 0.933333333f)
#define     color_darkorchid_3            GLKVector3Make(0.603921569f, 0.196078431f, 0.803921569f)
#define     color_darkorchid_4            GLKVector3Make(0.407843137f, 0.133333333f, 0.545098039f)
#define     color_indigo                  GLKVector3Make(0.294117647f, 0.0f, 0.509803922f)
#define     color_blueviolet              GLKVector3Make(0.541176471f, 0.168627451f, 0.88627451f)
#define     color_purple_1                GLKVector3Make(0.607843137f, 0.188235294f, 1.0f)
#define     color_purple_2                GLKVector3Make(0.568627451f, 0.17254902f, 0.933333333f)
#define     color_purple_3                GLKVector3Make(0.490196078f, 0.149019608f, 0.803921569f)
#define     color_purple_4                GLKVector3Make(0.333333333f, 0.101960784f, 0.545098039f)
#define     color_mediumpurple            GLKVector3Make(0.576470588f, 0.439215686f, 0.858823529f)
#define     color_mediumpurple_1          GLKVector3Make(0.670588235f, 0.509803922f, 1.0f)
#define     color_mediumpurple_2          GLKVector3Make(0.623529412f, 0.474509804f, 0.933333333f)
#define     color_mediumpurple_3          GLKVector3Make(0.537254902f, 0.407843137f, 0.803921569f)
#define     color_mediumpurple_4          GLKVector3Make(0.364705882f, 0.278431373f, 0.545098039f)
#define     color_darkslateblue           GLKVector3Make(0.282352941f, 0.239215686f, 0.545098039f)
#define     color_lightslateblue          GLKVector3Make(0.517647059f, 0.439215686f, 1.0f)
#define     color_mediumslateblue         GLKVector3Make(0.482352941f, 0.407843137f, 0.933333333f)
#define     color_slateblue               GLKVector3Make(0.415686275f, 0.352941176f, 0.803921569f)
#define     color_slateblue_1             GLKVector3Make(0.51372549f, 0.435294118f, 1.0f)
#define     color_slateblue_2             GLKVector3Make(0.478431373f, 0.403921569f, 0.933333333f)
#define     color_slateblue_3             GLKVector3Make(0.411764706f, 0.349019608f, 0.803921569f)
#define     color_slateblue_4             GLKVector3Make(0.278431373f, 0.235294118f, 0.545098039f)
#define     color_ghostwhite              GLKVector3Make(0.97254902f, 0.97254902f, 1.0f)
#define     color_lavender                GLKVector3Make(0.901960784f, 0.901960784f, 0.980392157f)
#define     color_blue                    GLKVector3Make(0.0f, 0.0f, 1.0f)
#define     color_blue_2                  GLKVector3Make(0.0f, 0.0f, 0.933333333f)
#define     color_blue_3                  GLKVector3Make(0.0f, 0.0f, 0.803921569f)
#define     color_blue_4                  GLKVector3Make(0.0f, 0.0f, 0.545098039f)
#define     color_navy                    GLKVector3Make(0.0f, 0.0f, 0.501960784f)
#define     color_midnightblue            GLKVector3Make(0.098039216f, 0.098039216f, 0.439215686f)
#define     color_cobalt                  GLKVector3Make(0.239215686f, 0.349019608f, 0.670588235f)
#define     color_royalblue               GLKVector3Make(0.254901961f, 0.411764706f, 0.882352941f)
#define     color_royalblue_1             GLKVector3Make(0.282352941f, 0.462745098f, 1.0f)
#define     color_royalblue_2             GLKVector3Make(0.262745098f, 0.431372549f, 0.933333333f)
#define     color_royalblue_3             GLKVector3Make(0.22745098f, 0.37254902f, 0.803921569f)
#define     color_royalblue_4             GLKVector3Make(0.152941176f, 0.250980392f, 0.545098039f)
#define     color_cornflowerblue          GLKVector3Make(0.392156863f, 0.584313725f, 0.929411765f)
#define     color_lightsteelblue          GLKVector3Make(0.690196078f, 0.768627451f, 0.870588235f)
#define     color_lightsteelblue_1        GLKVector3Make(0.792156863f, 0.882352941f, 1.0f)
#define     color_lightsteelblue_2        GLKVector3Make(0.737254902f, 0.823529412f, 0.933333333f)
#define     color_lightsteelblue_3        GLKVector3Make(0.635294118f, 0.709803922f, 0.803921569f)
#define     color_lightsteelblue_4        GLKVector3Make(0.431372549f, 0.482352941f, 0.545098039f)
#define     color_lightslategray          GLKVector3Make(0.466666667f, 0.533333333f, 0.6f)
#define     color_slategray               GLKVector3Make(0.439215686f, 0.501960784f, 0.564705882f)
#define     color_slategray_1             GLKVector3Make(0.776470588f, 0.88627451f, 1.0f)
#define     color_slategray_2             GLKVector3Make(0.725490196f, 0.82745098f, 0.933333333f)
#define     color_slategray_3             GLKVector3Make(0.623529412f, 0.71372549f, 0.803921569f)
#define     color_slategray_4             GLKVector3Make(0.423529412f, 0.482352941f, 0.545098039f)
#define     color_dodgerblue              GLKVector3Make(0.117647059f, 0.564705882f, 1.0f)
#define     color_dodgerblue_2            GLKVector3Make(0.109803922f, 0.525490196f, 0.933333333f)
#define     color_dodgerblue_3            GLKVector3Make(0.094117647f, 0.454901961f, 0.803921569f)
#define     color_dodgerblue_4            GLKVector3Make(0.062745098f, 0.305882353f, 0.545098039f)
#define     color_aliceblue               GLKVector3Make(0.941176471f, 0.97254902f, 1.0f)
#define     color_steelblue               GLKVector3Make(0.274509804f, 0.509803922f, 0.705882353f)
#define     color_steelblue_1             GLKVector3Make(0.388235294f, 0.721568627f, 1.0f)
#define     color_steelblue_2             GLKVector3Make(0.360784314f, 0.674509804f, 0.933333333f)
#define     color_steelblue_3             GLKVector3Make(0.309803922f, 0.580392157f, 0.803921569f)
#define     color_steelblue_4             GLKVector3Make(0.211764706f, 0.392156863f, 0.545098039f)
#define     color_lightskyblue            GLKVector3Make(0.529411765f, 0.807843137f, 0.980392157f)
#define     color_lightskyblue_1          GLKVector3Make(0.690196078f, 0.88627451f, 1.0f)
#define     color_lightskyblue_2          GLKVector3Make(0.643137255f, 0.82745098f, 0.933333333f)
#define     color_lightskyblue_3          GLKVector3Make(0.552941176f, 0.71372549f, 0.803921569f)
#define     color_lightskyblue_4          GLKVector3Make(0.376470588f, 0.482352941f, 0.545098039f)
#define     color_skyblue_1               GLKVector3Make(0.529411765f, 0.807843137f, 1.0f)
#define     color_skyblue_2               GLKVector3Make(0.494117647f, 0.752941176f, 0.933333333f)
#define     color_skyblue_3               GLKVector3Make(0.423529412f, 0.650980392f, 0.803921569f)
#define     color_skyblue_4               GLKVector3Make(0.290196078f, 0.439215686f, 0.545098039f)
#define     color_skyblue                 GLKVector3Make(0.529411765f, 0.807843137f, 0.921568627f)
#define     color_deepskyblue             GLKVector3Make(0.0f, 0.749019608f, 1.0f)
#define     color_deepskyblue_2           GLKVector3Make(0.0f, 0.698039216f, 0.933333333f)
#define     color_deepskyblue_3           GLKVector3Make(0.0f, 0.603921569f, 0.803921569f)
#define     color_deepskyblue_4           GLKVector3Make(0.0f, 0.407843137f, 0.545098039f)
#define     color_peacock                 GLKVector3Make(0.2f, 0.631372549f, 0.788235294f)
#define     color_lightblue               GLKVector3Make(0.678431373f, 0.847058824f, 0.901960784f)
#define     color_lightblue_1             GLKVector3Make(0.749019608f, 0.937254902f, 1.0f)
#define     color_lightblue_2             GLKVector3Make(0.698039216f, 0.874509804f, 0.933333333f)
#define     color_lightblue_3             GLKVector3Make(0.603921569f, 0.752941176f, 0.803921569f)
#define     color_lightblue_4             GLKVector3Make(0.407843137f, 0.51372549f, 0.545098039f)
#define     color_powderblue              GLKVector3Make(0.690196078f, 0.878431373f, 0.901960784f)
#define     color_cadetblue_1             GLKVector3Make(0.596078431f, 0.960784314f, 1.0f)
#define     color_cadetblue_2             GLKVector3Make(0.556862745f, 0.898039216f, 0.933333333f)
#define     color_cadetblue_3             GLKVector3Make(0.478431373f, 0.77254902f, 0.803921569f)
#define     color_cadetblue_4             GLKVector3Make(0.325490196f, 0.525490196f, 0.545098039f)
#define     color_turquoise_1             GLKVector3Make(0.0f, 0.960784314f, 1.0f)
#define     color_turquoise_2             GLKVector3Make(0.0f, 0.898039216f, 0.933333333f)
#define     color_turquoise_3             GLKVector3Make(0.0f, 0.77254902f, 0.803921569f)
#define     color_turquoise_4             GLKVector3Make(0.0f, 0.525490196f, 0.545098039f)
#define     color_cadetblue               GLKVector3Make(0.37254902f, 0.619607843f, 0.62745098f)
#define     color_darkturquoise           GLKVector3Make(0.0f, 0.807843137f, 0.819607843f)
#define     color_azure                   GLKVector3Make(0.941176471f, 1.0f, 1.0f)
#define     color_azure_2                 GLKVector3Make(0.878431373f, 0.933333333f, 0.933333333f)
#define     color_azure_3                 GLKVector3Make(0.756862745f, 0.803921569f, 0.803921569f)
#define     color_azure_4                 GLKVector3Make(0.51372549f, 0.545098039f, 0.545098039f)
#define     color_lightcyan               GLKVector3Make(0.878431373f, 1.0f, 1.0f)
#define     color_lightcyan_2             GLKVector3Make(0.819607843f, 0.933333333f, 0.933333333f)
#define     color_lightcyan_3             GLKVector3Make(0.705882353f, 0.803921569f, 0.803921569f)
#define     color_lightcyan_4             GLKVector3Make(0.478431373f, 0.545098039f, 0.545098039f)
#define     color_paleturquoise           GLKVector3Make(0.733333333f, 1.0f, 1.0f)
#define     color_paleturquoise_2         GLKVector3Make(0.682352941f, 0.933333333f, 0.933333333f)
#define     color_paleturquoise_3         GLKVector3Make(0.588235294f, 0.803921569f, 0.803921569f)
#define     color_paleturquoise_4         GLKVector3Make(0.4f, 0.545098039f, 0.545098039f)
#define     color_darkslategray           GLKVector3Make(0.184313725f, 0.309803922f, 0.309803922f)
#define     color_darkslategray_1         GLKVector3Make(0.592156863f, 1.0f, 1.0f)
#define     color_darkslategray_2         GLKVector3Make(0.552941176f, 0.933333333f, 0.933333333f)
#define     color_darkslategray_3         GLKVector3Make(0.474509804f, 0.803921569f, 0.803921569f)
#define     color_darkslategray_4         GLKVector3Make(0.321568627f, 0.545098039f, 0.545098039f)
#define     color_cyan                    GLKVector3Make(0.0f, 1.0f, 1.0f)
#define     color_cyan_2                  GLKVector3Make(0.0f, 0.933333333f, 0.933333333f)
#define     color_cyan_3                  GLKVector3Make(0.0f, 0.803921569f, 0.803921569f)
#define     color_cyan_4                  GLKVector3Make(0.0f, 0.545098039f, 0.545098039f)
#define     color_teal                    GLKVector3Make(0.0f, 0.501960784f, 0.501960784f)
#define     color_mediumturquoise         GLKVector3Make(0.282352941f, 0.819607843f, 0.8f)
#define     color_lightseagreen           GLKVector3Make(0.125490196f, 0.698039216f, 0.666666667f)
#define     color_manganeseblue           GLKVector3Make(0.011764706f, 0.658823529f, 0.619607843f)
#define     color_turquoise               GLKVector3Make(0.250980392f, 0.878431373f, 0.815686275f)
#define     color_coldgrey                GLKVector3Make(0.501960784f, 0.541176471f, 0.529411765f)
#define     color_turquoiseblue           GLKVector3Make(0.0f, 0.780392157f, 0.549019608f)
#define     color_aquamarine              GLKVector3Make(0.498039216f, 1.0f, 0.831372549f)
#define     color_aquamarine_2            GLKVector3Make(0.462745098f, 0.933333333f, 0.776470588f)
#define     color_aquamarine_3            GLKVector3Make(0.4f, 0.803921569f, 0.666666667f)
#define     color_aquamarine_4            GLKVector3Make(0.270588235f, 0.545098039f, 0.454901961f)
#define     color_mediumspringgreen       GLKVector3Make(0.0f, 0.980392157f, 0.603921569f)
#define     color_mintcream               GLKVector3Make(0.960784314f, 1.0f, 0.980392157f)
#define     color_springgreen             GLKVector3Make(0.0f, 1.0f, 0.498039216f)
#define     color_springgreen_1           GLKVector3Make(0.0f, 0.933333333f, 0.462745098f)
#define     color_springgreen_2           GLKVector3Make(0.0f, 0.803921569f, 0.4f)
#define     color_springgreen_3           GLKVector3Make(0.0f, 0.545098039f, 0.270588235f)
#define     color_mediumseagreen          GLKVector3Make(0.235294118f, 0.701960784f, 0.443137255f)
#define     color_seagreen_1              GLKVector3Make(0.329411765f, 1.0f, 0.623529412f)
#define     color_seagreen_2              GLKVector3Make(0.305882353f, 0.933333333f, 0.580392157f)
#define     color_seagreen_3              GLKVector3Make(0.262745098f, 0.803921569f, 0.501960784f)
#define     color_seagreen_4              GLKVector3Make(0.180392157f, 0.545098039f, 0.341176471f)
#define     color_emeraldgreen            GLKVector3Make(0.0f, 0.788235294f, 0.341176471f)
#define     color_mint                    GLKVector3Make(0.741176471f, 0.988235294f, 0.788235294f)
#define     color_cobaltgreen             GLKVector3Make(0.239215686f, 0.568627451f, 0.250980392f)
#define     color_honeydew                GLKVector3Make(0.941176471f, 1.0f, 0.941176471f)
#define     color_honeydew_2              GLKVector3Make(0.878431373f, 0.933333333f, 0.878431373f)
#define     color_honeydew_3              GLKVector3Make(0.756862745f, 0.803921569f, 0.756862745f)
#define     color_honeydew_4              GLKVector3Make(0.51372549f, 0.545098039f, 0.51372549f)
#define     color_darkseagreen            GLKVector3Make(0.560784314f, 0.737254902f, 0.560784314f)
#define     color_darkseagreen_1          GLKVector3Make(0.756862745f, 1.0f, 0.756862745f)
#define     color_darkseagreen_2          GLKVector3Make(0.705882353f, 0.933333333f, 0.705882353f)
#define     color_darkseagreen_3          GLKVector3Make(0.607843137f, 0.803921569f, 0.607843137f)
#define     color_darkseagreen_4          GLKVector3Make(0.411764706f, 0.545098039f, 0.411764706f)
#define     color_palegreen               GLKVector3Make(0.596078431f, 0.984313725f, 0.596078431f)
#define     color_palegreen_1             GLKVector3Make(0.603921569f, 1.0f, 0.603921569f)
#define     color_palegreen_2             GLKVector3Make(0.564705882f, 0.933333333f, 0.564705882f)
#define     color_palegreen_3             GLKVector3Make(0.48627451f, 0.803921569f, 0.48627451f)
#define     color_palegreen_4             GLKVector3Make(0.329411765f, 0.545098039f, 0.329411765f)
#define     color_limegreen               GLKVector3Make(0.196078431f, 0.803921569f, 0.196078431f)
#define     color_forestgreen             GLKVector3Make(0.133333333f, 0.545098039f, 0.133333333f)
#define     color_lime                    GLKVector3Make(0.0f, 1.0f, 0.0f)
#define     color_green_2                 GLKVector3Make(0.0f, 0.933333333f, 0.0f)
#define     color_green_3                 GLKVector3Make(0.0f, 0.803921569f, 0.0f)
#define     color_green_4                 GLKVector3Make(0.0f, 0.545098039f, 0.0f)
#define     color_green                   GLKVector3Make(0.0f, 0.501960784f, 0.0f)
#define     color_darkgreen               GLKVector3Make(0.0f, 0.392156863f, 0.0f)
#define     color_sapgreen                GLKVector3Make(0.188235294f, 0.501960784f, 0.078431373f)
#define     color_lawngreen               GLKVector3Make(0.48627451f, 0.988235294f, 0.0f)
#define     color_chartreuse              GLKVector3Make(0.498039216f, 1.0f, 0.0f)
#define     color_chartreuse_2            GLKVector3Make(0.462745098f, 0.933333333f, 0.0f)
#define     color_chartreuse_3            GLKVector3Make(0.4f, 0.803921569f, 0.0f)
#define     color_chartreuse_4            GLKVector3Make(0.270588235f, 0.545098039f, 0.0f)
#define     color_greenyellow             GLKVector3Make(0.678431373f, 1.0f, 0.184313725f)
#define     color_darkolivegreen_1        GLKVector3Make(0.792156863f, 1.0f, 0.439215686f)
#define     color_darkolivegreen_2        GLKVector3Make(0.737254902f, 0.933333333f, 0.407843137f)
#define     color_darkolivegreen_3        GLKVector3Make(0.635294118f, 0.803921569f, 0.352941176f)
#define     color_darkolivegreen_4        GLKVector3Make(0.431372549f, 0.545098039f, 0.239215686f)
#define     color_darkolivegreen          GLKVector3Make(0.333333333f, 0.419607843f, 0.184313725f)
#define     color_olivedrab               GLKVector3Make(0.419607843f, 0.556862745f, 0.137254902f)
#define     color_olivedrab_1             GLKVector3Make(0.752941176f, 1.0f, 0.243137255f)
#define     color_olivedrab_2             GLKVector3Make(0.701960784f, 0.933333333f, 0.22745098f)
#define     color_olivedrab_3             GLKVector3Make(0.603921569f, 0.803921569f, 0.196078431f)
#define     color_olivedrab_4             GLKVector3Make(0.411764706f, 0.545098039f, 0.133333333f)
#define     color_ivory                   GLKVector3Make(1.0f, 1.0f, 0.941176471f)
#define     color_ivory_2                 GLKVector3Make(0.933333333f, 0.933333333f, 0.878431373f)
#define     color_ivory_3                 GLKVector3Make(0.803921569f, 0.803921569f, 0.756862745f)
#define     color_ivory_4                 GLKVector3Make(0.545098039f, 0.545098039f, 0.51372549f)
#define     color_beige                   GLKVector3Make(0.960784314f, 0.960784314f, 0.862745098f)
#define     color_lightyellow             GLKVector3Make(1.0f, 1.0f, 0.878431373f)
#define     color_lightyellow_2           GLKVector3Make(0.933333333f, 0.933333333f, 0.819607843f)
#define     color_lightyellow_3           GLKVector3Make(0.803921569f, 0.803921569f, 0.705882353f)
#define     color_lightyellow_4           GLKVector3Make(0.545098039f, 0.545098039f, 0.478431373f)
#define     color_lightgoldenrodyellow    GLKVector3Make(0.980392157f, 0.980392157f, 0.823529412f)
#define     color_yellow                  GLKVector3Make(1.0f, 1.0f, 0.0f)
#define     color_yellow_2                GLKVector3Make(0.933333333f, 0.933333333f, 0.0f)
#define     color_yellow_3                GLKVector3Make(0.803921569f, 0.803921569f, 0.0f)
#define     color_yellow_4                GLKVector3Make(0.545098039f, 0.545098039f, 0.0f)
#define     color_warmgrey                GLKVector3Make(0.501960784f, 0.501960784f, 0.411764706f)
#define     color_olive                   GLKVector3Make(0.501960784f, 0.501960784f, 0.0f)
#define     color_darkkhaki               GLKVector3Make(0.741176471f, 0.717647059f, 0.419607843f)
#define     color_khaki_2                 GLKVector3Make(1.0f, 0.964705882f, 0.560784314f)
#define     color_khaki_3                 GLKVector3Make(0.933333333f, 0.901960784f, 0.521568627f)
#define     color_khaki_4                 GLKVector3Make(0.803921569f, 0.776470588f, 0.450980392f)
#define     color_khaki_5                 GLKVector3Make(0.545098039f, 0.525490196f, 0.305882353f)
#define     color_khaki                   GLKVector3Make(0.941176471f, 0.901960784f, 0.549019608f)
#define     color_palegoldenrod           GLKVector3Make(0.933333333f, 0.909803922f, 0.666666667f)
#define     color_lemonchiffon            GLKVector3Make(1.0f, 0.980392157f, 0.803921569f)
#define     color_lemonchiffon_2          GLKVector3Make(0.933333333f, 0.91372549f, 0.749019608f)
#define     color_lemonchiffon_3          GLKVector3Make(0.803921569f, 0.788235294f, 0.647058824f)
#define     color_lemonchiffon_4          GLKVector3Make(0.545098039f, 0.537254902f, 0.439215686f)
#define     color_lightgoldenrod_1        GLKVector3Make(1.0f, 0.925490196f, 0.545098039f)
#define     color_lightgoldenrod_2        GLKVector3Make(0.933333333f, 0.862745098f, 0.509803922f)
#define     color_lightgoldenrod_3        GLKVector3Make(0.803921569f, 0.745098039f, 0.439215686f)
#define     color_lightgoldenrod_4        GLKVector3Make(0.545098039f, 0.505882353f, 0.298039216f)
#define     color_banana                  GLKVector3Make(0.890196078f, 0.811764706f, 0.341176471f)
#define     color_gold                    GLKVector3Make(1.0f, 0.843137255f, 0.0f)
#define     color_gold_2                  GLKVector3Make(0.933333333f, 0.788235294f, 0.0f)
#define     color_gold_3                  GLKVector3Make(0.803921569f, 0.678431373f, 0.0f)
#define     color_gold_4                  GLKVector3Make(0.545098039f, 0.458823529f, 0.0f)
#define     color_cornsilk                GLKVector3Make(1.0f, 0.97254902f, 0.862745098f)
#define     color_cornsilk_2              GLKVector3Make(0.933333333f, 0.909803922f, 0.803921569f)
#define     color_cornsilk_3              GLKVector3Make(0.803921569f, 0.784313725f, 0.694117647f)
#define     color_cornsilk_4              GLKVector3Make(0.545098039f, 0.533333333f, 0.470588235f)
#define     color_goldenrod               GLKVector3Make(0.854901961f, 0.647058824f, 0.125490196f)
#define     color_goldenrod_1             GLKVector3Make(1.0f, 0.756862745f, 0.145098039f)
#define     color_goldenrod_2             GLKVector3Make(0.933333333f, 0.705882353f, 0.133333333f)
#define     color_goldenrod_3             GLKVector3Make(0.803921569f, 0.607843137f, 0.11372549f)
#define     color_goldenrod_4             GLKVector3Make(0.545098039f, 0.411764706f, 0.078431373f)
#define     color_darkgoldenrod           GLKVector3Make(0.721568627f, 0.525490196f, 0.043137255f)
#define     color_darkgoldenrod_1         GLKVector3Make(1.0f, 0.725490196f, 0.058823529f)
#define     color_darkgoldenrod_2         GLKVector3Make(0.933333333f, 0.678431373f, 0.054901961f)
#define     color_darkgoldenrod_3         GLKVector3Make(0.803921569f, 0.584313725f, 0.047058824f)
#define     color_darkgoldenrod_4         GLKVector3Make(0.545098039f, 0.396078431f, 0.031372549f)
#define     color_orange                  GLKVector3Make(1.0f, 0.647058824f, 0.0f)
#define     color_orange_2                GLKVector3Make(0.933333333f, 0.603921569f, 0.0f)
#define     color_orange_3                GLKVector3Make(0.803921569f, 0.521568627f, 0.0f)
#define     color_orange_4                GLKVector3Make(0.545098039f, 0.352941176f, 0.0f)
#define     color_floralwhite             GLKVector3Make(1.0f, 0.980392157f, 0.941176471f)
#define     color_oldlace                 GLKVector3Make(0.992156863f, 0.960784314f, 0.901960784f)
#define     color_wheat                   GLKVector3Make(0.960784314f, 0.870588235f, 0.701960784f)
#define     color_wheat_1                 GLKVector3Make(1.0f, 0.905882353f, 0.729411765f)
#define     color_wheat_2                 GLKVector3Make(0.933333333f, 0.847058824f, 0.682352941f)
#define     color_wheat_3                 GLKVector3Make(0.803921569f, 0.729411765f, 0.588235294f)
#define     color_wheat_4                 GLKVector3Make(0.545098039f, 0.494117647f, 0.4f)
#define     color_moccasin                GLKVector3Make(1.0f, 0.894117647f, 0.709803922f)
#define     color_papayawhip              GLKVector3Make(1.0f, 0.937254902f, 0.835294118f)
#define     color_blanchedalmond          GLKVector3Make(1.0f, 0.921568627f, 0.803921569f)
#define     color_navajowhite             GLKVector3Make(1.0f, 0.870588235f, 0.678431373f)
#define     color_navajowhite_2           GLKVector3Make(0.933333333f, 0.811764706f, 0.631372549f)
#define     color_navajowhite_3           GLKVector3Make(0.803921569f, 0.701960784f, 0.545098039f)
#define     color_navajowhite_4           GLKVector3Make(0.545098039f, 0.474509804f, 0.368627451f)
#define     color_eggshell                GLKVector3Make(0.988235294f, 0.901960784f, 0.788235294f)
#define     color_tan                     GLKVector3Make(0.823529412f, 0.705882353f, 0.549019608f)
#define     color_brick                   GLKVector3Make(0.611764706f, 0.4f, 0.121568627f)
#define     color_cadmiumyellow           GLKVector3Make(1.0f, 0.6f, 0.070588235f)
#define     color_antiquewhite            GLKVector3Make(0.980392157f, 0.921568627f, 0.843137255f)
#define     color_antiquewhite_1          GLKVector3Make(1.0f, 0.937254902f, 0.858823529f)
#define     color_antiquewhite_2          GLKVector3Make(0.933333333f, 0.874509804f, 0.8f)
#define     color_antiquewhite_3          GLKVector3Make(0.803921569f, 0.752941176f, 0.690196078f)
#define     color_antiquewhite_4          GLKVector3Make(0.545098039f, 0.51372549f, 0.470588235f)
#define     color_burlywood               GLKVector3Make(0.870588235f, 0.721568627f, 0.529411765f)
#define     color_burlywood_1             GLKVector3Make(1.0f, 0.82745098f, 0.607843137f)
#define     color_burlywood_2             GLKVector3Make(0.933333333f, 0.77254902f, 0.568627451f)
#define     color_burlywood_3             GLKVector3Make(0.803921569f, 0.666666667f, 0.490196078f)
#define     color_burlywood_4             GLKVector3Make(0.545098039f, 0.450980392f, 0.333333333f)
#define     color_bisque                  GLKVector3Make(1.0f, 0.894117647f, 0.768627451f)
#define     color_bisque_2                GLKVector3Make(0.933333333f, 0.835294118f, 0.717647059f)
#define     color_bisque_3                GLKVector3Make(0.803921569f, 0.717647059f, 0.619607843f)
#define     color_bisque_4                GLKVector3Make(0.545098039f, 0.490196078f, 0.419607843f)
#define     color_melon                   GLKVector3Make(0.890196078f, 0.658823529f, 0.411764706f)
#define     color_carrot                  GLKVector3Make(0.929411765f, 0.568627451f, 0.129411765f)
#define     color_darkorange              GLKVector3Make(1.0f, 0.549019608f, 0.0f)
#define     color_darkorange_1            GLKVector3Make(1.0f, 0.498039216f, 0.0f)
#define     color_darkorange_2            GLKVector3Make(0.933333333f, 0.462745098f, 0.0f)
#define     color_darkorange_3            GLKVector3Make(0.803921569f, 0.4f, 0.0f)
#define     color_darkorange_4            GLKVector3Make(0.545098039f, 0.270588235f, 0.0f)
#define     color_tan_1                   GLKVector3Make(1.0f, 0.647058824f, 0.309803922f)
#define     color_tan_2                   GLKVector3Make(0.933333333f, 0.603921569f, 0.28627451f)
#define     color_tan_3                   GLKVector3Make(0.803921569f, 0.521568627f, 0.247058824f)
#define     color_tan_4                   GLKVector3Make(0.545098039f, 0.352941176f, 0.168627451f)
#define     color_linen                   GLKVector3Make(0.980392157f, 0.941176471f, 0.901960784f)
#define     color_peachpuff               GLKVector3Make(1.0f, 0.854901961f, 0.725490196f)
#define     color_peachpuff_2             GLKVector3Make(0.933333333f, 0.796078431f, 0.678431373f)
#define     color_peachpuff_3             GLKVector3Make(0.803921569f, 0.68627451f, 0.584313725f)
#define     color_peachpuff_4             GLKVector3Make(0.545098039f, 0.466666667f, 0.396078431f)
#define     color_seashell                GLKVector3Make(1.0f, 0.960784314f, 0.933333333f)
#define     color_seashell_2              GLKVector3Make(0.933333333f, 0.898039216f, 0.870588235f)
#define     color_seashell_3              GLKVector3Make(0.803921569f, 0.77254902f, 0.749019608f)
#define     color_seashell_4              GLKVector3Make(0.545098039f, 0.525490196f, 0.509803922f)
#define     color_sandybrown              GLKVector3Make(0.956862745f, 0.643137255f, 0.376470588f)
#define     color_rawsienna               GLKVector3Make(0.780392157f, 0.380392157f, 0.078431373f)
#define     color_chocolate               GLKVector3Make(0.823529412f, 0.411764706f, 0.117647059f)
#define     color_chocolate_1             GLKVector3Make(1.0f, 0.498039216f, 0.141176471f)
#define     color_chocolate_2             GLKVector3Make(0.933333333f, 0.462745098f, 0.129411765f)
#define     color_chocolate_3             GLKVector3Make(0.803921569f, 0.4f, 0.11372549f)
#define     color_chocolate_4             GLKVector3Make(0.545098039f, 0.270588235f, 0.074509804f)
#define     color_ivoryblack              GLKVector3Make(0.160784314f, 0.141176471f, 0.129411765f)
#define     color_flesh                   GLKVector3Make(1.0f, 0.490196078f, 0.250980392f)
#define     color_cadmiumorange           GLKVector3Make(1.0f, 0.380392157f, 0.011764706f)
#define     color_burntsienna             GLKVector3Make(0.541176471f, 0.211764706f, 0.058823529f)
#define     color_sienna                  GLKVector3Make(0.62745098f, 0.321568627f, 0.176470588f)
#define     color_sienna_1                GLKVector3Make(1.0f, 0.509803922f, 0.278431373f)
#define     color_sienna_2                GLKVector3Make(0.933333333f, 0.474509804f, 0.258823529f)
#define     color_sienna_3                GLKVector3Make(0.803921569f, 0.407843137f, 0.223529412f)
#define     color_sienna_4                GLKVector3Make(0.545098039f, 0.278431373f, 0.149019608f)
#define     color_lightsalmon             GLKVector3Make(1.0f, 0.62745098f, 0.478431373f)
#define     color_lightsalmon_2           GLKVector3Make(0.933333333f, 0.584313725f, 0.447058824f)
#define     color_lightsalmon_3           GLKVector3Make(0.803921569f, 0.505882353f, 0.384313725f)
#define     color_lightsalmon_4           GLKVector3Make(0.545098039f, 0.341176471f, 0.258823529f)
#define     color_coral                   GLKVector3Make(1.0f, 0.498039216f, 0.31372549f)
#define     color_orangered               GLKVector3Make(1.0f, 0.270588235f, 0.0f)
#define     color_orangered_2             GLKVector3Make(0.933333333f, 0.250980392f, 0.0f)
#define     color_orangered_3             GLKVector3Make(0.803921569f, 0.215686275f, 0.0f)
#define     color_orangered_4             GLKVector3Make(0.545098039f, 0.145098039f, 0.0f)
#define     color_sepia                   GLKVector3Make(0.368627451f, 0.149019608f, 0.070588235f)
#define     color_darksalmon              GLKVector3Make(0.91372549f, 0.588235294f, 0.478431373f)
#define     color_salmon_1                GLKVector3Make(1.0f, 0.549019608f, 0.411764706f)
#define     color_salmon_2                GLKVector3Make(0.933333333f, 0.509803922f, 0.384313725f)
#define     color_salmon_3                GLKVector3Make(0.803921569f, 0.439215686f, 0.329411765f)
#define     color_salmon_4                GLKVector3Make(0.545098039f, 0.298039216f, 0.223529412f)
#define     color_coral_1                 GLKVector3Make(1.0f, 0.447058824f, 0.337254902f)
#define     color_coral_2                 GLKVector3Make(0.933333333f, 0.415686275f, 0.31372549f)
#define     color_coral_3                 GLKVector3Make(0.803921569f, 0.356862745f, 0.270588235f)
#define     color_coral_4                 GLKVector3Make(0.545098039f, 0.243137255f, 0.184313725f)
#define     color_burntumber              GLKVector3Make(0.541176471f, 0.2f, 0.141176471f)
#define     color_tomato                  GLKVector3Make(1.0f, 0.388235294f, 0.278431373f)
#define     color_tomato_2                GLKVector3Make(0.933333333f, 0.360784314f, 0.258823529f)
#define     color_tomato_3                GLKVector3Make(0.803921569f, 0.309803922f, 0.223529412f)
#define     color_tomato_4                GLKVector3Make(0.545098039f, 0.211764706f, 0.149019608f)
#define     color_salmon                  GLKVector3Make(0.980392157f, 0.501960784f, 0.447058824f)
#define     color_mistyrose               GLKVector3Make(1.0f, 0.894117647f, 0.882352941f)
#define     color_mistyrose_2             GLKVector3Make(0.933333333f, 0.835294118f, 0.823529412f)
#define     color_mistyrose_3             GLKVector3Make(0.803921569f, 0.717647059f, 0.709803922f)
#define     color_mistyrose_4             GLKVector3Make(0.545098039f, 0.490196078f, 0.482352941f)
#define     color_snow                    GLKVector3Make(1.0f, 0.980392157f, 0.980392157f)
#define     color_snow_2                  GLKVector3Make(0.933333333f, 0.91372549f, 0.91372549f)
#define     color_snow_3                  GLKVector3Make(0.803921569f, 0.788235294f, 0.788235294f)
#define     color_snow_4                  GLKVector3Make(0.545098039f, 0.537254902f, 0.537254902f)
#define     color_rosybrown               GLKVector3Make(0.737254902f, 0.560784314f, 0.560784314f)
#define     color_rosybrown_1             GLKVector3Make(1.0f, 0.756862745f, 0.756862745f)
#define     color_rosybrown_2             GLKVector3Make(0.933333333f, 0.705882353f, 0.705882353f)
#define     color_rosybrown_3             GLKVector3Make(0.803921569f, 0.607843137f, 0.607843137f)
#define     color_rosybrown_4             GLKVector3Make(0.545098039f, 0.411764706f, 0.411764706f)
#define     color_lightcoral              GLKVector3Make(0.941176471f, 0.501960784f, 0.501960784f)
#define     color_indianred               GLKVector3Make(0.803921569f, 0.360784314f, 0.360784314f)
#define     color_indianred_1             GLKVector3Make(1.0f, 0.415686275f, 0.415686275f)
#define     color_indianred_2             GLKVector3Make(0.933333333f, 0.388235294f, 0.388235294f)
#define     color_indianred_4             GLKVector3Make(0.545098039f, 0.22745098f, 0.22745098f)
#define     color_indianred_3             GLKVector3Make(0.803921569f, 0.333333333f, 0.333333333f)
#define     color_brown                   GLKVector3Make(0.647058824f, 0.164705882f, 0.164705882f)
#define     color_brown_1                 GLKVector3Make(1.0f, 0.250980392f, 0.250980392f)
#define     color_brown_2                 GLKVector3Make(0.933333333f, 0.231372549f, 0.231372549f)
#define     color_brown_3                 GLKVector3Make(0.803921569f, 0.2f, 0.2f)
#define     color_brown_4                 GLKVector3Make(0.545098039f, 0.137254902f, 0.137254902f)
#define     color_firebrick               GLKVector3Make(0.698039216f, 0.133333333f, 0.133333333f)
#define     color_firebrick_1             GLKVector3Make(1.0f, 0.188235294f, 0.188235294f)
#define     color_firebrick_2             GLKVector3Make(0.933333333f, 0.17254902f, 0.17254902f)
#define     color_firebrick_3             GLKVector3Make(0.803921569f, 0.149019608f, 0.149019608f)
#define     color_firebrick_4             GLKVector3Make(0.545098039f, 0.101960784f, 0.101960784f)
#define     color_red                     GLKVector3Make(1.0f, 0.0f, 0.0f)
#define     color_red_2                   GLKVector3Make(0.933333333f, 0.0f, 0.0f)
#define     color_red_3                   GLKVector3Make(0.803921569f, 0.0f, 0.0f)
#define     color_red_4                   GLKVector3Make(0.545098039f, 0.0f, 0.0f)
#define     color_maroon                  GLKVector3Make(0.501960784f, 0.0f, 0.0f)
#define     color_sgi_beet                GLKVector3Make(0.556862745f, 0.219607843f, 0.556862745f)
#define     color_sgi_slateblue           GLKVector3Make(0.443137255f, 0.443137255f, 0.776470588f)
#define     color_sgi_lightblue           GLKVector3Make(0.490196078f, 0.619607843f, 0.752941176f)
#define     color_sgi_teal                GLKVector3Make(0.219607843f, 0.556862745f, 0.556862745f)
#define     color_sgi_chartreuse          GLKVector3Make(0.443137255f, 0.776470588f, 0.443137255f)
#define     color_sgi_olivedrab           GLKVector3Make(0.556862745f, 0.556862745f, 0.219607843f)
#define     color_sgi_brightgray          GLKVector3Make(0.77254902f, 0.756862745f, 0.666666667f)
#define     color_sgi_salmon              GLKVector3Make(0.776470588f, 0.443137255f, 0.443137255f)
#define     color_sgi_darkgray            GLKVector3Make(0.333333333f, 0.333333333f, 0.333333333f)
#define     color_sgi_gray_12             GLKVector3Make(0.117647059f, 0.117647059f, 0.117647059f)
#define     color_sgi_gray_16             GLKVector3Make(0.156862745f, 0.156862745f, 0.156862745f)
#define     color_sgi_gray_32             GLKVector3Make(0.317647059f, 0.317647059f, 0.317647059f)
#define     color_sgi_gray_36             GLKVector3Make(0.356862745f, 0.356862745f, 0.356862745f)
#define     color_sgi_gray_52             GLKVector3Make(0.517647059f, 0.517647059f, 0.517647059f)
#define     color_sgi_gray_56             GLKVector3Make(0.556862745f, 0.556862745f, 0.556862745f)
#define     color_sgi_lightgray           GLKVector3Make(0.666666667f, 0.666666667f, 0.666666667f)
#define     color_sgi_gray_72             GLKVector3Make(0.717647059f, 0.717647059f, 0.717647059f)
#define     color_sgi_gray_76             GLKVector3Make(0.756862745f, 0.756862745f, 0.756862745f)
#define     color_sgi_gray_92             GLKVector3Make(0.917647059f, 0.917647059f, 0.917647059f)
#define     color_sgi_gray_96             GLKVector3Make(0.956862745f, 0.956862745f, 0.956862745f)
#define     color_white                   GLKVector3Make(1.0f, 1.0f, 1.0f)
#define     color_white_smoke             GLKVector3Make(0.960784314f, 0.960784314f, 0.960784314f)
#define     color_gainsboro               GLKVector3Make(0.862745098f, 0.862745098f, 0.862745098f)
#define     color_lightgrey               GLKVector3Make(0.82745098f, 0.82745098f, 0.82745098f)
#define     color_silver                  GLKVector3Make(0.752941176f, 0.752941176f, 0.752941176f)
#define     color_darkgray                GLKVector3Make(0.662745098f, 0.662745098f, 0.662745098f)
#define     color_gray                    GLKVector3Make(0.501960784f, 0.501960784f, 0.501960784f)
#define     color_dimgray                 GLKVector3Make(0.411764706f, 0.411764706f, 0.411764706f)
#define     color_black                   GLKVector3Make(0.0f, 0.0f, 0.0f)
#define     color_gray_99                 GLKVector3Make(0.988235294f, 0.988235294f, 0.988235294f)
#define     color_gray_98                 GLKVector3Make(0.980392157f, 0.980392157f, 0.980392157f)
#define     color_gray_97                 GLKVector3Make(0.968627451f, 0.968627451f, 0.968627451f)
#define     color_gray_95                 GLKVector3Make(0.949019608f, 0.949019608f, 0.949019608f)
#define     color_gray_94                 GLKVector3Make(0.941176471f, 0.941176471f, 0.941176471f)
#define     color_gray_93                 GLKVector3Make(0.929411765f, 0.929411765f, 0.929411765f)
#define     color_gray_92                 GLKVector3Make(0.921568627f, 0.921568627f, 0.921568627f)
#define     color_gray_91                 GLKVector3Make(0.909803922f, 0.909803922f, 0.909803922f)
#define     color_gray_90                 GLKVector3Make(0.898039216f, 0.898039216f, 0.898039216f)
#define     color_gray_89                 GLKVector3Make(0.890196078f, 0.890196078f, 0.890196078f)
#define     color_gray_88                 GLKVector3Make(0.878431373f, 0.878431373f, 0.878431373f)
#define     color_gray_87                 GLKVector3Make(0.870588235f, 0.870588235f, 0.870588235f)
#define     color_gray_86                 GLKVector3Make(0.858823529f, 0.858823529f, 0.858823529f)
#define     color_gray_85                 GLKVector3Make(0.850980392f, 0.850980392f, 0.850980392f)
#define     color_gray_84                 GLKVector3Make(0.839215686f, 0.839215686f, 0.839215686f)
#define     color_gray_83                 GLKVector3Make(0.831372549f, 0.831372549f, 0.831372549f)
#define     color_gray_82                 GLKVector3Make(0.819607843f, 0.819607843f, 0.819607843f)
#define     color_gray_81                 GLKVector3Make(0.811764706f, 0.811764706f, 0.811764706f)
#define     color_gray_80                 GLKVector3Make(0.8f, 0.8f, 0.8f)
#define     color_gray_79                 GLKVector3Make(0.788235294f, 0.788235294f, 0.788235294f)
#define     color_gray_78                 GLKVector3Make(0.780392157f, 0.780392157f, 0.780392157f)
#define     color_gray_77                 GLKVector3Make(0.768627451f, 0.768627451f, 0.768627451f)
#define     color_gray_76                 GLKVector3Make(0.760784314f, 0.760784314f, 0.760784314f)
#define     color_gray_75                 GLKVector3Make(0.749019608f, 0.749019608f, 0.749019608f)
#define     color_gray_74                 GLKVector3Make(0.741176471f, 0.741176471f, 0.741176471f)
#define     color_gray_73                 GLKVector3Make(0.729411765f, 0.729411765f, 0.729411765f)
#define     color_gray_72                 GLKVector3Make(0.721568627f, 0.721568627f, 0.721568627f)
#define     color_gray_71                 GLKVector3Make(0.709803922f, 0.709803922f, 0.709803922f)
#define     color_gray_70                 GLKVector3Make(0.701960784f, 0.701960784f, 0.701960784f)
#define     color_gray_69                 GLKVector3Make(0.690196078f, 0.690196078f, 0.690196078f)
#define     color_gray_68                 GLKVector3Make(0.678431373f, 0.678431373f, 0.678431373f)
#define     color_gray_67                 GLKVector3Make(0.670588235f, 0.670588235f, 0.670588235f)
#define     color_gray_66                 GLKVector3Make(0.658823529f, 0.658823529f, 0.658823529f)
#define     color_gray_65                 GLKVector3Make(0.650980392f, 0.650980392f, 0.650980392f)
#define     color_gray_64                 GLKVector3Make(0.639215686f, 0.639215686f, 0.639215686f)
#define     color_gray_63                 GLKVector3Make(0.631372549f, 0.631372549f, 0.631372549f)
#define     color_gray_62                 GLKVector3Make(0.619607843f, 0.619607843f, 0.619607843f)
#define     color_gray_61                 GLKVector3Make(0.611764706f, 0.611764706f, 0.611764706f)
#define     color_gray_60                 GLKVector3Make(0.6f, 0.6f, 0.6f)
#define     color_gray_59                 GLKVector3Make(0.588235294f, 0.588235294f, 0.588235294f)
#define     color_gray_58                 GLKVector3Make(0.580392157f, 0.580392157f, 0.580392157f)
#define     color_gray_57                 GLKVector3Make(0.568627451f, 0.568627451f, 0.568627451f)
#define     color_gray_56                 GLKVector3Make(0.560784314f, 0.560784314f, 0.560784314f)
#define     color_gray_55                 GLKVector3Make(0.549019608f, 0.549019608f, 0.549019608f)
#define     color_gray_54                 GLKVector3Make(0.541176471f, 0.541176471f, 0.541176471f)
#define     color_gray_53                 GLKVector3Make(0.529411765f, 0.529411765f, 0.529411765f)
#define     color_gray_52                 GLKVector3Make(0.521568627f, 0.521568627f, 0.521568627f)
#define     color_gray_51                 GLKVector3Make(0.509803922f, 0.509803922f, 0.509803922f)
#define     color_gray_50                 GLKVector3Make(0.498039216f, 0.498039216f, 0.498039216f)
#define     color_gray_49                 GLKVector3Make(0.490196078f, 0.490196078f, 0.490196078f)
#define     color_gray_48                 GLKVector3Make(0.478431373f, 0.478431373f, 0.478431373f)
#define     color_gray_47                 GLKVector3Make(0.470588235f, 0.470588235f, 0.470588235f)
#define     color_gray_46                 GLKVector3Make(0.458823529f, 0.458823529f, 0.458823529f)
#define     color_gray_45                 GLKVector3Make(0.450980392f, 0.450980392f, 0.450980392f)
#define     color_gray_44                 GLKVector3Make(0.439215686f, 0.439215686f, 0.439215686f)
#define     color_gray_43                 GLKVector3Make(0.431372549f, 0.431372549f, 0.431372549f)
#define     color_gray_42                 GLKVector3Make(0.419607843f, 0.419607843f, 0.419607843f)
#define     color_gray_40                 GLKVector3Make(0.4f, 0.4f, 0.4f)
#define     color_gray_39                 GLKVector3Make(0.388235294f, 0.388235294f, 0.388235294f)
#define     color_gray_38                 GLKVector3Make(0.380392157f, 0.380392157f, 0.380392157f)
#define     color_gray_37                 GLKVector3Make(0.368627451f, 0.368627451f, 0.368627451f)
#define     color_gray_36                 GLKVector3Make(0.360784314f, 0.360784314f, 0.360784314f)
#define     color_gray_35                 GLKVector3Make(0.349019608f, 0.349019608f, 0.349019608f)
#define     color_gray_34                 GLKVector3Make(0.341176471f, 0.341176471f, 0.341176471f)
#define     color_gray_33                 GLKVector3Make(0.329411765f, 0.329411765f, 0.329411765f)
#define     color_gray_32                 GLKVector3Make(0.321568627f, 0.321568627f, 0.321568627f)
#define     color_gray_31                 GLKVector3Make(0.309803922f, 0.309803922f, 0.309803922f)
#define     color_gray_30                 GLKVector3Make(0.301960784f, 0.301960784f, 0.301960784f)
#define     color_gray_29                 GLKVector3Make(0.290196078f, 0.290196078f, 0.290196078f)
#define     color_gray_28                 GLKVector3Make(0.278431373f, 0.278431373f, 0.278431373f)
#define     color_gray_27                 GLKVector3Make(0.270588235f, 0.270588235f, 0.270588235f)
#define     color_gray_26                 GLKVector3Make(0.258823529f, 0.258823529f, 0.258823529f)
#define     color_gray_25                 GLKVector3Make(0.250980392f, 0.250980392f, 0.250980392f)
#define     color_gray_24                 GLKVector3Make(0.239215686f, 0.239215686f, 0.239215686f)
#define     color_gray_23                 GLKVector3Make(0.231372549f, 0.231372549f, 0.231372549f)
#define     color_gray_22                 GLKVector3Make(0.219607843f, 0.219607843f, 0.219607843f)
#define     color_gray_21                 GLKVector3Make(0.211764706f, 0.211764706f, 0.211764706f)
#define     color_gray_20                 GLKVector3Make(0.2f, 0.2f, 0.2f)
#define     color_gray_19                 GLKVector3Make(0.188235294f, 0.188235294f, 0.188235294f)
#define     color_gray_18                 GLKVector3Make(0.180392157f, 0.180392157f, 0.180392157f)
#define     color_gray_17                 GLKVector3Make(0.168627451f, 0.168627451f, 0.168627451f)
#define     color_gray_16                 GLKVector3Make(0.160784314f, 0.160784314f, 0.160784314f)
#define     color_gray_15                 GLKVector3Make(0.149019608f, 0.149019608f, 0.149019608f)
#define     color_gray_14                 GLKVector3Make(0.141176471f, 0.141176471f, 0.141176471f)
#define     color_gray_13                 GLKVector3Make(0.129411765f, 0.129411765f, 0.129411765f)
#define     color_gray_12                 GLKVector3Make(0.121568627f, 0.121568627f, 0.121568627f)
#define     color_gray_11                 GLKVector3Make(0.109803922f, 0.109803922f, 0.109803922f)
#define     color_gray_10                 GLKVector3Make(0.101960784f, 0.101960784f, 0.101960784f)
#define     color_gray_9                  GLKVector3Make(0.090196078f, 0.090196078f, 0.090196078f)
#define     color_gray_8                  GLKVector3Make(0.078431373f, 0.078431373f, 0.078431373f)
#define     color_gray_7                  GLKVector3Make(0.070588235f, 0.070588235f, 0.070588235f)
#define     color_gray_6                  GLKVector3Make(0.058823529f, 0.058823529f, 0.058823529f)
#define     color_gray_5                  GLKVector3Make(0.050980392f, 0.050980392f, 0.050980392f)
#define     color_gray_4                  GLKVector3Make(0.039215686f, 0.039215686f, 0.039215686f)
#define     color_gray_3                  GLKVector3Make(0.031372549f, 0.031372549f, 0.031372549f)
#define     color_gray_2                  GLKVector3Make(0.019607843f, 0.019607843f, 0.019607843f)
#define     color_gray_1                  GLKVector3Make(0.011764706f, 0.011764706f, 0.011764706f)
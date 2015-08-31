#import "GEshader.h"

@interface GEShader()

- (bool)loadShaderWithFileName:(NSString*)shadername BufferMode:(enum GE_BUFFER_MODE)buffermode;
- (bool)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file;
- (bool)linkProgram:(GLuint)prog;
- (bool)validateProgram:(GLuint)prog;

@end

@implementation GEShader

// ------------------------------------------------------------------------------ //
// ------------------------------- Initialization ------------------------------- //
// ------------------------------------------------------------------------------ //
#pragma mark Initialization

- (id)initWithFileName:(NSString*)filename BufferMode:(enum GE_BUFFER_MODE)buffermode
{
	self = [super init];
	
	if(self)
    {
        m_programID = 0;
        [self loadShaderWithFileName:filename BufferMode:buffermode];
    }
	
	return self;
}

- (void)dealloc
{
    if(m_programID)
        glDeleteProgram(m_programID);
}

// ------------------------------------------------------------------------------ //
// --------------------------- Load - Compile - Link ---------------------------- //
// ------------------------------------------------------------------------------ //
#pragma mark Load - Compile - Link

- (bool)loadShaderWithFileName:(NSString*)shadername BufferMode:(enum GE_BUFFER_MODE)buffermode
{
    GLuint vertShader, fragShader;
    NSString *vertShaderPathname, *fragShaderPathname;
    
    // Create shader program.
    m_programID = glCreateProgram();
    
    // Create and compile vertex shader.
    vertShaderPathname = [[NSBundle mainBundle] pathForResource:shadername ofType:@"vsh"];
    if (![self compileShader:&vertShader type:GL_VERTEX_SHADER file:vertShaderPathname])
    {
        NSLog(@"Failed to compile vertex shader");
        return NO;
    }
    
    // Create and compile fragment shader.
    fragShaderPathname = [[NSBundle mainBundle] pathForResource:shadername ofType:@"fsh"];
    if (![self compileShader:&fragShader type:GL_FRAGMENT_SHADER file:fragShaderPathname])
    {
        NSLog(@"Failed to compile fragment shader");
        return NO;
    }
    
    // Attach vertex shader to program.
    glAttachShader(m_programID, vertShader);
    
    // Attach fragment shader to program.
    glAttachShader(m_programID, fragShader);
    
    // Bind attribute locations.
    // This needs to be done prior to linking.
    if(buffermode == GE_BUFFER_MODE_ALL)
    {
        glBindAttribLocation(m_programID, GLKVertexAttribPosition, "positionCoord");
        glBindAttribLocation(m_programID, GLKVertexAttribNormal, "normalCoord");
        glBindAttribLocation(m_programID, GLKVertexAttribTexCoord0, "textureCoord");
    }
    else if(buffermode == GE_BUFFER_MODE_POSITION)
    {
        glBindAttribLocation(m_programID, GLKVertexAttribPosition, "positionCoord");
    }
    else if(buffermode == GE_BUFFER_MODE_POSITION_TEXTURE)
    {
        glBindAttribLocation(m_programID, GLKVertexAttribPosition, "positionCoord");
        glBindAttribLocation(m_programID, GLKVertexAttribTexCoord0, "textureCoord");
    }
    else if(buffermode == GE_BUFFER_MODE_POSITION_NORMAL)
    {
        glBindAttribLocation(m_programID, GLKVertexAttribPosition, "positionCoord");
        glBindAttribLocation(m_programID, GLKVertexAttribNormal, "normalCoord");
    }
    
    // Link program.
    if (![self linkProgram:m_programID])
    {
        NSLog(@"Failed to link program: %d", m_programID);
        
        if (vertShader)
        {
            glDeleteShader(vertShader);
            vertShader = 0;
        }
        if (fragShader)
        {
            glDeleteShader(fragShader);
            fragShader = 0;
        }
        if (m_programID)
        {
            glDeleteProgram(m_programID);
            m_programID = 0;
        }
        
        return false;
    }
    
    // Release vertex and fragment shaders.
    if (vertShader)
    {
        glDetachShader(m_programID, vertShader);
        glDeleteShader(vertShader);
    }
    if (fragShader)
    {
        glDetachShader(m_programID, fragShader);
        glDeleteShader(fragShader);
    }
    
    return true;
}

- (bool)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file
{
    GLint status;
    const GLchar *source;
    
    source = (GLchar *)[[NSString stringWithContentsOfFile:file encoding:NSUTF8StringEncoding error:nil] UTF8String];
    if (!source)
    {
        NSLog(@"Failed to load vertex shader");
        return false;
    }
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
#if defined(DEBUG)
    GLint logLength;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);
        NSLog(@"Shader compile log:\n%s", log);
        free(log);
    }
#endif
    
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0)
    {
        glDeleteShader(*shader);
        return false;
    }
    
    return true;
}

- (bool)linkProgram:(GLuint)prog
{
    GLint status;
    glLinkProgram(prog);
    
#if defined(DEBUG)
    GLint logLength;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        NSLog(@"Program link log:\n%s", log);
        free(log);
    }
#endif
    
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status == 0)
        return false;
    
    return true;
}

- (bool)validateProgram:(GLuint)prog
{
    GLint logLength, status;
    
    glValidateProgram(prog);
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        NSLog(@"Program validate log:\n%s", log);
        free(log);
    }
    
    glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
    if (status == 0)
        return false;
    
    return true;
}

@end

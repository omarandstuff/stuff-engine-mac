#import "GEtexture.h"

@interface GEMaterial : NSObject

// -------------------------------------------- //
// ---------------- Properties ---------------- //
// -------------------------------------------- //
#pragma mark Properties
@property GLKVector2 TextureCompression;
@property GETexture* DiffuseMap;
@property GETexture* SpecularMap;
@property GLKVector3 AmbientColor;
@property GLKVector3 DiffuseColor;
@property GLKVector3 SpecularColor;
@property float Shininess;
@property float Opasity;

@end
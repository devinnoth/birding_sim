#ifndef CSCIx229
#define CSCIx229

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))
#define length2d(Ax, Ay, Bx, By) sqrt( pow( Bx - Ax, 2.0 ) + pow( By - Ay, 2.0 ) )
#define length3d(x, y, z) sqrt( pow( x, 2.0 ) + pow( y, 2.0 ) + pow( z, 2.0 ) )
#define DotProduct(a,b) (a.x * b.x) + (a.y * b.y) + (a.z * b.z)

#ifdef __cplusplus
extern "C" {
#endif

struct Vec3 {
    double x, y, z;
};

struct Sphere {
    struct Vec3 pos;
    double r;
};

struct Bird {
    // spawn bool in case requirements not met (feeders not filled);
    int spawn, model, species;
    double x, y, z, rot, scale;
};

struct Birdfeeder {
    double x, y, z, Tx, Tz, rot, scale;
    int empty;
};

// base CSCIx229.h functions
void Print(const char* format , ...);
void Fatal(const char* format , ...);
unsigned int LoadTexBMP(const char* file);
void Project(double fov,double asp,double dim);
void ErrCheck(const char* where);
int  LoadOBJ(const char* file);


// shape.c functions
void Vertex( double th,double ph, int sphere, int top );
void sphere( double x, double y, double z, double r, double ox, double oy, double oz, double rot, unsigned int texture, int textureMode, int emission, float shiny );
void cone( double x, double y, double z, double h, double br, double rotation, double dx, double dy, double dz, unsigned int texture, int textureMode, int emission, float shiny );
void cube( double x,double y,double z, double dx,double dy,double dz, double th, unsigned int texture, int textureMode, float shiny );
void cylinder( double x, double y, double z, double h, double br, double rotation, double dx, double dy, double dz, unsigned int texture, int textureMode, int emission, float shiny );
void circle( double x, double y, double z, double r );

// birds.c functions
void sparrow( struct Bird bird );
void crested( struct Bird bird );
void owl( struct Bird bird );

// models.c functions
void camera( double x, double y, double z, double scale );
void journal( double x, double y, double z, double scale, int index );
void Sky( double D, int index );
void ground( double dim );
void rocks( double x, double y, double z, double rot, double scale );
void lake( double x, double y, double z, double scale );
void grass( double x, double y, double z, double rot, double scale );
void pine1( double x, double y, double z, double scale );
void pine2( double x, double y, double z, double scale );
void trees1( double x, double y, double z, double rot, double scale );
void trees2( double x, double y, double z, double rot, double scale );
void car( double x, double y, double z, double rot, double scale );
void path( double x, double y, double z, double rot, double scale );
void birdfeeder( struct Birdfeeder feeder );

// texture arrays
unsigned int sparrow_textures[ 6 ][ 7 ];
unsigned int crested_textures[ 4 ][ 8 ];
unsigned int owl_textures[ 3 ][ 6 ];
// separate for leg since its global for all birds
unsigned int leg;
unsigned int camera_textures[ 8 ];
unsigned int setting_textures[ 9 ];
unsigned int skybox[ 2 ];
unsigned int car_textures[ 7 ];
unsigned int journals[ 8 ];

// etc vars
int graphicsIndex; // graphics controller (higher: better shape rendering)
int gArr[5]; // array of potential graphics dividers
double t; // time
struct Bird birdSpawns[15]; // circualr array for bird spawns

#ifdef __cplusplus
}
#endif

#endif

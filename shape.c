#include "CSCIx229.h"

/*
 * Vertex()
 * THIS FUNCTION WAS TAKEN FROM ex8.c file from 09/17/2020 lecture.
 * https://canvas.colorado.edu/courses/65300/modules/items/2127646
 * Vertex uses the same coordinates for Normal vectors, so storing them then sending to both functions works.
 * Draw vertex in polar coordinates
 * This function is used by the sphere and triangle functions to draw their respective shapes
 */
void Vertex(double th,double ph, int sphere, int top)
{
   double x = Sin(th)*Cos(ph);
   double y = Sin(ph);
   double z = Cos(th)*Cos(ph);
   if ( sphere ) {
      glNormal3d(x, y, z);
   } else {
      top ?
         glNormal3d( x, 1, z ) :
         glNormal3d( 0, -1, 0 );
   }
   glVertex3d(x, y, z);
}

void circle( double x, double y, double z, double r ) {

   int th;
   const int d = 45 / gArr[ graphicsIndex ];

   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glScaled( r, r, r );

   double tempX;
   double tempZ;
   glShadeModel( GL_SMOOTH );
   glBegin( GL_QUAD_STRIP );
   for ( th=0; th <= 360; th+=d ) {
      tempX = Sin(th);
      tempZ = Cos(th);
      glNormal3d( 0, 1, 0 );
      glTexCoord2f( th / 360.0, 0 );
      glVertex3f( tempX, 0, tempZ );
      glTexCoord2f( th / 360.0, 1 );
      glVertex3f( 0, 0, 0 );
   }
   glEnd();

   glPopMatrix();
}

/*
 * sphere()
 * THIS FUNCTION WAS TAKEN FROM ex8.c file from 09/17/2020 lecture.
 * https://canvas.colorado.edu/courses/65300/modules/items/2127646
 * I've only changed the y scale of the sphere created, to make it more oval shaped
 * at (x,y,z)
 * radius (r)
 */
void sphere( double x, double y, double z, double r, double ox, double oy, double oz,
               double rot, unsigned int texture, int textureMode, int emission, float shiny ) {
   const int d=45 / gArr[ graphicsIndex ];
   int th,ph;
   // emmission and yellow arrays from ex13
   float yellow[] = { 1.0, 1.0, 0.0, 1.0 };
   float Emission[]  = { 0.0, 0.0, 0.01 * emission, 1.0 };
   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslatef(x,y,z);
   // dividing y axis to make a more oval shape
   glRotatef( rot, 0, 1, 0 );
   glScalef( r * ox, r * oy, r * oz );

   glMaterialf( GL_FRONT, GL_SHININESS, shiny );
   glMaterialfv( GL_FRONT, GL_SPECULAR, yellow );
   glMaterialfv( GL_FRONT, GL_EMISSION, Emission );

   glEnable(GL_TEXTURE_2D);
   glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, textureMode ? GL_REPLACE : GL_MODULATE );
   glColor3f(1,1,1);
   glBindTexture( GL_TEXTURE_2D, texture );

   // Latitude bands
   glShadeModel( GL_SMOOTH );
   for ( ph=-90; ph < 90; ph+=d ) {
      glBegin( GL_QUAD_STRIP );
      glTexCoord2f( 0, 0 );
      for ( th=0; th <= 360; th += d )
      {
         // dividing th and ph to make coord range < 1 and > 0 to properly wrap texture.
         glTexCoord2f( th / 360.0, ( ph + 90 ) / 180.0 );
         Vertex(th,ph, 1, 0);
         glTexCoord2f( th/360.0, (ph + d + 90 ) / 180.0 );
         Vertex(th,ph+d, 1, 0);
      }
      glTexCoord2f( 0, 1 );
      glEnd();
   }

   // Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

/**
 * cone()
 * Creates a cone at (x, y, z), with height h and base radius br
 * I designed this function based off the previous sphere function, replacing
 * the way it created the vertexes by simply creating lines that all end at the specific height, essentially making
 * a 360 of lines that form a cone.
 * The cone is hollow intentionally for the thruster objects on the satellite.
 */
void cone( double x, double y, double z, double h, double br,
            double rotation, double dx, double dy, double dz,
               unsigned int texture, int textureMode, int emission, float shiny ) {
    const int d=45 / gArr[ graphicsIndex ];
    int th;

    float yellow[] = { 1.0, 1.0, 0.0, 1.0 };
    float Emission[]  = { 0.0, 0.0, 0.01 * emission, 1.0 };
    //  Save transformation
    glPushMatrix();
    //  Offset and scale
    glTranslatef( x, y, z );
    glRotatef( rotation, dx, dy, dz );
    glScalef( br, h, br );

    glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, shiny );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, yellow );
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, Emission );

    glEnable(GL_TEXTURE_2D);
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, textureMode ? GL_REPLACE : GL_MODULATE );
    glColor3f(1,1,1);
    glBindTexture( GL_TEXTURE_2D, texture );

    glShadeModel( GL_SMOOTH );
    glBegin( GL_QUAD_STRIP );
    for ( th=0; th <= 360; th+=d) {
        // Have each line connect to tip of cone.
        glTexCoord2f( th / 360.0, 0.5 );
        Vertex( th , 0, 0, 1 );
        glTexCoord2f( th / 360.0, 1 );
        glVertex3d( 0, h, 0 );
    }
    for ( th=0; th <= 360; th+=d) {
        // create flat circle on bottom
        glTexCoord2f( th / 360.0, 0.5 );
        Vertex( th , 0, 0, 0 );
        glTexCoord2f( th / 360.0, 0 );
        glVertex3f( 0, 0, 0 );
    }
    glEnd();

   // Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

/**
 * cylinder()
 * Creates a cylinder at (x, y, z), with height h and base radius br
 * I designed this function based off the previous sphere function, replacing
 * the way it created the vertexes by simply creating lines that all end at the specific height, essentially making
 * a 360 of lines that form a cone.
 * The cone is hollow intentionally for the thruster objects on the satellite.
 */
void cylinder( double x, double y, double z, double h, double br,
                  double rotation, double dx, double dy, double dz, 
                    unsigned int texture, int textureMode, int emission, float shiny ) {
   const int d=45 / gArr[ graphicsIndex ];
   int th;

   float yellow[] = { 1.0, 1.0, 0.0, 1.0 };
   float Emission[]  = { 0.0, 0.0, 0.01 * emission, 1.0 };
   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslatef( x, y, z );
   glRotatef( rotation, dx, dy, dz );
   glScalef( br, h, br );

   glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, shiny );
   glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, yellow );
   glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, Emission );

   glEnable( GL_TEXTURE_2D );
   glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, textureMode ? GL_REPLACE : GL_MODULATE );
   glColor3f(1,1,1);
   glBindTexture( GL_TEXTURE_2D, texture );

   //  Latitude bands
   double tempX;
   double tempZ;
   glShadeModel( GL_SMOOTH );
   glBegin( GL_QUAD_STRIP );
   for ( th=0; th <= 360; th+=d ) {
      // top circle
      tempX = Sin(th);
      tempZ = Cos(th);
      glNormal3d( 0, 1, 0 );
      glTexCoord2f( th / 360.0, 0.75 );
      glVertex3f( tempX, h / 2.0, tempZ );
      glTexCoord2f( th / 360.0, 1 );
      glVertex3f( 0, h / 2.0, 0 );
   }
   for ( th=0; th <= 360; th+=d ) {
      // middle pipe
      tempX = Sin(th);
      tempZ = Cos(th);
      glNormal3d( tempX, 0, z );
      glTexCoord2f( th / 360.0, 0.75 );
      glVertex3f( tempX, h / 2.0, tempZ );
      glTexCoord2f( th / 360.0, 0.25 );
      glVertex3f( tempX, -h / 2.0, tempZ );
   }
   for ( th=0; th <= 360; th+=d ) {
      // bottom circle
      tempX = Sin(th);
      tempZ = Cos(th);
      glNormal3d( 0, -1, 0 );
      glTexCoord2f( th / 360.0, 0.25 );
      glVertex3f( tempX, -h / 2.0, tempZ );
      glTexCoord2f( th / 360.0, 0 );
      glVertex3f( 0, -h / 2.0, 0 );
   }
   glEnd();

   // Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

/*
 * cube()
 * THIS FUNCTION WAS TAKEN FROM ex8.c file from 09/17/2020 lecture.
 * https://canvas.colorado.edu/courses/65300/modules/items/2127646
 * I removed the glColor3f calls so I could manually set the whole shape color before calling the function
 * Normal functions added for lighting purposes
 * Draw a cube at (x,y,z)
 * dimensions (dx,dy,dz)
 * rotated th about the y axis
 */
void cube( double x,double y,double z,
                 double dx,double dy,double dz,
                 double th, unsigned int texture, int textureMode, float shiny ) {
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, shiny );
   glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, white );
   glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, black );
   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslatef(x,y,z);
   glRotatef(th,0,1,0);
   glScalef(dx,dy,dz);

   // enable textures and use either the gold tin or satellite based on what's passed in
   glEnable(GL_TEXTURE_2D);
   glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, textureMode ? GL_REPLACE : GL_MODULATE );
   glColor3f(1,1,1);
   glBindTexture( GL_TEXTURE_2D, texture );
   //  Cube
   glShadeModel( GL_SMOOTH );
   glBegin(GL_QUADS);
   //  Front
   glNormal3f( 0, 0, 1);
   glTexCoord2f( 0, 0 ); glVertex3f(-1,-1, 1);
   glTexCoord2f( 1, 0 ); glVertex3f(+1,-1, 1);
   glTexCoord2f( 1, 1 ); glVertex3f(+1,+1, 1);
   glTexCoord2f( 0, 1 ); glVertex3f(-1,+1, 1);
   //  Back
   glNormal3f( 0, 0,-1);
   glTexCoord2f( 0, 0 ); glVertex3f(+1,-1,-1);
   glTexCoord2f( 1, 0 ); glVertex3f(-1,-1,-1);
   glTexCoord2f( 1, 1 ); glVertex3f(-1,+1,-1);
   glTexCoord2f( 0, 1 ); glVertex3f(+1,+1,-1);
   //  Right
   glNormal3f(+1, 0, 0);
   glTexCoord2f( 0, 0 ); glVertex3f(+1,-1,+1);
   glTexCoord2f( 1, 0 ); glVertex3f(+1,-1,-1);
   glTexCoord2f( 1, 1 ); glVertex3f(+1,+1,-1);
   glTexCoord2f( 0, 1 ); glVertex3f(+1,+1,+1);
   //  Left
   glNormal3f(-1, 0, 0);
   glTexCoord2f( 0, 0 ); glVertex3f(-1,-1,-1);
   glTexCoord2f( 1, 0 ); glVertex3f(-1,-1,+1);
   glTexCoord2f( 1, 1 ); glVertex3f(-1,+1,+1);
   glTexCoord2f( 0, 1 ); glVertex3f(-1,+1,-1);
   //  Top
   glNormal3f( 0,+1, 0);
   glTexCoord2f( 0, 0 ); glVertex3f(-1,+1,+1);
   glTexCoord2f( 1, 0 ); glVertex3f(+1,+1,+1);
   glTexCoord2f( 1, 1 ); glVertex3f(+1,+1,-1);
   glTexCoord2f( 0, 1 ); glVertex3f(-1,+1,-1);
   //  Bottom
   glNormal3f( 0, -1, 0);
   glTexCoord2f( 0, 0 ); glVertex3f(-1,-1,-1);
   glTexCoord2f( 1, 0 ); glVertex3f(+1,-1,-1);
   glTexCoord2f( 1, 1 ); glVertex3f(+1,-1,+1);
   glTexCoord2f( 0, 1 ); glVertex3f(-1,-1,+1);
   //  End
   glEnd();
   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}
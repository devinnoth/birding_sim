#include "CSCIx229.h"

// loads camera model
void camera( double x, double y, double z, double scale ) {

    glPushMatrix();
    glTranslated( x, y, z );
    glScaled( scale, scale, scale );
    glColor3d( 1.0, 1.0, 1.0 );

    // main body
    cube( 0, 0, 0, 1.75, 1.25, 0.5, 0, camera_textures[ 0 ], 0, 1 );
    cube( -1.5, 0, 0, 0.25, 1.15, 0.55, 0, camera_textures[ 2 ], 0, 1 );
    cylinder( -1.25, 0, 0.6, 1.55, 0.45, 0, 0, 0, 0, camera_textures[ 2 ], 0, 1, 1 );
    sphere( -1.25, 1.15, 0.6, 0.25, 1, 0.5, 1, 0, camera_textures[ 1 ], 0, 1, 1 );
    sphere( -0.9, 0.45, -0.5, 0.1, 1, 0.8, 0.25, 0, camera_textures[ 4 ], 0, 1, 1 );
    sphere( -0.9, 0, -0.5, 0.1, 1, 0.8, 0.25, 0, camera_textures[ 5 ], 0, 1, 1 );
    sphere( -0.9, -0.45, -0.5, 0.1, 1, 0.8, 0.25, 0, camera_textures[ 6 ], 0, 1, 1 );
    cylinder( 1.3, 1.3, 0, 0.3, 0.4, 0, 0, 0, 0, camera_textures[ 7 ], 0, 1, 1 );
    // screen
    cube( 0.35, -0.25, -0.45, 1, 0.8, 0.1, 0, camera_textures[ 1 ], 0, 1 );
    // viewfinder
    cube( 0.25, 1.25, 0.2, 0.6, 0.6, 0.75, 0, camera_textures[ 1 ], 0, 1 );
    cylinder( 0.25, 1.25, -0.6, 0.2, 0.45, 90, 1, 0, 0, camera_textures[ 1 ], 0, 1, 1 );
    // lens
    cylinder( 0, 0, 2, 2, 1, 90, 1, 0, 0, camera_textures[ 1 ], 0, 1, 1 );
    cylinder( 0, 0, 2, 1.6, 1.1, 90, 1, 0, 0, camera_textures[ 3 ], 0, 1, 1 );

    glPopMatrix();
};

// loads journal model
void journal( double x, double y, double z, double scale, int index ) {
    glPushMatrix();
    glTranslated( x, y, z );
    glScaled( scale, scale, scale );
    glColor3d( 1.0, 1.0, 1.0 );

    glEnable(GL_TEXTURE_2D);
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    // texture based off level and if user took correct photo
    glBindTexture( GL_TEXTURE_2D, journals[ index ] );

    glBegin(GL_QUADS);
    glNormal3f( 0, 0, -1);
    glTexCoord2f( 0, 0 ); glVertex3f(+1,-1.5, 0);
    glTexCoord2f( 1, 0 ); glVertex3f(-1,-1.5, 0);
    glTexCoord2f( 1, 1 ); glVertex3f(-1,+1.5, 0);
    glTexCoord2f( 0, 1 ); glVertex3f(+1,+1.5, 0);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

/**
 * skybox function
 * Taken and slightly manipulated from ex25.c file
 * Manipulated to use single texture
 */
void Sky( double D, int index )
{
    glColor3f( 1, 1, 1 );
    glEnable( GL_TEXTURE_2D );

    //  Sides
    glBindTexture( GL_TEXTURE_2D, skybox[ index ] );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,1.0/3.0 - 0.001); glVertex3f(-D,-D,-D);
    glTexCoord2f(0.25,1.0/3.0 - 0.001); glVertex3f(+D,-D,-D);
    glTexCoord2f(0.25,2.0/3.0 - 0.001); glVertex3f(+D,+D,-D);
    glTexCoord2f(0.0,2.0/3.0 - 0.001); glVertex3f(-D,+D,-D);

    glTexCoord2f(0.25,1.0/3.0); glVertex3f(+D,-D,-D);
    glTexCoord2f(0.5,1.0/3.0); glVertex3f(+D,-D,+D);
    glTexCoord2f(0.5,2.0/3.0); glVertex3f(+D,+D,+D);
    glTexCoord2f(0.25,2.0/3.0); glVertex3f(+D,+D,-D);

    glTexCoord2f(0.5,1.0/3.0 - 0.001); glVertex3f(+D,-D,+D);
    glTexCoord2f(0.75,1.0/3.0 - 0.001); glVertex3f(-D,-D,+D);
    glTexCoord2f(0.75,2.0/3.0 - 0.001); glVertex3f(-D,+D,+D);
    glTexCoord2f(0.5,2.0/3.0 - 0.001); glVertex3f(+D,+D,+D);

    glTexCoord2f(0.75,1.0/3.0 - 0.001); glVertex3f(-D,-D,+D);
    glTexCoord2f(1.0,1.0/3.0 - 0.001); glVertex3f(-D,-D,-D);
    glTexCoord2f(1.0,2.0/3.0 - 0.001); glVertex3f(-D,+D,-D);
    glTexCoord2f(0.75,2.0/3.0 - 0.001); glVertex3f(-D,+D,+D);

    //  Top and bottom
    glTexCoord2f(0.251,2.0/3.0); glVertex3f(+D,+D,-D);
    glTexCoord2f(0.499,2.0/3.0); glVertex3f(+D,+D,+D);
    glTexCoord2f(0.499,0.999); glVertex3f(-D,+D,+D);
    glTexCoord2f(0.251,0.999); glVertex3f(-D,+D,-D);

    glTexCoord2f(0.5,1.0/3.0); glVertex3f(-D,-D,+D);
    glTexCoord2f(0.25,1.0/3.0); glVertex3f(+D,-D,+D);
    glTexCoord2f(0.25,0); glVertex3f(+D,-D,-D);
    glTexCoord2f(0.5,0); glVertex3f(-D,-D,-D);
    glEnd();

   glDisable( GL_TEXTURE_2D );
}

/**
 * Use to create ground plane
 */
void ground( double D ) {
    glColor3f( 1, 1, 1 );
    glEnable( GL_TEXTURE_2D );
    // glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    // glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glBindTexture( GL_TEXTURE_2D, setting_textures[ 0 ] );

    glBegin( GL_QUADS );
    glNormal3f( 0,+1, 0);
    // texcoord of 20 to have repeated textures
    glTexCoord2f( 20.0, 20.0 ); glVertex3f(-D,0,+D);
    glTexCoord2f( 0.0, 20.0 ); glVertex3f(+D,0,+D);
    glTexCoord2f( 0.0, 0.0 ); glVertex3f(+D,0,-D);
    glTexCoord2f( 20.0, 0.0 ); glVertex3f(-D,0,-D);
    glEnd();

    glDisable( GL_TEXTURE_2D );
}

// loads row of 4 rocks
void rocks( double x, double y, double z, double rot, double scale ) {
    glPushMatrix();
    glTranslatef( x, y, z );
    glRotatef( rot, 0, 1, 0 );
    glScalef( scale, scale, scale );

    sphere( -11, 0, 0, 5, 1, 0.2, 0.2, 0, setting_textures[ 8 ], 0, 1, 1 );
    sphere( -6, 0, 0.5, 5, 0.9, 0.3, 0.3, 0, setting_textures[ 8 ], 0, 1, 1 );
    sphere( 0, 0, -0.5, 5, 1.1, 0.2, 0.35, 0, setting_textures[ 8 ], 0, 1, 1 );
    sphere( 4, 0, 0.5, 5, 0.8, 0.35, 0.3, 0, setting_textures[ 8 ], 0, 1, 1 );

    glPopMatrix();

}

/**
 * Helper function to create pine needles on pine trees
 * Takes length and width as parameters
 */
void needles( double l, double w ) {
    glColor3f( 0, 0.50, 0 );
    glBegin( GL_QUAD_STRIP );
    for ( double i = 0; i < l; i += 0.025 ){
        glVertex3f( 0, -0.4, i );
        glVertex3f( w, -0.3, i );
        glVertex3f( 0, -0.4, i );
        glVertex3f( -w, -0.3, i );
    }
    glEnd();
    glColor3f( 1, 1, 1 );
}

/**
 * Helper function to create a basic branch.
 * Scaling and rotating versions of these will be essential in creating our threes
 */
void branch() {
    // branch twig
    cylinder( 0, 0, 0, 1.3, 0.1, 120, 1, 0, 0, setting_textures[ 1 ], 0, 1, 1 );
    // needles
    glPushMatrix();
    glTranslatef(0, 0.4, 0);
    glRotatef( 30, 1, 0, 0 );
    needles( 1.1, 0.25 );
    glPopMatrix();

    cone( 0, -.4, 0.7, 1.25, 0.1, 90, 1, 0, 0, setting_textures[ 1 ], 0, 1, 1 );
    glPushMatrix();
    glTranslatef(0, 0, 1.1);
    needles( 0.9, 0.2 );
    glPopMatrix();

    glPushMatrix();
    glTranslatef( 0, 0, 1 );
    glRotatef( 35, 0, 1, 0 );
    needles( 0.7, 0.15 );
    cone( 0, -.4, 0, 0.9, 0.05, 90, 1, 0, 0, setting_textures[ 1 ], 0, 1, 1 );
    glPopMatrix();

    glPushMatrix();
    glTranslated( 0, 0, 1.3 );
    glRotatef( -35, 0, 1, 0 );
    needles( 0.6, 0.13 );
    cone( 0, -.4, 0, 0.8, 0.035, 90, 1, 0, 0, setting_textures[ 1 ], 0, 1, 1 );
    glPopMatrix();
}

/**
 * Spawns base branch in a rising height and lowering scale
 */
void pine1( double x, double y, double z, double scale ) {
    glPushMatrix();
    glTranslatef( x, y, z );
    glScalef( scale, scale, scale );
    // main body
    cone( 0, 0, 0, 1, 1.3, 0, 0, 0, 0, setting_textures[ 1 ], 0, 1, 1 );
    cylinder( 0, 8, 0, 4, 0.6, 0, 0, 0, 0, setting_textures[ 1 ], 0, 1, 1 );
    cone( 0, 16, 0, 5, 0.6, 0, 0, 0, 0, setting_textures[ 1 ], 0, 1, 1 );

    glEnable(GL_TEXTURE_2D);
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glColor3f(1,1,1);
    glBindTexture( GL_TEXTURE_2D, setting_textures[ 7 ] );
    circle( 0, 0.05, 0, 3.5 );
    glDisable(GL_TEXTURE_2D);

    // branches
    int offset = 15;
    double scaled = 1;
    int th;
    for ( int h = 8; h <= 28; h += 4 ) {
        offset += 30;
        scaled = 36 / h;
        glPushMatrix();
        glTranslatef( 0, h, 0 );
        glScalef( scaled, scaled, scaled );
        for( th = offset; th < 360 + offset; th += 72 ) {
            glPushMatrix();
            glRotatef( th, 0, 1, 0 );
            glTranslated( 0, 0, 0.7 );
            branch();
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
}

/**
 * Spawns base branch that increases then decreases in scale
 */
void pine2( double x, double y, double z, double scale ) {
    glPushMatrix();
    glTranslatef( x, y, z );
    glScalef( scale, scale, scale );
    // main body
    cone( 0, 0, 0, 1, 1.3, 0, 0, 0, 0, setting_textures[ 1 ], 0, 1, 1 );
    cylinder( 0, 8, 0, 4, 0.6, 0, 0, 0, 0, setting_textures[ 1 ], 0, 1, 1 );
    cone( 0, 16, 0, 5.5, 0.6, 0, 0, 0, 0, setting_textures[ 1 ], 0, 1, 1 );

    glEnable(GL_TEXTURE_2D);
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glColor3f(1,1,1);
    glBindTexture( GL_TEXTURE_2D, setting_textures[ 7 ] );
    circle( 0, 0.05, 0, 3.5 );
    glDisable(GL_TEXTURE_2D);

    // branches
    int offset = 15;
    double scaled = 1;
    int th;
    // first for loop goes branch scale ascending
    for ( int h = 12; h <= 24; h += 4 ) {
        offset += 22;
        scaled = 36 / ( 36 - h );
        glPushMatrix();
        glTranslatef( 0, h, 0 );
        glScalef( scaled, scaled, scaled );
        for( th = offset; th < 360 + offset; th += 72 ) {
            glPushMatrix();
            glRotatef( th, 0, 1, 0 );
            glTranslatef( 0, 0, 0.7 );
            branch();
            glPopMatrix();
        }
        glPopMatrix();
    }
    // second creates descending
    for ( int h = 26; h <= 40; h += 4 ) {
        offset += 30;
        scaled = 78 / h;
        glPushMatrix();
        glTranslatef( 0, h, 0 );
        glScalef( scaled, scaled, scaled );
        for( th = offset; th < 360 + offset; th += 72 ) {
            glPushMatrix();
            glRotatef( th, 0, 1, 0 );
            glTranslatef( 0, 0, 0.7 );
            branch();
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();

}

/**
 * 1st tree cluster with more of pine1 than 2
 */
void trees1( double x, double y, double z, double rot, double scale ) {

    glPushMatrix();
    glTranslatef( x, y, z );
    glRotatef( rot, 0, 1, 0 );
    glScalef( scale, scale, scale );

    pine1( 0, 0, 0, 1 );
    pine2( -6, 0, 3, 0.8 );
    pine1( 7.5, 0, -3, 0.4 );
    pine1( -12.5, 0, -2.5, 0.5 );
    pine1( -17.5, 0, -0, 0.6 );
    glPushMatrix();
    glTranslatef( -25, 0, 3 );
    glRotatef( 180, 0, 1, 0 );
    glScalef( 0.9, 0.9, 0.9 );
    pine1( 0, 0, 0, 1 );
    pine2( -6, 0, 3, 0.8 );
    pine1( 7.5, 0, -3, 0.4 );
    pine1( -12.5, 0, -2.5, 0.5 );
    pine1( -17.5, 0, -0, 0.6 );
    glPopMatrix();
    glPopMatrix();
}

/**
 * 2nd tree cluster with more of pine2 than 1
 */
void trees2( double x, double y, double z, double rot, double scale ) {
    glPushMatrix();
    glTranslatef( x, y, z );
    glRotatef( rot, 0, 1, 0 );
    glScalef( scale, scale, scale );

    pine2( 0, 0, 0, 1 );
    pine2( -10, 0, 1, 1.2 );
    pine2( -18, 0, -2, 0.9 );
    pine1( -16, 0, 5, 0.7 );
    pine2( -25, 0, 3, 1.4 );
    pine2( -35, 0, 2, 1.1 );
    pine2( -43, 0, -2, 1 );
    pine1( -32, 0, 5, 0.6 );

    glPopMatrix();
}

/**
 * Simple oval for lake with no texture since we will stencil
 * with the area it covers
 */
void lake( double x, double y, double z, double scale ) {
    glPushMatrix();
    glTranslatef( x, y, z );
    glScalef( scale, scale, scale );
    glPushMatrix();
    glScalef( 2, 1, 1 );
    circle( 0, 0, 0, 20 );
    glPopMatrix();
    glPopMatrix();
}

/**
 * Slightly deformed cube with top vertexes slightly curved
 * to emulate volkswagen van
 */
void car( double x, double y, double z, double rot, double scale ) {
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, 1 );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, white );
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, black );
    //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslatef(x,y,z);
    glRotatef( rot, 0, 1, 0) ;
    glScalef( scale, scale, scale );

    // enable textures and use either the gold tin or satellite based on what's passed in
    glEnable(GL_TEXTURE_2D);
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glColor3f(1,1,1);
    glBindTexture( GL_TEXTURE_2D, car_textures[ 0 ] );
    glBegin(GL_QUADS);
    //  Front
    glNormal3f( 0, 0, 1);
    glTexCoord2f( 0, 0 ); glVertex3f(-1,-1, 2);
    glTexCoord2f( 1, 0 ); glVertex3f(+1,-1, 2);
    glTexCoord2f( 1, 1 ); glVertex3f(+1,+1, 1.8);
    glTexCoord2f( 0, 1 ); glVertex3f(-1,+1, 1.8);
    glEnd();
    //  Back
    glBindTexture( GL_TEXTURE_2D, car_textures[ 1 ] );
    glBegin(GL_QUADS);
    glNormal3f( 0, 0,-1);
    glTexCoord2f( 0, 0 ); glVertex3f(+1,-1,-2);
    glTexCoord2f( 1, 0 ); glVertex3f(-1,-1,-2);
    glTexCoord2f( 1, 1 ); glVertex3f(-1,+1,-1.8);
    glTexCoord2f( 0, 1 ); glVertex3f(+1,+1,-1.8);
    glEnd();
    //  Right
    glBindTexture( GL_TEXTURE_2D, car_textures[ 2 ] );
    glBegin(GL_QUADS);
    glNormal3f(+1, 0, 0);
    glTexCoord2f( 0, 0 ); glVertex3f(+1,-1,+2);
    glTexCoord2f( 1, 0 ); glVertex3f(+1,-1,-2);
    glTexCoord2f( 1, 1 ); glVertex3f(+1,+1,-1.8);
    glTexCoord2f( 0, 1 ); glVertex3f(+1,+1,+1.8);
    glEnd();
    //  Left
    glBindTexture( GL_TEXTURE_2D, car_textures[ 3 ] );
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glTexCoord2f( 0, 0 ); glVertex3f(-1,-1,-2);
    glTexCoord2f( 1, 0 ); glVertex3f(-1,-1,+2);
    glTexCoord2f( 1, 1 ); glVertex3f(-1,+1,+1.8);
    glTexCoord2f( 0, 1 ); glVertex3f(-1,+1,-1.8);
    glEnd();
    //  Top
    glBindTexture( GL_TEXTURE_2D, car_textures[ 4 ] );
    glBegin(GL_QUADS);
    glNormal3f( 0,+1, 0);
    glTexCoord2f( 0, 0 ); glVertex3f(-1,+1,+1.8);
    glTexCoord2f( 1, 0 ); glVertex3f(+1,+1,+1.8);
    glTexCoord2f( 1, 1 ); glVertex3f(+1,+1,-1.8);
    glTexCoord2f( 0, 1 ); glVertex3f(-1,+1,-1.8);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // wheels
    cylinder( 1, -1.1, 1.3, 0.4, 0.4, -90, 0, 0, 1, car_textures[ 5 ], 0, 1, 1 );
    cylinder( 1, -1.1, -1.3, 0.4, 0.4, -90, 0, 0, 1, car_textures[ 5 ], 0, 1, 1 );
    cylinder( -1, -1.1, 1.3, 0.4, 0.4, 90, 0, 0, 1, car_textures[ 5 ], 0, 1, 1 );
    cylinder( -1, -1.1, -1.3, 0.4, 0.4, 90, 0, 0, 1, car_textures[ 5 ], 0, 1, 1 );
    
    glPopMatrix();
}

/**
 * Small grass cluster used in path
 */
void grass( double x, double y, double z, double rot, double scale ) {
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, 1 );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, white );
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, black );

    glPushMatrix();
    glTranslatef( x, y, z );
    glRotatef( rot, 0, 1, 0 );
    glScalef( scale, scale, scale );

    glEnable(GL_TEXTURE_2D);
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glColor3f(1,1,1);
    glBindTexture( GL_TEXTURE_2D, setting_textures[ 3 ] );

    glBegin( GL_QUAD_STRIP );
    glTexCoord2f( 0, 0 ); glVertex3f( -0.5, 0, 0 );
    glTexCoord2f( 0.5, 0 ); glVertex3f( -0.35, 0, 0 );
    glTexCoord2f( 1, 0 ); glVertex3f( -0.2, 0, 0 );
    glTexCoord2f( 0.5, 1 ); glVertex3f( -0.35, 0.5, 0.25 );
    glEnd();
    glBegin( GL_QUAD_STRIP );
    glTexCoord2f( 0, 0 ); glVertex3f( -0.25, 0, 0 );
    glTexCoord2f( 0.5, 1 ); glVertex3f( -0.15, 0, 0 );
    glTexCoord2f( 1, 0 ); glVertex3f( 0, 0, 0 );
    glTexCoord2f( 0.5, 1 ); glVertex3f( -0.15, 0.7, -0.25 );
    glEnd();
    glBegin( GL_QUAD_STRIP );
    glTexCoord2f( 0, 0 ); glVertex3f( 0.1, 0, 0 );
    glTexCoord2f( 0.5, 1 ); glVertex3f( 0.25, 0, 0 );
    glTexCoord2f( 1, 0 ); glVertex3f( 0.35, 0, 0 );
    glTexCoord2f( 0.5, 1 ); glVertex3f( 0.25, 0.6, 0 );
    glEnd();
    glPopMatrix();
    glDisable( GL_TEXTURE_2D );
}

/**
 * Straight path with small grass on sides
 */
void path( double x, double y, double z, double rot, double scale ) {
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, 1 );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, white );
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, black );
    //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslatef(x,y,z);
    glRotatef( rot, 0, 1, 0) ;
    glScalef( scale, scale, scale );

    // enable textures and use either the gold tin or satellite based on what's passed in
    glEnable(GL_TEXTURE_2D);
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glColor3f(1,1,1);
    glBindTexture( GL_TEXTURE_2D, setting_textures[ 2 ] );
    glBegin(GL_QUADS);
    glNormal3f( 0,+1, 0);
    glTexCoord2f( 1, 1 ); glVertex3f(-1,0,+3);
    glTexCoord2f( 1, 0 ); glVertex3f(+1,0,+3);
    glTexCoord2f( 0, 0 ); glVertex3f(+1,0,-3);
    glTexCoord2f( 0, 1 ); glVertex3f(-1,0,-3);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    grass( 0.75, 0, 2.0, 90, 1 );
    grass( -0.75, 0, 0.6, 90, 1 );
    grass( -0.75, 0, -2, 90, 1 );
    glPopMatrix();
}

/**
 * Birdfeeder with birdfeeder holder and feeder itself
 */
void birdfeeder( struct Birdfeeder feeder ) {
    // takes in birdfeeder struct since pos variables will be adjusted often
    glPushMatrix();
    glTranslatef( feeder.x, feeder.y, feeder.z );
    glRotatef( feeder.rot, 0, 1, 0 );
    glScalef( feeder.scale, feeder.scale, feeder.scale );
    cube( 0, 0, 0, 0.1, 4, 0.1, 0, setting_textures[ 1 ], 0, 1 );
    cube( 1.4, 4, 0, 1.5, 0.1, 0.1, 0, setting_textures[ 1 ], 0, 1 );
    glColor3f(0,0,0);
    glLineWidth( 2 );
    glBegin( GL_LINES );
    glVertex3f( 2.8, 4, 0 );
    glVertex3f( 2.8, 3, 0 );
    glEnd();

    cone( 2.8, 2.5, 0, 0.75, 0.8, 0, 0, 0, 0, setting_textures[ 4 ], 0, 1, 1 );
    cylinder( 2.8, 1, 0, 1.75, 0.4, 90, 0, 1, 0, setting_textures[ 5 + feeder.empty ], 0, 1, 1 );
    cylinder( 2.8, -0.4, 0, 1.25, 0.05, 90, 1, 0, 0, setting_textures[ 4 ], 0, 1, 1 );
    glPopMatrix();
    // Display fill prompt if empty
    if ( feeder.empty == 1 && feeder.Tx != feeder.x ) {
        glPushMatrix();
        glDisable( GL_LIGHTING );
        glColor3f( 1, 1, 1 );
        glRasterPos3d( feeder.Tx, feeder.y + 1, feeder.Tz );
        Print("Push 'f' to fill birdfeeder");
        glPopMatrix();
        glEnable( GL_LIGHTING );
    }
}

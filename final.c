/**
 * Devin Noth - Final Project: Birding Simulator
 * 
 * 
 */

#include "CSCIx229.h"

// Window & game view vars
static GLint window = 0; // window storage
static GLint windowSizeX = 1280; // window width
static GLint windowSizeY = 960; // window height
static GLint debugMode = 0; // starts not in debug mode
static GLint mouseLock = 1; // var used for locking mouse in window
static GLfloat fps = 0; // fps used for debugging
static GLint Frames = 0; // frame count var for debuggin
static GLint T0 = 0; // used for frame count
int fov = 60;   //  Field of view
double asp = 1.33;    // Aspect Ratio
int mX = 0;     // mouse pos x
int mY = 0;     // mouse pos y

// graphics vars
int light = 1;  // light on/off
int shadows = 1; // shadows on/off
int reflections = 1; //lake reflection on/off

// world vars
int cameraEquipped = 1; // bool for if camera or journal equipped
int viewfinder = 0; // bool for viewfinder mode
double zoom = 1;    // zoom var for viewfinder mode
int shutterFrameCount = -1; // shutter var used for shutter animation
double th = 0;  // azimuth of view angle 
double ph = 0;  // elevation of view angle
double Px = -70; //  Player pos x
double Py = 1;  //  Player pos y
double Pz = -70;  //  Player pos z
double Lx = 0;  //  Looking at x
double Ly = 0;  //  Looking at y
double Lz = 0;  //  Looking at z
double walkSpeed = 1.0; // walk speed if user is on ground or in lake
double dim = 150.0; // size of world
double groundY = -5.0; // ground offset
int level = 0;  // current game level
int curModel = 0; // current looking for model index
int curSpecies = 1; // current looking for species index
int objComplete = 0; // bool for if player has completed objective
int night = 0;  // flashlight on/off
struct Birdfeeder lFeeder = { 110, -0.5, 10, 110, 10, 180, 1, 1 }; // left feeder
struct Birdfeeder rFeeder = { -10, -0.5, 60, -10, 60, -90, 1, 1 };  // right feeder
struct Sphere innerBounds[3]; // lake bounding spheres

// lighting vars (initialized to daytime)
int ambient = 40; // ambient intensity (%)
int diffuse = 75; // diffuse intensity (%)
int specular = 25; // specular intensity (%)
float Pos[]  = { 120, 100, 50, 1.0 }; // light pos
float sN[] = { 0, -1, 0 }; // shadow normal values
float gP[] = {0, -4.95, 0 }; // ground offset plane

/**
 * Enables lighting in scene with stored ambient, diffuse, specular, and position vars
 * Spawns light in Sun skybox position
 */
void lighting() {
    //  Translate intensity to color vectors
    float Ambient[]   = { 0.01 * ambient , 0.01 * ambient, 0.01 * ambient, 1.0 };
    float Diffuse[]   = { 0.01 * diffuse ,0.01 * diffuse, 0.01 * diffuse, 1.0 };
    float Specular[]  = { 0.01 * specular, 0.01 * specular, 0.01 * specular, 1.0 };
    //  OpenGL should normalize normal vectors
    glEnable(GL_NORMALIZE);
    //  Enable lighting
    glEnable(GL_LIGHTING);
    //  Location of viewer for specular calculations
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);
    //  glColor sets ambient and diffuse color materials
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    //  Enable light 0
    glEnable(GL_LIGHT0);
    //  Set ambient, diffuse, specular components and position of light 0
    glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
    glLightfv(GL_LIGHT0,GL_POSITION,Pos);
}

/**
 * Used for animating flash when a picture is taken in night mode
 */
void animateFlash() {
    if ( shutterFrameCount == 0 ) {
        ambient = 50;
        diffuse = 50;
    } else if ( shutterFrameCount == 1 ) {
        ambient = 75;
        diffuse = 75;
    } else if ( shutterFrameCount == 2 ) {
        ambient = 95;
        diffuse = 95;
    } else if ( shutterFrameCount == 8 ) {
        ambient = 95;
        diffuse = 95;
    } else if ( shutterFrameCount == 9 ) {
        ambient = 75;
        diffuse = 75;
    } else if ( shutterFrameCount == 10 ) {
        ambient = 50;
        diffuse = 50;
    } else if ( shutterFrameCount == 11 ) {
        ambient = 10;
        diffuse = 10;
    }
}

/**
 * Derived from ex20.c File's Cockpit() function
 * Creates an overlay in viewfinder mode that emulates a camera's viewfinder
 * Also creates a full black overlay to simulate a camera shutter after a photo is taken
 */
void overlay()
{
    glDisable( GL_LIGHTING );
    //  Save transform attributes (Matrix Mode and Enabled Modes)
    glPushAttrib(GL_TRANSFORM_BIT|GL_ENABLE_BIT);
    //  Save projection matrix and set unit transform
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-asp,+asp,-1,1,-1,1);
    //  Save model view matrix and set to indentity
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    if ( shutterFrameCount > -1 ) {
        if ( shutterFrameCount > 2 && shutterFrameCount < 8 ) {
        // load black screen for shutter animation
            glColor3f(0,0,0);
            glBegin(GL_QUADS);
            glVertex2f( -10, -10 );
            glVertex2f( 10, -10 );
            glVertex2f( 10, 10 );
            glVertex2f( -10, 10 );
            glEnd();
            glPopAttrib();
        }
        // stop shutter animation after 8 frames
        shutterFrameCount += shutterFrameCount < 11 ? 1 : -12;
    } else {
        // Draw viewfinder lines
        glColor3f(1,1,1);
        glLineWidth( 2 );
        glBegin(GL_LINES);
        glVertex2f(0,0.05);
        glVertex2f(0,-0.05);
        glVertex2f(0.05, 0);
        glVertex2f(-0.05, 0);

        // small corners
        glVertex2f( -0.125, -0.125 );
        glVertex2f( -0.125, -0.075 );
        glVertex2f( -0.125, -0.125 );
        glVertex2f( -0.075, -0.125 );
        glVertex2f( 0.125, -0.125 );
        glVertex2f( 0.125, -0.075 );
        glVertex2f( 0.125, -0.125 );
        glVertex2f( 0.075, -0.125 );
        glVertex2f( -0.125, 0.125 );
        glVertex2f( -0.125, 0.075 );
        glVertex2f( -0.125, 0.125 );
        glVertex2f( -0.075, 0.125 );
        glVertex2f( 0.125, 0.125 );
        glVertex2f( 0.125, 0.075 );
        glVertex2f( 0.125, 0.125 );
        glVertex2f( 0.075, 0.125 );
        glEnd();

        // big corners
        glLineWidth( 4 );
        glBegin(GL_LINES);
        glVertex2f( -0.9, -0.7 );
        glVertex2f( -0.9, -0.5 );
        glVertex2f( -0.9, -0.7 );
        glVertex2f( -0.7, -0.7 );
        glVertex2f( 0.9, -0.7 );
        glVertex2f( 0.9, -0.5 );
        glVertex2f( 0.9, -0.7 );
        glVertex2f( 0.7, -0.7 );
        glVertex2f( -0.9, 0.7 );
        glVertex2f( -0.9, 0.5 );
        glVertex2f( -0.9, 0.7 );
        glVertex2f( -0.7, 0.7 );
        glVertex2f( 0.9, 0.7 );
        glVertex2f( 0.9, 0.5 );
        glVertex2f( 0.9, 0.7 );
        glVertex2f( 0.7, 0.7 );
        glEnd();
        //  Reset model view matrix
        glPopMatrix();
        //  Reset projection matrix
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        //  Pop transform attributes (Matrix Mode and Enabled Modes)
        glPopAttrib();

        // Display zoom val
        glPushMatrix();
        glColor3f( 1, 1, 1 );
        glWindowPos2i(220,155);
        Print( "Zoom: %.0fx", zoom );
        glPopMatrix();
    }
    glEnable( GL_LIGHTING );
}

/**
 * Global scene draw function with parameters for drawing shadow or reflection scenes as well
 * Pass 1 into reflection and 0 into shadow to draw reflection scene, vice versa for shadow scene
 * Pass 1 into both parameters to draw full scene
 */
void scene( int shadow, int reflection ) {
    if ( reflection == 1 ) {
        // only need sky, some rocks, trees for reflection
        Sky( dim * 2.5, night );
        glPushMatrix();
        glTranslatef( 0, -10, 0 );
        rocks( 70, 0, -145, 0, 10 );
        rocks( -140, 0, 75, -90, 9 );
        rocks( -70, 0, 145, 180, 10 );
        glPopMatrix();
    }
    // trees are both in reflection and shadow scenes, but specific layers so we need a separate bool
    glPushMatrix();
    glTranslatef( 0, groundY, 0 );
    trees1( 70, 0, 52, 0, 2 );
    trees1( -40, 0, 75, -45, 2.5 );
    trees2( 50, 0, -60, 0, 2 );
    glPopMatrix();
    if ( shadow == 1 ) {
        // only rocks that need shadows
        glPushMatrix();
        glTranslatef( 0, -10, 0 );
        rocks( 140, 0, -10, 90, 9 );
        glPopMatrix();
        // things we don't care about reflecting but do care about adding shadows
        // path around lake
        glPushMatrix();
        glTranslatef( 0, groundY + 0.05, 0 );
        path( -82.5, 0.1, -82.5, 45, 3 );
        path( -70, 0.2, -70, 45, 3 );
        path( -50, 0.1, -70, 120, 5 );
        path( -25, 0.15, -80, 100, 5 );
        path( 5, 0.1, -82.5, 90, 6 );
        path( 32.5, 0.15, -77, 65, 5 );
        path( 55, 0.1, -62.5, 45, 5 );
        path( 70, 0.15, -45, 45, 5 );
        path( 90, 0.1, -25, 45, 7 );
        path( 100, 0.15, 0, 5, 6 );
        path( 100, 0.1, 35, 0, 7 );
        path( 90, 0.15, 60, -65, 5 );
        path( 65, 0.1, 70, -75, 6 );
        path( 35, 0.15, 75, -85, 6 );
        path( 2.5, 0.1, 75, -100, 7 );
        path( -25, 0.15, 67.5, -110, 6 );
        path( -55, 0.1, 60, -100, 6 );
        path( -85, 0.15, 50, 60, 5 );
        path( -100, 0.1, 30, 10, 6 );
        path( -104, 0.15, 0, 5, 5 );
        path( -100, 0.1, -25, -30, 7 );
        path( -77.5, 0.15, -52.5, -50, 6 );
        glPopMatrix();
        // load journal or camera
        if ( cameraEquipped == 0 ) {
            glPushMatrix();
            glTranslatef( Lx + 0.2 * Cos( th ), Py - 0.1, Lz + 0.2 * Sin( th ) );
            glRotatef( -th - 90, 0.0, 1.0, 0.0 );
            glRotatef( ( ph + 10 ) / 1.2, 1.0, 0.0, 0.0 );
            journal( 0, 0, 0, 0.07, ( level * 2 ) + objComplete );
            glPopMatrix();
        } else if ( viewfinder == 0 ) {
            glPushMatrix();
            glTranslatef( Lx + 0.2 * Cos( th - 90 ), ( Ly / 2 ) + 0.3, Lz + 0.2 * Sin( th - 90 ) );
            glRotatef( -th - 75, 0.0, 1.0, 0.0 );
            glRotatef( ( ph + 10 ) / 1.2, 1.0, 0.0, 0.0 );
            camera( 0, 0, 0, 0.05 );
            glPopMatrix();
        }
        car( -95, 1.25, -95, 0, 4.5 );
        birdfeeder( lFeeder );
        birdfeeder( rFeeder );

        // load birds
        int i = t / 6;
        int count = 0;
        struct Bird bird;
        while( count < 10 ) {
        bird = birdSpawns[ i ];
        if ( bird.spawn == 1 ) {
        if ( bird.model == 0 ) {
            sparrow( bird );
        } else if ( bird.model == 1 ) {
            crested( bird );
        } else {
            owl( bird );
        }
        }

        // either advance index by 1 or go back to 0
        i += i < 14 ? 1 : -14;
        count++;
        }
    }
}

/**
 * Derived from shadowProjection() function from ex34.c file
 * Used to create a flat model matrix to draw a scene to to then color and simulate shadows
 */
void ShadowProjection()
{
   float mat[16];
   float e = gP[0]*sN[0] + gP[1]*sN[1] + gP[2]*sN[2];
   float l = Pos[0]*sN[0] + Pos[1]*sN[1] + Pos[2]*sN[2];
   float c = e - l;
   //  Create the matrix.
   mat[0] = sN[0]*Pos[0]+c; mat[4] = sN[1]*Pos[0];   mat[8]  = sN[2]*Pos[0];   mat[12] = -e*Pos[0];
   mat[1] = sN[0]*Pos[1];   mat[5] = sN[1]*Pos[1]+c; mat[9]  = sN[2]*Pos[1];   mat[13] = -e*Pos[1];
   mat[2] = sN[0]*Pos[2];   mat[6] = sN[1]*Pos[2];   mat[10] = sN[2]*Pos[2]+c; mat[14] = -e*Pos[2];
   mat[3] = sN[0];        mat[7] = sN[1];        mat[11] = sN[2];        mat[15] = -l;
   //  Multiply modelview matrix
   glMultMatrixf(mat);
}

/**
 * Derived from ex34.c file
 * Creates a stencil buffer similar to the lake reflection,
 * needs to create a flat matrix to draw scene too however instead of
 * a simple reverse y scene
 */
void drawShadows() {
    glDisable(GL_LIGHTING);
    //  Enable stencil operations
    glEnable(GL_STENCIL_TEST);
    //  Existing value of stencil buffer doesn't matter
    glStencilFunc(GL_ALWAYS,1,0xFFFFFFFF);
    //  Set the value to 1 (REF=1 in StencilFunc)
    //  only if Z-buffer would allow write
    glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
    //  Make Z-buffer and color buffer read-only
    glDepthMask(0);
    glColorMask(0,0,0,0);
    // draw projection matrix
    glPushMatrix();
    ShadowProjection();
    scene(1, 0);
    glPopMatrix();
    //  Make Z-buffer and color buffer read-write
    glDepthMask(1);
    glColorMask(1,1,1,1);
    //  Set the stencil test draw where stencil buffer is > 0
    glStencilFunc(GL_LESS,0,0xFFFFFFFF);
    //  Make the stencil buffer read-only
    glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
    //  Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0,0,0,0.3);
    //  Draw the shadow over the entire floor
    glBegin(GL_QUADS);
    glVertex3f(-dim,-4.95,+dim);
    glVertex3f(+dim,-4.95,+dim);
    glVertex3f(+dim,-4.95,-dim);
    glVertex3f(-dim,-4.95,-dim);
    glEnd();
    glDisable( GL_BLEND );
    glDisable(GL_STENCIL_TEST);
    glEnable(GL_LIGHTING);
}

/**
 * Creates a stencil buffer where the lake is drawn that displays an upside down
 * rendering of some parts of our scene.
 * Not all parts, since most won't show up in the reflection anyway and rendering the entire scene twice
 * is much harder on our GPU than only loading specific parts
 */
void drawReflection() {
    if ( reflections == 1 ) {
        // disable depth test so ground underneath does not appear
        glDisable(GL_DEPTH_TEST);
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        // stencil buffer with val 1
        glEnable(GL_STENCIL_TEST);
        glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
        glStencilFunc(GL_ALWAYS, 1, 0xffffffff);
        // draw lake area where reflection will appear
        lake( 0, groundY + 0.1, 0, 2.5 );
        // re enable
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glEnable(GL_DEPTH_TEST);
        // draw where stencil equals 1
        glStencilFunc(GL_EQUAL, 1, 0xffffffff);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        // draw reflected scene
        glPushMatrix();
        // disable depth test so ground doesn't appear beneath reflection
        glDisable( GL_DEPTH_TEST );
        glScalef(1.0, -1.0, 1.0);
        if ( light == 1 ) {
            lighting();
        }
        scene(0, 1);
        glEnable( GL_DEPTH_TEST );
        glPopMatrix();
        glDisable(GL_STENCIL_TEST);
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // blend with slight blue tint (not too necessary but I think it helps the look overall)
    glColor4f(0.0, 0.0, 0.7, 0.2);
    lake( 0, groundY + 0.1, 0, 2.5 );
    glDisable(GL_BLEND);

}

/**
 * Main display function
 * Always displays the frame rate in the console
 * Responsible for displaying either regular or default mode and proper overlays
 */
void draw() {
    // erase buffers
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
    // Enable Z-buffering in OpenGL
    glEnable( GL_DEPTH_TEST );

    Project( fov, asp, dim );
    glLoadIdentity();

    gluLookAt( Px, Py, Pz, Lx, Ly, Lz, 0, 1, 0 );

    glPushMatrix();

    if ( debugMode == 0 ) {
        // draw ground
        glPushMatrix();
        glTranslatef( 0, groundY, 0 );
        ground( dim );
        glPopMatrix();
        // call no matter what, even if reflection var is 0 so lake outline can always be drawn
        drawReflection();
        if ( shadows == 1 ) {
            drawShadows();
        }
        if ( light == 1 ) {
            lighting();
        }
        scene( 1, 1 );
    } else {
        // debug mode
        Sky(dim * 2.5, night);
        glPushMatrix();
        glTranslatef( 0, groundY, 0 );
        ground( dim );
        glPopMatrix();
        // display inner bounds
        glEnable(GL_TEXTURE_2D);
        glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
        glColor3f(1,1,1);
        glBindTexture( GL_TEXTURE_2D, setting_textures[ 1 ] );
        circle( innerBounds[ 0 ].pos.x, innerBounds[ 0 ].pos.y, innerBounds[ 0 ].pos.z, innerBounds[ 0 ].r );
        circle( innerBounds[ 1 ].pos.x, innerBounds[ 1 ].pos.y, innerBounds[ 1 ].pos.z, innerBounds[ 1 ].r );
        circle( innerBounds[ 2 ].pos.x, innerBounds[ 2 ].pos.y, innerBounds[ 2 ].pos.z, innerBounds[ 2 ].r );
        glDisable(GL_TEXTURE_2D);
        // display frame rate in console, from gears.c file
        Frames++;
        {
        GLint t = glutGet(GLUT_ELAPSED_TIME);
        if (t - T0 >= 5000) {
        GLfloat seconds = (t - T0) / 1000.0;
        fps = Frames / seconds;
        printf("%d frames in %6.3f seconds = %6.3f FPS\n", Frames, seconds, fps);
        T0 = t;
        Frames = 0;
        }
        }
    }
    glPopMatrix();

    // Display viewfinder overlay if in viewfinder, animate flash if night and picture taken
    if ( viewfinder == 1 ) {
        if ( night == 1 && shutterFrameCount > -1 ) {
            animateFlash();
        }
        overlay();
    }
    glFlush();
    glutSwapBuffers();
}

/**
 * Updates Looking at pos for viewing vector
 * Also determines distance from player to both bird feeders,
 * If close enough text with instructions will display
 */
void updateLookingAt() {
    Lx = Px - 0.5 * Cos( th );
    Ly = Py - 0.5 * Sin( ph );
    Lz = Pz - 0.5 * Sin( th );

    // if player close to feeders, display text in between player and feeder
    if ( length2d( Px, Pz, lFeeder.x, lFeeder.z ) < 15 ) {
        double theta = atan2( Px - lFeeder.x, Pz - lFeeder.z );
        lFeeder.Tx = lFeeder.x - 2.0 * Cos( theta );
        lFeeder.Tz = lFeeder.z - 2.0 * Sin( theta );
    } else {
        lFeeder.Tx = lFeeder.x;
        lFeeder.Tz = lFeeder.z;
    }
    if ( length2d( Px, Pz, rFeeder.x, rFeeder.z ) < 15 ) {
        double theta = atan2( Px - rFeeder.x, Pz - rFeeder.z );
        rFeeder.Tx = rFeeder.x - 2.0 * Cos( theta );
        rFeeder.Tz = rFeeder.z - 2.0 * Sin( theta );
    } else {
        rFeeder.Tx = rFeeder.x;
        rFeeder.Tz = rFeeder.z;
    }
}

/**
 * Used for checking valid player position.
 * AKA making sure user isn't where they're not supposed to be
 * How it works, it limits the outer bounds by not letting you move there,
 * but for the inner bounds, it will move you at quarter speed to simulate treading through water.
 * This method was decided due to the difficulty of completely limiting moving accross the lake and still
 * having the movement feel natural
 */
void checkBounds() {
    // check outer bounds
    if ( Px < -dim * 0.825 ) {
        Px = -dim * 0.825;
    } else if ( Px > dim * 0.825 ) {
        Px = dim * 0.825;
    } else if ( Pz < -dim * 0.825 ) {
        Pz = -dim * 0.825;
    } else if ( Pz > dim * 0.825 ) {
        Pz = dim * 0.825;
    }
    // check inner bounds
    float dist;
    int in = 0;
    for ( int i = 0; i < 3; i++ ) {
        dist = length2d( Px, Pz, innerBounds[ i ].pos.x, innerBounds[ i ].pos.z );
        if ( dist < innerBounds[ i ].r ) {
            in = 1;
        }
    }
    walkSpeed = in == 1 ? 0.25 : 1.0;
}

/**
 * Once feeders are filled, update all birds to can be spawned
 */
void updateBirdVisibility() {
    for( int i = 0; i < 15; i++ ) {
        birdSpawns[ i ].spawn = 1;
    }
}

/**
 * Updates time varibale while idleing used for spawning birds
 */
void idle() {
    //  Calc passed time for bird spawns
    t = ( glutGet(GLUT_ELAPSED_TIME) % 90000 ) / 1000.0;
    glutPostRedisplay();
}

/**
 * Called when in viewfinder, user hits left mouse button, and objective not complete
 */
void takePicture() {
    shutterFrameCount = 0;
    // Get vectors needed
    struct Vec3 birdVecs[ 2 ];
    struct Vec3 bird1 = { 0, 0, 0 };
    struct Vec3 bird2 = { 0, 0, 0 };
    birdVecs[ 0 ] = bird1;
    birdVecs[ 1 ] = bird2;
    struct Vec3 lookingVec = { Lx - Px, Ly - Py, Lz - Pz };
    int index = 0;
    for ( int i = 0; i < 15; i++ ) {
        if( birdSpawns[ i ].model == curModel && birdSpawns[ i ].species == curSpecies ) {
            birdVecs[ index ].x = birdSpawns[ i ].x - Px;
            birdVecs[ index ].y = birdSpawns[ i ].y - Py;
            birdVecs[ index ].z = birdSpawns[ i ].z - Pz;
            index++;
        }
    }
    // normalize vectors
    double length;
    length = length3d( lookingVec.x, lookingVec.y, lookingVec.z );
    lookingVec.x = lookingVec.x / length;
    lookingVec.y = lookingVec.y / length;
    lookingVec.z = lookingVec.z / length;
    length = length3d( birdVecs[ 0 ].x, birdVecs[ 0 ].y, birdVecs[ 0 ].z );
    birdVecs[ 0 ].x = birdVecs[ 0 ].x / length;
    birdVecs[ 0 ].y = birdVecs[ 0 ].y / length;
    birdVecs[ 0 ].z = birdVecs[ 0 ].z / length;
    length = length3d( birdVecs[ 1 ].x, birdVecs[ 1 ].y, birdVecs[ 1 ].z );
    birdVecs[ 1 ].x = birdVecs[ 1 ].x / length;
    birdVecs[ 1 ].y = birdVecs[ 1 ].y / length;
    birdVecs[ 1 ].z = birdVecs[ 1 ].z / length;
    // take dot product of vectors
    double d1, d2;
    d1 = DotProduct( lookingVec, birdVecs[ 0 ] );
    d2 = DotProduct( lookingVec, birdVecs[ 1 ] );
    // If either dot product is close enough to 1, then mark obj complete
    if ( d1 > 0.99 || d2 > 0.99 ) {
        objComplete = 1;
    }
}

/**
 * Handler function for when user hits a mouse button
 */
void mouseButton( int button, int state, int x, int y ) {
    // only when button is down
    if ( state == GLUT_DOWN ) {
        // go in viewfinder mode with RMB
        if ( button == GLUT_RIGHT_BUTTON ) {
            if ( cameraEquipped == 1 ) {
                // If not in viewfinder mode, turn it on
                if ( viewfinder == 0 ) {
                    fov = 55;
                    viewfinder = 1;
                } else {
                    // if in viewfinder, increase zoom until max then turn off viewfinder
                    if ( zoom == 1 ) {
                        fov = 50;
                        zoom = 2;
                    } else if ( zoom == 2 ) {
                        fov = 25;
                        zoom = 5;
                    } else if ( zoom == 5 ) {
                        fov = 10;
                        zoom = 10;
                    } else {
                        fov = 60;
                        viewfinder = 0;
                        zoom = 1;
                    }
                }
            }
        // Take picture with LMB
        } else if ( button == GLUT_LEFT_BUTTON ) {
            // can only take a pic in viewfinder mode
            if ( viewfinder == 1 && objComplete == 0 ) {
                takePicture();
            }
        }
    }
    updateLookingAt();  
}

/**
 * Called when mouse moves, used for rotating first person camera
 */
void mouse( int x, int y ) {
    th += ( x - mX ) / 10.0;
    ph += ( y - mY ) / 10.0;
    // upper and lower bounds on looking up and down
    ph = ph > 60 ? 60 : ph;
    ph = ph < -60 ? -60 : ph;
    mX = x;
    mY = y;
    updateLookingAt();

    if ( mX <= 0 || mX >= 1000 || mY <= 0 || mY >= 1000 ) {
        mX = 500;
        mY = 500;
        glutWarpPointer( 500, 500 );
    }

    glutPostRedisplay();
}

/**
 * Responsible for loading birds for each level
 * In each level, there exist 2 of the bird the player is looking for
 */
void loadBirdSpawns() {
    // loads level 1 birds
    if ( level == 0 ) {
        struct Bird bird0 = { 1, 0, 0, 10, -0.05, 56.5, 120, 0.2 };
        birdSpawns[ 0 ] = bird0;
        struct Bird bird1 = { 1, 0, 4, -50, 3.75, 51, 45, 0.25 };
        birdSpawns[ 1 ] = bird1;
        struct Bird bird2 = { 1, 0, 5, -15, 2.1, 75, 90, 0.15 };
        birdSpawns[ 2 ] = bird2;
        struct Bird bird3 = { 0, 0, 3, -9.4, -0.6, 62.75, 100, 0.2 };
        birdSpawns[ 3 ] = bird3;
        struct Bird bird4 = { 0, 0, 1, -10.7, -0.55, 62.75, -80, 0.25 };
        birdSpawns[ 4 ] = bird4;
        struct Bird bird5 = { 0, 0, 3, -25, 6.5, 81.5, 50, 0.225 };
        birdSpawns[ 5 ] = bird5;
        struct Bird bird6 = { 1, 0, 5, 2.75, 3.25, 62.5, 100, 0.15 };
        birdSpawns[ 6 ] = bird6;
        struct Bird bird7 = { 1, 1, 1, 29, 44.5, 51, 170, 0.35 };
        birdSpawns[ 7 ] = bird7;
        struct Bird bird8 = { 1, 1, 1, 60, 42.5, 53.5, 130, 0.35 };
        birdSpawns[ 8 ] = bird8;
        struct Bird bird9 = { 1, 1, 2, -57.5, 45, 70, 130, 0.4 };
        birdSpawns[ 9 ] = bird9;
        struct Bird bird10 = { 1, 1, 2, 1.5, 49.5, -45, -20, 0.35 };
        birdSpawns[ 10 ] = bird10;
        struct Bird bird11 = { 1, 1, 1, 23.5, 51, -50, -40, 0.35 };
        birdSpawns[ 11 ] = bird11;
        struct Bird bird12 = { 1, 0, 4, -20, 8.5, -47.5, -60, 0.2 };
        birdSpawns[ 12 ] = bird12;
        struct Bird bird13 = { 1, 0, 0, 20, 7.5, -47.5, -60, 0.2 };
        birdSpawns[ 13 ] = bird13;
        struct Bird bird14 = { 0, 0, 1, 107, -0.55, 10.6, -170, 0.2 };
        birdSpawns[ 14 ] = bird14;
    } else if ( level == 1 ) {
        // loads level 2 birds (index 1)
        struct Bird bird0 = { 1, 0, 4, 10, -0.05, 56.5, 120, 0.2 };
        birdSpawns[ 0 ] = bird0;
        struct Bird bird1 = { 1, 0, 3, -50, 3.75, 51, 45, 0.3 };
        birdSpawns[ 1 ] = bird1;
        struct Bird bird2 = { 1, 0, 3, -15, 2.1, 75, 90, 0.25 };
        birdSpawns[ 2 ] = bird2;
        struct Bird bird3 = { 0, 1, 0, 15.5, 10, 54, -150, 0.4 };
        birdSpawns[ 3 ] = bird3;
        struct Bird bird4 = { 1, 0, 2, 2.75, 3.25, 62.5, 100, 0.2 };
        birdSpawns[ 4 ] = bird4;
        struct Bird bird5 = { 0, 0, 0, -10.7, -0.55, 62.75, -80, 0.2 };
        birdSpawns[ 5 ] = bird5;
        struct Bird bird6 = { 1, 1, 2, -9.4, -0.6, 62.75, 100, 0.2 };
        birdSpawns[ 6 ] = bird6;
        struct Bird bird7 = { 1, 0, 5, 107, -0.575, 9.3, 190, 0.15 };
        birdSpawns[ 7 ] = bird7;
        struct Bird bird8 = { 1, 1, 2, 60, 42.5, 53.5, 130, 0.35 };
        birdSpawns[ 8 ] = bird8;
        struct Bird bird9 = { 1, 1, 0, -57.5, 45, 70, 130, 0.4 };
        birdSpawns[ 9 ] = bird9;
        struct Bird bird10 = { 1, 1, 2, 1.5, 49.5, -45, -20, 0.35 };
        birdSpawns[ 10 ] = bird10;
        struct Bird bird11 = { 1, 1, 2, 23.5, 51, -50, -40, 0.35 };
        birdSpawns[ 11 ] = bird11;
        struct Bird bird12 = { 1, 0, 0, -20, 8.5, -47.5, -60, 0.2 };
        birdSpawns[ 12 ] = bird12;
        struct Bird bird13 = { 0, 1, 0, 107, -0.55, 10.6, -170, 0.2 };
        birdSpawns[ 13 ] = bird13;
        struct Bird bird14 = { 1, 0, 2, 20, 7.5, -47.5, -60, 0.2 };
        birdSpawns[ 14 ] = bird14;
    } else if ( level == 2 ) {
        // loads level 3 birds
        struct Bird bird0 = { 1, 0, 2, 107, -0.55, 10.6, -170, 0.2 };
        birdSpawns[ 0 ] = bird0;
        struct Bird bird1 = { 1, 0, 5, 107, -0.575, 9.3, 190, 0.15 };
        birdSpawns[ 1 ] = bird1;
        struct Bird bird2 = { 1, 0, 2, -10.7, -0.55, 62.75, -80, 0.2 };
        birdSpawns[ 2 ] = bird2;
        struct Bird bird3 = { 1, 1, 0, -9.4, -0.6, 62.75, 100, 0.2 };
        birdSpawns[ 3 ] = bird3;
        struct Bird bird4 = { 1, 1, 3, 23.5, 66, -53, -40, 0.35 };
        birdSpawns[ 4 ] = bird4;
        struct Bird bird5 = { 1, 1, 0, 1.5, 49.5, -45, -20, 0.35 };
        birdSpawns[ 5 ] = bird5;
        struct Bird bird6 = { 1, 1, 0, 23.5, 51, -50, -40, 0.35 };
        birdSpawns[ 6 ] = bird6;
        struct Bird bird7 = { 1, 0, 2, 10, -0.05, 56.5, 120, 0.2 };
        birdSpawns[ 7 ] = bird7;
        struct Bird bird8 = { 1, 0, 4, -50, 3.75, 51, 45, 0.3 };
        birdSpawns[ 8 ] = bird8;
        struct Bird bird9 = { 1, 0, 2, -15, 2.1, 75, 90, 0.25 };
        birdSpawns[ 9 ] = bird9;
        struct Bird bird10 = { 1, 0, 0, 15.5, 10, 54, -150, 0.3 };
        birdSpawns[ 10 ] = bird10;
        struct Bird bird11 = { 1, 1, 1, 20, 7.5, -47.5, -60, 0.4 };
        birdSpawns[ 11 ] = bird11;
        struct Bird bird12 = { 1, 1, 0, -20, 8.5, -47.5, -60, 0.35 };
        birdSpawns[ 12 ] = bird12;
        struct Bird bird13 = { 1, 0, 5, 28.5, 23.5, -55.5, -60, 0.2 };
        birdSpawns[ 13 ] = bird13;
        struct Bird bird14 = { 1, 1, 3, -57.5, 56.5, 69.5, 130, 0.4 };
        birdSpawns[ 14 ] = bird14;
    } else if ( level == 3 ) {
        // loads level 4 birds
        struct Bird bird0 = { 1, 2, 0, -94, 6.5, -94, -30, 0.5 };
        birdSpawns[ 0 ] = bird0;
        birdSpawns[ 1 ].spawn = 0;
        birdSpawns[ 2 ].spawn = 0;
        struct Bird bird3 = { 1, 2, 1, -57.5, 37.25, 69, 130, 0.6 };
        birdSpawns[ 3 ] = bird3;
        birdSpawns[ 4 ].spawn = 0;
        birdSpawns[ 5 ].spawn = 0;
        struct Bird bird6 = { 1, 2, 2, 9.75, 0.75, 56.75, 0, 0.55 };
        birdSpawns[ 6 ] = bird6;
        birdSpawns[ 7 ].spawn = 0;
        birdSpawns[ 8 ].spawn = 0;
        struct Bird bird9 = { 1, 2, 2, 1.5, 49.75, -45, -20, 0.5 };
        birdSpawns[ 9 ] = bird9;
        birdSpawns[ 10 ].spawn = 0;
        birdSpawns[ 11 ].spawn = 0;
        struct Bird bird12 = { 1, 2, 1, 19.75, 8.5, -47.75, -60, 0.6 };
        birdSpawns[ 12 ] = bird12;
        birdSpawns[ 13 ].spawn = 0;
        birdSpawns[ 14 ].spawn = 0;
    }
}

/**
 * handles keyboard inputs
 */
static void key( unsigned char ch, int x, int y ) {
    // walk controls with WASD
    if ( ch == 'w' || ch == 'W' ) {
        Px -= walkSpeed * Cos( th );
        Pz -= walkSpeed * Sin( th );
        checkBounds();
    } else if ( ch == 'a' || ch == 'A' ) {
        Px -= walkSpeed * Cos( th - 90 );
        Pz -= walkSpeed * Sin( th - 90 );
        checkBounds();
    } else if ( ch == 's' || ch == 'S' ) {
        Px += walkSpeed * Cos( th );
        Pz += walkSpeed * Sin( th );
        checkBounds();
    } else if ( ch == 'd' || ch == 'D' ) {
        Px -= walkSpeed * Cos( th + 90 );
        Pz -= walkSpeed * Sin( th + 90 );
        checkBounds();
    } else if ( ch == 'm' || ch == 'M' ) {
        // m switches between regular and debug mode
        debugMode = 1 - debugMode;
    } else if ( ch == 'e' || ch == 'E' ) {
        // e switches between the camera and journal
        cameraEquipped = 1 - cameraEquipped;
        viewfinder = 0;
        zoom = 1;
        fov = 60;
    } else if ( ch == 'f' || ch == 'F' ) {
        // if near an unfilled feeder and press f, feeder becomes filled
        if ( lFeeder.empty == 1 && length2d( Px, Pz, lFeeder.x, lFeeder.z ) < 15 ) {
            lFeeder.empty = 0;
            if ( rFeeder.empty == 0 ) {
                updateBirdVisibility();
            }
        } else if ( rFeeder.empty == 1 && length2d( Px, Pz, rFeeder.x, rFeeder.z ) < 15 ) {
            rFeeder.empty = 0;
            if ( lFeeder.empty == 0 ) {
                updateBirdVisibility();
            }
        }
    } else if ( ch == 'z' || ch == 'Z' ) {
        // z switches lighting on and off
        light = 1 - light;
        if ( light == 0 ) {
            glDisable( GL_LIGHTING );
        }
    } else if ( ch == 'x' || ch == 'X' ) {
        // x switches shadows on and off
        shadows = 1 - shadows;
    } else if ( ch == 'c' || ch == 'C' ) {
        // c switches reflections on and off
        reflections = 1 - reflections;
    } else if( ch == 9 ) {
        // TAB lets user pause so their mouse becomes unlocked
        if( mouseLock ) {
            glutPassiveMotionFunc( NULL );
            glutSetCursor( GLUT_CURSOR_LEFT_ARROW );
        } else {
            glutPassiveMotionFunc( mouse );
            glutSetCursor( GLUT_CURSOR_NONE );
        }
        mouseLock = !mouseLock;
    } else if ( ch == 32 ) {
        // spacebar hit
        if ( objComplete && level < 3 ) {
            level++;
            objComplete = 0;
            loadBirdSpawns();
            if ( level == 1 ) {
                // switch to goldfinch
                curModel = 0;
                curSpecies = 2;
                lFeeder.empty = 1;
                rFeeder.empty = 1;
                // re-empty feeders on level 2
                lFeeder.Tx = lFeeder.x;
                rFeeder.Tx = rFeeder.x;
            } else if ( level == 2 ) {
                // switch to waxwing
                curModel = 1;
                curSpecies = 3;
            } else {
                // switch to grey owl
                curModel = 2;
                curSpecies = 1;
                night = 1;
                ambient = 10;
                specular = 0;
                diffuse = 10;
            }
            
        }
    } else if ( ch == 27 ) {
        // ESC to exit
	  exit( 0 );
    }
    updateLookingAt();
    glutPostRedisplay();
}

void special( int k, int x, int y ) {
    switch ( k ) {
        case GLUT_KEY_UP:
            if ( graphicsIndex < 4 ) {
                // increase shape graphics with up arrow
                graphicsIndex++;
            }
            break;
        case GLUT_KEY_DOWN:
            if ( graphicsIndex > 0 ) {
                // decrease shape graphics with down arrow
                graphicsIndex--;
            }
            break;
        default:
            return;
    }
    glutPostRedisplay();
}

/**
 * reshape()
 * The function takes in the new width and height, and creates a
 * new viewport to be the correct width and height. It saves the new width and height
 */
static void reshape( int width, int height ) {
    GLfloat h = (GLfloat) height / (GLfloat) width;
    windowSizeX = width;
    windowSizeY = height;
    asp = (h>0) ? (double)width/height : 1;
    glViewport(0, 0, (GLint) width, (GLint) height);
}

/**
 * Init function used for loading all textures
 */
void loadTextures() {
    // load skybox textures
    skybox[ 0 ] = LoadTexBMP( "textures/sky.bmp" );
    skybox[ 1 ] = LoadTexBMP( "textures/nightsky.bmp" );

    // load journal textures
    journals[ 0 ] = LoadTexBMP( "textures/journal0.bmp" );
    journals[ 1 ] = LoadTexBMP( "textures/journal1.bmp" );
    journals[ 2 ] = LoadTexBMP( "textures/journal2.bmp" );
    journals[ 3 ] = LoadTexBMP( "textures/journal3.bmp" );
    journals[ 4 ] = LoadTexBMP( "textures/journal4.bmp" );
    journals[ 5 ] = LoadTexBMP( "textures/journal5.bmp" );
    journals[ 6 ] = LoadTexBMP( "textures/journal6.bmp" );
    journals[ 7 ] = LoadTexBMP( "textures/journal7.bmp" );

    leg = LoadTexBMP( "textures/leg.bmp" );

    // loading sparrow model textures
    // index 0: common sparrow
    sparrow_textures[ 0 ][ 0 ] = LoadTexBMP( "textures/sp_head.bmp" );
    sparrow_textures[ 0 ][ 1 ] = LoadTexBMP( "textures/sp_eye.bmp" );
    sparrow_textures[ 0 ][ 2 ] = LoadTexBMP( "textures/sp_beak.bmp" );
    sparrow_textures[ 0 ][ 3 ] = LoadTexBMP( "textures/sp_body.bmp" );
    sparrow_textures[ 0 ][ 4 ] = LoadTexBMP( "textures/sp_twing.bmp" );
    sparrow_textures[ 0 ][ 5 ] = LoadTexBMP( "textures/sp_bwing.bmp" );
    sparrow_textures[ 0 ][ 6 ] = LoadTexBMP( "textures/sp_tail.bmp" );
    // index 1: bluebird
    sparrow_textures[ 1 ][ 0 ] = LoadTexBMP( "textures/bb_head.bmp" );
    sparrow_textures[ 1 ][ 1 ] = LoadTexBMP( "textures/bb_eye.bmp" );
    sparrow_textures[ 1 ][ 2 ] = LoadTexBMP( "textures/bb_beak.bmp" );
    sparrow_textures[ 1 ][ 3 ] = LoadTexBMP( "textures/bb_body.bmp" );
    sparrow_textures[ 1 ][ 4 ] = LoadTexBMP( "textures/bb_twing.bmp" );
    sparrow_textures[ 1 ][ 5 ] = LoadTexBMP( "textures/bb_bwing.bmp" );
    sparrow_textures[ 1 ][ 6 ] = LoadTexBMP( "textures/bb_tail.bmp" );
    // index 2: goldfinch
    sparrow_textures[ 2 ][ 0 ] = LoadTexBMP( "textures/gf_head.bmp" );
    sparrow_textures[ 2 ][ 1 ] = LoadTexBMP( "textures/gf_eye.bmp" );
    sparrow_textures[ 2 ][ 2 ] = LoadTexBMP( "textures/gf_beak.bmp" );
    sparrow_textures[ 2 ][ 3 ] = LoadTexBMP( "textures/gf_body.bmp" );
    sparrow_textures[ 2 ][ 4 ] = LoadTexBMP( "textures/gf_twing.bmp" );
    sparrow_textures[ 2 ][ 5 ] = LoadTexBMP( "textures/gf_bwing.bmp" );
    sparrow_textures[ 2 ][ 6 ] = LoadTexBMP( "textures/gf_tail.bmp" );
    // index 3: rosefinch
    sparrow_textures[ 3 ][ 0 ] = LoadTexBMP( "textures/rf_head.bmp" );
    sparrow_textures[ 3 ][ 1 ] = LoadTexBMP( "textures/rf_eye.bmp" );
    sparrow_textures[ 3 ][ 2 ] = LoadTexBMP( "textures/rf_beak.bmp" );
    sparrow_textures[ 3 ][ 3 ] = LoadTexBMP( "textures/rf_body.bmp" );
    sparrow_textures[ 3 ][ 4 ] = LoadTexBMP( "textures/rf_twing.bmp" );
    sparrow_textures[ 3 ][ 5 ] = LoadTexBMP( "textures/rf_bwing.bmp" );
    sparrow_textures[ 3 ][ 6 ] = LoadTexBMP( "textures/rf_tail.bmp" );
    // index 4: Junco
    sparrow_textures[ 4 ][ 0 ] = LoadTexBMP( "textures/ju_head.bmp" );
    sparrow_textures[ 4 ][ 1 ] = LoadTexBMP( "textures/ju_eye.bmp" );
    sparrow_textures[ 4 ][ 2 ] = LoadTexBMP( "textures/ju_beak.bmp" );
    sparrow_textures[ 4 ][ 3 ] = LoadTexBMP( "textures/ju_body.bmp" );
    sparrow_textures[ 4 ][ 4 ] = LoadTexBMP( "textures/ju_twing.bmp" );
    sparrow_textures[ 4 ][ 5 ] = LoadTexBMP( "textures/ju_bwing.bmp" );
    sparrow_textures[ 4 ][ 6 ] = LoadTexBMP( "textures/ju_tail.bmp" );
    // index 5: Chickadee
    sparrow_textures[ 5 ][ 0 ] = LoadTexBMP( "textures/ch_head.bmp" );
    sparrow_textures[ 5 ][ 1 ] = LoadTexBMP( "textures/ch_eye.bmp" );
    sparrow_textures[ 5 ][ 2 ] = LoadTexBMP( "textures/ch_beak.bmp" );
    sparrow_textures[ 5 ][ 3 ] = LoadTexBMP( "textures/ch_body.bmp" );
    sparrow_textures[ 5 ][ 4 ] = LoadTexBMP( "textures/ch_twing.bmp" );
    sparrow_textures[ 5 ][ 5 ] = LoadTexBMP( "textures/ch_bwing.bmp" );
    sparrow_textures[ 5 ][ 6 ] = LoadTexBMP( "textures/ch_tail.bmp" );

    // loading crested model textures
    // index 0: northern cardinal
    crested_textures[ 0 ][ 0 ] = LoadTexBMP( "textures/nc_head.bmp" );
    crested_textures[ 0 ][ 1 ] = LoadTexBMP( "textures/nc_crest.bmp" );
    crested_textures[ 0 ][ 2 ] = LoadTexBMP( "textures/nc_eye.bmp" );
    crested_textures[ 0 ][ 3 ] = LoadTexBMP( "textures/nc_beak.bmp" );
    crested_textures[ 0 ][ 4 ] = LoadTexBMP( "textures/nc_body.bmp" );
    crested_textures[ 0 ][ 5 ] = LoadTexBMP( "textures/nc_twing.bmp" );
    crested_textures[ 0 ][ 6 ] = LoadTexBMP( "textures/nc_bwing.bmp" );
    crested_textures[ 0 ][ 7 ] = LoadTexBMP( "textures/nc_tail.bmp" );
    // index 1: Blue Jay
    crested_textures[ 1 ][ 0 ] = LoadTexBMP( "textures/bj_head.bmp" );
    crested_textures[ 1 ][ 1 ] = LoadTexBMP( "textures/bj_crest.bmp" );
    crested_textures[ 1 ][ 2 ] = LoadTexBMP( "textures/bj_eye.bmp" );
    crested_textures[ 1 ][ 3 ] = LoadTexBMP( "textures/bj_beak.bmp" );
    crested_textures[ 1 ][ 4 ] = LoadTexBMP( "textures/bj_body.bmp" );
    crested_textures[ 1 ][ 5 ] = LoadTexBMP( "textures/bj_twing.bmp" );
    crested_textures[ 1 ][ 6 ] = LoadTexBMP( "textures/bj_bwing.bmp" );
    crested_textures[ 1 ][ 7 ] = LoadTexBMP( "textures/bj_tail.bmp" );
    // index 2: Stellar's Jay
    crested_textures[ 2 ][ 0 ] = LoadTexBMP( "textures/sj_head.bmp" );
    crested_textures[ 2 ][ 1 ] = LoadTexBMP( "textures/sj_crest.bmp" );
    crested_textures[ 2 ][ 2 ] = LoadTexBMP( "textures/sj_eye.bmp" );
    crested_textures[ 2 ][ 3 ] = LoadTexBMP( "textures/sj_beak.bmp" );
    crested_textures[ 2 ][ 4 ] = LoadTexBMP( "textures/sj_body.bmp" );
    crested_textures[ 2 ][ 5 ] = LoadTexBMP( "textures/sj_twing.bmp" );
    crested_textures[ 2 ][ 6 ] = LoadTexBMP( "textures/sj_bwing.bmp" );
    crested_textures[ 2 ][ 7 ] = LoadTexBMP( "textures/sj_tail.bmp" );
    // index 3: Cedar Waxwing
    crested_textures[ 3 ][ 0 ] = LoadTexBMP( "textures/ww_head.bmp" );
    crested_textures[ 3 ][ 1 ] = LoadTexBMP( "textures/ww_crest.bmp" );
    crested_textures[ 3 ][ 2 ] = LoadTexBMP( "textures/ww_eye.bmp" );
    crested_textures[ 3 ][ 3 ] = LoadTexBMP( "textures/ww_beak.bmp" );
    crested_textures[ 3 ][ 4 ] = LoadTexBMP( "textures/ww_body.bmp" );
    crested_textures[ 3 ][ 5 ] = LoadTexBMP( "textures/ww_twing.bmp" );
    crested_textures[ 3 ][ 6 ] = LoadTexBMP( "textures/ww_bwing.bmp" );
    crested_textures[ 3 ][ 7 ] = LoadTexBMP( "textures/ww_tail.bmp" );

    // loading owl model textures
    // index 0: Barn Owl
    owl_textures[ 0 ][ 0 ] = LoadTexBMP( "textures/bo_head.bmp" );
    owl_textures[ 0 ][ 1 ] = LoadTexBMP( "textures/bo_beak.bmp" );
    owl_textures[ 0 ][ 2 ] = LoadTexBMP( "textures/bo_body.bmp" );
    owl_textures[ 0 ][ 3 ] = LoadTexBMP( "textures/bo_twing.bmp" );
    owl_textures[ 0 ][ 4 ] = LoadTexBMP( "textures/bo_bwing.bmp" );
    owl_textures[ 0 ][ 5 ] = LoadTexBMP( "textures/bo_tail.bmp" );
    // index 1: Grey Owl
    owl_textures[ 1 ][ 0 ] = LoadTexBMP( "textures/go_head.bmp" );
    owl_textures[ 1 ][ 1 ] = LoadTexBMP( "textures/go_beak.bmp" );
    owl_textures[ 1 ][ 2 ] = LoadTexBMP( "textures/go_body.bmp" );
    owl_textures[ 1 ][ 3 ] = LoadTexBMP( "textures/go_twing.bmp" );
    owl_textures[ 1 ][ 4 ] = LoadTexBMP( "textures/go_bwing.bmp" );
    owl_textures[ 1 ][ 5 ] = LoadTexBMP( "textures/go_tail.bmp" );
    // index 2: Barred Owl˙
    owl_textures[ 2 ][ 0 ] = LoadTexBMP( "textures/ba_head.bmp" );
    owl_textures[ 2 ][ 1 ] = LoadTexBMP( "textures/ba_beak.bmp" );
    owl_textures[ 2 ][ 2 ] = LoadTexBMP( "textures/ba_body.bmp" );
    owl_textures[ 2 ][ 3 ] = LoadTexBMP( "textures/ba_twing.bmp" );
    owl_textures[ 2 ][ 4 ] = LoadTexBMP( "textures/ba_bwing.bmp" );
    owl_textures[ 2 ][ 5 ] = LoadTexBMP( "textures/ba_tail.bmp" );
    
    // camera textures
    camera_textures[ 0 ] = LoadTexBMP( "textures/cam_body.bmp" );
    camera_textures[ 1 ] = LoadTexBMP( "textures/cam_glossy.bmp" );
    camera_textures[ 2 ] = LoadTexBMP( "textures/cam_grip.bmp" );
    camera_textures[ 3 ] = LoadTexBMP( "textures/cam_lens.bmp" );
    camera_textures[ 4 ] = LoadTexBMP( "textures/cam_zoomIn.bmp" );
    camera_textures[ 5 ] = LoadTexBMP( "textures/cam_zoomOut.bmp" );
    camera_textures[ 6 ] = LoadTexBMP( "textures/cam_shareButton.bmp" );
    camera_textures[ 7 ] = LoadTexBMP( "textures/cam_dial.bmp" );

    // scene textures
    setting_textures[ 0 ] = LoadTexBMP( "textures/ground.bmp" );
    setting_textures[ 1 ] = LoadTexBMP( "textures/bark.bmp" );
    setting_textures[ 2 ] = LoadTexBMP( "textures/path.bmp" );
    setting_textures[ 3 ] = LoadTexBMP( "textures/grass.bmp" );
    setting_textures[ 4 ] = LoadTexBMP( "textures/tfeeder.bmp" );
    setting_textures[ 5 ] = LoadTexBMP( "textures/bfeeder_f.bmp" );
    setting_textures[ 6 ] = LoadTexBMP( "textures/bfeeder_e.bmp" );
    setting_textures[ 7 ] = LoadTexBMP( "textures/btree.bmp" );
    setting_textures[ 8 ] = LoadTexBMP( "textures/rock.bmp" );

    // car textures
    car_textures[ 0 ] = LoadTexBMP( "textures/car0.bmp" );
    car_textures[ 1 ] = LoadTexBMP( "textures/car1.bmp" );
    car_textures[ 2 ] = LoadTexBMP( "textures/car2.bmp" );
    car_textures[ 3 ] = LoadTexBMP( "textures/car3.bmp" );
    car_textures[ 4 ] = LoadTexBMP( "textures/car4.bmp" );
    car_textures[ 5 ] = LoadTexBMP( "textures/car5.bmp" );
}

int main( int argc, char* argv[] ) {

    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL );
    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize( windowSizeX, windowSizeY );
    window = glutCreateWindow( "Final Project - Birding Simulator: Devin Noth" );

    // Assign action functions for GLUT to respond to user interaction
    glutDisplayFunc( draw );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( key );
    glutSpecialFunc( special );
    glutIdleFunc( idle );
    glutPassiveMotionFunc( mouse );
    glutMouseFunc( mouseButton );

    // init textures and level 1 birds
    loadTextures();
    loadBirdSpawns();

    // init inner lake bounding spheres
    struct Vec3 vec1 = { 0, 0, 0 };
    struct Sphere sphere1 = { vec1, 50 };
    innerBounds[ 0 ] = sphere1;
    struct Vec3 vec2 = { 47.5, 0, 0 };
    struct Sphere sphere2 = { vec2, 45 };
    innerBounds[ 1 ] = sphere2;
    struct Vec3 vec3 = { -50, 0, 0 };
    struct Sphere sphere3 = { vec3, 42.5 };
    innerBounds[ 2 ] = sphere3;

    // initialize graphics array for changing graphics level
    graphicsIndex = 0;
    gArr[0] = 1;
    gArr[1] = 3;
    gArr[2] = 5;
    gArr[3] = 9;
    gArr[4] = 15;
    glutSetCursor( GLUT_CURSOR_NONE );

    glutMainLoop();
    return 0;
}
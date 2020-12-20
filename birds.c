
#include "CSCIx229.h"

/**
 * Sparrow Model Spawner:
 * Generally smaller in size, has 6 possible bird species
 */
void sparrow( struct Bird bird ) {
    glPushMatrix();
    glTranslated( bird.x, bird.y, bird.z );
    glRotatef( bird.rot, 0, 1, 0 );
    glScalef( bird.scale, bird.scale, bird.scale );

    // head
    sphere( 1.5, 1, 0, 0.75, 1, 0.92, 1, -90, sparrow_textures[ bird.species ][ 0 ], 0, 1, 1 );
    // eyes
    sphere( 2.12, 1.1, 0.3, 0.15, 1, 1, 0.1, 235, sparrow_textures[ bird.species ][ 1 ], 0, 1, 1 );
    sphere( 2.12, 1.1, -0.3, 0.15, 1, 1, 0.1, -55, sparrow_textures[ bird.species ][ 1 ], 0, 1, 1 );
    // beak
    cone( 2.2, 0.95, 0, 0.6, 0.13, -90, 0, 0, 1, sparrow_textures[ bird.species ][ 2 ], 0, 1, 1 );
    
    glPushMatrix();
    glRotated( 105, 0, 0, 1 );
    //under wing
    sphere( 0.2, 0, 0, 1, 0.9, 2, 0.9, 0, sparrow_textures[ bird.species ][ 0 ], 0, 1, 1 );
    // body
    sphere( 0, 0, 0, 1, 0.9, 2, 0.9, 0, sparrow_textures[ bird.species ][ 3 ], 0, 1, 1 );
    // right wing
    sphere( 0.75, 0.5, 0.7, 1, 0.05, 1.5, 0.7, -45, sparrow_textures[ bird.species ][ 4 ], 0, 1, 1 );
    sphere( 0.75, 1.1, 0.7, 1, 0.05, 1.3, 0.55, -45, sparrow_textures[ bird.species ][ 5 ], 0, 1, 1 );
    // left wing
    sphere( 0.75, 0.5, -0.7, 1, 0.05, 1.5, 0.7, 45, sparrow_textures[ bird.species ][ 4 ], 0, 1, 1 );
    sphere( 0.75, 1.1, -0.7, 1, 0.05, 1.3, 0.55, 45, sparrow_textures[ bird.species ][ 5 ], 0, 1, 1 );
    //tail
    sphere( 0.3, 2.6, 0.25, 1, 0.05, 1, 0.33, -35, sparrow_textures[ bird.species ][ 6 ], 0, 1, 1 );
    sphere( 0.3, 2.6, -0.25, 1, 0.05, 1, 0.33, 35, sparrow_textures[ bird.species ][ 6 ], 0, 1, 1 );
    glPopMatrix();

    // left leg
    glColor3f( 0, 0.5, 0.5 );
    cylinder( -0.7, -1, -0.45, 1.1, 0.05, 50, 0.1, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.05, -1.4, -0.5, 0.7, 0.05, 85, 0, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.05, -1.4, -0.7, 0.68, 0.05, 85, 1, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.05, -1.4, -0.3, 0.68, 0.05, 85, -1, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.4, -1.4, -0.5, 0.65, 0.05, -85, 0, 0, 1, leg, 0, 1, 1 );
    glColor3f( 0, 0.8, 0.8 );
    cone( 0.2, -1.42, -0.5, 0.4, 0.05, -100, 0, 0, 1, sparrow_textures[ bird.species ][ 2 ], 0, 1, 1 );
    cone( -0.6, -1.42, -0.5, 0.4, 0.05, -100, 0, 0, -1, sparrow_textures[ bird.species ][ 2 ], 0, 1, 1 );
    cone( 0.1, -1.42, -0.15, 0.4, 0.05, -100, -1, 0, 1, sparrow_textures[ bird.species ][ 2 ], 0, 1, 1 );
    cone( 0.1, -1.42, -0.85, 0.4, 0.05, -100, 1, 0, 1, sparrow_textures[ bird.species ][ 2 ], 0, 1, 1 );

    // right leg
    glColor3f( 0, 0.5, 0.5 );
    cylinder( -0.7, -1, 0.45, 1.1, 0.05, 50, -0.1, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.05, -1.4, 0.5, 0.7, 0.05, 85, 0, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.05, -1.4, 0.7, 0.68, 0.05, 85, -1, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.05, -1.4, 0.3, 0.68, 0.05, 85, 1, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.4, -1.4, 0.5, 0.65, 0.05, -85, 0, 0, 1, leg, 0, 1, 1 );
    glColor3f( 0, 0.8, 0.8 );
    cone( 0.2, -1.42, 0.5, 0.4, 0.05, -100, 0, 0, 1, sparrow_textures[ bird.species ][ 2 ], 0, 1, 1 );
    cone( -0.6, -1.42, 0.5, 0.4, 0.05, -100, 0, 0, -1, sparrow_textures[ bird.species ][ 2 ], 0, 1, 1 );
    cone( 0.1, -1.42, 0.15, 0.4, 0.05, -100, 1, 0, 1, sparrow_textures[ bird.species ][ 2 ], 0, 1, 1 );
    cone( 0.1, -1.42, 0.85, 0.4, 0.05, -100, -1, 0, 1, sparrow_textures[ bird.species ][ 2 ], 0, 1, 1 );
    glPopMatrix();
}

/**
 * Crested Spawner:
 * Spawns medium sized crested birds
 * Has 4 possible species
 */
void crested( struct Bird bird ) {
    glPushMatrix();
    glTranslated( bird.x, bird.y, bird.z );
    glRotatef( bird.rot, 0, 1, 0 );
    glScalef( bird.scale, bird.scale, bird.scale );

    // head
    glPushMatrix();
    glTranslatef( 1.35, 1.2, 0 );
    sphere( 0, 0, 0, 0.7, 1, 1.1, 1, -90, crested_textures[ bird.species ][ 0 ], 0, 1, 1 );
    cone( 0, 0.25, 0, 1, 0.6, 20, 0, 0, 1, crested_textures[ bird.species ][ 1 ], 0, 1, 1 );
    // eyes
    sphere( 0.55, 0.1, 0.4, 0.15, 1, 1, 0.1, 235, crested_textures[ bird.species ][ 2 ], 0, 1, 1 );
    sphere( 0.55, 0.1, -0.4, 0.15, 1, 1, 0.1, -55, crested_textures[ bird.species ][ 2 ], 0, 1, 1 );
    // beak
    cone( 0.65, -0.05, 0, 0.65, 0.25, -90, 0, 0, 1, crested_textures[ bird.species ][ 3 ], 0, 1, 1 );
    glPopMatrix();
    
    glPushMatrix();
    glRotated( 115, 0, 0, 1 );
    //under wing
    sphere( 0.2, 0, 0, 1, 0.9, 2, 0.9, 0, crested_textures[ bird.species ][ 1 ], 0, 1, 1 );
    // body
    sphere( 0, 0, 0, 1, 0.9, 2, 0.9, 0, crested_textures[ bird.species ][ 4 ], 0, 1, 1 );
    // right wing
    sphere( 0.75, 0.5, 0.65, 1, 0.05, 1.5, 0.7, -45, crested_textures[ bird.species ][ 5 ], 0, 1, 1 );
    sphere( 0.75, 1.1, 0.65, 1, 0.05, 1.6, 0.55, -45, crested_textures[ bird.species ][ 6 ], 0, 1, 1 );
    // left wing
    sphere( 0.75, 0.5, -0.65, 1, 0.05, 1.5, 0.7, 45, crested_textures[ bird.species ][ 5 ], 0, 1, 1 );
    sphere( 0.75, 1.1, -0.65, 1, 0.05, 1.6, 0.55, 45, crested_textures[ bird.species ][ 6 ], 0, 1, 1 );
    glPopMatrix();
    //tail
    glPushMatrix();
    glTranslatef( -2.8, -0.5, 0 );
    glRotatef( 80, 0, 0, 1 );
    sphere( 0, 0, 0.25, 1, 0.05, 1.3, 0.33, -35, crested_textures[ bird.species ][ 7 ], 0, 1, 1 );
    sphere( 0, 0, -0.25, 1, 0.05, 1.3, 0.33, 35, crested_textures[ bird.species ][ 7 ], 0, 1, 1 );
    glPopMatrix();

    // left leg
    glColor3f( 0, 0.5, 0.5 );
    cylinder( -0.7, -1, -0.45, 1.1, 0.05, 50, 0.1, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.05, -1.4, -0.5, 0.7, 0.05, 85, 0, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.05, -1.4, -0.7, 0.68, 0.05, 85, 1, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.05, -1.4, -0.3, 0.68, 0.05, 85, -1, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.4, -1.4, -0.5, 0.65, 0.05, -85, 0, 0, 1, leg, 0, 1, 1 );
    glColor3f( 0, 0.8, 0.8 );
    cone( 0.2, -1.42, -0.5, 0.4, 0.05, -100, 0, 0, 1, crested_textures[ bird.species ][ 3 ], 0, 1, 1 );
    cone( -0.6, -1.42, -0.5, 0.4, 0.05, -100, 0, 0, -1, crested_textures[ bird.species ][ 3 ], 0, 1, 1 );
    cone( 0.1, -1.42, -0.15, 0.4, 0.05, -100, -1, 0, 1, crested_textures[ bird.species ][ 3 ], 0, 1, 1 );
    cone( 0.1, -1.42, -0.85, 0.4, 0.05, -100, 1, 0, 1, crested_textures[ bird.species ][ 3 ], 0, 1, 1 );

    // right leg
    glColor3f( 0, 0.5, 0.5 );
    cylinder( -0.7, -1, 0.45, 1.1, 0.05, 50, -0.1, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.05, -1.4, 0.5, 0.7, 0.05, 85, 0, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.05, -1.4, 0.7, 0.68, 0.05, 85, -1, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.05, -1.4, 0.3, 0.68, 0.05, 85, 1, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.4, -1.4, 0.5, 0.65, 0.05, -85, 0, 0, 1, leg, 0, 1, 1 );
    glColor3f( 0, 0.8, 0.8 );
    cone( 0.2, -1.42, 0.5, 0.4, 0.05, -100, 0, 0, 1, crested_textures[ bird.species ][ 3 ], 0, 1, 1 );
    cone( -0.6, -1.42, 0.5, 0.4, 0.05, -100, 0, 0, -1, crested_textures[ bird.species ][ 3 ], 0, 1, 1 );
    cone( 0.1, -1.42, 0.15, 0.4, 0.05, -100, 1, 0, 1, crested_textures[ bird.species ][ 3 ], 0, 1, 1 );
    cone( 0.1, -1.42, 0.85, 0.4, 0.05, -100, -1, 0, 1, crested_textures[ bird.species ][ 3 ], 0, 1, 1 );
    glPopMatrix();
}

/**
 * Owl spawner:
 * Large size bird models. Only appears in night level
 * 3 possible species
 */
void owl( struct Bird bird ) {
    glPushMatrix();
    glTranslated( bird.x, bird.y, bird.z );
    glRotatef( bird.rot, 0, 1, 0 );
    glScalef( bird.scale, bird.scale, bird.scale );

    // head
    glPushMatrix();
    glTranslatef( 0.4, 1.8, 0 );
    sphere( 0, 0, 0, 0.85, 1, 1, 0.85, -90, owl_textures[ bird.species ][ 0 ], 0, 1, 1 );
    glPopMatrix();
    
    glPushMatrix();
    glRotated( 170, 0, 0, 1 );
    //under wing
    sphere( 0.2, 0, 0, 1, 1, 1.75, 1, 0, owl_textures[ bird.species ][ 2 ], 0, 1, 1 );
    // body
    sphere( 0, 0, 0, 1, 1, 1.75, 1, 0, owl_textures[ bird.species ][ 2 ], 0, 1, 1 );
    // right wing
    sphere( 0.8, 0.25, 0.8, 1, 0.05, 1.5, 0.7, -45, owl_textures[ bird.species ][ 3 ], 0, 1, 1 );
    sphere( 0.8, 1, 0.8, 1, 0.05, 1.6, 0.55, -45, owl_textures[ bird.species ][ 4 ], 0, 1, 1 );
    // left wing
    sphere( 0.8, 0.25, -0.8, 1, 0.05, 1.5, 0.7, 45, owl_textures[ bird.species ][ 3 ], 0, 1, 1 );
    sphere( 0.8, 1, -0.8, 1, 0.05, 1.6, 0.55, 45, owl_textures[ bird.species ][ 4 ], 0, 1, 1 );
    glPopMatrix();
    //tail
    glPushMatrix();
    glTranslatef( -1, -1.5, 0 );
    glRotatef( 170, 0, 0, 1 );
    sphere( 0, 0, 0.25, 1, 0.05, 1, 0.33, -35, owl_textures[ bird.species ][ 5 ], 0, 1, 1 );
    sphere( 0, 0, -0.25, 1, 0.05, 1, 0.33, 35, owl_textures[ bird.species ][ 5 ], 0, 1, 1 );
    glPopMatrix();

    // left leg
    glPushMatrix();
    glTranslatef( 0.2, -0.6, 0 );
    glColor3f( 0, 0.5, 0.5 );
    cylinder( -0.35, -0.8, -0.5, 1.1, 0.05, 5, 0.1, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.05, -1.4, -0.5, 0.7, 0.05, 85, 0, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.05, -1.4, -0.7, 0.68, 0.05, 85, 1, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.05, -1.4, -0.3, 0.68, 0.05, 85, -1, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.4, -1.4, -0.5, 0.65, 0.05, -85, 0, 0, 1, leg, 0, 1, 1 );
    glColor3f( 0, 0.8, 0.8 );
    cone( 0.2, -1.42, -0.5, 0.4, 0.05, -100, 0, 0, 1, owl_textures[ bird.species ][ 1 ], 0, 1, 1 );
    cone( -0.6, -1.42, -0.5, 0.4, 0.05, -100, 0, 0, -1, owl_textures[ bird.species ][ 1 ], 0, 1, 1 );
    cone( 0.1, -1.42, -0.15, 0.4, 0.05, -100, -1, 0, 1, owl_textures[ bird.species ][ 1 ], 0, 1, 1 );
    cone( 0.1, -1.42, -0.85, 0.4, 0.05, -100, 1, 0, 1, owl_textures[ bird.species ][ 1 ], 0, 1, 1 );

    // right leg
    glColor3f( 0, 0.5, 0.5 );
    cylinder( -0.35, -0.8, 0.5, 1.1, 0.05, 5, -0.1, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.05, -1.4, 0.5, 0.7, 0.05, 85, 0, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.05, -1.4, 0.7, 0.68, 0.05, 85, -1, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.05, -1.4, 0.3, 0.68, 0.05, 85, 1, 0, 1, leg, 0, 1, 1 );
    cylinder( -0.4, -1.4, 0.5, 0.65, 0.05, -85, 0, 0, 1, leg, 0, 1, 1 );
    glColor3f( 0, 0.8, 0.8 );
    cone( 0.2, -1.42, 0.5, 0.4, 0.05, -100, 0, 0, 1, owl_textures[ bird.species ][ 1 ], 0, 1, 1 );
    cone( -0.6, -1.42, 0.5, 0.4, 0.05, -100, 0, 0, -1, owl_textures[ bird.species ][ 1 ], 0, 1, 1 );
    cone( 0.1, -1.42, 0.15, 0.4, 0.05, -100, 1, 0, 1, owl_textures[ bird.species ][ 1 ], 0, 1, 1 );
    cone( 0.1, -1.42, 0.85, 0.4, 0.05, -100, -1, 0, 1, owl_textures[ bird.species ][ 1 ], 0, 1, 1 );
    glPopMatrix();
    glPopMatrix();
}
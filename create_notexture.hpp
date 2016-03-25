#include "gl_framework.cpp"
#include "shader_util.hpp"
#include "SOIL/SOIL.h"
#define TORSO_HEIGHT 1.0
#define UPPER_ARM_HEIGHT 1.0f
#define LOWER_ARM_HEIGHT 1.0f
#define UPPER_LEG_RADIUS  0.5
#define LOWER_LEG_RADIUS  0.5



#define LOWER_LEG_LENGTH  0.3f
#define UPPER_LEG_LENGTH  0.3f
#define LOWER_LEG_HEIGHT 0.6f
#define UPPER_LEG_HEIGHT 0.6f
#define TOE_POINT -0.2f
#define TORSO_RADIUS 1.0f
#define TORSO_LENGTH 1.4f
#define TORSO_START_WIDTH 0.1f
#define UPPER_LEG_START_WIDTH 0.5f
#define LOWER_LEG_START_WIDTH 0.4f
#define UPPER_LEG_FINAL_WIDTH 0.6f


#define UPPER_ARM_RADIUS  0.5
#define LOWER_ARM_RADIUS  0.5
#define HEAD_HEIGHT 1.5
#define HEAD_RADIUS 1.0
#define NEW_PELVIS_VERTICAL_RADIUS 0.5
#define NEW_PELVIS_VERTICAL_HEIGHT 0.2

#define NEW_PELVIS_HORIZONTAL_RADIUS 0.2
#define NEW_PELVIS_HORIZONTAL_HEIGHT 0.2
#define BICEPS_HEIGHT 0.5f
#define BICEPS_RADIUS 0.2f


#define torso      1 
#define pelvis      2
#define right_upper_leg   3
#define left_upper_leg    4
#define right_upper_arm   5
#define left_upper_arm    6
#define right_lower_leg 7
#define left_lower_leg  8
#define right_lower_arm   9
#define left_lower_arm    10
#define head      11

#define new_torso      12
#define new_left_lower_leg      13
#define new_left_upper_leg      14


#define new_left_lower_arm      15
#define new_left_upper_arm      16
#define new_cannon 17
#define new_left_thigh 18
#define new_right_thigh 19
#define new_head 20
#define new_frame 21
#define new_hand 22
#define new_env 23

#define CANNON_INNER_RADIUS  0.15
#define CANNON_OUTER_RADIUS  0.2
#define CANNON_INNER_HEIGHT  4.0
#define CANNON_OUTER_HEIGHT  3.0
#define NEW_THIGH_HEIGHT 4.0
#define NEW_THIGH_RADIUS 1.0
static GLfloat theta[11] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,
        180.0,0.0,180.0,0.0}; /* initial joint angles */
static GLint angle = 2;
static GLfloat armScale=0.4f, legScale=0.2f;
//material definitions


unsigned int texture[10];

GLfloat mat_specularWHITE[] ={255.0,255.0,255.0,1.0};
GLfloat mat_ambientWHITE[] ={255.0,255.0,255.0,1.0};
GLfloat mat_diffuseWHITE[] ={255.0,255.0,255.0,1.0};
GLfloat mat_shininessWHITE[] ={128.0 * 0.4};


GLfloat mat_specularCOLOURLESS[] ={1.0,1.0,1.0 ,1.0};
GLfloat mat_ambientCOLOURLESS[] ={1.0,1.0,1.0 ,1.0};
GLfloat mat_diffuseCOLOURLESS[] ={1.0,1.0,1.0 ,1.0};
GLfloat mat_shininessCOLOURLESS[] ={128.0 * 0.4};

GLfloat mat_specularGRAY[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientGRAY[] ={0.5,0.5,0.5,1.0};
GLfloat mat_diffuseGRAY[] ={0.50,0.50,0.50,1.0};
GLfloat mat_shininessGRAY[] ={128.0 * 0.6};

GLfloat mat_specularBLUE[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientBLUE[] ={0,0,1,1.0};
GLfloat mat_diffuseBLUE[] ={0.50,0.50,0.50,1.0};
GLfloat mat_shininessBLUE[] ={128.0 };

GLfloat mat_specularGREEN[] ={0.633, 0.727811, 0.633,1.0};
GLfloat mat_ambientGREEN[] ={0.0215, 0.1745, 0.0215,1.0};
GLfloat mat_diffuseGREEN[] ={0.07568, 0.61424, 0.07568,1.0};
GLfloat mat_shininessGREEN[] ={128.0};

GLfloat mat_specularYELLOW[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientYELLOW[] ={1,1,0,1.0};
GLfloat mat_diffuseYELLOW[] ={0.50,0.50,0.50,1.0};
GLfloat mat_shininessYELLOW[] ={128.0};

GLfloat mat_specularRED[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientRED[] ={1.0,0.0,0.0,1.0};
GLfloat mat_diffuseRED[] ={0.50,0.50,0.50,1.0};
GLfloat mat_shininessRED[] ={128.0};
int env=24;
//Quadric Objetcs
GLUquadricObj *t, *h, *lua, *lla, *rua, *rla, *lll, *rll, *rul, *lul, *cul, *lt, *rt, *np, *nhand,*bi;

double size=1.0;

void SetMaterial(GLfloat spec[], GLfloat amb[], GLfloat diff[], GLfloat shin[])
{

  glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
  glMaterialfv(GL_FRONT, GL_SHININESS, shin);
  glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
}
void create_new_env()
{
glNewList(new_env,GL_COMPILE);
glPushMatrix();

//glRotatef(-90.0, 1.0, 0.0, 0.0);
glScalef(env*armScale,env*armScale,env*armScale);

glBegin(GL_QUADS); 
SetMaterial(mat_specularCOLOURLESS, mat_ambientCOLOURLESS, mat_diffuseCOLOURLESS, mat_shininessCOLOURLESS);
glNormal3f(0,-1,0);
glVertex3f( 0.5f,-0.5f, 0.5f);          // Top Right Of The Quad (Bottom)
glVertex3f(-0.5f,-0.5f, 0.5f);          // Top Left Of The Quad (Bottom) 
glVertex3f(-0.5f,-0.5f,-0.5f);          // Bottom Left Of The Quad (Bottom)
glVertex3f( 0.5f,-0.5f,-0.5f);          // Bottom Right Of The Quad (Bottom)*/ 
glEnd();

glNormal3f(0,1,0);
glVertex3f( 0.5f, 0.5f,-0.5f);          // Top Right Of The Quad (Top)
glVertex3f(-0.5f, 0.5f,-0.5f);          // Top Left Of The Quad (Top) 
glVertex3f(-0.5f, 0.5f, 0.5f);          // Bottom Left Of The Quad (Top)
glVertex3f( 0.5f, 0.5f, 0.5f);          // Bottom Right Of The Quad (Top) 
//SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);

// SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED);
glNormal3f(0,0,1);
//SetMaterial(mat_specularRED, mat_ambientGREEN, mat_diffuseGREEN, mat_shininessGREEN);
glVertex3f( 0.5f, 0.5f, 0.5f);          // Top Right Of The Quad (Front)
glVertex3f(-0.5f, 0.5f, 0.5f);          // Top Left Of The Quad (Front) 
glVertex3f(-0.5f,-0.5f, 0.5f);          // Bottom Left Of The Quad (Front)
glVertex3f( 0.5f,-0.5f, 0.5f);          // Bottom Right Of The Quad (Front) 
//SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
//std::cout<<"Haaiu"<<std::endl;
glNormal3f(0,0,-1);
glVertex3f( 0.5f,-0.5f,-0.5f);          // Bottom Left Of The Quad (Back)
glVertex3f(-0.5f,-0.5f,-0.5f);          // Bottom Right Of The Quad (Back) 
glVertex3f(-0.5f, 0.5f,-0.5f);          // Top Right Of The Quad (Back)
glVertex3f( 0.5f, 0.5f,-0.5f);          // Top Left Of The Quad (Back) 
//SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
/*glNormal3f(-1,0,0);
glVertex3f(-0.5f, 0.5f, 0.5f);          // Top Right Of The Quad (Left)
glVertex3f(-0.5f, 0.5f,-0.5f);          // Top Left Of The Quad (Left) 
glVertex3f(-0.5f,-0.5f,-0.5f);          // Bottom Left Of The Quad (Left)
glVertex3f(-0.5f,-0.5f, 0.5f);          // Bottom Right Of The Quad (Left) 
//SetMaterial(mat_specularGREEN, mat_ambientGREEN, mat_diffuseGREEN, mat_shininessGREEN);*/
glNormal3f(1,0,0);
glVertex3f( 0.5f, 0.5f,-0.5f);          // Top Right Of The Quad (Right)
glVertex3f( 0.5f, 0.5f, 0.5f);          // Top Left Of The Quad (Right) 
glVertex3f( 0.5f,-0.5f, 0.5f);          // Bottom Left Of The Quad (Right)
glVertex3f( 0.5f,-0.5f,-0.5f);          // Bottom Right Of The Quad (Right)*/ 
glEnd();

                        // Done Drawing The Quad*/
// gluCylinder(lua,UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);
glPopMatrix();
glEndList();
}
void create_new_pelvis()
{
  glPushMatrix();
  SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED);
  glTranslatef(CANNON_OUTER_RADIUS,-0.1,-0.2);
  glRotatef(180.0, 0.0, 1.0, 0.0);
//glRotatef(-90.0, 0.0, 1.0, 0.0);
//aglScalef(0.1,0.1,0.1);
  gluCylinder(np, NEW_PELVIS_VERTICAL_RADIUS, 0.2*NEW_PELVIS_VERTICAL_RADIUS, NEW_PELVIS_VERTICAL_HEIGHT,10,10);
  
  glPopMatrix();
  
  glPushMatrix();
  SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED);
  glTranslatef(CANNON_OUTER_RADIUS,-0.1,-0.2);
//glRotatef(-90.0, 0.0, 1.0, 0.0);
  glScalef(0.1,0.1,0.1);
//glTranslatef(-NEW_PELVIS_HEIGHT/2,0,0);
  gluCylinder(np, NEW_PELVIS_HORIZONTAL_RADIUS, NEW_PELVIS_HORIZONTAL_RADIUS, NEW_PELVIS_HORIZONTAL_HEIGHT,10,10);
  glPopMatrix();
}


void create_new_torso()
{

glNewList(new_torso,GL_COMPILE);
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, texture[0]);  
  glBegin(GL_QUADS);

  SetMaterial(mat_specularBLUE, mat_ambientBLUE, mat_diffuseBLUE, mat_shininessBLUE);
glVertex3f( (TORSO_LENGTH) /2, 0.0f, TORSO_HEIGHT ); //vertex 4
glVertex3f( (TORSO_LENGTH) /2, LOWER_LEG_START_WIDTH, TORSO_HEIGHT ); //vertex 3 
glVertex3f( (TORSO_LENGTH) /2, TORSO_START_WIDTH, 0.0f ); //vertex 3
glVertex3f( (TORSO_LENGTH) /2, 0.0f, 0.0f ); //vertex 3 

//SetMaterial(mat_specularBLUE, mat_ambientBLUE, mat_diffuseBLUE, mat_shininessBLUE);


glVertex3f( (TORSO_LENGTH) /2, TORSO_START_WIDTH, 0.0f ); //vertex 3
glVertex3f( (TORSO_LENGTH) /2, 0.0f, 0.0f ); //vertex 3 
glVertex3f( -(TORSO_LENGTH) /2, 0.0f, 0.0f ); //vertex 3
glVertex3f( -(TORSO_LENGTH) /2, TORSO_START_WIDTH, 0.0f ); //vertex 3 

//SetMaterial(mat_specularBLUE, mat_ambientBLUE, mat_diffuseBLUE, mat_shininessBLUE);
glVertex3f( (TORSO_LENGTH) /2,LOWER_LEG_START_WIDTH , TORSO_HEIGHT ); //vertex 3
glVertex3f( (TORSO_LENGTH) /2, 0.0f, TORSO_HEIGHT ); //vertex 3 
glVertex3f( -(TORSO_LENGTH) /2, 0.0f, TORSO_HEIGHT ); //vertex 3
glVertex3f( -(TORSO_LENGTH) /2, LOWER_LEG_START_WIDTH, TORSO_HEIGHT ); //vertex 3 

//SetMaterial(mat_specularBLUE, mat_ambientBLUE, mat_diffuseBLUE, mat_shininessBLUE);

glVertex3f( (TORSO_LENGTH) /2, 0.0 , TORSO_HEIGHT ); //vertex 3
glVertex3f( (TORSO_LENGTH) /2, 0.0f, 0.0 ); //vertex 3 
glVertex3f( -(TORSO_LENGTH) /2, 0.0f, 0.0 ); //vertex 3
glVertex3f( -(TORSO_LENGTH) /2, 0.0, TORSO_HEIGHT ); //vertex 3 

//SetMaterial(mat_specularBLUE, mat_ambientBLUE, mat_diffuseBLUE, mat_shininessBLUE);
glTexCoord2f(0.0f, 0.0f);  glVertex3f( -(TORSO_LENGTH) /2, TORSO_START_WIDTH, 0.0f ); //vertex 3
glTexCoord2f(0.5f, 0.0f);glVertex3f( -(TORSO_LENGTH) /2, LOWER_LEG_START_WIDTH, TORSO_HEIGHT ); //vertex 3
glTexCoord2f(0.5f, 0.5f);glVertex3f(  (TORSO_LENGTH) /2, LOWER_LEG_START_WIDTH, TORSO_HEIGHT ); //vertex 2  
glTexCoord2f(0.0f, 0.5f);glVertex3f(  (TORSO_LENGTH) /2, TORSO_START_WIDTH, 0.0 ); //vertex 1 

//SetMaterial(mat_specularBLUE, mat_ambientBLUE, mat_diffuseBLUE, mat_shininessBLUE);

glVertex3f( -(TORSO_LENGTH) /2, 0.0f, 0.0f ); //vertex 3
glVertex3f( -(TORSO_LENGTH) /2, TORSO_START_WIDTH, 0.0f ); //vertex 3 
glVertex3f( -(TORSO_LENGTH) /2, LOWER_LEG_START_WIDTH, TORSO_HEIGHT ); //vertex 2  
glVertex3f( -(TORSO_LENGTH) /2, 0.0f, TORSO_HEIGHT ); //vertex 1 

glEnd();

glEndList();
}

void create_new_left_lower_leg()
{
glNewList(new_left_lower_leg,GL_COMPILE );
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, texture[0]);  

glBegin(GL_QUADS);
glRotatef(90,1,0,0);
glColor4f(0.5, 0.0, 0.0, 0.5);
//Front
glNormal3f(0,0,1);
glTexCoord2f(0.0f, 0.0f); glVertex3f( TOE_POINT, 0.0f, 0.0f ); //vertex 1
glTexCoord2f(0.5f, 0.0f);glVertex3f( LOWER_LEG_LENGTH, 0.0f, 0.0f ); //vertex 4
glTexCoord2f(0.5f, 0.5f); glVertex3f( LOWER_LEG_LENGTH, LOWER_LEG_START_WIDTH, 0.0f ); //vertex 3
 glTexCoord2f(0.0f, 0.5f);glVertex3f( TOE_POINT, LOWER_LEG_START_WIDTH, 0.0f ); //vertex 2
 
//Along the side
 SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
 glNormal3f(1,0,0);
glVertex3f( LOWER_LEG_LENGTH, LOWER_LEG_START_WIDTH, 0.0f ); //vertex 3
glVertex3f( LOWER_LEG_LENGTH, 0.0f, 0.0f ); //vertex 4 
glVertex3f( LOWER_LEG_LENGTH, -0.0f, LOWER_LEG_HEIGHT );
glVertex3f( LOWER_LEG_LENGTH,  UPPER_LEG_START_WIDTH, LOWER_LEG_HEIGHT ); 
//Back
SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
glNormal3f(0,0,-1);
glVertex3f( LOWER_LEG_LENGTH,  UPPER_LEG_START_WIDTH, LOWER_LEG_HEIGHT );
glVertex3f( LOWER_LEG_LENGTH, -0.0f, LOWER_LEG_HEIGHT ); 
glVertex3f( 0.0f, -0.0f, LOWER_LEG_HEIGHT );
glVertex3f( 0.0f,  UPPER_LEG_START_WIDTH, LOWER_LEG_HEIGHT ); 

SetMaterial(mat_specularGREEN,mat_ambientGREEN, mat_diffuseGREEN, mat_shininessGREEN);
glNormal3f(-1,0,0);
glVertex3f( 0.0f,  UPPER_LEG_START_WIDTH, LOWER_LEG_HEIGHT );
glVertex3f( 0.0f, -0.0f, LOWER_LEG_HEIGHT ); 
glVertex3f( 0.0f, -0.0f, 3*LOWER_LEG_HEIGHT /5 );
glVertex3f( 0.0f,  UPPER_LEG_START_WIDTH, 3*LOWER_LEG_HEIGHT /5); 
//Angled part of foot
SetMaterial(mat_specularBLUE, mat_ambientBLUE, mat_diffuseBLUE, mat_shininessBLUE);
glNormal3f(0,0,1);
glTexCoord2f(0.5f, 0.0f);glVertex3f( 0.0f, 0.0f, 3*LOWER_LEG_HEIGHT /5);
glVertex3f( 0.0f,  UPPER_LEG_START_WIDTH, 3*LOWER_LEG_HEIGHT /5); 
glVertex3f( TOE_POINT, LOWER_LEG_START_WIDTH, 2*LOWER_LEG_HEIGHT /5 );
glVertex3f( TOE_POINT, 0.0f, 2*LOWER_LEG_HEIGHT /5 ); 
//TOes

glNormal3f(1,0,0);
SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
glVertex3f( TOE_POINT, 0.0f, 2*LOWER_LEG_HEIGHT /5 );
glVertex3f( TOE_POINT, LOWER_LEG_START_WIDTH, 2*LOWER_LEG_HEIGHT /5 ); 
glVertex3f( TOE_POINT, LOWER_LEG_START_WIDTH, 0.0f );
glVertex3f( TOE_POINT, 0.0f, 0.0f ); 

SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED);
glNormal3f(0,1,0);
glVertex3f( TOE_POINT, LOWER_LEG_START_WIDTH, 0.0f);
glVertex3f( TOE_POINT, LOWER_LEG_START_WIDTH, 2*LOWER_LEG_HEIGHT /5 ); 
glVertex3f( LOWER_LEG_LENGTH, LOWER_LEG_START_WIDTH, 2*LOWER_LEG_HEIGHT /5 );
glVertex3f( LOWER_LEG_LENGTH, LOWER_LEG_START_WIDTH, 0.0f ); 

glNormal3f(0,1,0);
glVertex3f( LOWER_LEG_LENGTH, LOWER_LEG_START_WIDTH, 2*LOWER_LEG_HEIGHT /5 );
glVertex3f( TOE_POINT, LOWER_LEG_START_WIDTH, 2*LOWER_LEG_HEIGHT /5 ); 
glVertex3f( 0.0f, UPPER_LEG_START_WIDTH, 3*LOWER_LEG_HEIGHT /5 );
glVertex3f( LOWER_LEG_LENGTH, UPPER_LEG_START_WIDTH, 3*LOWER_LEG_HEIGHT /5  ); 

glNormal3f(0,1,0);
glVertex3f( 0.0f, UPPER_LEG_START_WIDTH, 3*LOWER_LEG_HEIGHT/5);
glVertex3f( 0.0f, UPPER_LEG_START_WIDTH, LOWER_LEG_HEIGHT); 
glVertex3f( LOWER_LEG_LENGTH, UPPER_LEG_START_WIDTH, LOWER_LEG_HEIGHT  );
glVertex3f( LOWER_LEG_LENGTH, UPPER_LEG_START_WIDTH, 3*LOWER_LEG_HEIGHT /5 ); 
glEnd();

glEndList();
}
void create_new_left_upper_leg()
{
glNewList(new_left_upper_leg,GL_COMPILE);
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, texture[0]); 
glBegin(GL_QUADS);

SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED); 
glVertex3f( UPPER_LEG_LENGTH,  UPPER_LEG_START_WIDTH, 0.0f );
glVertex3f( UPPER_LEG_LENGTH, -0.0f, 0.0f ); 
glVertex3f( 0.0f, -0.0f, 0.0f );
glVertex3f( 0.0f,  UPPER_LEG_START_WIDTH, 0.0f ); 

//SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED); 
glVertex3f( UPPER_LEG_LENGTH,  UPPER_LEG_START_WIDTH, 0.0f );
glVertex3f( 0.0f, UPPER_LEG_START_WIDTH, 0.0f ); 
glVertex3f( 0.0f, UPPER_LEG_FINAL_WIDTH, UPPER_LEG_HEIGHT );
glVertex3f(UPPER_LEG_LENGTH,  UPPER_LEG_FINAL_WIDTH, UPPER_LEG_HEIGHT ); 

//SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED); 
glVertex3f( UPPER_LEG_LENGTH,  0.0f, 0.0f );
glVertex3f( 0.0f,  0.0f, 0.0f ); 
glVertex3f( 0.0f,  0.0f, UPPER_LEG_HEIGHT );
glVertex3f(UPPER_LEG_LENGTH,   0.0f, UPPER_LEG_HEIGHT ); 

//SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED); 
glVertex3f( UPPER_LEG_LENGTH,  UPPER_LEG_START_WIDTH, 0.0f );
glVertex3f( UPPER_LEG_LENGTH, -0.0f, 0.0f ); 
glVertex3f( UPPER_LEG_LENGTH, -0.0f, UPPER_LEG_HEIGHT );
glVertex3f( UPPER_LEG_LENGTH,  UPPER_LEG_FINAL_WIDTH, UPPER_LEG_HEIGHT ); 

//SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED); 
glVertex3f( UPPER_LEG_LENGTH, -0.0f, UPPER_LEG_HEIGHT );
glVertex3f( UPPER_LEG_LENGTH,  UPPER_LEG_FINAL_WIDTH, UPPER_LEG_HEIGHT ); 
glVertex3f( 0.0f,  UPPER_LEG_FINAL_WIDTH, UPPER_LEG_HEIGHT );
glVertex3f( 0.0f, -0.0f, UPPER_LEG_HEIGHT ); 
SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED);
glVertex3f( 0.0f,  UPPER_LEG_FINAL_WIDTH, UPPER_LEG_HEIGHT );
glVertex3f( 0.0f, -0.0f, UPPER_LEG_HEIGHT ); 
glVertex3f( 0.0f, -0.0f, 0.0f );
glVertex3f( 0.0f,  UPPER_LEG_START_WIDTH, 0.0f ); 
glEnd();


glEndList();
}
void create_new_frame()
{
glNewList(new_frame,GL_COMPILE );
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, texture[0]); 
glBegin(GL_QUADS);
glRotatef(90,1,0,0);
glColor4f(0.5, 0.0, 0.0, 0.5);
//Torso
glNormal3f(0,0,1);
SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
glVertex3f( (TORSO_LENGTH) /2,LOWER_LEG_START_WIDTH , TORSO_HEIGHT ); //vertex 3
glVertex3f( (TORSO_LENGTH) /2, 0.0f, TORSO_HEIGHT ); //vertex 3  
glVertex3f( -(TORSO_LENGTH) /2, 0.0f, TORSO_HEIGHT ); //vertex 3
glVertex3f( -(TORSO_LENGTH) /2, LOWER_LEG_START_WIDTH, TORSO_HEIGHT ); //vertex 3*/  

//Left
// SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
glNormal3f(1,0,0);
glVertex3f( (TORSO_LENGTH) /2, 0.0f, TORSO_HEIGHT ); //vertex 3
glVertex3f( (TORSO_LENGTH) /2, LOWER_LEG_START_WIDTH, TORSO_HEIGHT ); //vertex 4  
glVertex3f((TORSO_LENGTH) /2, UPPER_LEG_START_WIDTH, TORSO_HEIGHT + LOWER_LEG_HEIGHT );
glVertex3f( (TORSO_LENGTH) /2,  0.0, TORSO_HEIGHT + LOWER_LEG_HEIGHT );  

glVertex3f( (TORSO_LENGTH) /2,  0.0, TORSO_HEIGHT + LOWER_LEG_HEIGHT );
glVertex3f((TORSO_LENGTH) /2, UPPER_LEG_START_WIDTH, TORSO_HEIGHT + LOWER_LEG_HEIGHT );  
glVertex3f((TORSO_LENGTH) /2, UPPER_LEG_FINAL_WIDTH, TORSO_HEIGHT + LOWER_LEG_HEIGHT + UPPER_LEG_HEIGHT );
glVertex3f( (TORSO_LENGTH) /2,  0.0, TORSO_HEIGHT + LOWER_LEG_HEIGHT + UPPER_LEG_HEIGHT );  

//Right
// SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
glNormal3f(1,0,0);
glVertex3f( -(TORSO_LENGTH) /2, 0.0f, TORSO_HEIGHT ); //vertex 3
glVertex3f( -(TORSO_LENGTH) /2, LOWER_LEG_START_WIDTH, TORSO_HEIGHT ); //vertex 4  
glVertex3f(-(TORSO_LENGTH) /2, UPPER_LEG_START_WIDTH, TORSO_HEIGHT + LOWER_LEG_HEIGHT );
glVertex3f( -(TORSO_LENGTH) /2,  0.0, TORSO_HEIGHT + LOWER_LEG_HEIGHT );  

glVertex3f( -(TORSO_LENGTH) /2,  0.0, TORSO_HEIGHT + LOWER_LEG_HEIGHT );
glVertex3f(-(TORSO_LENGTH) /2, UPPER_LEG_START_WIDTH, TORSO_HEIGHT + LOWER_LEG_HEIGHT );  
glVertex3f(-(TORSO_LENGTH) /2, UPPER_LEG_FINAL_WIDTH, TORSO_HEIGHT + LOWER_LEG_HEIGHT + UPPER_LEG_HEIGHT );
glVertex3f( -(TORSO_LENGTH) /2,  0.0, TORSO_HEIGHT + LOWER_LEG_HEIGHT + UPPER_LEG_HEIGHT );  


//Back
// SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
glNormal3f(1,0,0);
glVertex3f( (TORSO_LENGTH) /2,  0.0, TORSO_HEIGHT + LOWER_LEG_HEIGHT + UPPER_LEG_HEIGHT );
glVertex3f(-(TORSO_LENGTH) /2, 0.0, TORSO_HEIGHT + LOWER_LEG_HEIGHT + UPPER_LEG_HEIGHT);  
glVertex3f(-(TORSO_LENGTH) /2, UPPER_LEG_FINAL_WIDTH, TORSO_HEIGHT + LOWER_LEG_HEIGHT + UPPER_LEG_HEIGHT );
glVertex3f( (TORSO_LENGTH) /2,  UPPER_LEG_FINAL_WIDTH, TORSO_HEIGHT + LOWER_LEG_HEIGHT + UPPER_LEG_HEIGHT );  

glEnd();


glEndList();
}



void create_new_left_upper_arm()
{
glNewList(new_left_upper_arm,GL_COMPILE);
glPushMatrix();

//glRotatef(-90.0, 1.0, 0.0, 0.0);
glScalef(armScale,armScale,armScale);
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, texture[0]); 
glBegin(GL_QUADS); 
SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
glNormal3f(0,1,0);
glVertex3f( 0.5f, 0.5f,-0.5f);          // Top Right Of The Quad (Top)
glVertex3f(-0.5f, 0.5f,-0.5f);          // Top Left Of The Quad (Top) 
glVertex3f(-0.5f, 0.5f, 0.5f);          // Bottom Left Of The Quad (Top)
glVertex3f( 0.5f, 0.5f, 0.5f);          // Bottom Right Of The Quad (Top) 
// SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
glNormal3f(0,-1,0);
glVertex3f( 0.5f,-0.5f, 0.5f);          // Top Right Of The Quad (Bottom)
glVertex3f(-0.5f,-0.5f, 0.5f);          // Top Left Of The Quad (Bottom) 
glVertex3f(-0.5f,-0.5f,-0.5f);          // Bottom Left Of The Quad (Bottom)
glVertex3f( 0.5f,-0.5f,-0.5f);          // Bottom Right Of The Quad (Bottom) 
// SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED);
glNormal3f(0,0,1);
// SetMaterial(mat_specularRED, mat_ambientGREEN, mat_diffuseGREEN, mat_shininessGREEN);
glVertex3f( 0.5f, 0.5f, 0.5f);          // Top Right Of The Quad (Front)
glVertex3f(-0.5f, 0.5f, 0.5f);          // Top Left Of The Quad (Front) 
glVertex3f(-0.5f,-0.5f, 0.5f);          // Bottom Left Of The Quad (Front)
glVertex3f( 0.5f,-0.5f, 0.5f);          // Bottom Right Of The Quad (Front) 
//SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
//std::cout<<"Haaiu"<<std::endl;
glNormal3f(0,0,-1);
glVertex3f( 0.5f,-0.5f,-0.5f);          // Bottom Left Of The Quad (Back)
glVertex3f(-0.5f,-0.5f,-0.5f);          // Bottom Right Of The Quad (Back) 
glVertex3f(-0.5f, 0.5f,-0.5f);          // Top Right Of The Quad (Back)
glVertex3f( 0.5f, 0.5f,-0.5f);          // Top Left Of The Quad (Back) 
// SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
glNormal3f(-1,0,0);
glVertex3f(-0.5f, 0.5f, 0.5f);          // Top Right Of The Quad (Left)
glVertex3f(-0.5f, 0.5f,-0.5f);          // Top Left Of The Quad (Left) 
glVertex3f(-0.5f,-0.5f,-0.5f);          // Bottom Left Of The Quad (Left)
glVertex3f(-0.5f,-0.5f, 0.5f);          // Bottom Right Of The Quad (Left) 
// SetMaterial(mat_specularGREEN, mat_ambientGREEN, mat_diffuseGREEN, mat_shininessGREEN);
glNormal3f(1,0,0);
glVertex3f( 0.5f, 0.5f,-0.5f);          // Top Right Of The Quad (Right)
glVertex3f( 0.5f, 0.5f, 0.5f);          // Top Left Of The Quad (Right) 
glVertex3f( 0.5f,-0.5f, 0.5f);          // Bottom Left Of The Quad (Right)
glVertex3f( 0.5f,-0.5f,-0.5f);          // Bottom Right Of The Quad (Right) 
glEnd();

                        // Done Drawing The Quad*/
// gluCylinder(lua,UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);
glPopMatrix();
glEndList();
}
void create_new_head()
{
//glNewList(new_head,GL_COMPILE);
glPushMatrix();
glTranslatef(CANNON_OUTER_RADIUS,0,0);
//glRotatef(-90.0, 1.0, 0.0, 0.0);
glScalef(armScale,armScale,armScale);
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, texture[0]); 
glBegin(GL_QUADS); 
SetMaterial(mat_specularWHITE, mat_ambientWHITE, mat_diffuseWHITE, mat_shininessWHITE);
glNormal3f(0,1,0);
glVertex3f( 0.5f, 0.5f,-0.5f);          // Top Right Of The Quad (Top)
glVertex3f(-0.5f, 0.5f,-0.5f);          // Top Left Of The Quad (Top) 
glVertex3f(-0.5f, 0.5f, 0.5f);          // Bottom Left Of The Quad (Top)
glVertex3f( 0.5f, 0.5f, 0.5f);          // Bottom Right Of The Quad (Top) 
//SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
glNormal3f(0,-1,0);
glVertex3f( 0.5f,-0.5f, 0.5f);          // Top Right Of The Quad (Bottom)
glVertex3f(-0.5f,-0.5f, 0.5f);          // Top Left Of The Quad (Bottom) 
glVertex3f(-0.5f,-0.5f,-0.5f);          // Bottom Left Of The Quad (Bottom)
glVertex3f( 0.5f,-0.5f,-0.5f);          // Bottom Right Of The Quad (Bottom) 
// SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED);
glNormal3f(0,0,1);
//SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED);
glVertex3f( 0.5f, 0.5f, 0.5f);          // Top Right Of The Quad (Front)
glVertex3f(-0.5f, 0.5f, 0.5f);          // Top Left Of The Quad (Front) 
glVertex3f(-0.5f,-0.5f, 0.5f);          // Bottom Left Of The Quad (Front)
glVertex3f( 0.5f,-0.5f, 0.5f);          // Bottom Right Of The Quad (Front) 
//SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
// std::cout<<"Haaiu"<<std::endl;
glNormal3f(0,0,-1);
glVertex3f( 0.5f,-0.5f,-0.5f);          // Bottom Left Of The Quad (Back)
glVertex3f(-0.5f,-0.5f,-0.5f);          // Bottom Right Of The Quad (Back) 
glVertex3f(-0.5f, 0.5f,-0.5f);          // Top Right Of The Quad (Back)
glVertex3f( 0.5f, 0.5f,-0.5f);          // Top Left Of The Quad (Back) 
//SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
glNormal3f(-1,0,0);
glVertex3f(-0.5f, 0.5f, 0.5f);          // Top Right Of The Quad (Left)
glVertex3f(-0.5f, 0.5f,-0.5f);          // Top Left Of The Quad (Left) 
glVertex3f(-0.5f,-0.5f,-0.5f);          // Bottom Left Of The Quad (Left)
glVertex3f(-0.5f,-0.5f, 0.5f);          // Bottom Right Of The Quad (Left) 
//SetMaterial(mat_specularGREEN, mat_ambientRED, mat_diffuseGREEN, mat_shininessGREEN);
glNormal3f(1,0,0);
glVertex3f( 0.5f, 0.5f,-0.5f);          // Top Right Of The Quad (Right)
glVertex3f( 0.5f, 0.5f, 0.5f);          // Top Left Of The Quad (Right) 
glVertex3f( 0.5f,-0.5f, 0.5f);          // Bottom Left Of The Quad (Right)
glVertex3f( 0.5f,-0.5f,-0.5f);          // Bottom Right Of The Quad (Right) 
glEnd();

                        // Done Drawing The Quad*/
// gluCylinder(lua,UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);
glPopMatrix();
//glEndList();
}

void create_new_left_lower_arm()
{
glNewList(new_left_lower_arm,GL_COMPILE);
glPushMatrix();
glScalef(armScale,armScale,armScale);
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, texture[0]); 
glBegin(GL_TRIANGLES); //Begin triangle coordinates

//Pentagon 
//FRONT FACE
SetMaterial(mat_specularGREEN, mat_ambientGREEN, mat_diffuseGREEN, mat_shininessGREEN);
glNormal3f(0,0,1);
glTexCoord2f(0.0f, 0.0f);glVertex3f(-0.5f, 0.5f,   0.5f); // left top
glTexCoord2f(0.5f, 0.0f);glVertex3f( 0.5f,  -0.5f,   0.5f); //right bottom
glTexCoord2f(0.5f, 0.5f);glVertex3f( 0.5f,  0.5f,   0.5f); //right top
glNormal3f(0,0,1);
glTexCoord2f(0.0f, 0.0f);glVertex3f(-0.5f, 0.5f,    0.5f); //left top
glTexCoord2f(0.5f, 0.0f);glVertex3f(-0.5f, -0.5f,   0.5f); //left bottom
glTexCoord2f(0.5f, 0.5f);glVertex3f( 0.5f,  -0.5f,  0.5f); //right bottom
glNormal3f(0,0,1);
glTexCoord2f(0.0f, 0.0f);glVertex3f(0.5f, -0.5f,   0.5f);	//right top
glTexCoord2f(0.5f, 0.0f);glVertex3f(-0.5f,  -0.5f, 0.5f);  //left top
glTexCoord2f(0.5f, 0.5f);glVertex3f(0.0f,  -1.5f,  0.5f);	//middle bottom
    //RIGHT FACE
// SetMaterial(mat_specularGREEN, mat_ambientGREEN, mat_diffuseGREEN, mat_shininessGREEN);
glNormal3f(0,1,1);
glTexCoord2f(0.0f, 0.0f);glVertex3f(0.5f, -0.5f,   0.5f); 
glTexCoord2f(0.5f, 0.0f);glVertex3f(0.0f,  -1.5f,  0.5f);
glTexCoord2f(0.5f, 0.5f);glVertex3f(0.5f,  -0.5f, -0.5f);

glNormal3f(1,0,0);
glTexCoord2f(0.0f, 0.0f);glVertex3f(0.5f, -0.5f,   0.5f); //BOTTOM LEFT
glTexCoord2f(0.5f, 0.0f);glVertex3f(0.5f,  -0.5f, -0.5f); //BOTTOM RIGHT
glTexCoord2f(0.5f, 0.5f);glVertex3f(0.5f,  0.5f,  -0.5f); //TOP RIGHT

glNormal3f(0,0,1);
glTexCoord2f(0.0f, 0.0f);glVertex3f(0.5f, -0.5f,   0.5f);
glTexCoord2f(0.5f, 0.0f);glVertex3f(0.5f,  0.5f,  -0.5f);
glTexCoord2f(0.5f, 0.5f);glVertex3f(0.5f,  0.5f,  0.5f);

//LEFT FACE
//SetMaterial(mat_specularBLUE, mat_ambientBLUE, mat_diffuseBLUE, mat_shininessBLUE);
glNormal3f(0,0,1);
glTexCoord2f(0.0f, 0.0f);glVertex3f(-0.5f, -0.5f,   0.5f); 
glTexCoord2f(0.5f, 0.0f);glVertex3f(0.0f,  -1.5f,  0.5f);
glTexCoord2f(0.5f, 0.5f);glVertex3f(-0.5f,  -0.5f, -0.5f);
glNormal3f(0,0,1);
glTexCoord2f(0.0f, 0.0f);glVertex3f(-0.5f, -0.5f,   0.5f); //BOTTOM LEFT
glTexCoord2f(0.5f, 0.0f);glVertex3f(-0.5f,  -0.5f, -0.5f); //BOTTOM RIGHT
glTexCoord2f(0.5f, 0.5f);glVertex3f(-0.5f,  0.5f,  -0.5f); //TOP RIGHT
glNormal3f(0,0,1);
glTexCoord2f(0.0f, 0.0f);glVertex3f(-0.5f, -0.5f,   0.5f);
glTexCoord2f(0.5f, 0.0f);glVertex3f(-0.5f,  0.5f,  -0.5f);
glTexCoord2f(0.5f, 0.5f);glVertex3f(-0.5f,  0.5f,  0.5f);

//BOTTOM FACE
//SetMaterial(mat_specularGREEN, mat_ambientGREEN, mat_diffuseGREEN, mat_shininessGREEN);
glNormal3f(0,0,1);
glTexCoord2f(0.0f, 0.0f);glVertex3f(0.0f,  -1.5f,  0.5f);
glTexCoord2f(0.5f, 0.0f);glVertex3f(0.5f,  -0.5f, -0.5f);
glTexCoord2f(0.5f, 0.5f);glVertex3f(-0.5f,  -0.5f, -0.5f);

glEnd();

glBegin(GL_QUADS);
//BACK
//SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
glNormal3f(0,0,1);
glVertex3f(0.5f, -0.5f, -0.5f); 
glVertex3f(0.5f, 0.5f, -0.5f); 
glVertex3f(-0.5f, 0.5f, -0.5f);
glVertex3f(-0.5f, -0.5f, -0.5f); 
//TOP
//SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED);
glNormal3f(0,0,1);
glVertex3f( 0.5f, 0.5f,-0.5f);          // Top Right Of The Quad (Top)
glVertex3f(-0.5f, 0.5f,-0.5f);          // Top Left Of The Quad (Top) 
glVertex3f(-0.5f, 0.5f, 0.5f);          // Bottom Left Of The Quad (Top)
glVertex3f( 0.5f, 0.5f, 0.5f);          // Bottom Right Of The Quad (Top)     
//  glVertex
glEnd();


// glRotatef(180.0, 1.0, 0.0, 0.0);
// gluCylinder(lla,LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT,10,10);
glPopMatrix();
glEndList();
}

void create_cannon()
{

//glNewList(new_cannon,GL_COMPILE);
glPushMatrix();
SetMaterial(mat_specularBLUE, mat_ambientBLUE, mat_diffuseBLUE, mat_shininessBLUE);
glTranslatef(CANNON_OUTER_RADIUS,0,0);
// glRotatef(-90.0, 0.0, 1.0, 0.0);
glScalef(armScale,armScale,armScale);
gluCylinder(cul,CANNON_INNER_RADIUS, CANNON_INNER_RADIUS, CANNON_INNER_HEIGHT,10,10);  
SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
gluCylinder(cul,CANNON_OUTER_RADIUS, CANNON_OUTER_RADIUS, CANNON_OUTER_HEIGHT,10,10);
glPopMatrix();
//glEndList();
}

void create_new_left_thigh()
{
glPushMatrix();
SetMaterial(mat_specularGREEN, mat_ambientGREEN, mat_diffuseGREEN, mat_shininessGREEN);
//glTranslatef(-(NEW_THIGH_RADIUS),0,0);
///glRotatef(-90.0, 0.0, 1.0, 0.0);
glScalef(legScale,legScale,legScale);
gluCylinder(lt,NEW_THIGH_RADIUS, NEW_THIGH_RADIUS, NEW_THIGH_HEIGHT,10,10);  
glPopMatrix();
}	

void create_new_hand()
{
glNewList(new_hand,GL_COMPILE);
glPushMatrix();

//glRotatef(-90.0, 1.0, 0.0, 0.0);
glScalef(armScale/2,armScale/2,armScale/2);
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, texture[0]); 
glBegin(GL_QUADS); 
SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED);
glNormal3f(0,1,0);
glVertex3f( 0.5f, 0.5f,-0.5f);          // Top Right Of The Quad (Top)
glVertex3f(-0.5f, 0.5f,-0.5f);          // Top Left Of The Quad (Top) 
glVertex3f(-0.5f, 0.5f, 0.5f);          // Bottom Left Of The Quad (Top)
glVertex3f( 0.5f, 0.5f, 0.5f);          // Bottom Right Of The Quad (Top) 
//SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
glNormal3f(0,-1,0);
glVertex3f( 0.5f,-0.5f, 0.5f);          // Top Right Of The Quad (Bottom)
glVertex3f(-0.5f,-0.5f, 0.5f);          // Top Left Of The Quad (Bottom) 
glVertex3f(-0.5f,-0.5f,-0.5f);          // Bottom Left Of The Quad (Bottom)
glVertex3f( 0.5f,-0.5f,-0.5f);          // Bottom Right Of The Quad (Bottom) 
// SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED);
glNormal3f(0,0,1);
//SetMaterial(mat_specularRED, mat_ambientGREEN, mat_diffuseGREEN, mat_shininessGREEN);
glVertex3f( 0.5f, 0.5f, 0.5f);          // Top Right Of The Quad (Front)
glVertex3f(-0.5f, 0.5f, 0.5f);          // Top Left Of The Quad (Front) 
glVertex3f(-0.5f,-0.5f, 0.5f);          // Bottom Left Of The Quad (Front)
glVertex3f( 0.5f,-0.5f, 0.5f);          // Bottom Right Of The Quad (Front) 
//SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
//std::cout<<"Haaiu"<<std::endl;
glNormal3f(0,0,-1);
glVertex3f( 0.5f,-0.5f,-0.5f);          // Bottom Left Of The Quad (Back)
glVertex3f(-0.5f,-0.5f,-0.5f);          // Bottom Right Of The Quad (Back) 
glVertex3f(-0.5f, 0.5f,-0.5f);          // Top Right Of The Quad (Back)
glVertex3f( 0.5f, 0.5f,-0.5f);          // Top Left Of The Quad (Back) 
//SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
glNormal3f(-1,0,0);
glVertex3f(-0.5f, 0.5f, 0.5f);          // Top Right Of The Quad (Left)
glVertex3f(-0.5f, 0.5f,-0.5f);          // Top Left Of The Quad (Left) 
glVertex3f(-0.5f,-0.5f,-0.5f);          // Bottom Left Of The Quad (Left)
glVertex3f(-0.5f,-0.5f, 0.5f);          // Bottom Right Of The Quad (Left) 
//SetMaterial(mat_specularGREEN, mat_ambientGREEN, mat_diffuseGREEN, mat_shininessGREEN);
glNormal3f(1,0,0);
glVertex3f( 0.5f, 0.5f,-0.5f);          // Top Right Of The Quad (Right)
glVertex3f( 0.5f, 0.5f, 0.5f);          // Top Left Of The Quad (Right) 
glVertex3f( 0.5f,-0.5f, 0.5f);          // Bottom Left Of The Quad (Right)
glVertex3f( 0.5f,-0.5f,-0.5f);          // Bottom Right Of The Quad (Right) 
glEnd();

                        // Done Drawing The Quad*/
// gluCylinder(lua,UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);
glPopMatrix();
glEndList();
}

void create_new_biceps()
{
glPushMatrix();
SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED);
//glTranslatef(-(NEW_THIGH_RADIUS),0,0);
///glRotatef(-90.0, 0.0, 1.0, 0.0);
//glScalef(armScale,armScale,armScale);
gluCylinder(bi,BICEPS_RADIUS, BICEPS_RADIUS, BICEPS_HEIGHT,10,10);  
glPopMatrix();
}
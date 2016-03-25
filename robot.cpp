// Use dislayt1 and not displayt2(2), latter is broken for unknown reasons
// ToDo : transfer motion control from display() to main()
#include "create.hpp"
#include <time.h> 
void displayt2(int);
static GLfloat diagScale = 0.4;
extern unsigned int texture[10];
void myReshape(int,int);
int LoadGLTextures(std::string textures,int i)       // Load Bitmaps And Convert To Textures
{
// load an image file directly as a new OpenGL texture 
  texture[i] = SOIL_load_OGL_texture
  (
    textures.c_str(),
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
    );

  if(texture[0] == 0)
    return false;

// Typical Texture Generation Using Data From The Bitmap
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT );
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

return true;                                        // Return Success
}

void create()
{
//create_pelvis();
// create_new_head(); 
  create_new_left_upper_leg();
  create_new_left_lower_leg();
  create_new_torso();
  create_new_frame();
  create_new_left_lower_arm();
  create_new_left_upper_arm();
  create_new_hand();
  create_new_env();
}

void tankLegs(int a)
{
  glPushMatrix(); 
    glTranslatef(TORSO_LENGTH/2 - LOWER_LEG_LENGTH,0,TORSO_HEIGHT);
    glCallList(new_left_lower_leg);
    glPushMatrix(); 
      glTranslatef(LOWER_LEG_LENGTH - WHEEL_RADIUS/4,0,0);
      glRotatef(90,0,1,0);
      create_new_wheel(a);
      glPopMatrix(); 

      glTranslatef(LOWER_LEG_LENGTH- UPPER_LEG_LENGTH ,0,UPPER_LEG_HEIGHT);
      glCallList(new_left_upper_leg);
      glPushMatrix(); 
        glTranslatef(UPPER_LEG_LENGTH - WHEEL_RADIUS/4,0,UPPER_LEG_HEIGHT);
        glRotatef(90,0,1,0);
        create_new_wheel(a);
        glPopMatrix(); 

        glTranslatef(UPPER_LEG_LENGTH/2,UPPER_LEG_FINAL_WIDTH/2,0); 
        create_new_left_thigh();
        glPopMatrix(); 


      }
      void display_arm(int step,bool can, float handx,float handz )
      {
        glPushMatrix(); 
          if(step>=5)
          {
            glPushMatrix(); 

              glTranslatef(TORSO_LENGTH/2 +UPPER_ARM_HEIGHT*armScale/2 , UPPER_LEG_FINAL_WIDTH*0.8,(TORSO_HEIGHT+2*LOWER_LEG_HEIGHT+UPPER_LEG_HEIGHT)/2  );
              glRotatef(90,0,0,1);
              glTranslatef(-TORSO_LENGTH/2 -UPPER_ARM_HEIGHT*armScale/2 , -UPPER_LEG_FINAL_WIDTH*0.8,-(TORSO_HEIGHT+2*LOWER_LEG_HEIGHT+UPPER_LEG_HEIGHT)/2  );
            }
            if(step>=6)
            { 
//lTranslatef(1, 0, 0  );
              glPushMatrix(); 
glTranslatef(-UPPER_LEG_FINAL_WIDTH*0.4,0,(LOWER_LEG_HEIGHT)/2) ; // cancel the elevation
glTranslatef(TORSO_LENGTH/4 +UPPER_ARM_HEIGHT*armScale/2 , UPPER_LEG_FINAL_WIDTH*0.8,(TORSO_HEIGHT+2*LOWER_LEG_HEIGHT+UPPER_LEG_HEIGHT)/2  );
glRotatef(180,0,0,1);
glTranslatef(-TORSO_LENGTH/4 -UPPER_ARM_HEIGHT*armScale/2, -UPPER_LEG_FINAL_WIDTH*0.8,-(TORSO_HEIGHT+2*LOWER_LEG_HEIGHT+UPPER_LEG_HEIGHT)/2  );//0.1 is random
}
glScalef(1,1,-1);
glTranslatef(0,UPPER_LEG_FINAL_WIDTH*0.8,-(TORSO_HEIGHT+2*LOWER_LEG_HEIGHT+UPPER_LEG_HEIGHT)/2  );//Elevate and bring to centre
glPushMatrix(); 
  glPushMatrix(); 
    glTranslatef(UPPER_ARM_HEIGHT*armScale/2,0,0);
    create_new_biceps();
    glCallList(new_left_upper_arm);

    if(step>=6)
      { glPushMatrix(); 
        glTranslatef(0,0,BICEPS_HEIGHT);
      }
      glPushMatrix(); 
        glTranslatef(0,0,.1);
        glRotatef(90,0,0,1);
        glRotatef(90,-1,0,0);
        glPushMatrix(); 
          glCallList(new_left_lower_arm);
          glPopMatrix(); 
          glPopMatrix(); 

          if(can)
            {glPushMatrix(); 
              glScalef(-1,1,1);
glTranslatef(-UPPER_ARM_HEIGHT*0.2/2,0,1.0*armScale); // 1.5 is lowerArm ht.
glPushMatrix(); 
  create_cannon();
  glPopMatrix(); 
  glPopMatrix(); 
}


if(step>=5)  
  { glPushMatrix(); 
    glTranslatef(-0.1,0,1.2-BICEPS_HEIGHT);
  }
/*if(step>=6)
{ glPushMatrix(); 
glTranslatef(0,0,BICEPS_HEIGHT);
}*/
glTranslatef(0,0,-0.5/2);
glRotatef(handx*20,1,0,0);
glTranslatef(0,0,0.5/2);
glRotatef(handz*20,0,0,1);
glCallList(new_hand);
glPopMatrix(); 
glPopMatrix(); 
//glPopMatrix(); 

if(step>=5)
{
  glPopMatrix(); 
  glPopMatrix(); 
}
if(step>=6)
{
  glPopMatrix(); 
  glPopMatrix(); 
//glPopMatrix(); 
}
glPopMatrix(); 
}
void transform_tankLegs()
{
  glPushMatrix(); 
    glTranslatef(TORSO_LENGTH/2 - LOWER_LEG_LENGTH,0,TORSO_HEIGHT);
//glCallList(new_left_lower_leg);
    glTranslatef(LOWER_LEG_LENGTH- UPPER_LEG_LENGTH ,0,UPPER_LEG_HEIGHT );

    glCallList(new_left_upper_leg);

    glPushMatrix(); 
      glTranslatef(UPPER_LEG_LENGTH/2,UPPER_LEG_FINAL_WIDTH/2,0); 
      glPushMatrix(); 
        create_new_left_thigh();
        glPopMatrix(); 
        glPopMatrix(); 
        glPushMatrix(); 
          glTranslatef(UPPER_LEG_LENGTH + LOWER_LEG_LENGTH,0,LOWER_LEG_HEIGHT);
          glRotatef(180,0,1,0);
          glPushMatrix(); 
           glCallList(new_left_lower_leg);
           glPopMatrix(); 
           glPopMatrix(); 
           glPopMatrix(); 

         }
         void transform_tankLegs2(int step ,float tx, float ty, float tz)
         {
           glPushMatrix(); 
             if (step >=4)
             {
              glPushMatrix(); 
                glTranslatef(0,0,UPPER_LEG_HEIGHT);
              }
              glTranslatef(TORSO_LENGTH/2 - LOWER_LEG_LENGTH,0,TORSO_HEIGHT);
              glTranslatef(LOWER_LEG_LENGTH- UPPER_LEG_LENGTH ,0,UPPER_LEG_HEIGHT );
              glPushMatrix(); 
                glTranslatef(UPPER_LEG_LENGTH/2,UPPER_LEG_FINAL_WIDTH/2,0); 

                glRotatef(-20*tx,1,0,0);
                glRotatef(20*ty,0,1,0);
                glRotatef(20*tz,0,0,1);
                glPushMatrix(); 
                  create_new_left_thigh();
                  glPopMatrix(); 
                  glTranslatef(-UPPER_LEG_LENGTH/2,-UPPER_LEG_FINAL_WIDTH/2,0); 
                  if(step>=3)
                  {
                    glPushMatrix(); 
                      glTranslatef( (NEW_THIGH_RADIUS)*legScale,(NEW_THIGH_RADIUS)*legScale,0);
                      glRotatef(90,0,0,1);
                      glTranslatef(-(NEW_THIGH_RADIUS)*legScale,-(NEW_THIGH_RADIUS)*legScale,0);
                    }
                    glPushMatrix(); 
                      glTranslatef(0,0,legScale* NEW_THIGH_HEIGHT); 

                      glCallList(new_left_upper_leg);


                      glPushMatrix(); 
                        glTranslatef(UPPER_LEG_LENGTH + LOWER_LEG_LENGTH,0,LOWER_LEG_HEIGHT);
                        if(step>=2)
                          glRotatef(180,0,1,0);
                        glPushMatrix(); 
                          glCallList(new_left_lower_leg);
                          glPopMatrix(); 

                          glPopMatrix(); 
                          glPopMatrix(); 
                          if (step>=3)
                            glPopMatrix(); 
                          if(step>=4)
                            glPopMatrix(); 
                          glPopMatrix(); 

                        }


                        void display_robot()
                        {
                          create();
                          glPushMatrix(); 
                            glRotatef(60,-1,0,0);
                            glRotatef(120,0,1,0);

                            glTranslatef(0,-1,0);
                            glPushMatrix(); 
// glCallList(new_hand);
                              glPushMatrix(); 
                                glTranslatef(0,armScale*env/2,0);
                                glCallList(new_env);
                                glPopMatrix(); 
                                glTranslatef(-x_m,0,-z_m);
//glTranslatef(0,0,(UPPER_LEG_HEIGHT+LOWER_LEG_HEIGHT+TORSO_HEIGHT)/2);
                                glRotatef(turn,0,1,0);
//glTranslatef(0,0,-(UPPER_LEG_HEIGHT+LOWER_LEG_HEIGHT+TORSO_HEIGHT)/2);

                                glPushMatrix(); 
                                  glRotatef(90,1,0,0);

// glTranslatef((UPPER_LEG_HEIGHT+LOWER_LEG_HEIGHT+TORSO_HEIGHT),0,0);
                                  glTranslatef(0,0,-(UPPER_LEG_HEIGHT+LOWER_LEG_HEIGHT+TORSO_HEIGHT)*3/2-LOWER_LEG_HEIGHT/2);
                                  glRotatef(180,0,0,1);
                                  displayt2(6);
                                  glPopMatrix(); 

                                  glPopMatrix(); 
                                  glPopMatrix(); 
                                }
                                void display(void)
                                {
                                  create();

                                  if (index==0)
                                  {
                                    glPushMatrix(); 
                                      glRotatef(60,-1,0,0);
                                      glRotatef(120,0,1,0);

                                      glTranslatef(0,-1,0);
                                      glPushMatrix(); 
// glCallList(new_hand);
                                        glPushMatrix(); 
                                          glTranslatef(0,armScale*env/2,0);
                                          glCallList(new_env);
                                          glPopMatrix(); 
                                          glTranslatef(-x_m,WHEEL_RADIUS,-z_m);
                                          glTranslatef(0,0,(UPPER_LEG_HEIGHT+LOWER_LEG_HEIGHT+TORSO_HEIGHT)/2);
                                          glRotatef(turn,0,1,0);
                                          glTranslatef(0,0,-(UPPER_LEG_HEIGHT+LOWER_LEG_HEIGHT+TORSO_HEIGHT)/2);
                                        }

//gluPerspective(90,1,0.1,1000);
if (index !=0) // First/third person camera
  glRotatef(45,1,0,0);

if (index != 1)
{
  if (flag2)
  {
    glPushMatrix();
    GLfloat headlight[] = {0.0f, 0.0f, 0.0f,1.0};
    lights(GL_LIGHT2,headlight,1);
    glPopMatrix();
  }
  if (robot)
  {
    glPushMatrix(); 
      glRotatef(90,1,0,0);

// glTranslatef((UPPER_LEG_HEIGHT+LOWER_LEG_HEIGHT+TORSO_HEIGHT),0,0);
      glTranslatef(0,0,-(UPPER_LEG_HEIGHT+LOWER_LEG_HEIGHT+TORSO_HEIGHT)*3/2-LOWER_LEG_HEIGHT/2);
      glRotatef(180,0,0,1);

      displayt2(6);
      glPopMatrix(); 
    }
    else
    {
    
      glCallList(new_wheel); glCallList(new_torso);
      glCallList(new_frame);
      glPushMatrix(); 
        glTranslatef((TORSO_LENGTH/2+ WHEEL_RADIUS/4),0,0);
        glRotatef(-90,0,1,0);
        create_new_wheel(0);
        glPopMatrix(); 

        glPushMatrix(); 
          glTranslatef(-(TORSO_LENGTH/2+ WHEEL_RADIUS/4),0,0);
          glRotatef(90,0,1,0);
          create_new_wheel(0);
          glPopMatrix(); 


          glPushMatrix(); 
            tankLegs(0);
            glPopMatrix(); 
            glPushMatrix(); 
              glScalef(-1,1,1);
              tankLegs(1);
              glPopMatrix(); 

//Arms
              glPushMatrix(); 
                display_arm(1,false,rhandx,rhandz);
                glPushMatrix(); 
                  glScalef(-1,1,1);
                  display_arm(1,true,lhandx,lhandz);
                  glPopMatrix(); 
                  glPopMatrix(); 
                }

              }
              if (index!=0)
              {
                if (robot && index==2)
                {
                  glPushMatrix(); 
                    glRotatef(-180,0,0,1);
                    glTranslatef(0,0,(UPPER_LEG_HEIGHT+LOWER_LEG_HEIGHT+TORSO_HEIGHT)*3/2 + LOWER_LEG_HEIGHT/2);
                    glRotatef(-90,1,0,0);

// glTranslatef((UPPER_LEG_HEIGHT+LOWER_LEG_HEIGHT+TORSO_HEIGHT),0,0);

                  }

                  glTranslatef(0,0,(UPPER_LEG_HEIGHT+LOWER_LEG_HEIGHT+TORSO_HEIGHT)/2);
                  glRotatef(-turn,0,1,0);
                  glTranslatef(0,0,-(UPPER_LEG_HEIGHT+LOWER_LEG_HEIGHT+TORSO_HEIGHT)/2);    
                  glTranslatef(x_m,-WHEEL_RADIUS,z_m);
                  glPushMatrix(); 

                    glTranslatef(0,armScale*env/2,0);
                    glCallList(new_env);
                    glPopMatrix(); 
                    glPopMatrix(); 
                  }
                  glPopMatrix(); 
                  glPopMatrix(); 
                }


                void displayt1()
                {
                  create();

                  glPushMatrix(); 
                    glCallList(new_wheel); glCallList(new_torso);
                    glCallList(new_frame);

/*
glPushMatrix(); 
glTranslatef(-0.5 * diagScale,0,TORSO_HEIGHT); // HalfWIdth of head is 0.5 and entire diagram is scaled by 0.4
create_new_head();
glPopMatrix(); 
*/
glPushMatrix(); 
  transform_tankLegs();
  glPopMatrix(); 
  glPushMatrix(); 
    glScalef(-1,1,1);
    transform_tankLegs();
    glPopMatrix(); 
    glPushMatrix(); 

//arms
      glPushMatrix(); 
        display_arm(1,false,rhandx, rhandz);
        glPushMatrix(); 
          glScalef(-1,1,1);
          display_arm(1,true,lhandx, lhandz);
          glPopMatrix(); 
          glPopMatrix(); 


          glPopMatrix(); 
          glPopMatrix(); 
        }
        void displayt2(int step)
        {
          create();

          glPushMatrix(); 
            if(step>=4)
            {
              glPushMatrix(); 
                glTranslatef(0,0,TORSO_HEIGHT+LOWER_LEG_HEIGHT+UPPER_LEG_HEIGHT);
                glRotatef(-20*trsx,1,0,0);
                glRotatef(20*trsy,0,1,0);
                glRotatef(20*trsz,0,0,1);
                glTranslatef(0,0,-(TORSO_HEIGHT+LOWER_LEG_HEIGHT+UPPER_LEG_HEIGHT));
                glPushMatrix(); 
                  glTranslatef(0,TORSO_START_WIDTH,TORSO_HEIGHT);
                  glRotatef(-180,1,0,0);
                  glRotatef(180,0,0,1);
                  glTranslatef(0,-TORSO_START_WIDTH,-TORSO_HEIGHT);
                  glCallList(new_wheel); glCallList(new_torso);
                  glPopMatrix(); 
                }
                else
                  glCallList(new_wheel); glCallList(new_torso);



                glCallList(new_frame);
//FIrst time we see head
                glPushMatrix(); 
glTranslatef(-0.5 * diagScale,0.5 * diagScale,TORSO_HEIGHT-0.5 * diagScale); // HalfWIdth of head is 0.5 and entire diagram is scaled by 0.4
create_new_head();
glPopMatrix(); 
glPushMatrix(); 
glTranslatef(0,-UPPER_LEG_FINAL_WIDTH*0.8,(TORSO_HEIGHT+2*LOWER_LEG_HEIGHT+UPPER_LEG_HEIGHT)/2  );//0.1 is random
glRotatef(180,0,1,0);
glTranslatef(0,UPPER_LEG_FINAL_WIDTH*0.8,-(TORSO_HEIGHT+2*LOWER_LEG_HEIGHT+UPPER_LEG_HEIGHT)/2  );//0.1 is random

//arms
glPushMatrix(); 
  display_arm(step,false,rhandx,rhandz);
  glPushMatrix(); 
    glScalef(-1,1,1);
    display_arm(step,true,lhandx,lhandz);
    glPopMatrix(); 
    glPopMatrix(); 
    if (step>=4)
      glPopMatrix(); 
    glPushMatrix(); 
      transform_tankLegs2(step, rtx, rty, rtz);
      glPopMatrix(); 
      glPushMatrix(); 
        glScalef(-1,1,1);
        transform_tankLegs2(step, ltx, lty, ltz);
        glPopMatrix(); 



        glPopMatrix(); 
        glPopMatrix(); 
      }
      void complete_transform( float currTime)
      {

        if (currTime<2)
        {
          display();
        }
        else if (currTime<4)
        {
          displayt1();
        }
        else if (currTime<6)
        {

          displayt2(3);
        }
        else if (currTime<8)
        {
          displayt2(4);
        }
        else if (currTime<10)
        {
          displayt2(5);
        }

        else if (currTime<12)
        {
          displayt2(6);
        }

      }
      void arms(float elbow, float shlx,float shly,float shlz, bool cannon)
      {
        glPushMatrix(); 


          glTranslatef(TORSO_LENGTH/2,TORSO_HEIGHT,0);

          glTranslatef(UPPER_ARM_HEIGHT*armScale /2,0,0);

          glRotatef(-20*shlx,1,0,0);
          glRotatef(20*shly,0,1,0);
          glRotatef(20*shlz,0,0,1);

          glCallList(new_left_upper_arm);

// Call Arm Joint
          glTranslatef(0,-UPPER_ARM_HEIGHT*armScale*2 ,0);
          glRotatef(-elbow*20,1,0,0);
          glPushMatrix(); 
            glCallList(new_left_lower_arm);
            glPopMatrix(); 
            if (cannon)
            {
              glPushMatrix(); 
glTranslatef(-0.5*armScale,-1.0*armScale,0); // Length of lowerarm
glRotatef(90,1,0,0); // X Axis
glPushMatrix(); 
  create_cannon();
  glPopMatrix(); 
  glPopMatrix(); 
}

glPopMatrix(); 
}
void legs(float knee, float tx, float ty, float tz)
{
//glCallList(new_left_thigh);
  glPushMatrix(); 


    glRotatef(-20*tx,1,0,0);
    glRotatef(20*ty,0,1,0);
    glRotatef(20*tz,0,0,1);
    glPushMatrix(); 
      glRotatef(90,1,0,0);
      create_new_left_thigh();
      glPopMatrix(); 
      glTranslatef(-UPPER_LEG_LENGTH/2,-(NEW_THIGH_HEIGHT)*legScale-UPPER_LEG_HEIGHT,NEW_THIGH_RADIUS*legScale );
      glPushMatrix(); 
        glTranslatef(0,UPPER_LEG_START_WIDTH,0);
        glRotatef(knee*20,1,0,0);
        glTranslatef(0,-UPPER_LEG_START_WIDTH,0);
        glRotatef(90,0,1,0);
        glPushMatrix(); 


// Y axis
          glCallList(new_left_upper_leg);
          glTranslatef(-UPPER_LEG_LENGTH,0,UPPER_LEG_HEIGHT);
          glRotatef(90,-1,0,0);
          glCallList(new_left_lower_leg);
          glPopMatrix(); 
          glPopMatrix(); 

          glPopMatrix(); 
        }
        void robot_display()
        {
          create();

          glPushMatrix(); 
            glPushMatrix(); 

              glRotatef(-90,1,0,0);

              glCallList(new_wheel); glCallList(new_torso);
              glPopMatrix();  
// call pelvis
              glPushMatrix(); 
                glTranslatef(0.1,0,0);
                glRotatef(180,1,0,0);
                glPushMatrix(); 
//create_new_pelvis();
                  glPopMatrix(); 
                  glPopMatrix(); 
                  glPushMatrix(); 
                    arms(relbow,rshlx,rshly,rshlz,0);
                    glPopMatrix(); 
                    glPushMatrix(); 
                      glScalef(-1,1,1);
                      arms(lelbow,lshlx,lshly,lshlz,1);
                      glPopMatrix(); 
// At Plevis, translate to legs
//Begin Left legs

                      glPushMatrix(); 
glTranslatef(-(2*NEW_PELVIS_HORIZONTAL_RADIUS),0,0); // Half Width between thighs
legs(lknee,ltx,lty,ltz);

glPopMatrix(); 
// Right legs
glPushMatrix(); 
glTranslatef((2*NEW_PELVIS_HORIZONTAL_RADIUS),0,0); // Half Width between thighs
glScalef(-1,1,1);
legs(rknee,rtx,rty,rtz);
glPopMatrix(); 
}
void transform_1()
{
  display();
glTranslatef( (TORSO_LENGTH/2) + LOWER_LEG_LENGTH, 0,LOWER_LEG_HEIGHT + TORSO_HEIGHT + UPPER_LEG_HEIGHT);// go to joint around which rotation should be done
// ROtate
//glTranslatef(0,0,TORSO_HEIGHT);// go to start point of drawing
glRotatef(180,0,1,0);
glCallList(new_left_lower_leg);
}
void 
myReshape(int w, int h)
{
// w*=3; h*=3;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
//glFrustrum()
  glLoadIdentity();

  if (w <= h)
    glOrtho(-10.0, 10.0, -10.0 * (GLfloat) h / (GLfloat) w,10.0 * (GLfloat) h / (GLfloat) w, -10.0, 1000.0);
//glFrustum(-w,w,-h,h,10,1000.0);
//gluPerspective(90,1,0.1,1000);
  else
    glOrtho(-10.0 * (GLfloat) w / (GLfloat) h,
      10.0 * (GLfloat) w / (GLfloat) h, 0.0, 10.0, 0.001, 10000.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


void myinit()
{


  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  glDepthFunc(GL_LESS);
  glPolygonMode(GL_FRONT, GL_FILL);

//lights(GL_LIGHT0, position1, 0);

//glRotatef(0.0, 1.0, 0.0, 0.0);

  np=gluNewQuadric();
  gluQuadricDrawStyle(np, GLU_FILL);
  rt=gluNewQuadric();
  gluQuadricDrawStyle(rt, GLU_FILL);
  lt=gluNewQuadric();
  gluQuadricDrawStyle(lt, GLU_FILL); 
  cul=gluNewQuadric();
  gluQuadricDrawStyle(cul, GLU_FILL);
  h=gluNewQuadric();
  gluQuadricDrawStyle(h, GLU_FILL);
  t=gluNewQuadric();
  gluQuadricDrawStyle(t, GLU_FILL);
  lua=gluNewQuadric();
  gluQuadricDrawStyle(lua, GLU_FILL);
  lla=gluNewQuadric();
  gluQuadricDrawStyle(lla, GLU_FILL);
  rua=gluNewQuadric();
  gluQuadricDrawStyle(rua, GLU_FILL);
  rla=gluNewQuadric();
  gluQuadricDrawStyle(rla, GLU_FILL);
  lul=gluNewQuadric();
  gluQuadricDrawStyle(lul, GLU_FILL);
  nhand=gluNewQuadric();
  gluQuadricDrawStyle(nhand, GLU_FILL);
  lll=gluNewQuadric();
  gluQuadricDrawStyle(lll, GLU_FILL);
  w=gluNewQuadric();
  gluQuadricDrawStyle(w, GLU_FILL);
  bi=gluNewQuadric();
  gluQuadricDrawStyle(bi, GLU_FILL);
  rul=gluNewQuadric();
  gluQuadricDrawStyle(rul, GLU_FILL);
  rll=gluNewQuadric();
  gluQuadricDrawStyle(rll, GLU_FILL);
}


int main(int argc, char** argv)
{
//! The pointer to the GLFW window
  GLFWwindow* window;

//! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

//! Initialize GLFW
  if (!glfwInit())
    return -1;

//! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(500, 500, "CS475/CS675 OpenGL Framework", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

//! Make the window's context current 
  glfwMakeContextCurrent(window);

//Initialize GLEW
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
//Problem: glewInit failed, something is seriously wrong.
    std::cerr<<"GLEW Init Failed : %s"<<std::endl;
  }

//Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

//Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
//Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

// Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
LoadGLTextures("texture1.jpg",0); // load 0th texture into library
LoadGLTextures("skyTexture.jpg",1); // load sky texture into library
LoadGLTextures("groundTexture.jpg",2); // load ground texture into library
LoadGLTextures("wheel.jpg",3); // load ground texture into library
LoadGLTextures("metal.jpg",4); // load ground texture into library
LoadGLTextures("Gold.jpg",5); // load ground texture into library
LoadGLTextures("tank.jpg",6); // load ground texture into library
LoadGLTextures("metal2.jpg",7); // load ground texture into library

//Initialize GL state
csX75::initGL();

// Loop until the user closes the window
int flag=90;
clock_t begin_time = clock();
float currTime=0;


glPushMatrix(); 
  myinit();      
  glPopMatrix(); 
//  GLfloat position0[] =  {env/12, env/4, -env/6, 0.0};
  GLfloat position0[] =  {-env/12, env/12,-env/6 , 0.0};
  GLfloat position1[] = {env/12, env/12, env/6, 0.0};
  while (glfwWindowShouldClose(window) == 0)
  {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//if(index!=0)
//myReshape(100,100);
    glLoadIdentity();



    std::cout<<"Index "<<index<<std::endl;
    if (index ==1)
    {
//glViewport(0, 0, 500, 500);
      glMatrixMode(GL_PROJECTION);
//glFrustrum()
      glLoadIdentity();
      gluPerspective(90,1,0.001,100);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glRotatef(180,0,1,0);
      glScalef(-1,1,1);
    }
    else
    {
      myReshape(500,500);
      glScalef(5,5,-5);
    }
    glScalef(-zoom,zoom,zoom);
    if (index!=0)
      glScalef(1.5,1.5,-1.5);

    glDisable(GL_LIGHT0);   
    glDisable(GL_LIGHT1); 
    glDisable(GL_LIGHT2);   
    if(dirLight1)   
      lights(GL_LIGHT0, position0, 1);
    std::cout<<" dirLight1 "<<dirLight1;

    if(dirLight2)
      lights(GL_LIGHT1, position1, 1);
    std::cout<<"dirLight2 "<<dirLight2;
    glPushMatrix(); 
      glRotatef(360-camera->ay,0,1,0);
      glRotatef(360-camera->ax,1,0,0);
      glPushMatrix(); 
//myinit();   

        glPopMatrix(); 
        glPushMatrix(); 
//
          std::cout<<currTime<<std::endl;
          currTime=float( clock () - begin_time ) /  CLOCKS_PER_SEC;
          if( currTime > 12)
          {
            begin_time = clock();
            currTime=0;
          }
          if(transformMode==1)
            complete_transform(currTime);
          else 
            display();
          if(flag!=0)
          {
            flag=0;
            glRotatef(flag,0,1,0);
//glTranslatef(-3,0,-3);
          }
          glPopMatrix(); 
          glPopMatrix(); 
// Swap front and back buffers
          glfwSwapBuffers(window);

// Poll for and process events
          glfwPollEvents();
        }


        glfwTerminate();
        return 0;
      }

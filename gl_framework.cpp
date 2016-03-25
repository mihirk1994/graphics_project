#include "gl_framework.hpp"
#define piover180 3.1416/180
#include <cmath>
#include <iostream>
typedef float point[3];
int heading;
typedef struct
{
  float x,y,z;
  float ax,ay,az;
}camera_t,*camera_t_ptr;
camera_t cameras[3];
camera_t *camera;
int lightturn,lightturn1;
float rknee=0,lknee=0,relbow=0,lelbow=0;
float lshlx=0,lshly=0,lshlz=0,rshlx=0,rshly=0,rshlz=0;
float ltx=0,lty=0,ltz=0,rtx=0,rty=0,rtz=0;
bool sh=0, dirLight1=0, dirLight2=0;
float trsx=0, trsy=0, trsz=0;
float lhandx=0,lhandz=0, rhandx=0,rhandz=0;
float transformMode=0;
float fwd=0, turn=0, wheel_turn=0;
float x_m=0, z_m=0;
int flag = 1,flag1=1; 
int flag2 = 0;
float zoom=0.25;
int index=0;
bool robot=0;
float rot=0;
namespace csX75
{
//! Initialize GL State
  void initGL(void)
  {
    camera = &cameras[index];
    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE); 
// glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT,GL_FILL);
    glDisable(GL_CULL_FACE);
// glEnable(GL_CULL_FACE);
//glCullFace(GL_BACK);

  }

//!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }

//!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    if  ( height == 0 ) height = 1;
    glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,50.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
//glTranslatef(0,1,-10);
//    win_width = width;
//  win_height = height;
  }


//!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
  //!Close the window if the ESC key was pressed
   if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
  if (key=='N')
  {
    heading=1;
    std::cout<<"Camera x"<<camera->x<< "z" <<camera->z<<std::endl;

    camera->x-=(float)sin(heading*piover180) * 0.15f;
    camera->z-=(float)cos(heading*piover180) * 0.15f;
  }
  if (key==GLFW_KEY_M)
  {
    heading=1;
    camera->x+=(float)sin(heading*piover180) * 0.15f;
    camera->z+=(float)cos(heading*piover180) * 0.15f;

  }
  if (key==GLFW_KEY_F11)
  {
    camera->z-=(float)cos(heading*piover180) * 0.15f;
  }
  if (key==GLFW_KEY_F12)
  {
    heading=1;
    camera->z+=(float)cos(heading*piover180) * 0.15f;

  }
  if (key== GLFW_KEY_X)
  {
    lightturn=(lightturn+5) % 360;
    std::cout<<"lightturn"<<lightturn<<std::endl;
  }
  if (key== GLFW_KEY_C)
    lightturn1= (lightturn1+5) % 360;
  if (key=='V')
  {
    camera->ay-=1.0f;;
  }
  if (key=='B')
  {
    camera->ay+=1.0f;
  }

  if (key==',')
  {
    camera->ax-=1.0f;;
  }
  if (key=='.')
  {
    camera->ax+=1.0f;
  }

  if (key=='W')
  {
    if(rknee<=4)
      rknee+=0.1;
  }

  if (key=='S')
  {
    if(rknee>=0)
      rknee-=0.1;
  }

  if (key=='Q')
  {
    if(lknee<=4)
      lknee+=0.1;
  }

  if (key=='A')
  {
    if(lknee>=0)
      lknee-=0.1;
  }

  if (key=='E')
  {
    if(lelbow<=4)
      lelbow+=0.1;
  }

  if (key=='D')
  {
    if(lelbow>=0)
      lelbow-=0.1;
  }

  if (key=='R')
  {
    if(relbow<=4)
      relbow+=0.1;
  }

  if (key=='F')
  {
    if(relbow>=0)
      relbow-=0.1;
  }

    // x axis for shoulder
  if (key=='T')
  {
    if(sh)
    {
      if(lshlx<=4)
        lshlx+=0.1;
    }
    else
    {
      if(ltx<=2)
        ltx+=0.1;
    }
  }

  if (key=='G')
  {
    if(sh)
    {
      if(lshlx>=-4)
        lshlx-=0.1;
    }
    else
    {
      if(ltx>=-2)
        ltx-=0.1;
    }
  }

  if (key=='Y')
  {
    if(sh)
    {
      if(rshlx<=4)
        rshlx+=0.1;
    }
    else
    {
      if(rtx<=2)
        rtx+=0.1;
    }
  }

  if (key=='H')
  {
    if(sh)
    {
      if(rshlx>=-4)
        rshlx-=0.1;
    }
    else
    {
     if(rtx>=-2)
      rtx-=0.1;
  }
}

    //y

if (key=='U')
{
  if (sh)
  {
    if(lshly<=4)
      lshly+=0.1;
  }
  else
  {
    if(lty<=1)
      lty+=0.1;
  }
}

if (key=='J')
{
  if(sh)
  {
    if(lshly>=0)
      lshly-=0.1;
  }
  else
  {
    if(lty>=-1)
      lty-=0.1;
  }
}

if (key=='I')
{
  if (sh)
  {
    if(rshly<=4)
      rshly+=0.1;
  }
  else
  {
    if(rty<=1)
      rty+=0.1;
  }
}

if (key=='K')
{
  if(sh)
  {
    if(rshly>=0)
      rshly-=0.1;
  }
  else
  {
    if(rty>=-1)
      rty-=0.1;
  }

}
    //z

if (key=='O')
{
  if(sh)
  {
    if(lshlz<=4)
      lshlz+=0.1;
  }
  else
  {
   if(ltz<=1)
    ltz+=0.1; 
}
}

if (key=='L')
{
  if (sh)
  {
    if(lshlz>=0)
      lshlz-=0.1;
  }
  else
  {
    if(ltz>=-1)
      ltz-=0.1;
  }
}

if (key=='P')
{
  if(sh)
  {
    if(rshlz<=4)
      rshlz+=0.1;
  }
  else
  {
   if(rtz<=1)
    rtz+=0.1; 
}
}

if (key==';')
{
  if(sh)
  {
    if(rshlz>=0)
      rshlz-=0.1;
  }
  else
  {
    if(rtz>=-1)
      rtz-=0.1;
  }
}
if(key=='1')
  sh=0;
if(key=='2')
  sh=1;

if (key=='3')
{
  if(trsx<=2)
    trsx+=0.1;
}

if (key=='4')
{
  if(trsx>=-2)
    trsx-=0.1;
}

if (key=='5')
{
  if(trsy<=0.5)
    trsy+=0.1;      }

  if (key=='6')
  {
    if(trsy>=-0.5)
      trsy-=0.1;
  }

  if (key=='7')
  {
    if(trsz<=1)
      trsz+=0.1;
  }

  if (key=='8')
  {
    if(trsz>=-1)
      trsz-=0.1;
  }
    if (key == '0') // complete transform
    {
      transformMode=1;
    }

    if (key == '9') // complete transform
    {
      transformMode=0;
    }

    if (key==GLFW_KEY_F1)
    {
      if(lhandx<=1)
        lhandx+=0.1;
    }

    if (key==GLFW_KEY_F2)
    {
      if(lhandx>=-1)
        lhandx-=0.1;
    }
    if (key==GLFW_KEY_F3)
    {
      if(lhandz<=1)
        lhandz+=0.1;
    }

    if (key==GLFW_KEY_F4)
    {
      if(lhandz>=-1)
        lhandz-=0.1;
    }


    if (key==GLFW_KEY_F5)
    {
      if(rhandx<=1)
        rhandx+=0.1;
    }

    if (key==GLFW_KEY_F6)
    {
      if(rhandx>=-1)
        rhandx-=0.1;
    }
    if (key==GLFW_KEY_F7)
    {
      if(rhandz<=1)
        rhandz+=0.1;
    }

    if (key==GLFW_KEY_F8)
    {
      if(rhandz>=-1)
        rhandz-=0.1;
    }
    if (key==GLFW_KEY_LEFT)
    {
      turn-=1;
      wheel_turn-=1;         
      if(turn<=0)
      {
        turn+=360;            
        //flag=0;
      }
      if(wheel_turn<=0)
      {
        wheel_turn+=360;            
        flag=0;
      }
      flag1=0;        
      //std::cout<<wheel_turn<<std::endl;
      //std::cout<<flag<<std::endl;
    }
    if (key==GLFW_KEY_RIGHT)
    {
      turn+=1;
      wheel_turn+=1;        
      if(turn>=360)
      {
        turn-=360;          
        //flag = 1;
      }
      if(wheel_turn>=360)
      {
        wheel_turn-=360;            
        flag=1;
      }
      flag1=0;    

      //std::cout<<wheel_turn<<std::endl;
      //std::cout<<flag<<std::endl;
    }


    if (key==GLFW_KEY_UP)
    {
      x_m = x_m + 0.1*sin(turn*3.14159/180);
      z_m = z_m + 0.1*cos(turn*3.14159/180);
      rot = rot+1;
      flag1=1; 
    }

    if (key==GLFW_KEY_DOWN)
    {
      x_m = x_m - (0.1*sin(turn*3.14159/180));
      z_m = z_m - 0.1*cos(turn*3.14159/180);
      rot = rot-1;
      flag1=1;        
    }
    
    if (key==GLFW_KEY_F9)
    {
      flag2=(flag2+1)%2;        
    }

    if (key==GLFW_KEY_PAGE_UP)
      zoom+=0.1;

    if (key==GLFW_KEY_PAGE_DOWN) 
      zoom-=0.1;
    if (key==GLFW_KEY_RIGHT_CONTROL)
    {
      index = (index+1) %3;
      camera = &cameras[index];
    }
    if (key==GLFW_KEY_HOME)
    {
      dirLight1= !dirLight1;
    } 
    if (key==GLFW_KEY_DELETE)
    {
      dirLight2= !dirLight2;
    }
    if (key==GLFW_KEY_LEFT_CONTROL)
    {
      robot = !robot;
    } 
  }
};  




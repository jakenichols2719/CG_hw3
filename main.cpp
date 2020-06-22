#include "objects.h"

TObject* objects[15];
float th = 0;
float ph = 0;
float look[3] = {0,0,-1}; //look vector

//lighting variables (copied from ex13 for now)
int light     =   1;  // Lighting
int one       =   1;  // Unit value
int distance  =   15;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
float ambient   =  50;  // Ambient intensity (%)
float diffuse   =  80;  // Diffuse intensity (%)
float specular  =  20;  // Specular intensity (%)
float atn[3] = {1,.12,0};
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light angle
float ylight  =   0;  // Elevation of light

//timing variables
float lastTime;
static int targetFPS = 144;

//key variables
bool key_buffer[4]; //up, left, down, right
bool rotate_light = true;

//returns delta, locking to FPS when able.
static float delta_()
{
  float delt = (glutGet(GLUT_ELAPSED_TIME)/1000.0) - lastTime;
  if(delt >= 1.0/(float)targetFPS) {
    lastTime = (glutGet(GLUT_ELAPSED_TIME)/1000.0);
    return delt;
  } else {
    return 0;
  }
}

void process_keys(float delta)
{
  if(key_buffer[0]) {
    ph -= 100 * delta;
  }
  if(key_buffer[1]) {
    th -= 100 * delta;
  }
  if(key_buffer[2]) {
    ph += 100 * delta;
  }
  if(key_buffer[3]) {
    th += 100 * delta;
  }
  //wrap rotation variables
  if(ph > 89) ph = 89;
  if(ph < -89) ph = -89;
  if(th > 360) th = 0;
  if(th < 0) th = 360;
}

void runLighting()
{
  //  Translate intensity to color vectors
  float Ambient[]   = {(float)0.01*ambient ,(float)0.01*ambient ,(float)0.01*ambient ,1.0};
  float Diffuse[]   = {(float)0.01*diffuse ,(float)0.01*diffuse ,(float)0.01*diffuse ,1.0};
  float Specular[]  = {(float)0.01*specular,(float)0.01*specular,(float)0.01*specular,1.0};
  //  Light position
  //float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};
  //float Position[] = {2,0,2};
  float Position[] = {2*Sin(zh),1,4*Cos(zh)};
  //illustrate light
  glPointSize(10);
  glColor3f(1,1,0);
  glBegin(GL_POINTS);
  glVertex3f(Position[0],Position[1],Position[2]);
  glEnd();
  //  Set ambient, diffuse, specular components and position of light 0
  glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
  glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
  glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
  glLightfv(GL_LIGHT0,GL_POSITION,Position);
  glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION, atn[0]);
  glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION, atn[1]);
  glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION, atn[2]);
}

//glut idle func
void idle()
{
  float delta = delta_();
  if(delta) {
    process_keys(delta);
    if(rotate_light){
      zh += 90.0*delta;
      zh %= 360;
    }
  }
   glutPostRedisplay();
}

void transform_camera()
{
  look[0] = Sin(th)*Cos(ph);
  look[1] = -Sin(ph);
  look[2] = -Cos(th)*Cos(ph);
  gluLookAt(0,0,4, look[0],look[1],look[2]+4, 0,1,0);
  glPointSize(10);
  glColor3f(1,0,0);
  glBegin(GL_POINTS);
  glVertex3f(look[0],look[1],look[2]+4);
  glEnd();

}
//glut display func
void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  transform_camera();
  //gluLookAt(0,0,5, 0,0,0, 0,1,0);
  glPushMatrix();
  //glRotated(ph,1,0,0);
  //glRotated(th,0,1,0);
  runLighting();
  for(int n=0; n<12; n++) {
    objects[n]->draw();
  }
  glPopMatrix();
  glutSwapBuffers();
}

void reshape(int width,int height)
{
  //gWidth = width;
  //gHeight = height;
  //set viewport
  glViewport(0, 0, (GLsizei) width, (GLsizei) height);
  //projection mode
  glMatrixMode (GL_PROJECTION);
  //reset transform
  glLoadIdentity ();
  //set up perspective
  //glOrtho(0, 0, (GLsizei) width, (GLsizei) height, -1, 1);
  float asp = (float)width/height;
  gluPerspective(60,asp,1,128);
  //set back to modelview
  glMatrixMode (GL_MODELVIEW);
  //reset modelview too for good measure
  glLoadIdentity();
}

//OpenGL special key function
void special(int key,int x,int y)
{
  switch(key) {
    case GLUT_KEY_UP:
      key_buffer[0] = 1;
      break;
    case GLUT_KEY_LEFT:
      key_buffer[1] = 1;
      break;
    case GLUT_KEY_DOWN:
      key_buffer[2] = 1;
      break;
    case GLUT_KEY_RIGHT:
      key_buffer[3] = 1;
      break;
    default:
      break;
  }
}
void specialUp(int key, int x, int y)
{
  switch(key) {
    case GLUT_KEY_UP:
      key_buffer[0] = 0;
      break;
    case GLUT_KEY_LEFT:
      key_buffer[1] = 0;
      break;
    case GLUT_KEY_DOWN:
      key_buffer[2] = 0;
      break;
    case GLUT_KEY_RIGHT:
      key_buffer[3] = 0;
      break;
    default:
      break;
  }
}

void keyboard(unsigned char key, int x, int y)
{
  switch(key) {
    case 's':
      rotate_light = !rotate_light;
      break;
    case 27:
      exit(0);
  }
}

void program_init()
{
  objects[0] = new TargetRack(0,0,0, 1,1,1, 0,0,-10); objects[0]->init();
  objects[0]->toggle_light_at(1,1);
  objects[1] = new SurfaceRect(0,0,0, 10,1,25, 0,-3,-4, 1,1,1, (char*)"hay.bmp"); objects[1]->init();
  objects[1]->set_texture_scale(5);
  objects[2] = new SurfaceRect(0,0,-90, 10,1,25, -5,2,-4, 1,1,1, (char*)"darkwood.bmp"); objects[2]->init();
  objects[2]->set_texture_scale(5);
  objects[3] = new SurfaceRect(0,0,90, 10,1,25, 5,2,-4, 1,1,1, (char*)"darkwood.bmp"); objects[3]->init();
  objects[3]->set_texture_scale(5);
  objects[4] = new SurfaceRect(0,0,180, 10,1,25, 0,6,-4, 1,1,1, (char*)"darkwood.bmp"); objects[4]->init();
  objects[4]->set_texture_scale(5);
  objects[5] = new SurfaceRect(90,0,0, 10,1,10, 0,1,-16, 1,1,1, (char*)"darkwood.bmp"); objects[5]->init();
  objects[5]->set_texture_scale(5);
  objects[6] = new Cuboid(0,20,0, 2,2,2, -3.5,-2,-14, 1,1,1, (char*)"crate.bmp"); objects[6]->init();
  objects[7] = new Cuboid(0,30,0, 1,1,1, -3.5,-.5,-14, 1,1,1, (char*)"crate.bmp"); objects[7]->init();
  objects[8] = new Cuboid(0,30,0, 2,2,2,  3.5,-2,0, 1,1,1, (char*)"crate.bmp"); objects[8]->init();
  objects[9] = new Cuboid(0,-10,0, 1.6,1.6,1.6,  1.0,-2.2,.2, 1,1,1, (char*)"crate.bmp"); objects[9]->init();
  objects[10] = new Cuboid(0,45,0, 1.4,1.4,1.4,  -.7,-2.2,-.1, 1,1,1, (char*)"crate.bmp"); objects[10]->init();
  objects[11] = new Cuboid(0,10,0, 1.9,1.9,1.9,  -3,-2,-.1, 1,1,1, (char*)"crate.bmp"); objects[11]->init();
}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv); //initialize glut
  //init with rgb, double buffer, depth test
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(600,600); //600x600 window
  glutCreateWindow("James Nichols"); //create window
  glutIdleFunc(idle);
  glutDisplayFunc(display); //display function
  glutReshapeFunc(reshape); //reshape function
  glutSpecialFunc(special); //arrow keys, esc
  glutSpecialUpFunc(specialUp);
  glutKeyboardFunc(keyboard); //keyboard controls
  //face culling/depth test
  glEnable(GL_DEPTH_TEST);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  //lighting
  glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  program_init();
  glutMainLoop();
  return 0;
}

#include "objects.h"

TObject* objects[3];
float th = 15;
float ph = 45;

//lighting variables (copied from ex13 for now)
int light     =   1;  // Lighting
int one       =   1;  // Unit value
int distance  =   5;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
float ambient   =  40;  // Ambient intensity (%)
float diffuse   =  50;  // Diffuse intensity (%)
float specular  =  10;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light

//timing variables
float lastTime;
static int targetFPS = 120;

//key variables
bool key_buffer[8]; //up, left, down, right, w, a, s, d

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
    ph += 50 * delta;
  }
  if(key_buffer[1]) {
    th += 50 * delta;
  }
  if(key_buffer[2]) {
    ph -= 50 * delta;
  }
  if(key_buffer[3]) {
    th -= 50 * delta;
  }
  //wrap rotation variables
  if(ph > 360) ph = 0;
  if(ph < 0) ph = 360;
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
  float Position[] = {-5,3,5};
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
}

//glut idle func
void idle()
{
  float delta = delta_();
  if(delta) {
    process_keys(delta);
    zh += 90.0*delta;
    zh %= 360;
  }
   glutPostRedisplay();
}

//glut display func
void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  //transformCamera();
  gluLookAt(0,0,5, 0,0,0, 0,1,0);
  glPushMatrix();
  glRotated(ph,1,0,0);
  glRotated(th,0,1,0);
  runLighting();
  objects[0]->draw();
  objects[1]->draw();
  objects[2]->draw();
  glPopMatrix();
  glPointSize(10);
  glColor3f(1,0,0);
  glBegin(GL_POINTS);
  glVertex3f(0,0,0);
  glEnd();
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

void program_init()
{
  objects[0] = new Cuboid(0,0,0, 1,1,1, 0,0,0, 1,1,1, (char*)"crate.bmp"); objects[0]->init();
  objects[1] = new Cuboid(0,0,0, .5,.5,.5, 1,0,0, 1,1,1, (char*)"darkwood.bmp"); objects[1]->init();
  objects[2] = new Circle(90,0,0, 1,1,1, 0,0,-3, 1,1,1, (char*)"target.bmp"); objects[2]->init();
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
  //glutKeyboardFunc(keyboard); //keyboard controls
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

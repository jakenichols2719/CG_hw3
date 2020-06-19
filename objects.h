#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <iostream>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
//CSCI library
#include "CSCIx229.h"

//trig macros, stolen from ex8
//#define Cos(x) (cos((x)*(float)3.1415927/180))
//#define Sin(x) (sin((x)*(float)3.1415927/180))

/*
 * Transformable object class
 * Defines scale, rotation, and translation
*/
class TObject
{
protected:
  //transform
  float sca[3] = {1,1,1};
  float rot[3] = {0,0,0};
  float pos[3] = {0,0,0};
  float col[3] = {1,1,1};
  //texture
  float tex_sca = 1.0;
  bool hasTexture = false;
  GLuint texture;
public:
  //constructors
  TObject();
  TObject(float rx, float ry, float rz,
          float sx, float sy, float sz,
          float px, float py, float pz); // no color
  TObject(float rx, float ry, float rz,
          float sx, float sy, float sz,
          float px, float py, float pz,
          float c0, float c1, float c2); // color
  TObject(float rx, float ry, float rz,
          float sx, float sy, float sz,
          float px, float py, float pz,
          float c0, float c1, float c2,
          char* file);                   // texture and color
  //getters/setters
  float* scale_() { return sca; };
  float* rotation_() { return rot; };
  float* position_() { return pos; };
  float* color_() { return col; };
  float texture_scale_() { return tex_sca; };
  void set_scale(float _sca[3]) { sca[0] = _sca[0]; sca[1] = _sca[1]; sca[2] = _sca[2]; };
  void set_rotation(float _rot[3]) { rot[0] = _rot[0]; rot[1] = _rot[1]; rot[2] = _rot[2]; };
  void set_position(float _pos[3]) { pos[0] = _pos[0]; pos[1] = _pos[1]; pos[2] = _pos[2]; };
  void set_color(float _col[3]) { col[0] = _col[0]; col[1] = _col[1]; col[2] = _col[2]; }
  void set_texture_scale(float _tex_sca) { tex_sca = _tex_sca; };
  //apply transformations
  int apply_transform();
  //virtual functions for inheritance. will print out a message if not implemented.
  virtual void init(); //I feel like I might need this but leaving out for now.
  virtual void draw();
};


/*
 * Cuboid
 * 1x1x1 cube centered on (0,0,0)
*/
class Cuboid : public TObject
{
  using TObject::TObject;
private:
  float shine_value = 1;
  float spec_color[4] = {1,1,1,1};
  float em_color[4]   = {0,0,0,1};
public:
  void init();
  void draw();
};

/*
 * Surface rectangle (flat)
 * 1x1 plane, centered on (0,0,0), facing up
*/
class SurfaceRect : public TObject
{
  using TObject::TObject;
private:
  float shine_value = 1;
  float spec_color[4] = {1,1,1,1};
  float em_color[4]   = {0,0,0,1};
public:
  void init();
  void draw();
};

/*
 * Circle
 * Textures are placed in a circular pattern, with
 * the top being placed in the middle and the bottom
 * being the outside ring.
*/
class Circle : public TObject
{
  using TObject::TObject;
private:
  float shine_value = 1;
  float spec_color[4] = {1,1,1,1};
  float em_color[4]   = {0,0,0,1};
public:
  void init();
  void draw();
};

/*
 * Sphere
*/
class Sphere : public TObject
{
  using TObject::TObject;
private:
  GLuint sphere_list;
  float shine_value = 1;
  float spec_color[4] = {1,1,1,1};
  float em_color[4]   = {0,0,0,1};
};

//===FABRICATED OBJECTS===
/*
 * Target Face
 * 1x1 circular face, .4 deep in y direction by default
 * Texture applies to area between targets
*/
class TargetFace : public TObject
{
  using TObject::TObject;
private:
  Circle front = Circle(0,0,0, 1,1,1, 0,.2,0, 1,1,1, (char*)"target.bmp");
  Circle back = Circle(180,0,0, 1,1,1, 0,-.2,0, 1,1,1, (char*)"target.bmp");
  float shine_value = 1;
  float spec_color[4] = {1,1,1,1};
  float em_color[4]   = {0,0,0,1};
public:
  void init();
  void draw();
};

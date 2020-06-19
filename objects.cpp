#include "objects.h"

TObject::TObject()
{
  //but there was nothing there...
}
TObject::TObject(float rx, float ry, float rz,
                 float sx, float sy, float sz,
                 float px, float py, float pz)
{
  rot[0] = rx; rot[1] = ry; rot[2] = rz;
  sca[0] = sx; sca[1] = sy; sca[2] = sz;
  pos[0] = px; pos[1] = py; pos[2] = pz;
}
TObject::TObject(float rx, float ry, float rz,
                 float sx, float sy, float sz,
                 float px, float py, float pz,
                 float c0, float c1, float c2)
{
  rot[0] = rx; rot[1] = ry; rot[2] = rz;
  sca[0] = sx; sca[1] = sy; sca[2] = sz;
  pos[0] = px; pos[1] = py; pos[2] = pz;
  col[0] = c0; col[1] = c1; col[2] = c2;
}
TObject::TObject(float rx, float ry, float rz,
                 float sx, float sy, float sz,
                 float px, float py, float pz,
                 float c0, float c1, float c2,
                 char* file)
{
  rot[0] = rx; rot[1] = ry; rot[2] = rz;
  sca[0] = sx; sca[1] = sy; sca[2] = sz;
  pos[0] = px; pos[1] = py; pos[2] = pz;
  col[0] = c0; col[1] = c1; col[2] = c2;
  hasTexture = true;
  texture = LoadTexBMP(file);
}

int TObject::apply_transform()
{
  //apply texture
  if(hasTexture) {
    glBindTexture(GL_TEXTURE_2D, texture);
  }
  //translate
  glTranslatef(pos[0], pos[1], pos[2]);
  //scale
  glScalef(sca[0],sca[1],sca[2]);
  //rotate
  glRotatef(rot[2],0,0,1);
  glRotatef(rot[1],0,1,0);
  glRotatef(rot[0],1,0,0);
  return 0;
}

void TObject::init()
{
  std::cout << "Didn't implement init for this shape" << std::endl;
}

void TObject::draw()
{
  std::cout << "Didn't implement draw for this shape" << std::endl;
}


//===CUBOID===
void Cuboid::init()
{
  //cuboid doesn't need initialization right now
}
void Cuboid::draw()
{
  glPushMatrix();
  apply_transform();
  //draw with texture
  if(hasTexture) {
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_value);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,em_color);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
      glColor3f(col[0],col[1],col[2]);
      glNormal3f( 0, 0, .5);
      glTexCoord2f(0.0,     0.0); glVertex3f(-.5,-.5, .5);
      glTexCoord2f(tex_sca, 0.0); glVertex3f(+.5,-.5, .5);
      glTexCoord2f(tex_sca, tex_sca); glVertex3f(+.5,+.5, .5);
      glTexCoord2f(0.0,     tex_sca); glVertex3f(-.5,+.5, .5);
      //  Back
      glNormal3f( 0, 0,-.5);
      glTexCoord2f(0.0,     0.0); glVertex3f(+.5,-.5,-.5);
      glTexCoord2f(tex_sca, 0.0); glVertex3f(-.5,-.5,-.5);
      glTexCoord2f(tex_sca, tex_sca); glVertex3f(-.5,+.5,-.5);
      glTexCoord2f(0.0,     tex_sca); glVertex3f(+.5,+.5,-.5);
      //  Right
      glNormal3f(+.5, 0, 0);
      glTexCoord2f(0.0,     0.0); glVertex3f(+.5,-.5,+.5);
      glTexCoord2f(tex_sca,     0.0); glVertex3f(+.5,-.5,-.5);
      glTexCoord2f(tex_sca, tex_sca); glVertex3f(+.5,+.5,-.5);
      glTexCoord2f(0.0,     tex_sca); glVertex3f(+.5,+.5,+.5);
      //  Left
      glNormal3f(-.5, 0, 0);
      glTexCoord2f(0.0,     0.0); glVertex3f(-.5,-.5,-.5);
      glTexCoord2f(tex_sca,     0.0); glVertex3f(-.5,-.5,+.5);
      glTexCoord2f(tex_sca, tex_sca); glVertex3f(-.5,+.5,+.5);
      glTexCoord2f(0.0,     tex_sca); glVertex3f(-.5,+.5,-.5);
      //  Top
      glNormal3f( 0,+.5, 0);
      glTexCoord2f(0.0,     0.0); glVertex3f(-.5,+.5,+.5);
      glTexCoord2f(tex_sca,     0.0); glVertex3f(+.5,+.5,+.5);
      glTexCoord2f(tex_sca, tex_sca); glVertex3f(+.5,+.5,-.5);
      glTexCoord2f(0.0,     tex_sca); glVertex3f(-.5,+.5,-.5);
      //  Bottom
      glNormal3f( 0,-.5, 0);
      glTexCoord2f(0.0,     0.0); glVertex3f(-.5,-.5,-.5);
      glTexCoord2f(tex_sca,     0.0); glVertex3f(+.5,-.5,-.5);
      glTexCoord2f(tex_sca, tex_sca); glVertex3f(+.5,-.5,+.5);
      glTexCoord2f(0.0,     tex_sca); glVertex3f(-.5,-.5,+.5);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  }
  //draw without texture
  else {
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_value);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,em_color);
    glBegin(GL_QUADS);
      glColor3f(col[0],col[1],col[2]);
      glNormal3f( 0, 0, .5);
      glVertex3f(-.5,-.5, .5);
      glVertex3f(+.5,-.5, .5);
      glVertex3f(+.5,+.5, .5);
      glVertex3f(-.5,+.5, .5);
      //  Back
      glNormal3f( 0, 0,-.5);
      glVertex3f(+.5,-.5,-.5);
      glVertex3f(-.5,-.5,-.5);
      glVertex3f(-.5,+.5,-.5);
      glVertex3f(+.5,+.5,-.5);
      //  Right
      glNormal3f(+.5, 0, 0);
      glVertex3f(+.5,-.5,+.5);
      glVertex3f(+.5,-.5,-.5);
      glVertex3f(+.5,+.5,-.5);
      glVertex3f(+.5,+.5,+.5);
      //  Left
      glNormal3f(-.5, 0, 0);
      glVertex3f(-.5,-.5,-.5);
      glVertex3f(-.5,-.5,+.5);
      glVertex3f(-.5,+.5,+.5);
      glVertex3f(-.5,+.5,-.5);
      //  Top
      glNormal3f( 0,+.5, 0);
      glVertex3f(-.5,+.5,+.5);
      glVertex3f(+.5,+.5,+.5);
      glVertex3f(+.5,+.5,-.5);
      glVertex3f(-.5,+.5,-.5);
      //  Bottom
      glNormal3f( 0,-.5, 0);
      glVertex3f(-.5,-.5,-.5);
      glVertex3f(+.5,-.5,-.5);
      glVertex3f(+.5,-.5,+.5);
      glVertex3f(-.5,-.5,+.5);
    glEnd();
  }
  glPopMatrix();
}

//===RECTANGLE===
void SurfaceRect::init()
{

}
void SurfaceRect::draw()
{
  glPushMatrix();
  apply_transform();
  //draw with texture
  if(hasTexture) {
    //enable textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST);
    glEnable(GL_TEXTURE_2D);
    //enable lighting materials
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_value);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,em_color);
    //draw
    glBegin(GL_QUADS);
      glTexCoord2f(0.0,    0.0); glVertex3f(-.5,0,.5);
      glTexCoord2f(tex_sca,0.0); glVertex3f(.5,0,.5);
      glTexCoord2f(tex_sca,tex_sca); glVertex3f(.5,0,-.5);
      glTexCoord2f(0.0,    tex_sca); glVertex3f(-.5,0,-.5);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  }
  //draw without texture
  else {
    //enable lighting materials
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_value);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,em_color);
    //draw
    glBegin(GL_QUADS);
      glVertex3f(-.5,0,.5);
      glVertex3f(.5,0,.5);
      glVertex3f(.5,0,-.5);
      glVertex3f(-.5,0,-.5);
    glEnd();
  }
  glPopMatrix();
}

//===CIRCLE===
void Circle::init()
{

}
void Circle::draw()
{
  glPushMatrix();
  apply_transform();
  if(hasTexture) {
    //enable lighting materials
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_value);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,em_color);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST);
    glColor3f(col[0], col[1], col[2]);
    //draw
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    for(int th = 0; th < 360; th+=10) {
      glTexCoord2f(0,1); glVertex3f(0,0,0);
      glTexCoord2f(0,0); glVertex3f(-Sin(th+5),0,Cos(th+5));
      glTexCoord2f(1,0); glVertex3f(-Sin(th-5),0,Cos(th-5));
      glTexCoord2f(1,1); glVertex3f(0,0,0);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
  }
  else {
    //enable lighting materials
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_value);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,em_color);
    glColor3f(col[0], col[1], col[2]);
    //draw
    glBegin(GL_QUADS);
    for(int th = 0; th < 360; th+=10) {
      glVertex3f(0,0,0);
      glVertex3f(-Sin(th+5),0,Cos(th+5));
      glVertex3f(-Sin(th-5),0,Cos(th-5));
      glVertex3f(0,0,0);
    }
    glEnd();
  }
  glPopMatrix();
}

//===SPHERE===

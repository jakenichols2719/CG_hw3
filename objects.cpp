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
  //glScalef(sca[0],sca[1],sca[2]);
  //rotate
  glRotatef(rot[2],0,0,1);
  glRotatef(rot[1],0,1,0);
  glRotatef(rot[0],1,0,0);
    glScalef(sca[0],sca[1],sca[2]);
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

void TObject::toggle_light()
{
  std::cout << "toggle light not implemented for this object." << std::endl;
}
void TObject::toggle_light_at(int x, int y)
{
  std::cout << "toggle light at not implemented for this object." << std::endl;
}


//===CUBOID===
void Cuboid::init()
{
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_value);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,em_color);
}
void Cuboid::draw()
{
  glPushMatrix();
  apply_transform();
  //draw with texture
  if(hasTexture) {
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
      glNormal3f(0,1,0);
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
      glNormal3f(0,1,0);
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
    for(int th = 0; th < 360; th+=20) {
      glNormal3f(0,1,0);
      glTexCoord2f(0,1); glVertex3f(0,0,0);
      glTexCoord2f(0,0); glVertex3f(-Sin(th+10),0,Cos(th+10));
      glTexCoord2f(1,0); glVertex3f(-Sin(th-10),0,Cos(th-10));
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
      glNormal3f(0,1,0);
      glVertex3f(0,0,0);
      glVertex3f(-Sin(th+5),0,Cos(th+5));
      glVertex3f(-Sin(th-5),0,Cos(th-5));
      glVertex3f(0,0,0);
    }
    glEnd();
  }
  glPopMatrix();
}

//===TARGETFACE===
void TargetFace::init()
{
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_value);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,em_color);
}
void TargetFace::draw()
{
  glPushMatrix();
  apply_transform();
  //draw target faces
  front.draw();
  back.draw();
  glPopMatrix();
  //need to reset so that texture gets applied
  glPushMatrix();
  apply_transform();
  //draw wooden frame
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_NEAREST);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
    for(int th = 0; th < 360; th+=20) {
      glNormal3f(-Sin(th),0,Cos(th));
      glTexCoord2f(0,1); glVertex3f(-Sin(th+10),-.2,Cos(th+10));
      glTexCoord2f(0,0); glVertex3f(-Sin(th-10),-.2,Cos(th-10));
      glTexCoord2f(1,0); glVertex3f(-Sin(th-10),+.2,Cos(th-10));
      glTexCoord2f(1,1); glVertex3f(-Sin(th+10),+.2,Cos(th+10));
    }
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}
void TargetFace::toggle_light()
{
  lit = !lit;
  if(lit) front.set_texture((char*)"target_lit.bmp");
  if(!lit) front.set_texture((char*)"target.bmp");
}

//===FULLTARGET
void FullTarget::init()
{

}
void FullTarget::draw()
{
  glPushMatrix();
  apply_transform();
  targ.draw();
  prop1.draw();
  prop2.draw();
  prop3.draw();
  glPopMatrix();
}
void FullTarget::toggle_light()
{
  targ.toggle_light();
}

//===TARGETRACK===
void TargetRack::init()
{
  for(int y=0; y<4; y++) {
    float height = 3.3 - 2*y;
    shelves[y] = Cuboid(0,0,0, 6,.2,.5, 0,height,0, 1,1,1, (char*)"medwood.bmp");
    for(int x=0; x<4; x++) {
      float posx = -2.25 + 1.5*x;
      float posy = 4 - 2*y;
      targets[x + y*4] = FullTarget(0,0,0, .75,.75,1, posx,posy,0, 1,1,1, (char*)"darkwood.bmp");
    }
  }
  leftside.init();
  rightside.init();
  topside.init();
}

void TargetRack::draw()
{
  glPushMatrix();
  apply_transform();
  for(int n=0; n<4; n++) {
    shelves[n].draw();
  }
  for(int n=0; n<16; n++) {
    targets[n].draw();
  }
  leftside.draw();
  rightside.draw();
  topside.draw();
  glPopMatrix();
}

void TargetRack::toggle_light_at(int x, int y)
{
  targets[x+y*4].toggle_light();
}

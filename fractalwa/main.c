#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glext.h>
#include<GL/glcorearb.h>
#include<GL/glaux.h>
#include<GL/glxext.h>
#include<GL/wglext.h>

GLuint makeaTree;
float x,y,z;
//static float height,base;

void makeCylinder(float height, float base){
    GLUquadric *obj = gluNewQuadric();
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glRotatef(-90, 1.0,0.0,0.0);
    gluCylinder(obj, base,base-(0.2*base), height, 20,20);
    glPopMatrix();
}
void makeTree(float height, float base){
    float angle;
  makeCylinder(height, base);
    glTranslatef(0.0, height, 0.0);
    height =height- height*.2;
    base=base- base*0.3;
    for(int a= 0; a<3; a++){
        angle = rand()%50+20;
        if(angle >48)
            angle = -(rand()%50+20);
        if (height >2){
            glPushMatrix();
            glRotatef(angle,1,0.0,1);
            makeTree(height,base);
            glPopMatrix();
            }
    }
}
void init(void)
{
    glClearColor(1.0,1.0,1.0,1.0);
    makeaTree=glGenLists(1);
    glNewList(makeaTree, GL_COMPILE);
    makeTree(6,0.4);
    glEndList();
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glCallList(makeaTree);
    glPopMatrix();
    glutSwapBuffers();
}
void reshape(int w, int h)
{
    glViewport (0, 0,  w,  h);
    gluPerspective(30.0, (GLfloat) w/(GLfloat) h, 0.001, 1000.0);
    glTranslatef(0.0,-8.0,-50.0);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    //glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (1200, 800);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Fractals Tree");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
}

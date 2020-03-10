/* Name:
 *  Quarter, Year:
 *   Lab:
 *
 *    This file is to be modified by the student.
 *     main.cpp
 *     */
#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include <vector>
#include <cstdio>
#include <math.h>
#include "vec.h"
#include <iostream>

using namespace std;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
vector <vec2> mouseCoord; 


float factorial(int n){
	float fact = 1;
	if(n > 1){
		for(int i = 1; i <= n; i++)
			fact = fact * i;
	}
	return fact;
}

float combination(int n, int k){

	return (factorial(n)) / (factorial(n-k) * factorial(k) );
}

float binomial(int n, int k, float t){
	return ( combination(n,k) * pow(t,k) * pow((1-t), n-k)  );

}

void GL_render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();

    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f,0.0f,0.0f);
    
	for(float t = 0; t < 1; t += 0.01){
		vec2 b;
		b[0] = 0;
		b[1] = 0; 
		for(int i = 0; i < mouseCoord.size(); i++){
			b += binomial(mouseCoord.size() - 1, i, t) * mouseCoord[i];
		}

		glVertex2f(b[0], b[1]);
	}

	glEnd();
    glFlush();
}

void GL_mouse(int button,int state,int x,int y)
{
    y=WINDOW_HEIGHT-y;
    GLdouble mv_mat[16];
    GLdouble proj_mat[16];
    GLint vp_mat[4];
    glGetDoublev(GL_MODELVIEW_MATRIX,mv_mat);
    glGetDoublev(GL_PROJECTION_MATRIX,proj_mat);
    glGetIntegerv(GL_VIEWPORT,vp_mat);

    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        double px,py,dummy_z; /* we don't care about the z-value but need something to pass in */
        gluUnProject(x,y,0,mv_mat,proj_mat,vp_mat,&px,&py,&dummy_z);
        glutPostRedisplay();
   
	vec2 click;
	click[0] = px;
	click[1] = py;
	mouseCoord.push_back(click);
     }
}

/* Initializes OpenGL attributes */
void GLInit(int* argc, char** argv)
{
    glutInit(argc, argv);
    /* glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); */
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    /* glMatrixMode(GL_PROJECTION_MATRIX);
 *     glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1); */
    glutCreateWindow("CS 130 - <Insert Name Here>");
    glutDisplayFunc(GL_render);
    glutMouseFunc(GL_mouse);
}

int main(int argc, char** argv)
{
    GLInit(&argc, argv);
    glutMainLoop();
    return 0;
}

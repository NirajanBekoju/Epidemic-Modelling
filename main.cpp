#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#include "Person.h"

#define windowTitle "Circle Motion"
#define windowWidth 400
#define windowHeight 400

int refreshMillis = 30;

void display();
void reshape(int, int);
void init();
void draw_circle(Person);
void Timer(int);

Person p1;
Person p2;

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(windowTitle);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, Timer, 0);
    init();

    glutMainLoop();
    return 0;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    p1.drawPerson();
    p1.movePerson(false);
    p2.drawPerson();
    p2.movePerson(true);
    glutSwapBuffers();
}

void init()
{
    // set the background color
    glClearColor(0.0, 0.1, 0.1, 1.0);
}

void reshape(int w, int h)
{
    // set the viewport
    glViewport(0, 0, w, h);

    // projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 10, 0, 10);
    glMatrixMode(GL_MODELVIEW);
}

/* Called back when the timer expired */
void Timer(int value)
{
    glutPostRedisplay();                    // Post a paint request to activate display()
    glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
}
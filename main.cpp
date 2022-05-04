#include <iostream>
#include <fstream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>

#include "Person.h"

#define windowTitle "Epidemic Modelling"
#define windowWidth 400
#define windowHeight 400
#define INFECTION_RADIUS 0.3

int refreshMillis = 30;

void display();
void reshape(int, int);
void init();
void draw_circle(Person);
void Timer(int);

void initInfectedPerson();
void calculateSIR(std::vector<Person>);
void writeDataToFile();
void sortPeopleVec();
void showCX();
void infectSusceptible();
void checkRecovery();

int noPeople = 100;
int noOfSusceptible, noOfInfected, noOfRecovered;
std::vector<Person> p(noPeople);

int main(int argc, char **argv)
{   
    // initialize the infected person
    initInfectedPerson();

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
    for (int i = 0; i < noPeople; i++)
    {
        p[i].drawPerson();
        p[i].movePerson(false);
    }
    sortPeopleVec();
    calculateSIR(p);
    writeDataToFile();
    infectSusceptible();
    checkRecovery();
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

void initInfectedPerson()
{
    p[0].changeToInfected();
}

void calculateSIR(std::vector<Person> p)
{
    noOfSusceptible = 0;
    noOfInfected = 0;
    noOfRecovered = 0;
    for (int i = 0; i < noPeople; i++)
    {
        if (p[i].getPersonStatus() == 0)
        {
            noOfSusceptible += 1;
        }
        else if (p[i].getPersonStatus() == 1)
        {
            noOfInfected += 1;
        }
        else if (p[i].getPersonStatus() == 2)
        {
            noOfRecovered += 1;
        }
    }
}

void writeDataToFile()
{
    std::fstream file;
    file.open("data.csv", std::ios::out | std::ios::app);

    file << noOfSusceptible << ", "
         << noOfInfected << ", "
         << noOfRecovered << std::endl;
}

// Sort the people vector on the ascending order
void sortPeopleVec()
{
    Person temp;
    for (int i = 0; i < noPeople - 1; i++)
    {
        for (int j = 0; j < noPeople - i - 1; j++)
        {
            if (p[j].getCX() > p[j + 1].getCX())
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// check if sort
void showCX()
{
    for (int i = 0; i < noPeople; i++)
    {
        std::cout << p[i].getCX() << " ";
    }
    std::cout << "\n";
}

// Infect the susceptible person if they are under the infection area
void infectSusceptible()
{
    for (int i = 0; i < noPeople; i++)
    {
        // If i person is infected
        if (p[i].getPersonStatus() == 1)
        {
            std::cout << "Person " << i << "::INFECTED\n";
            // Check for the left neighbour
            int neighbourIndex = i - 1;

            if (neighbourIndex >= 0)
            {
                // check if the person is SUSCEPTIBLE
                if (p[neighbourIndex].getPersonStatus() == 0)
                {
                    std::cout << "LEFT NEIGHBOUR " << neighbourIndex << " INFECTION STATUS \n";
                    // while the neighbour are inside the infection radius
                    while ((p[i].getCX() - p[neighbourIndex].getCX()) < INFECTION_RADIUS)
                    {

                        std::cout << "NEIGHBOUR LEFT " << neighbourIndex << "::INFECTED_X_REGION"
                                  << "\n";
                        // check for y - coordinate
                        if (abs(p[i].getCY() - p[neighbourIndex].getCY()) < INFECTION_RADIUS)
                        {
                            std::cout << "NEIGHBOUR LEFT " << neighbourIndex << "::INFECTED_Y_REGION"
                                      << "\n";
                            std::cout << "NEIGHBOUR " << neighbourIndex << "::INFECTED_BY::" << i << std::endl;
                            p[neighbourIndex].changeToInfected();
                        }
                        neighbourIndex -= 1;
                        if (neighbourIndex < 0)
                        {
                            break;
                        }
                    }
                }
            }

            // Check for the RIGHT neighbour
            neighbourIndex = i + 1;
            if (neighbourIndex < noPeople)
            {
                // check if the person is SUSCEPTIBLE
                if (p[neighbourIndex].getPersonStatus() == 0)
                {
                    std::cout << "RIGHT NEIGHBOUR INFECTION STATTUS \n";
                    // while the neighbour are inside the infection radius
                    while ((p[neighbourIndex].getCX() - p[i].getCX()) < INFECTION_RADIUS)
                    {
                        std::cout << "NEIGHBOUR RIGHT " << neighbourIndex << "::INFECTED_X_REGION"
                                  << "\n";
                        if (abs(p[neighbourIndex].getCY() - p[i].getCY()) < INFECTION_RADIUS)
                        {
                            std::cout << "NEIGHBOUR RIGHT " << neighbourIndex << "::INFECTED_Y_REGION"
                                      << "\n";
                            std::cout << "NEIGHBOUR " << neighbourIndex << "::INFECTED_BY::" << i << std::endl;
                            p[neighbourIndex].changeToInfected();
                        }
                        neighbourIndex += 1;
                        if (neighbourIndex >= noPeople)
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
}

void checkRecovery()
{
    for (int i = 0; i < noPeople; i++)
    {
        if (p[i].getPersonStatus() == 1)
        {
            p[i].checkInfectedDays();
        }
    }
}

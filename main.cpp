#include <iostream>
#include <fstream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <string>

#include "Person.h"

// basic function for the GRAPHICS RENDERING
void display();
void reshape(int, int);
void init();
void Timer(int);

// FUNCTIONS for SIR model
void initInfectedPerson();
void calculateSIR(std::vector<Person>);
void writeDataToFile();
void sortPeopleVec();
void showCX();
void infectSusceptible();
void checkRecovery();

// Variable to define our window
#define windowTitle "Epidemic Modelling"
#define windowWidth 400
#define windowHeight 400
int refreshMillis = 30; // Frame rate per second

// File path to the data generated from the epidemic modellng
std::string FILE_PATH = "data/dataf03_120_100_10.csv";

// generate the vector of certain number of people
unsigned int noPeople = 100;
std::vector<Person> p(noPeople);

// keep track of no of susceptible, infected and recovered people
int noOfSusceptible, noOfInfected, noOfRecovered;

// factor affecting the epidemic
float INFECTION_RADIUS = 0.3;
unsigned int initialInfectedPercent = 10;

int main(int argc, char **argv)
{
    // initialize the infected person
    initInfectedPerson();

    // initialie the glue
    glutInit(&argc, argv);
    // initialie the display mode
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    // initialie the window size(width, height)
    glutInitWindowSize(windowWidth, windowHeight);
    // initial position of the window in out screen
    glutInitWindowPosition(100, 100);
    glutCreateWindow(windowTitle);

    // callback function for display
    glutDisplayFunc(display);
    // cullback function for reshaping the window
    glutReshapeFunc(reshape);
    // call back function for frame per sec
    glutTimerFunc(0, Timer, 0);
    // set the background color for our window
    init();

    // initialize the main loop for rendering
    glutMainLoop();
    return 0;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // draw all the person and make them move
    for (int i = 0; i < noPeople; i++)
    {
        p[i].drawPerson();
        p[i].movePerson(false);
    }
    // sort the vector pepole on the basis of their x-position
    sortPeopleVec();
    // track the no. of susceptible, infected and removed people
    calculateSIR(p);
    // write the current data into the csv file
    writeDataToFile();
    // infect the susceptible person within the infected region
    infectSusceptible();
    // recover the infected people who have completed the infection period
    checkRecovery();
    // swap the buffer for next screen
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

// initialize the no. of infected person
void initInfectedPerson()
{
    // initially, all are susceptible to disease
    // calc. initial infected number of people and infect them
    unsigned int initialInfectedNumber = (initialInfectedPercent * noPeople) / 100; 
    for(int i = 0; i < initialInfectedNumber; i++){
        p[i].changeToInfected();
    }
}

// keep track of the number of susceptible, infected and removed people
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

// write the no. of susceptible, infected and recovered people to a csv file
void writeDataToFile()
{
    std::fstream file;
    file.open(FILE_PATH, std::ios::out | std::ios::app);

    file << noOfSusceptible << ", "
         << noOfInfected << ", "
         << noOfRecovered << std::endl;
}

// Sort the people vector on the basis of x - coordinate 
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

// created in order to check if the vector is correctly sorted: just for debugging purpose
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


// check if the infected person has completed the infection period
// if he/she completed the infection period, removed them
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
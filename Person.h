#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h> // for random number rand()

// infection period is the unit of time up to which the infected person remains infected.
// after the infection period, the infected person is changed to removed status
#define INFECTION_PERIOD 120

// Status of a person at any time period
enum STATUS
{
    SUSCEPTIBLE,
    INFECTED,
    RECOVERED
};

class Person
{
private:
    // center(x, y) and radius of the circle to represent the peron
    float cx, cy, rad;
    // velocity of the person
    float vx, vy;
    // status of person: SUSCEPTIBLE, INFECTED OR RECOVERED
    STATUS status;
    // calculate the infected days for the INFECTED STATUS CATEGORY ONLY.
    int infectedDays;

public:
    Person();
    // initialize all variables cx, cy, vx, vy randomly
    void initVariables();
    // draw the circle to represent person
    void drawPerson();
    // move the person with given velocity
    void movePerson(bool moveStatus);

    // get the required person data
    int getPersonStatus();
    float getCX();
    float getCY();

    // change the status of the person from SUSCEPTIBLE => INFECTED => RECOVERED
    void changeToInfected();
    void changeToRecovered();

    // Check the no. of infected days and incrment it and change INFECTED=>RECOVERED
    void checkInfectedDays();
};

#endif // !PERSON_H
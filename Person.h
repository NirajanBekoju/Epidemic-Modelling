#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h> // for random number rand()
#include <ctime>

#define INFECTION_PERIOD 120

enum STATUS {SUSCEPTIBLE, INFECTED, RECOVERED};

class Person
{
private:
    float cx, cy, rad;
    float vx, vy;
    STATUS status;
    int infectedDays;
public:
    Person();
    void drawPerson();
    void movePerson(bool moveStatus);
    void initVariables();
    int getPersonStatus();
    float getCX();
    float getCY();
    void changeToInfected();
    void changeToRecovered();
    void checkInfectedDays();
};

#endif // !PERSON_H
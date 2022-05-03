#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h> // for random number rand()
#include <ctime>

#define PERMISSIBLE_ERROR 0.2

enum STATUS {SUSCEPTIBLE, INFECTED, RECOVERED};

class Person
{
private:
    float cx, cy, rad;
    float vx, vy;
    STATUS status;
public:
    Person();
    void drawPerson();
    void movePerson(bool moveStatus);
    void initVariables();
};

#endif // !PERSON_H
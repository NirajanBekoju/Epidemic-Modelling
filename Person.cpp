#include "Person.h"

Person::Person()
{
    rad = 0.1;
    Person::initVariables();
}

void Person::drawPerson()
{
    // check status for the color
    // GREEN=> SUSCEPTIBLE
    // RED => Infected
    // BLUE => Recovered
    if (status == 0)
    {
        glColor3f(0.0, 1.0, 0.0);
    }
    else if (status == 1)
    {
        glColor3f(1.0, 0.0, 0.0);
    }
    else if (status == 2)
    {
        glColor3f(0.0, 0.0, 1.0);
    }

    // Begin drawing the circles representing person
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    int numSegments = 100;
    GLfloat angle;
    for (int i = 0; i <= numSegments; i++)
    {
        angle = i * 2.0f * M_PI / numSegments;
        glVertex2f(cosf(angle) * rad + cx, sinf(angle) * rad + cy);
    }
    glEnd();
}

void Person::movePerson(bool moveStatus = false)
{
    cx += vx;
    cy += vy;
    if ((cx + rad > 10) || (cx - rad < 0))
    {
        vx = -vx;
    }
    else if ((cy + rad > 10) || (cy - rad < 0))
    {
        vy = -vy;
    }

    if (moveStatus)
    {
        std::cout << "Current Status of Person" << std::endl;
        std::cout << cx << " " << cy << " " << status << " " << vx << " " << vy << std::endl;
    }
}

// Initialize position, velocity and status of the person
void Person::initVariables()
{
    float i_end = 0.2;
    float i_start = 0.1;

    vx = ((float)rand() / RAND_MAX) * (i_end - i_start) + i_start;
    vy = ((float)rand() / RAND_MAX) * (i_end - i_start) + i_start;

    float upper_limit = 9;
    float lower_limit = 1;
    cx = ((upper_limit - lower_limit) * rand()) / RAND_MAX + lower_limit;
    cy = ((upper_limit - lower_limit) * rand()) / RAND_MAX + lower_limit;

    upper_limit = 1;
    lower_limit = 0;
    float var = ((upper_limit - lower_limit) * rand()) / RAND_MAX + lower_limit;
    std::cout << var << std::endl;
    var -= 0.3;
    if (var < 0.5)
    {
        status = SUSCEPTIBLE;
    }
    else
    {
        status = INFECTED;
    }

    std::cout << "Initial Status of Person" << std::endl;
    std::cout << cx << " " << cy << " " << status << " " << vx << " " << vy << std::endl;
}
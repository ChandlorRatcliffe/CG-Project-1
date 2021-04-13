#include <GL/glut.h>
#include "interactions.h"

using namespace Interactions;

std::vector<Coordinate> coord_collect;
Coordinate current;
Interactions::Polygon shape;

bool polygon_created = false;
int coord_count = 0;

/*
 * Drawing coordinates grabbed from mouse clicks to the window
 * Current hints set allow the point to be drawn as a dot instead
 * of a square.
 */
void Coordinate::drawPoint() {
    glPointSize(this->size);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NEAREST);
    glBegin(GL_POINTS);
    glVertex2fv(this->coords);
    glEnd();
}

void Polygon::drawPolygon() {
    glBegin(GL_POLYGON);
    for (auto i = 0; i < coord_count; i++) {
        glVertex2fv(this->vertices[i].coords);
    }
    glEnd();
}

/*
 * Subtracts the current (x, y) coordinate from the first
 * and checks if that value is in the range of -10 <= x,y <= 10
 */
bool isInRange() {
    float temp_x  = current.coords[0] - coord_collect[0].coords[0];
    float temp_y  = current.coords[1] - coord_collect[0].coords[1];
    bool in_range = -10 <= temp_x && temp_x <= 10 &&
                    -10 <= temp_y && temp_y <= 10;

    return in_range;
}


// Function to create a polygon and setting the polygon_created variable to true
void definePolygon() {
    shape = Interactions::Polygon(coord_count, coord_collect);
    polygon_created = true;
    
    // in place rotation upon creation of polygon
}

/*
 * Callback function for mouse events, also handling modifier key presses.
 * Currently handling left click up, left click down, shift+left click, right click down.
 */
void Interactions::handleMouseEvent(int button, int state, int x, int y) {

    bool left_click_down = (button == GLUT_LEFT_BUTTON  && state == GLUT_DOWN);
    bool left_click_up   = (button == GLUT_LEFT_BUTTON  && state == GLUT_UP);
    bool right_click_up  = (button == GLUT_RIGHT_BUTTON && state == GLUT_UP);

    /* glutGetModifiers() will return a specific value depending on which modifier key is pressed
     * 1 - Shift
     * 2 - Ctrl
     * 3 - Ctrl + Alt
     * 4 - Alt
     */
    int modifier = glutGetModifiers();

    if (left_click_down && !polygon_created) {
        current = Coordinate((GLfloat)x, WINDOW_HEIGHT - (GLfloat)y);
    }
    else if (left_click_down && polygon_created) { 
        // function to handle translation with mouse
    }
    else if (left_click_down && polygon_created && (modifier == 1)) {
        // function to handle scaling with mouse
    }

    if (left_click_up && !polygon_created) {
        if (coord_count == 0)
            current.first_point = true;

        coord_collect.push_back(current);

        if (isInRange() && coord_count > 0)
            definePolygon();

        coord_count++;
    }

    if (right_click_up) exit(0);

    glutPostRedisplay();
}

/*
 * Tracks position of mouse allowing for points to be positioned precisely
 */
void Interactions::handleMotionEvent(int x, int y) {
    current.setCoord((GLfloat)x, WINDOW_HEIGHT - (GLfloat)y);
    glutPostRedisplay();
}

/*
 * Draws either a point or if polygon_created is true, a Polygon.
 */
void Interactions::drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (!polygon_created) {
        std::vector<Coordinate>::iterator it;
        it = coord_collect.begin();
        while (it != coord_collect.end())
        {
            it->drawPoint();
            it++;
        }
        current.drawPoint();
    }
    else {
        shape.drawPolygon();
    }
    
    glFlush();
}



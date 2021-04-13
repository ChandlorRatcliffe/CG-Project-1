#include <GL/glut.h>
#include <vector>
#include "interactions.h"
#include "commonLibs.h"

using namespace Interactions;

std::vector<Coordinate> coord_collect;
Coordinate current;
Interactions::Polygon shape;

bool polygon_created = false;
int coord_count = 0;
GLfloat rotation_angle = 90.0;
GLfloat centroid[2];

void calcCentroid() {
    GLfloat xSum = 0, ySum = 0;
    for (int i = 0; i < shape.vert_count; i++) {
        xSum += shape.vertices[i].coords[0];
        ySum += shape.vertices[i].coords[1];
    }
    centroid[0] = xSum / shape.vert_count;
    centroid[1] = ySum / shape.vert_count;
}

void startRotation(int x) {
    TransformationMatrix R = RotationMatrix(rotation_angle);
    TransformationMatrix T = TranslationMatrix(centroid[0], centroid[1]);
    TransformationMatrix TI = TranslationMatrix(-centroid[0], -centroid[1]);
    T.composeWith(&R);
    T.composeWith(&TI);
    T.applyTo(shape.vertices[x].coords);
}

void doTranslation(int x, int y) {
    calcCentroid();
    GLfloat new_center[2] = { (GLfloat)x, WINDOW_HEIGHT - (GLfloat)y };
    printf("Centered at mouse and moving pos [%f, %f]\n", new_center[0], new_center[1]);

    GLfloat tx = new_center[0] - centroid[0];
    GLfloat ty = new_center[1] - centroid[1];
    printf("[tx,ty] = [%f, %f]\n", tx, ty);

    TranslationMatrix T = TranslationMatrix(tx, ty);
    for (int i = 0; i < shape.vert_count; i++) {
        T.applyTo(shape.vertices[i].coords);
    }
}

/*
 * Subtracts the current (x, y) coordinate from the first
 * and checks if that value is in the range of -10 <= x,y <= 10
 */
bool isInRange() {
    float temp_x = current.coords[0] - coord_collect[0].coords[0];
    float temp_y = current.coords[1] - coord_collect[0].coords[1];
    bool in_range = -10 <= temp_x && temp_x <= 10 &&
        -10 <= temp_y && temp_y <= 10;

    return in_range;
}

// Function to create a polygon and setting the polygon_created variable to true
void definePolygon() {
    shape = Interactions::Polygon(coord_count, coord_collect);
    polygon_created = true;
    calcCentroid();
}

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
    for (auto i = 0; i < shape.vert_count; i++) {
        if (is_polygon_rot) {
            startRotation(i);
        }
        glVertex2fv(this->vertices[i].coords);
    }
    glEnd();
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
        switch (modifier) {
        case 1:printf("scaling\n"); break;
        case 4:printf("Reverse rotation\n"); break;
        default: shape.is_polygon_rot = false; break;
        }
        // stop rotation so transformation can be performed
        shape.is_polygon_rot = false;
    }
    else if (left_click_up && !shape.is_polygon_rot) { 
        // restart rotation after any transformations are finished
        shape.is_polygon_rot = true;
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

    if (polygon_created) {
        doTranslation(x, y);
    }
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

/*
 *
 */
void Interactions::timer(int v) {
    if (shape.is_polygon_rot) {
        rotation_angle += 1.0;
        if (rotation_angle > 360.0) {
            rotation_angle = 0;
        }
        glutPostRedisplay();
    }
    glutTimerFunc(1000 / 60, timer, v);
}



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
GLfloat old_mouse_coord[2];

/*
 * Finds the center of the polygon(very crude) and populates the array
 * centroid with the x and y coordinates
 */
void calcCentroid() {
    GLfloat xSum = 0, ySum = 0;
    for (int i = 0; i < shape.vert_count; i++) {
        xSum += shape.vertices[i].coords[0];
        ySum += shape.vertices[i].coords[1];
    }
    centroid[0] = xSum / shape.vert_count;
    centroid[1] = ySum / shape.vert_count;
}

/*
 * Starts rotating the polygon in a clockwise manner about its origin
 */
void startRotatingShape(int x) {
    TransformationMatrix R = RotationMatrix(rotation_angle);
    TransformationMatrix T = TranslationMatrix(centroid[0], centroid[1]);
    TransformationMatrix TI = TranslationMatrix(-centroid[0], -centroid[1]);
    T.composeWith(&R);
    T.composeWith(&TI);
    T.applyTo(shape.vertices[x].coords);
}

/*
 * Scales polygon object by a fixed increment +- 0.01
 * Determines whether or not to scale up or down by comparing the
 * previous mouse coordinate to the current. Receives (x,y) coordiante
 * from the handleMotionEvent function.
 */
void startScalingShape(int x, int y) {
    GLfloat mouse_coord[2] = { (GLfloat)x, WINDOW_HEIGHT - (GLfloat)y };
    GLfloat sx, sy;

    if (mouse_coord[0] > old_mouse_coord[0]) {
        sx = 1.01f; sy = 1.01f;
    }
    else if (mouse_coord[0] < old_mouse_coord[0]) {
        sx = 0.99f; sy = 0.99f;
    }
    else {
        sx = 1.0f; sy = 1.0f; // no scaling performed
    }

    TransformationMatrix T = TranslationMatrix(centroid[0], centroid[1]);
    TransformationMatrix TI = TranslationMatrix(-centroid[0], -centroid[1]);
    TransformationMatrix S = ScaleMatrix(sx, sy);
    T.composeWith(&S);
    T.composeWith(&TI);
    for (int i = 0; i < shape.vert_count; i++) {
        T.applyTo(shape.vertices[i].coords);
    }
}

/*
 * Translation of the polygon, receives (x,y) coordinate
 * from the handleMotionEvent function.
 */
void startTranslatingshape(int x, int y) {
    calcCentroid();
    GLfloat mouse_coord[2] = { (GLfloat)x, WINDOW_HEIGHT - (GLfloat)y };

    GLfloat tx = mouse_coord[0] - centroid[0];
    GLfloat ty = mouse_coord[1] - centroid[1];

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
        if (this->is_rotating)
            startRotatingShape(i);

        glVertex2fv(this->vertices[i].coords);
    }
    glEnd();
}

/*
 * Callback function for mouse events, also handling modifier key presses.
 * Currently handling left click up, left click down, shift+left click, alt+left click
 * and right click down.
 */
void Interactions::handleMouseEvent(int button, int state, int x, int y) {

    bool left_click_down = (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);
    bool left_click_up = (button == GLUT_LEFT_BUTTON && state == GLUT_UP);
    bool right_click_up = (button == GLUT_RIGHT_BUTTON && state == GLUT_UP);   
    
    // Handling points when the mouse clicks in the window
    if (left_click_up && !polygon_created) {
        if (coord_count == 0)
            current.first_point = true;

        coord_collect.push_back(current);

        if (isInRange() && coord_count > 0)
            definePolygon();

        coord_count++;
    }
    else {

        int modifier = glutGetModifiers();

        if (left_click_down && !polygon_created) {
            current = Coordinate((GLfloat)x, WINDOW_HEIGHT - (GLfloat)y);
        }
        else if (left_click_down && polygon_created) {
            switch (modifier) {
            case GLUT_ACTIVE_SHIFT:
                shape.is_being_scaled = true;
                break;

            case GLUT_ACTIVE_ALT:
                // requires inverse rotation function??
                break;

            default:
                shape.is_rotating = false; // Stops rotation so shape can be translated
                break;
            }
        }
        else if (left_click_up && (!shape.is_rotating || shape.is_being_scaled)) {
            // restart rotation after any transformations are finished
            shape.is_rotating = true;
            shape.is_being_scaled = false;
        }
    }

    // Closes current window
    if (right_click_up) exit(0);

    glutPostRedisplay();
}

/*
 * Tracks position of mouse allowing for points to be positioned precisely
 * and handle transformations to be applied on the polygon
 */
void Interactions::handleMotionEvent(int x, int y) {
    current.setCoord((GLfloat)x, WINDOW_HEIGHT - (GLfloat)y);

    if (polygon_created && !shape.is_being_scaled) {
        startTranslatingshape(x, y);
    }
    else if (polygon_created && shape.is_being_scaled) {
        startScalingShape(x, y);
        old_mouse_coord[0] = (GLfloat)x;
        old_mouse_coord[1] = (GLfloat)y;
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
 * Timer callback function, Increments rotation_angle by 1 every frame.
 * resetting back to 0 once it hits 360 degrees,
 * Currently running at 60fps
 */
void Interactions::timer(int v) {
    if (shape.is_rotating) {
        rotation_angle += 1.0f;
        if (rotation_angle > 360.0f) {
            rotation_angle = 0;
        }
        glutPostRedisplay();
    }
    glutTimerFunc(1000 / 60, timer, v);
}



#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <cmath>

int windowWidth = 800;
int windowHeight = 600;
float R = 250, r = 50;
float t = 0;
int state = 1;
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 40; i++) {
        float angle = 2 * M_PI * i / 40;
        float xb = R * cos(angle);
        float yb = R * sin(angle);
        float xs = r * cos(angle);
        float ys = r * sin(angle);
        glVertex2f( (yb + 400)*(1 - t) + (ys + 400) * t, (xb + 300)*(1 - t) + (xs + 300) * t);
        //
        //r^2(sinA)^2 + r^2(cosA)^2 = r^2.
    }
    glEnd();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);

    switch(state) {
        case 1:
            if(t < 1) t += 0.01;
            else state = -1;
            break;
        case -1:
            if(t > 0) t -= 0.01;
            else state = 1;
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("oyu_tween");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glClearColor(0.5,0.5,0.5,0);
    glutMainLoop();
    return 0;
}

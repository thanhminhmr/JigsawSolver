#include "std.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class Painter {
public:
	size_t piece_count;
    struct PieceDt {
        size_t point_count;
        Point* points;
    };

	PieceDt* pieces;

    const int origin_pos = 0;
    const int width = 100;
    const int height = 64;

    Painter() {}
    ~Painter() {}
    void init();
    void displayOnePiece(PieceDt p);
    void display();
    void paint(int argc, char** argv);

};

void Painter::init()  {
      glClearColor(0.0, 0.0, 0.0, 0.0);
      glColor3f(1.0, 1.0, 1.0);
      glPointSize(3.0);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity( );
      gluOrtho2D(-origin_pos, width, -height, origin_pos); //Lay goc phan tu thu 2 - left, right, bottom, top
}

void Painter::displayOnePiece(PieceDt p) {
    glShadeModel(GL_SMOOTH);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glColor3f(0.0, 0.0, 0.0);
    //glBegin(GL_POLYGON);
    //for (int i = 0; i < p.point_count; i++) {
    //  glVertex2f(p.points[i].x, - p.points[i].y);
    //}
    //glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < p.point_count; i++) {
        glVertex2f(p.points[i].x, - p.points[i].y);
    }
    glEnd();
}

void Painter::display()  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    for (int i = 0; i < piece_count; i++) {
        displayOnePiece(pieces[i]);
    }
    glFlush();
    glutSwapBuffers();
}

void Painter::paint(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("painter");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}

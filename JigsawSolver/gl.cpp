    #include "std.h"
    /* -- INCLUDE FILES ------------------------------------------------------ */
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>

    using namespace std;
    int origin_pos = 0;
    int width = 100;
    int height = 64;
    State state = state.readFile("input.txt");

    void myInit(void)  {
      glClearColor(0.0, 0.0, 0.0, 0.0);
      glColor3f(1.0, 1.0, 1.0);
      glPointSize(3.0);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity( );
      gluOrtho2D(-origin_pos, width, -height, origin_pos); //Lay goc phan tu thu 2 - left, right, bottom, top
    }

    void displayOnePiece(Piece p) {
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

    void myDisplay(void)  {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
            for (int i = 0; i < state.piece_count; i++) {
                displayOnePiece(state.pieces[i]);
            }
            glFlush();
            glutSwapBuffers();
    }

    int main(int argc, char *argv[])  {


      // Initialize GLUT
      glutInit(&argc, argv);
      // Set the mode to draw in.
      glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
      // Set the window size in screen pixels.
      glutInitWindowSize(640, 480);
      // Set the window position in screen pixels.
      glutInitWindowPosition(100, 100);
      // Create the window.
      glutCreateWindow("line");
      // Set the callback funcion to call when we need to draw something.

      myInit();
      glutDisplayFunc(myDisplay);
      // Initialize some things.
      // Now that we have set everything up, loop responding to events.
      glutMainLoop();
      return 0;
    }



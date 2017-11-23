#include <string>
#include <iostream>
#include <fstream>
/* -- INCLUDE FILES ------------------------------------------------------ */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

//const char* FILENAME = "../Doc/de1_solution_reformat.txt";
const char* FILENAME = "output.txt";
const int origin_pos = 0; //change this to scale the board
const int width = 100*1.5;
const int height = 64*1.5;

using namespace std;
class Point
{
public:
    int x, y;
    // default constructor
    inline Point() : x(0), y(0) {}
    // constructor
    inline Point(int x, int y) : x(x), y(y) {}
};

class Piece
{
public:
    Point* points;
    int point_count;
    Piece()
    {
        point_count = 0;
        points = NULL;
    };
    inline Piece(Point* _point, size_t _size) : points(NULL), point_count(_size)
    {
        points = _point;
        point_count = _size;
    }
    ~Piece() {};
};

class State
{
public:
    int piece_count;
    Piece* pieces;
    inline ~State() {}
    inline State() : piece_count(0), pieces(NULL) {}
    //Board khong co Board(NULL)
    State readFile(string filename);
    void print();
    friend istream& operator>> (istream& is, State& state);
    friend ostream& operator<< (ostream& os, const State& state);
};

void State::print()
{
    cout << piece_count << endl;
    for (int i = 0; i < piece_count; i++)
    {
        cout << pieces[i].point_count << " ";
        for (int j = 0; j < pieces[i].point_count; j++)
        {
            cout << pieces[i].points[j].x << " " << pieces[i].points[j].y << " ";
        }
        cout << endl;
    }
}

State State::readFile(string filename)
{
    State state;
    ifstream in(filename);
    if (in.is_open())
    {
        in >> state;
        return state;
    }
    else
        cout << "Unable to open file";
}

istream& operator>>(istream& is, State &state)
{
    Piece *pieces;
    Point *points;
    int id_tmp, point_count;
    int x_tmp, y_tmp;

    is >> state.piece_count;
    pieces = new Piece[state.piece_count];
    for (int i = 0; i < state.piece_count; i++)
    {
        is >> id_tmp >> point_count;
        points = new Point[point_count];
        for (int j = 0; j < point_count; j++)
        {
            is >> x_tmp >> y_tmp;
            Point point_tmp(x_tmp, y_tmp);
            points[j] = point_tmp;
        }
        Piece piece_tmp(points, point_count);
        pieces[i] = piece_tmp;
    }
    state.pieces = pieces;
}

ostream& operator<< (ostream& os, const State& state)
{
    Piece* pieces = state.pieces;
    for (int i = 0; i < state.piece_count; i++)
    {
        for (int j = 0; j < pieces[i].point_count; j++)
        {
            os << pieces[i].points[j].x << " " << pieces[i].points[j].y << " ";
        }
        os << endl;
    }
}

State state = state.readFile(FILENAME);

void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(3.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluOrtho2D(-origin_pos, width, -height, origin_pos); //Lay goc phan tu thu 2 - left, right, bottom, top
}

void displayOnePiece(Piece p)
{
    glShadeModel(GL_SMOOTH);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glColor3f(0.0, 0.0, 0.0);
    //glBegin(GL_POLYGON);
    //for (int i = 0; i < p.point_count; i++) {
    //  glVertex2f(p.points[i].x, - p.points[i].y);
    //}
    //glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < p.point_count; i++)
    {
        glVertex2f(p.points[i].x, - p.points[i].y);
    }
    glEnd();
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    for (int i = 0; i < state.piece_count; i++)
    {
        displayOnePiece(state.pieces[i]);
    }
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    // Initialize rGLUT
    glutInit(&argc, argv);
    // Set the mode to draw in.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    // Set the window size in screen pixels.
    glutInitWindowSize(600, 390);
    // Set the window position in screen pixels.
    glutInitWindowPosition(100, 100);
    // Create the window.
    glutCreateWindow("painter");
    // Set the callback funcion to call when we need to draw something.
    myInit();
    glutDisplayFunc(myDisplay);
    // Initialize some things.
    // Now that we have set everything up, loop responding to events.
    glutMainLoop();
    return 0;
}


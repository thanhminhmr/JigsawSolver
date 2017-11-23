// main.cpp

#include "std.h"

// tip, edit the next line to //* to see the magic
//*

Piece piece;
Piece changedPiece;

void init() {
    Point points[8];

    //g.game.piece[1].id = 1;
    points[0] = Point(75, 30);
    points[1] = Point(75, 37);
    points[2] = Point(89, 37);
    points[3] = Point(89, 42);
    points[4] = Point(66, 42);
    points[5] = Point(50, 37);
    points[6] = Point(50, 30);

    piece = Piece(points, 7);
}

void printFile(const Piece& printPiece) {
    FILE* fout = fopen("output.txt", "w");
    fprintf(fout, "1\n");
    fprintf(fout, "1 ");
    fprintf(fout, "%u ", printPiece.size);
    for (int i = 0; i < printPiece.size; i++) {
        fprintf(fout, "%u %u ", printPiece.points[i].x, printPiece.points[i].y);
    }
}

void print(const Piece& printPiece) {
    printf("1\n");
    printf("1 ");
    printf("%u ", printPiece.size);
    for (int i = 0; i < printPiece.size; i++) {
        printf("%u %u ", printPiece.points[i].x, printPiece.points[i].y);
    }
    printf("\n");
}

int main() {
	init();
	//printf("%08X %08X %08X\n", &C.data, &C.x, &C.y);
    Game g;
    g.startup();


    printFile(changedPiece);
    //printFile(piece);
    return 0;
	//Angle angle(B, A, C);
	//return printf("%f", angle.toRad());
	// see the "/doc/test.png"
}
/*/
int main() {
	Point points[10];

	for (size_t i = 0; i < 10; i++) {
		long a, b;
		scanf("%ld;%ld", &a, &b);
		points[i] = Point(a, b);
	}

	Piece piece(points, 10);

	return printf("%d %d", points[0].x, points[0].y);
	// see the "/doc/test.png"
}
//*/

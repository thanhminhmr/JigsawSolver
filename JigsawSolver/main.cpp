// main.cpp

#include "std.h"

int main() {
	Point C(6, 2);
	Point A(1, 1);
	Point B(2, 4);

	Angle angle(B, A, C);
	return printf("%f", angle.toRad());
	// see the "/doc/test.png"
}

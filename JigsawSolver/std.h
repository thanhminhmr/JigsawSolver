#ifndef _STD_H_
#define _STD_H_

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

// add standard library here
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <new>


// add config here
#define MAX_POINT_COUNT 32
#define MAX_PIECE_COUNT 32
#define MAX_PIECEREF_COUNT 32

// add library here
#include "misc.h"

// add class here
#include "Point.h"
#include "Vector.h"
#include "Angle.h"
#include "Piece.h"
#include "Board.h"

// main class here
#include "Game.h"

#endif // !_STD_H_

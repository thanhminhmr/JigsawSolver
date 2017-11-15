#ifndef _PIECE_H_
#define _PIECE_H_

/**
* Piece.h
*
* Define a Piece
*
* ! initialize on create
* ! read - only
*/
class Piece {
protected:
	Point* point;
	Angle* angle;

	// normalize this Piece
	static inline void normalizeClockwise(Point* point_out, const Point* point_in, size_t size);
	static inline Vector normalizePosition(Point* point_out, const Point* point_in, size_t size);

public:
	const size_t size;

	// default destructor
	inline ~Piece() {
		memdealloc(point);
	}
	// default constructor
	inline Piece() : point(NULL), angle(NULL), size(0) {}
	// constructor
	inline Piece(const Point* _point, size_t _size) : point(NULL), angle(NULL), size(_size) {
		point = memalloc<Point>(size);
		normalize(point, _point, size);
	}
	// copy constructor
	inline Piece(const Piece& piece) : point(NULL), angle(NULL), size(piece.size) {
		point = memalloc<Point>(size);
		memcopy(point, piece.point, size);
	}
	// copy operator
	inline void operator=(const Piece& piece) {
		this->~Piece();
		new(this) Piece(piece);
	}
};

// normalize this Piece
inline void Piece::normalizeClockwise(Point* point_out, const Point* point_in, size_t size) {
	// TODO: do we need this?
	int sum = 0;
	for(int i=0; i<size; i++){
        sum += (point_in[i+1].x-point_in[i].x)*(point_in[i+1].y+point_in[i].y);
	}
	if(sum > 0) memcopy(point_out, point_in, size);
	else if(sum < 0){
        for(int i=0,j=size-1; i<size ;i++,j--){
            point_out[i] = point_in[j];
        }
	}
}

inline Vector Piece::normalizePosition(Point* point_out, const Point* point_in, size_t size){
	int8_t highest = point_out[0].y;
	int8_t left = point_out[0].x;
	for(int i=0; i<size; i++){
        if(highest<point_out[i].y) highest = point_out[i].y;
        if(left>point_out[i].x) left = point_out[i].x;
	}

	Vector a(-left,-highest);
    Vector b(left,highest);
	for(int i=0;i<size;i++){
        point_out[i]=a.move(point_out[i]);
	}
	return b;
}
#endif // !_PIECE_H_

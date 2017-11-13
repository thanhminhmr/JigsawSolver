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
	static inline void normalize(Point* point_out, const Point* point_in, size_t size);

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
inline void Piece::normalize(Point* point_out, const Point* point_in, size_t size) {
	// TODO: do we need this?
	double sum = 0.0;
	//Vector a(0,0), b(0,0);
	for(int i=0; i<size; i++){
        sum += (point_in[i+1].x-point_in[i].x)*(point_in[i+1].y+point_in[i].y);
	}
	if(sum > 0) memcopy(point_out, point_in, size);
	else if(sum < 0){
        for(int i=0,j=size-1; i<size ;i++,j--){
            point_out[i] = point_in[j];
        }
	}
	Point highest = point_out[0];
	Point left = point_out[0];
	for(int i=0; i<size; i++){
        if(highest.y<point_out[i].y) highest = point_out[i];
        if(left.x>point_out[i].x) left = point_out[i];
	}
	//a.x = 0;
	//a.y = -highest.y
	Vector a(0,-highest.y);
	Vector b(-left.x,0);
	//b.x = -left.x;
	//b.y = 0;
	for(int i=0;i<size;i++){
        point_out[i]=a.move(point_out[i]);
        point_out[i]=b.move(point_out[i]);
	}
}
#endif // !_PIECE_H_

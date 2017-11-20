#ifndef _PIECE_H_
#define _PIECE_H_

/**
* Piece.h
*
* Define a Piece
*
* ! sized on create
* ! read - write
*/
class Piece {
protected:
	// normalize this Piece to clockwise list of Point

	static inline void normalizeClockwise(Point* point_out, const Point* point_in, size_t size);

	static inline Vector normalizePosition(Point* point_out, const Point* point_in, size_t size);

	// create Angle array from normalized Point array
	static inline void createAngle(Angle* angle, const Point* point, size_t size);

	// check if two Piece (Point array) is identical
	static inline bool isIdentical(const Point* points_a, const Point* points_b, size_t size);

	// check if Piece a (Point array) can contain Piece b (Point array)
	static inline bool isContainable(const Point* points_a, const Point* points_b, size_t size, const Vector& position);


public:
	Point const* const points;
	Angle const* const angles;
	const size_t size;

	// default destructor
	inline ~Piece() {
		memdealloc(points);
		memdealloc(angles);
	}
	// default constructor
	inline Piece() : points(NULL), angles(NULL), size(0) {}
	// constructor
	inline Piece(const Point* points, size_t size)
		: points(memalloc<Point>(size)), angles(memalloc<Angle>(size)), size(size) {

		normalizeClockwise((Point*) this->points, points, size);
		createAngle((Angle*) angles, points, size);
	}
	// copy constructor
	inline Piece(const Piece& piece)
		: points(memalloc<Point>(piece.size)), angles(memalloc<Angle>(piece.size)), size(piece.size) {

		memcopy((Point*) points, piece.points, size);
		memcopy((Angle*) angles, piece.angles, size);
	}
	// copy operator
	inline void operator=(const Piece& piece) {
		this->~Piece();
		new(this) Piece(piece);
	}

	// misc, compare two Piece
	inline bool operator==(const Piece& piece) const {
		return isIdentical(points, piece.points, size);
	}
	// misc, compare two Piece
	inline bool operator!=(const Piece& piece) const {
		return isIdentical(points, piece.points, size) == false;
	}

	// check if Piece a (Point array) can contain Piece b (Point array)
	inline bool isContainable(const Piece& piece, const Vector& position) {
		return isContainable(points, piece.points, size, position);
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
// normalize this Piece position
inline Vector Piece::normalizePosition(Point* point_out, const Point* point_in, size_t size){
	int16_t highest = point_out[0].y;
	int16_t left = point_out[0].x;
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



// create Angle array from normalized Point array
inline void Piece::createAngle(Angle* angles, const Point* points, size_t size) {
	angles[0] = Angle(points[size - 1], points[0], points[1]);
	for (size_t i = 2; i < size; i++) {
		angles[i] = Angle(points[i - 2], points[i - 1], points[i]);
	}
	angles[size - 1] = Angle(points[size - 2], points[size - 1], points[0]);
}

// check if two Piece is identical
inline bool Piece::isIdentical(const Point* points_a, const Point* points_b, size_t size) {
	// TODO: implement this.
	return false;
}

// check if Piece a (Point array) can contain Piece b (Point array)
inline bool Piece::isContainable(const Point* points_a, const Point* points_b, size_t size, const Vector& position) {
	// TODO: implement this
	return false;
}

#endif // !_PIECE_H_

#ifndef _PIECE_H_
#define _PIECE_H_

#define INF 10000
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
	// normalize this Piece to clockwise list of Point
	static inline void normalizeClockwise(Point* point_out, const Point* point_in, size_t size);

	// normalize this Piece position
	static inline Vector normalizePosition(Point* point_out, const Point* point_in, size_t size);

	// create Angle array from normalized Point array
	static inline void createAngle(Angle* angle, const Point* point, size_t size);

	// check if two Piece (Point array) is identical
	static inline bool isIdentical(const Point* points_a, const Point* points_b, size_t size);

	// check if Piece a (Point array) can contain Piece b (Point array)
	static inline int orientation(Point p, Point q, Point r);
	static inline bool doIntersect(Point p1, Point q1, Point p2, Point q2);
	static inline bool isLine(Point p, Point q, Point r);
	static inline bool isInside(const Point* polygon, int n, Point p);
    static inline bool isContainable(const Point* points_a, const Point* points_b, size_t size, const Vector& position);


protected:
	// constructor, normalize Piece position
	inline Piece(const Piece& piece, Vector& position)
		: points(memalloc<Point>(piece.size)), angles(memalloc<Angle>(piece.size)), size(piece.size) {

		position = normalizePosition((Point*) points, piece.points, size);
		memcopy((Angle*) angles, piece.angles, size);
	}


public:
	Point const * const points;
	Angle const * const angles;
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
		assert(size >= 3);

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

	// normalize this Piece position, return new Piece and position
	inline Piece normalize(Vector& position) const {
		return Piece(*this, position);
	}

	// normalize this Piece position, return new Piece
	inline Piece normalize() const {
		Vector position;
		return Piece(*this, position);
	}

	// check if Piece a (Point array) can contain Piece b (Point array)
	inline bool isContainable(const Piece& piece, const Vector& position) const {
		return isContainable(points, piece.points, size, position);
	}
};

// To find orientation of ordered triplet (p, q, r).
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
inline int Piece::orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

// normalize this Piece to clockwise list of Point
inline void Piece::normalizeClockwise(Point* point_out, const Point* point_in, size_t size) {
	int32_t sum = ((int32_t) point_in[0].x - (int32_t) point_in[size - 1].x)
		* ((int32_t) point_in[0].y + (int32_t) point_in[size - 1].y);

	for (size_t i = 1; i < size; i++) {
		sum += ((int32_t) point_in[i].x - (int32_t) point_in[i - 1].x)
			* ((int32_t) point_in[i].y + (int32_t) point_in[i - 1].y);
	}
	if (sum > 0) {
		memcopy(point_out, point_in, size);
	} else if (sum < 0) {
		for (size_t i = 0, j = size - 1; (i < size && j >= 0); i++, j--) {
			point_out[i] = point_in[j];
		}
	}
}

// normalize this Piece position
inline Vector Piece::normalizePosition(Point* point_out, const Point* point_in, size_t size) {
	int16_t left = point_in[0].x;
	int16_t top = point_in[0].y;
	for (size_t i = 0; i < size; i++) {
		// if (highest < point_out[i].y) highest = point_out[i].y;
		top = (top < point_in[i].y) ? point_in[i].y : top;
		// if (left < point_out[i].x) left = point_out[i].x;
		left = (left < point_in[i].x) ? point_in[i].x : left;
	}
	Vector delta(-left, -top);
	for (size_t i = 0; i < size; i++) {
		point_out[i] = delta.move(point_in[i]); //!need to create new Point cuz Point is read only
	}
	return Vector(left, top);
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
bool Piece::isIdentical(const Point* points_a, const Point* points_b, size_t size) {
	for (size_t delta = 0; delta < size; delta++) {
		if (points_a[0] == points_b[delta]) {
			for (size_t i = 0; i < size; i++) {
				if (points_a[i] != points_b[(i + delta) % size]) {
					return false;
				}
			}
			return true;
		}
	}
	return false;
}

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool Piece::isLine(Point p, Point q, Point r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

// The function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool Piece::doIntersect(Point p1, Point q1, Point p2, Point q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    // General case
    if (o1 != o2 && o3 != o4)
        return true;
    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && isLine(p1, p2, q1)) return true;
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && isLine(p1, q2, q1)) return true;
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && isLine(p2, p1, q2)) return true;
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && isLine(p2, q1, q2)) return true;
    return false; // Doesn't fall in any of the above cases
}
// Returns true if the point p lies inside the polygon[] with n vertices
bool Piece::isInside(const Point* polygon, int n, Point p) {
    if (n < 3)  return false;
    // Create a point for line segment from p to infinite
    Point extreme = {INF, p.y};
    // Count intersections of the above line with sides of polygon
    int count = 0, i = 0;
    do {
    int next = (i+1)%n;
    // Check if the line segment from 'p' to 'extreme' intersects
    // with the line segment from 'polygon[i]' to 'polygon[next]'
        if (doIntersect(polygon[i], polygon[next], p, extreme)) {
            // If the point 'p' is colinear with line segment 'i-next',
            // then check if it lies on segment. If it lies, return true,
            // otherwise false
            if (orientation(polygon[i], p, polygon[next]) == 0)
               return isLine(polygon[i], p, polygon[next]);
            count++;
        }
        i = next;
    } while (i != 0);
    // Return true if count is odd, false otherwise
    return count&1;  // Same as (count%2 == 1)
}


// check if Piece a (Point array) can contain Piece b (Point array)
inline bool Piece::isContainable(const Point* points_a, const Point* points_b, size_t size, const Vector& position) {
    Point pos_b[size]; // Points_b after moving to position
    //Move Piece b to position
    for (int i = 0; i < size; i++) {
        pos_b[i] = Point(position.move(points_b[i]));
        if (!isInside(points_a, size, pos_b[i])) return false;
    }
	return true;
}

#endif // !_PIECE_H_

#ifndef _MISC_H_
#define _MISC_H_

// copy
template <typename type>
static inline void memcopy(type* dest, const type* source, size_t size) {
	for (size_t i = 0; i < size; i++) {
		dest[i] = source[i];
	}
}

// allocate
template<typename type>
static inline type* memalloc(size_t size) {
	// TODO: aligned alloc @thanhminhmr
	return new type[size];
}

// deallocate
template<typename type>
static inline void memdealloc(type* mem) {
	// TODO: aligned dealloc @thanhminhmr
	delete[] mem;
}
//find max - min
template <class T> const T& max (const T& a, const T& b) {
  return (a<b)?b:a;     // or: return comp(a,b)?b:a; for version (2)
}

template <class T> const T& min (const T& a, const T& b) {
  return !(b<a)?a:b;     // or: return !comp(b,a)?a:b; for version (2)
}


#endif // !_MISC_H_

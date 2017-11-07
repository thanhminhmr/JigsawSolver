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

#endif // !_MISC_H_

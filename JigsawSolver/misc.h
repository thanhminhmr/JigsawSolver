#ifndef _MISC_H_
#define _MISC_H_

template <typename type>
static inline void memcopy(type* dest, const type* source, size_t size) {
	for (size_t i = 0; i < size; i++) {
		dest[i] = source[i];
	}
}

#endif // !_MISC_H_

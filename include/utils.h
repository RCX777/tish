// Some macros and random stuff I'll use


#define INLINE static inline __attribute__((always_inline))

#define UNUSED __attribute__((unused))


char *strmbtok (char *input, char *delim, char *openblock, char *closeblock);

int strcount_s(char* str, char ch, size_t max_occ);

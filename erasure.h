#ifndef ERASURE
#define ERASURE

#define BUFFER_PART (1u<<24u)
#define OUTPUT_DIR "output"
#define OUTPUT_MASK "out"
#define OUTPUT_EXT ".enc"
#define META_FILE "metafile"

#define FLAG_ERROR (1u)
#define FLAG_CLEANUP (2u)
#define FLAG_ENCODE (4u)
#define FLAG_DECODE (8u)

#endif
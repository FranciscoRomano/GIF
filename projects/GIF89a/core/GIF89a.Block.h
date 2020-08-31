#ifndef GIF89a_Block_h
#define GIF89a_Block_h 1
/** Dependencies **********************************************************************************/
#include <stdio.h>
/** Declarations **********************************************************************************/

// Block [4+ Bytes]
typedef struct BlockGIF89a {
    unsigned long BlockSize;
    unsigned char* DataValues;
} BlockGIF89a;

// Function - Free Block Structure
void FreeBlockGIF89a(BlockGIF89a* data);

// Function - Read Block Structure
void ReadBlockGIF89a(FILE* file, BlockGIF89a* data);

// [ memory ] free and move array data
void* array_twin(void** dst, void* src);

// [ memory ] left free/copy array data
void* array_ldel(void* src, const size_t src_s, const size_t size, void* dst);

// [ memory ] right free/copy array data
void* array_rdel(void* src, const size_t src_s, const size_t size, void* dst);

// [ memory ] left fmov and join array data
void* array_ladd(void* lhs, const size_t lhs_s, const void* rhs, const size_t rhs_s);

// [ memory ] right fmov and join array data
void* array_radd(void* lhs, const size_t lhs_s, const void* rhs, const size_t rhs_s);

// [ memory ] allocate and copy new array data
void* array_join(const void* lhs, const size_t lhs_s, const void* rhs, const size_t rhs_s);

/**************************************************************************************************/
#endif//GIF89a_Block_h
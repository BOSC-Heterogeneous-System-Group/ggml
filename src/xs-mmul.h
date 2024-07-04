#include <stdint.h>

inline int64_t xs_mmul(int64_t a, int64_t b) {
    int64_t result;
    asm volatile(
        ".insn r 0x2b, 0, 0, %0, %1, %2"
        : "=r" (result)
        : "r" (a), "r" (b)
        : "memory"
    );
    return result;
}

static inline int64_t swap_bits(uint64_t x, int start1, int start2, int length) {
    // 提取需要交换的两个位段
    int64_t mask1 = (((int64_t)1 << length) - 1) << start1;
    int64_t mask2 = (((int64_t)1 << length) - 1) << start2;
    int64_t bits1 = (x & mask1) >> start1;
    int64_t bits2 = (x & mask2) >> start2;

    // 交换两个位段的位置
    int64_t swapped_bits = (bits2 << start1) | (bits1 << start2);

    // 将交换后的位段合并回原始数据中
    int64_t result = (x & ~mask1 & ~mask2) | swapped_bits;

    return result;
}
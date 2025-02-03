#include "slip.h"

#define END 0xC0
#define ESC 0xDB
#define ESC_END 0xDC
#define ESC_ESC 0xDD

size_t GetCapacity(size_t msg_size) {
    return 2 * msg_size + 2;
}

void Encapsulate(uint8_t *buf, size_t *size) {
    uint8_t temp_buf[*size];  // Fun fact: ISO C++ would not allow variable length array
    for (size_t i = 0; i < *size; ++i) {
        temp_buf[i] = buf[i];
    }
    size_t j = 0;
    buf[j++] = END;
    for (size_t i = 0; i < *size; ++i) {
        const uint8_t b = temp_buf[i];
        if (b == END) {
            buf[j++] = ESC;
            buf[j++] = ESC_END;
        } else if (b == ESC) {
            buf[j++] = ESC;
            buf[j++] = ESC_ESC;
        } else {
            buf[j++] = b;
        }
    }
    buf[j++] = END;
    *size = j;
}

int Deencapsulate(uint8_t *buf, size_t *size) {
    uint8_t temp_buf[*size];
    for (size_t i = 0; i < *size; ++i) {
        temp_buf[i] = buf[i];
    }
    size_t os = 0;  // output size
    int escape = 0;
    for (size_t cc = 0; cc < *size; ++cc) {  // cc: current char
        const uint8_t b = temp_buf[cc];
        if (escape) {
            if (b == ESC_END) {
                buf[os++] = END;
            } else if (b == ESC_ESC) {
                buf[os++] = ESC;
            } else {
                return 0;
            }
            escape = 0;
        } else {
            if (b == ESC) {
                escape = 1;
            } else if (b != END) {
                buf[os++] = b;
            }
        }
    }
    *size = os;
    return !escape;
}

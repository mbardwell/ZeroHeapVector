// C SLIP RFC 1055 encapsulation and deencapsulation
// Other examples:
// - Arduino https://github.com/bakercp/PacketSerial/blob/master/src/Encoding/SLIP.h (more C than C++)
// - Android https://android.googlesource.com/kernel/common/+/bcmdhd-3.10/drivers/net/slip/slip.c
// - custom w/ ring buffer https://github.com/lobaro/util-slip/blob/master/slip.c
// - custom w/ callbacks https://github.com/marcosatti/slips/blob/main/slips.c

#pragma once

#include <stdint.h>
#include <stddef.h>

#define C_SLIP_TEMP_BUFFER_SIZE 512

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get the capacity of a buffer for SLIP.
 * @param msg_size Size of the message.
 */
size_t GetCapacity(size_t msg_size);

/**
 * @brief Encapsulate a buffer with SLIP.
 * @param buf Buffer to encapsulate.
 * @param size Size of the buffer. Updated to the new size.
 */
void Encapsulate(uint8_t *buf, size_t *size);

/**
 * @brief Deencapsulate a buffer with SLIP.
 * @param buf Buffer to deencapsulate.
 * @param size Size of the buffer. Updated to the new size.
 * @return 1 if successful, 0 if failed.
 */
int Deencapsulate(uint8_t *buf, size_t *size);

#ifdef __cplusplus
} // extern "C"
#endif

/**
 * @file slip.h
 *
 * @brief RFC 1055 encapsulation and deencapsulation.
 */

#pragma once

#include <cstdint>

#include "static_vector.hpp"

namespace slip {

constexpr std::uint8_t END = 0xC0;
constexpr std::uint8_t ESC = 0xDB;
constexpr std::uint8_t ESC_END = 0xDC;
constexpr std::uint8_t ESC_ESC = 0xDD;
constexpr std::size_t GetCapacity(std::size_t msg_size) { return 2 * msg_size + 2; }

template <std::size_t Capacity>
using vector = static_vector<std::uint8_t, Capacity>;

template <std::size_t Capacity>
void Encapsulate(static_vector<std::uint8_t, Capacity> &buf) {
    const auto temp_buf = buf;
    std::size_t j = 0;
    buf[j++] = END;
    for (std::size_t i = 0; i < temp_buf.size(); ++i) {
        const std::uint8_t &b = temp_buf[i];
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
    buf[j] = END;
}

template <std::size_t Capacity>
bool Deencapsulate(static_vector<std::uint8_t, Capacity> &buf) {
    auto temp_buf = buf;
    buf.clear();
    std::int32_t os = 0;  // output size
    bool escape = false;
    for (std::size_t cc = 0; cc < temp_buf.size(); ++cc) {  // cc: current char
        const std::uint8_t &b = temp_buf[cc];
        if (escape) {
            if (b == ESC_END) {
                buf[os++] = END;
            } else if (b == ESC_ESC) {
                buf[os++] = ESC;
            } else {
                return false;
            }
            escape = false;
        } else {
            if (b == ESC) {
                escape = true;
            } else if (b != END) {
                buf[os++] = b;
            }
        }
    }
    return !escape;
}

}  // namespace slip

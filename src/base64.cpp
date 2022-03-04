#include "base64.h"

const std::string Base64::b64_chars = __BASE64_DICTIONARY__;

inline bool Base64::is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string Base64::encode(const std::string &s) {
    uint8_t i = 0U;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    std::string ret;

    for (const char &c : s) {
        char_array_3[i++] = c;
        if (i == 3U) {
            char_array_4[0] = (char_array_3[0] & 0xfcU) >> 2U;
            char_array_4[1] = ((char_array_3[0] & 0x03U) << 4U) + ((char_array_3[1] & 0xf0U) >> 4U);
            char_array_4[2] = ((char_array_3[1] & 0x0fU) << 2U) + ((char_array_3[2] & 0xc0U) >> 6U);
            char_array_4[3] = char_array_3[2] & 0x3fU;
            for (uint8_t j=0U; j<4U; j++) {
                ret += b64_chars[char_array_4[j]];
            }
            i = 0U;
        }
    }
    if (i) {
        for (uint8_t j=i; j<3U; j++) {
            char_array_3[j] = '\0';
        }
        char_array_4[0] = (char_array_3[0] & 0xfcU) >> 2U;
        char_array_4[1] = ((char_array_3[0] & 0x03U) << 4U) + ((char_array_3[1] & 0xf0U) >> 4U);
        char_array_4[2] = ((char_array_3[1] & 0x0fU) << 2U) + ((char_array_3[2] & 0xc0U) >> 6U);
        for (uint8_t j=0U; j<i+1U; j++) {
            ret += b64_chars[char_array_4[j]];
        }
        while(i++ < 3U) {
            ret += '=';
        }
    }
    return ret;
}

std::string Base64::decode(const std::string &s) {
    uint8_t i = 0U;
    std::size_t k = 0U;
    std::string ret;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    std::size_t in_len = s.size();

    while (in_len-- && (s[k] != '=') && is_base64(s[k])) {
        char_array_4[i++] = s[k];
        k++;
        if (i == 4U) {
            for (uint8_t j=0U; j<4U; j++) {
                char_array_4[j] = b64_chars.find(char_array_4[j]) & 0xffU;
            }
            char_array_3[0] = (char_array_4[0] << 2U) + ((char_array_4[1] & 0x30U) >> 4U);
            char_array_3[1] = ((char_array_4[1] & 0x0fU) << 4U) + ((char_array_4[2] & 0x3cU) >> 2U);
            char_array_3[2] = ((char_array_4[2] & 0x03U) << 6U) + char_array_4[3];
            for (uint8_t j=0U; j<3U; j++) {
                ret += char_array_3[j];
            }
            i = 0U;
        }
    }
    if (i) {
        for (uint8_t j=0U; j<i; j++) {
            char_array_4[j] = b64_chars.find(char_array_4[j]) & 0xffU;
        }
        char_array_3[0] = (char_array_4[0] << 2U) + ((char_array_4[1] & 0x30U) >> 4U);
        char_array_3[1] = ((char_array_4[1] & 0x0fU) << 4U) + ((char_array_4[2] & 0x3cU) >> 2U);
        for (uint8_t j=0U; j<i-1U; j++) {
            ret += char_array_3[j];
        }
    }
    return ret;
}
